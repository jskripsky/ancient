/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database Cache Source File 		    	*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#define Uses_TNSCollection
#define Uses_TStreamable
#include "Database\Cache.H"
#include "Database\Record.H"
#include "Database\File.H"

#include <TV.H>

#include "Database\Entry.H"
#include "Database\Record.H"

/*---- Constructors, Destructors ---------------*/

TDBCache::TDBCache( TDBFile *aFile, ushort aLimit ) :
	file( aFile ),
	limit( aLimit ),
	descriptors( new TNSCollection( aLimit, 0 ) ),
	items( new TNSCollection( aLimit, 0 ) )
{
}


TDBCache::~TDBCache()
{
	flush();
	delete descriptors;
	delete items;
}


/*---- Public Methods --------------------------*/

void TDBCache::insertIntoFile( RecordDescriptor *descriptor, void *item )
{
	file->createRecord( descriptor );
	file->writeRecord( descriptor, item );

	if( items->getCount() == limit )
		flushItem( items->at( 0 ) );

	items->insert( item );

	RecordDescriptor *d = new RecordDescriptor;
	*d = *descriptor;
	descriptors->insert( d );
}


void TDBCache::removeFromFile( RecordDescriptor *descriptor )
{
	RecordDescriptor *d = get( descriptor );

	if( d )
		flushItem( d );

	file->deleteRecord( descriptor );
}


void *TDBCache::getItem( RecordDescriptor *descriptor )
{
	RecordDescriptor *d = get( descriptor );
	if( d )
		return items->at( descriptors->indexOf( d ) );
	else
		{
		if( items->getCount() == limit )
			flushItem( items->at( 0 ) );

		void *item = file->readRecord( descriptor, this );

		items->insert( item );

		d = new RecordDescriptor;
		*d = *descriptor;
		descriptors->insert( d );

		return item;
		}
}


void TDBCache::setUpdateFlag( void *item )
{
	RecordDescriptor *d =
		(RecordDescriptor *)descriptors->at( items->indexOf( item ) );
	d->update = True;

	//// Immediate Update:

	file->writeRecord( d, item );

	d->update = False;
}


RecordDescriptor *TDBCache::get( RecordDescriptor *descriptor )
{
	RecordDescriptor *d = 0;

	for( int i = 0; i < descriptors->getCount(); i++ )
		{
		RecordDescriptor *temp = (RecordDescriptor *)descriptors->at( i );
		if( temp->position == descriptor->position )
			{
			d = temp;
			break;
			}
		}
	return d;
}


void TDBCache::flush()
{
	while( items->getCount() > 0 )
		flushItem( items->at( 0 ) );
}


void TDBCache::flushItem( void *item )
{
	flushItem(
		(RecordDescriptor *)descriptors->at( items->indexOf( item ) ) );
}


void TDBCache::flushItem( RecordDescriptor *descriptor )
{
	void *item = items->at( descriptors->indexOf( descriptor ) );

	if( descriptor->update )
		file->writeRecord( descriptor, item );

	delete ((TObject *)item);

	items->remove( item );
	descriptors->remove( descriptor );
	delete descriptor;
}
