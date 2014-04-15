#include "Contain.H"
#include "Storage.H"

#include <String.H>
#include <StdLib.H>


const initialBufferSize = 10;
const bufferSizeDelta = 10;


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

Container::Container() :
	count( 0 ),
	bufferSize( 0 ),
	items( 0 )
{
	resizeBuffer( initialBufferSize );
}


Container::~Container()
{
	delete items;
}


const char *Container::getClassName()
{
	return "Container";
}


long Container::insert( void *i )
{
//	if( hasItem( i ) )
//		{
//		return( getIndexOf( i ) );
//		}

	if( count == bufferSize )
		resizeBuffer( bufferSize + bufferSizeDelta );

	items[count] = i;
	count++;

	return (count - 1);
}


void Container::remove( void *i )
{
//	if( !hasItem( i ) )
//		return;

	removeAt( getIndexOf( i ) );
}


void Container::removeAt( long index )
{
	memmove( &items[index], &items[index + 1],
			 (count - index - 1) * sizeof( void * ) );

	if( bufferSize - count > bufferSizeDelta )
		resizeBuffer( bufferSize - bufferSizeDelta );
}


void *Container::at( long index )
{
	return items[index];
}


void *&Container::operator[]( long index )
{
	return items[index];
}


long Container::getIndexOf( void *i )
{
	long c = 0;
	while( (c < count) && (items[c] != i) )
		c++;

	if( c == count )
		{
#ifdef DEBUG
		abort();
#endif
		return NO_INDEX;
		}
	else
		return c;
}


long Container::getCount()
{
	return count;
}


void Container::resizeBuffer( long newBufferSize )
{
	void **newItems = new void *[newBufferSize];

	if( items )
		{
		memcpy( newItems, items, bufferSize * sizeof( void * ) );
		delete items;
		}

	items = newItems;
	bufferSize = newBufferSize;
}


//==========================================================
//===  item storage methods (Container)  ===================
//==========================================================

void Container::writeItem( void *item, StorageUnit& su )
{
	PersistentObject *o = (PersistentObject *)item;

	su.writeString( o->getClassName() );
	o->writeToStorage( su );
}


void *Container::readItem( StorageUnit& su )
{
	PersistentObject *o;

	char *className = su.readString();
	// create new object of class [classname].
	// o = new ....
	className;

	o->readFromStorage( su );
	return o;
}


//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================

void Container::write( StorageUnit& su )
{
	su << count;
	for( long i = 0; i < count; i++ )
		writeItem( items[i], su );
}


void Container::read( StorageUnit& su )
{
	su >> count;
	for( long i = 0; i < count; i++ )
		items[i] = readItem( su );
}
