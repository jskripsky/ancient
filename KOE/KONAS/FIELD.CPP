#include "Field.H"
#include "Storage.H"
#include "FieldWin.H"
#include "FieldPrn.H"
#include "Form.H"

#include <String.H>

//==========================================================
//===  constructors and destructor  ========================
//==========================================================

Field::Field() :
	obligatory( False ),
	form( 0 )
{
}


Field::~Field()
{
}


//==========================================================
//===  general data handling methods (Field)  ==============
//==========================================================

boolean Field::validate()
{
        if( !isFilledIn() )
                {
                getWindow()->showErrorMessage( "Muss-Feld ist leer!" );
                return False;
                }
        else
        	return True;
}


FieldWindow *Field::getWindow()
{
        return (FieldWindow *)window;
}


//==========================================================
//===  field presentation methods (Field)  =================
//==========================================================

//Printer *Field::createPrinter( const char *printerID )
//{
//}


//==========================================================
//===  form methods (Field)  ===============================
//==========================================================

void Field::attachToForm( Form *aForm )
{
	form = aForm;
        form->attachField( this );
}


const char *Field::getID()
{
	return id;
}


void Field::setID( const char *aID )
{
	// check with idManager, if ID is unique?

	if( id )
		delete[] id;

	id = new char[strlen( aID ) + 1];
	strcpy( id, aID );
}

//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================

void Field::write( StorageUnit& su )
{
        // Zuerst ID speichern!!!! (oder ID-Speicherung/Laden nur von aussen
        // zulassen)
	su << obligatory;
}


void Field::read( StorageUnit&  su )
{
        // Zuerst ID laden!!!! (oder ID-Speicherung/Laden nur von aussen
        // zulassen)
	su >> obligatory;
}
