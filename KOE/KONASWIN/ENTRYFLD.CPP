#include "EntryFld.H"
#include "EFldPrn.H"
#include "FieldWin.H"
#include "Storage.H"

#include <String.H>

#define INITIAL_MAX_TEXT_LENGTH 10


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

EntryField::EntryField() :
	text( 0 ),
	maxTextLength( INITIAL_MAX_TEXT_LENGTH )
{
}


EntryField::~EntryField()
{
	if( text )
		delete[] text;
}


const char *EntryField::getClassName()
{
	return "EntryField";
}


//==========================================================
//===  general data handling methods (Field)  ==============
//==========================================================

void EntryField::initializeData()
{
	text = new char[(int)maxTextLength + 1];
}


boolean EntryField::isFilledIn()
{
	if( strlen( text ) > 0 )
		return True;
	else
		return False;
}


const char *EntryField::getString()
{
	return text;
}


void EntryField::setToDefault()
{
	strcpy( text, defaultText );
	if( getWindow() )
		getWindow()->update();
}


FieldPrint *EntryField::createPrint( const char *printerID )
{
	printerID;
	return new EntryFieldPrint( this );
}


//==========================================================
//===  data storage methods (Field)  =======================
//==========================================================

void EntryField::writeData( StorageUnit& su )
{
	su.writeString( text, maxTextLength );
}


void EntryField::readData( StorageUnit& su )
{
	su.readString( text, maxTextLength );
}


//==========================================================
//===  data manipulation methods (EntryField)  =============
//==========================================================

void EntryField::setText( const char *newText )
{
	strncpy( text, newText, (int)maxTextLength );
	text[(int)maxTextLength] = 0;
}


const char *EntryField::getText()
{
	return text;
}


long EntryField::getMaxTextLength()
{
	return maxTextLength;
}


//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================

void EntryField::write( StorageUnit& su )
{
	Field::write( su );
	su << maxTextLength;
}


void EntryField::read( StorageUnit& su )
{
	Field::read( su );
	su >> maxTextLength;
}
