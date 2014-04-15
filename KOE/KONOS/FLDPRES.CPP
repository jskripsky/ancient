#include "FldPres.H"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

FieldPresentation::FieldPresentation( DataObject *dataObject ) :
	Presentation( dataObject )
{
}


FieldPresentation::~FieldPresentation()
{
}


//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================

void FieldPresentation::write( StorageUnit& )
{
}


void FieldPresentation::read( StorageUnit& )
{
}
