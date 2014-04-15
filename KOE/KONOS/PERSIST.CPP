#include "Persist.H"
#include "Storage.H"

#include <String.H>


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

PersistentObject::PersistentObject() :
	id( 0 )
{
}


PersistentObject::~PersistentObject()
{
	if( id )
		delete[] id;
}


const char *PersistentObject::getID()
{
	return id;
}


void PersistentObject::setID( const char *aID )
{
	// check with idManager, if ID is unique?

	if( id )
		delete[] id;

	id = new char[strlen( aID ) + 1];
	strcpy( id, aID );
}


void PersistentObject::writeToStorage( StorageUnit& su )
{
	su.startIDBlock( getID() );
	write( su );
	su.endIDBlock();
}


void PersistentObject::readFromStorage( StorageUnit& su )
{
	su.openIDBlock( getID() );
	read( su );
}
