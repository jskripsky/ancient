#include "Time.H"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

Time::Time() :
	hour( 0 ),
	minute( 0 ),
	second( 0 )
{
	setToCurrentTime();
}


void Time::setToCurrentTime()
{
}


boolean Time::set( char aHour, char aMinute, char aSecond )
{
	if( (aHour < 0) || (23 < aHour) ||
		(aMinute < 0) || (59 < aMinute) ||
		(aSecond < 0) || (59 < aSecond) )
		return False;
	else
		{
		hour = aHour;
		minute = aMinute;
		second = aSecond;
		return True;
		}
}
