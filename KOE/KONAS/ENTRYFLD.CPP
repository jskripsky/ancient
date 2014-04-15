#include "EntryFld.H"
#include "Storage.H"

#include <String.H>

#define INITIAL_MAX_TEXT_LENGTH 20


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
	text = new char[maxTextLength + 1];
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
	text[0] = 0;
}


Printer *EntryField::createPrinter( const char *printerID )
{
        printerID;
        return 0;
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
	strncpy( text, newText, maxTextLength );
	text[maxTextLength - 1] = 0;
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
