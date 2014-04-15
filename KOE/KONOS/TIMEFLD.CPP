#include "TimeFld.H"
#include "Storage.H"


//==========================================================
//===  general data handling methods (Field)  ==============
//==========================================================

void TimeField::setToDefault()
{
	filledIn = False;
}


boolean TimeField::isFilledIn()
{
	return filledIn;
}


//==========================================================
//===  data storage methods (Field)  =======================
//==========================================================

void TimeField::writeData( StorageUnit& su )
{
	su << filledIn;
	if( filledIn )
		{
		su << time.getHour();
		su << time.getMinute();
		}
}


void TimeField::readData( StorageUnit& su )
{
	su >> filledIn;
	if( filledIn )
		{
		short hour;
		short minute;

		su >> hour;
		su >> minute;

		time.set( hour, minute, 0 );
		}
}


//==========================================================
//===  data manipulation methods (EntryField)  =============
//==========================================================

boolean TimeField::setTime( char hour, char minute )
{
	if( time.set( hour, minute, 0 ) )
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


void TimeField::getTime( char *hour, char *minute )
{
	*hour = time.getHour();
	*minute = time.getMinute();
}
