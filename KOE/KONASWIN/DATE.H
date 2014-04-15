#ifndef DATE
#define DATE


#include "Types.H"


enum Month { January = 1, February, March, April, May, June, July,
			 August, September, October, November, December };


// Die "Date"-Klasse speichert ein Datum.
// Beim Setzen eines neuen Datums wird dieses auf Korrektheit berprft.



class Date
{
public:
	//=== constructors and destructor =====
	Date();
        // Nach der Ausfhrung des Contructors enth„lt dieses Objekt das
        // aktuelle System-Datum.

	void setToCurrentDate();
        // Setzt die Daten dieses Objekt auf das aktuelle System-Datum.

	boolean set( short aYear, Month, char aDay );
        // Setzt die Daten dieses Objekts und liefert True zurck. Falls die
        // bergebenen Parameter nicht korrekt sind, wird False
        // zurckgeliefert und die vorher gespeicherten Werte bleiben
        // erhalten.
        // (Korrekte Bereiche fr die Parameter: "aYear" 1800 - 2100,
        // "aMonth" January - December und "aDay" 1 - 28/29/30/31)

	short getYear();
	Month getMonth();
	char getDay();
        // Diese Methoden liefern das Jahr, den Monat und den Tag dieses
        // Objekts.


	static char getDaysInMonth( Month, short aYear );
        // Liefert die Anzahl Tage eines bestimmten Monats.

	static boolean isLeapYear( short aYear );
        // Liefert True, falls "aYear" ein Schaltjahr ist, sonst False.

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