#include "FieldPrn.H"
#include "Field.H"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

FieldPrint::FieldPrint( Field *field ) :
//	FieldPresentation( field ),
	Presentation( field ),
	enabled( True )
{
}


FieldPrint::~FieldPrint()
{
}


//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================

void FieldPrint::write( StorageUnit& )
{
}


void FieldPrint::read( StorageUnit& )
{
}
