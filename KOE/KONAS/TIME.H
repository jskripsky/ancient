#ifndef TIME
#define TIME


#include "Types.H"


// Die "Time"-Klasse speichert eine Uhrzeit.
// Beim Setzen einer neuen Zeit wird diese auf Korrektheit berprft.


class Time
{
public:
	//=== constructors and destructor =====
	Time();
        // Nach der Ausfhrung des Contructors enth„lt dieses Objekt die
        // aktuelle System-Zeit.

	void setToCurrentTime();
        // Setzt die Daten dieses Objekt auf die aktuelle System-Zeit.

	boolean set( char aHour, char aMinute, char aSecond );
        // Setzt die Daten dieses Objekts und liefert True zurck. Falls die
        // bergebenen Parameter nicht korrekt sind, wird False
        // zurckgeliefert und die vorher gespeicherten Werte bleiben
        // erhalten.
        // (Korrekte Bereiche fr die Parameter: "aHour" 0 - 23,
        // "aMinute" und "aSecond" 0 - 59)

	char getHour();
	char getMinute();
	char getSecond();
        // Diese Methoden liefern die Stunde, Minute und Sekunde dieses
        // Objekts.

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