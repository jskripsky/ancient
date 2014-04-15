#include "Storage.H"
#include "Contain.H"

/*
void StorageUnit::writeContainer( Container<PersistentObject *>& c )
{
	c.writeToStorage( *this );

	for( long i = 0; i < c.getCount(); i++ )
		{
//      writeString( c[i]->getClassName() );
		writeString( c[i]->getID() );
		}

	for( i = 0; i < c.getCount(); i++ )
		c[i]->writeToStorage( *this );
}


void StorageUnit::readContainer( Container<PersistentObject *>& c )
{
	c.readFromStorage( *this );

	for( long i = 0; i < c.count; i++ )
		{
		char *className = readString();
		PersistentObject *o;
		// create Object
		delete[] className;

		char *id = readString();
		o->setID( id );
		delete[] id;

		c.items[i] = o;
		}

	for( i = 0; i < c.getCount(); i++ )
		c[i]->readFromStorage( *this );
}


void StorageUnit::writeStringContainer(
	Container<char *>& sc )
{
	sc;
}


void StorageUnit::readStringContainer(
	Container<char *>& sc )
{
	sc;
}
*/