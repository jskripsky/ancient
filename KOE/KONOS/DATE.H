#ifndef DATE
#define DATE


#include "Types.H"


enum Month { January = 1, February, March, April, May, June, July,
			 August, September, October, November, December };


class Date
{
public:
	//=== constructors and destructor =====
	Date();

	static char getDaysInMonth( Month, short aYear );
	static boolean isLeapYear( short aYear );

	void setToCurrentDate();

	boolean set( short aYear, Month, char aDay );

	short getYear();
	Month getMonth();
	char getDay();

protected:
	short year;
	Month month;
	char day;
};


inline short Date::getYear()
	{ return year; }

inline Month Date::getMonth()
	{ return month; }

inline char Date::getDay()
	{ return day; }


#endif