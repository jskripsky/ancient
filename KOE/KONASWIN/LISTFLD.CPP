#include "ListFld.H"
#include "Storage.H"

#include "zApp.HPP"

declSlist( Entry );

//==========================================================
//===  constructors and destructor  ========================
//==========================================================

ListField::ListField() :
	list( new EntrySlist() )
{
}


ListField::~ListField()
{
	delete list;
}


//==========================================================
//===  data manipulation methods (ListField)  ==============
//==========================================================

EntrySlistIter *ListField::getListIterator()
{
	return new EntrySlistIter( list );
}


//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================

void ListField::write( StorageUnit& su )
{
	Field::write( su );
//	su << *list;
}


void ListField::read( StorageUnit& su )
{
	Field::read( su );
//	su >> *list;
}