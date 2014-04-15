#include "ListFld.H"
#include "Storage.H"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

ListField::ListField()
{
}


ListField::~ListField()
{
	//delete all list entries
}


//==========================================================
//===  data manipulation methods (ListField)  ==============
//==========================================================

StringContainer& ListField::getList()
{
	return list;
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
}
