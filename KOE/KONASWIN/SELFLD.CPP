#include "SelFld.H"
#include "Storage.H"
#include "SFldPrn.H"
#include "FieldWin.H"

#include <String.H>
#include "zApp.HPP"

declSlist( Entry );


SelectionField::SelectionField() :
	displayType( RadioButtons ),
	selection( 0 )
{
}


SelectionField::~SelectionField()
{
}


const char *SelectionField::getClassName()
{
	return "SelectionField";
}


void SelectionField::initializeData()
{
}


boolean SelectionField::isFilledIn()
{
	if( selection == noSelection )
		return False;
	else
		return True;
}


const char *SelectionField::getString()
{
	EntrySlistIter iter( list );

	Entry *e;
	for( int c = 0; c <= selection; c++ )
		e = iter();

	return e->string;
}


void SelectionField::setToDefault()
{
	selection = defaultSelection;
	if( getWindow() )
		getWindow()->update();
}


void SelectionField::setSelection( long number )
{
	selection = number;
}


long SelectionField::getSelection()
{
	return selection;
}


FieldPrint *SelectionField::createPrint( const char *printerID )
{
	printerID;
   return new SelectionFieldPrint( this );
}


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

