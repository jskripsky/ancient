#include "DateFld.H"
#include "Storage.H"


//==========================================================
//===  general data handling methods (Field)  ==============
//==========================================================

void DateField::setToDefault()
{
	filledIn = False;
}


boolean DateField::isFilledIn()
{
	return filledIn;
}


//==========================================================
//===  data storage methods (Field)  =======================
//==========================================================

void DateField::writeData( StorageUnit& su )
{
	su << filledIn;
	if( filledIn )
		{
		su << date.getYear();
		su << (short)date.getMonth();
		su << date.getDay();
		}
}


void DateField::readData( StorageUnit& su )
{
	su >> filledIn;
	if( filledIn )
		{
		short year;
		Month month;
		char day;

		su >> year;
		su >> (short&)month;
		su >> day;

		date.set( year, month, (char)day );
		}
}


//==========================================================
//===  data manipulation methods (EntryField)  =============
//==========================================================

boolean DateField::setDate( short year, Month month, char day )
{
	if( date.set( year, month, day ) )
		{
		filledIn = True;
		return True;
		}
	else
		{
		filledIn = False;
		return False;
		}
}


void DateField::getDate( short *year, Month *month, char *day )
{
	*year = date.getYear();
	*month = date.getMonth();
	*day = date.getDay();
}
