#ifndef TIME
#define TIME


#include "Types.H"


class Time
{
public:
	//=== constructors and destructor =====
	Time();

	void setToCurrentTime();

	boolean set( char aHour, char aMinute, char aSecond );

	char getHour();
	char getMinute();
	char getSecond();

protected:
	char hour;
	char minute;
	char second;
};


inline char Time::getHour()
	{ return hour; }

inline char Time::getMinute()
	{ return minute; }

inline char Time::getSecond()
	{ return second; }


#endif