#include "Date.H"


const char DaysInMonth[12] =
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

Date::Date() :
	year( 1980 ),
	month( January ),
	day( 1 )
{
	setToCurrentDate();
}


void Date::setToCurrentDate()
{
}


boolean Date::set( short aYear, Month aMonth, char aDay )
{
	if( (aYear < 1800) || (2100 < aYear) ||
		(aMonth < January) || (December < aMonth) ||
		(aDay < 1) || (getDaysInMonth( aMonth, aYear ) < aDay) )
		return False;
	else
		{
		year = aYear;
		month = aMonth;
		day = aDay;
		return True;
		}
}


char Date::getDaysInMonth( Month m, short aYear )
{
	if( (m == February) && isLeapYear( aYear ) )
		return DaysInMonth[m - 1] + 1;
	else
		return DaysInMonth[m - 1];
}


boolean Date::isLeapYear( short aYear )
{
	if( aYear % 4 != 0 )
		return False;
	else
		{
		if( aYear % 100 != 0 )
			return True;
		else
			{
			if( aYear % 400 != 0 )
				return False;
			else
				return True;
			}
		}
}