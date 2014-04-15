#include "Persist.H"
#include "Storage.H"

#include <String.H>


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

PersistentObject::PersistentObject()
{
}


PersistentObject::~PersistentObject()
{
}


void PersistentObject::writeToStorage( StorageUnit& su )
{
        su.writeString( getClassName() );
	write( su );
}


void PersistentObject::readFromStorage( StorageUnit& su )
{
        char *className = su.readString();

        // Check, ob className == getClassName!!!!
        delete[] className;

	read( su );
}
