#include "SelFld.H"
#include "Storage.H"



//==========================================================
//===  data storage methods (Field)  =======================
//==========================================================

void SelectionField::writeData( StorageUnit& su )
{
	su << selection;
}


void SelectionField::readData( StorageUnit& su )
{
	su >> selection;
}


//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================

void SelectionField::write( StorageUnit& su )
{
	ListField::write( su );
	su << defaultSelection;
	su << noSelection;
}


void SelectionField::read( StorageUnit& su )
{
	ListField::read( su );
	su >> defaultSelection;
	su >> noSelection;
}

