#include "Field.H"
#include "Storage.H"
#include "FieldWin.H"
#include "FieldPrn.H"
#include "FormWin.H"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

Field::Field() :
	obligatory( False ),
	form( 0 ),	
	printer( 0 )
{
}


Field::~Field()
{
	if( printer )
		destroyPrinter();
}


//==========================================================
//===  general data handling methods (Field)  ==============
//==========================================================

boolean Field::validate()
{
	// check, if field is filled in?
	return True;
}


void Field::hasChanged()
{
}


//==========================================================
//===  field presentation methods (Field)  =================
//==========================================================

//Window *Field::createWindow( zWindow *parent )
//{
//
//}


//Printer *Field::createPrinter( const char *printerID )
//{
//}


void Field::destroyPrinter()
{
//	delete printer;
	printer = 0;
}


//==========================================================
//===  form methods (Field)  ===============================
//==========================================================

void Field::attachToForm( Form *aForm )
{
	form = aForm;
}


//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================

void Field::write( StorageUnit& su )
{
	su << obligatory;
}


void Field::read( StorageUnit&  su )
{
	su >> obligatory;
}
