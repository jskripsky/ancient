#ifndef TIMEFLD
#define TIMEFLD


#include "Field.H"
#include "Time.H"


// Zeitfeld.


class TimeField : public Field
{
public:
	//=== constructors and destructor =====
	TimeField();
	virtual ~TimeField();

	virtual const char *getClassName();

	//=== general data handling =====
	virtual void initializeData();

	virtual boolean isFilledIn();
        // (Liefert in dieser Klasse den Wert der Variable "filledIn".)

	virtual const char *getString();

	virtual void setToDefault();


	//=== data storage =====
	virtual void writeData( StorageUnit& );
	virtual void readData( StorageUnit& );

	//=== field presentation =====
	virtual Window *createWindow( void *parent );
	virtual Printer *createPrinter( const char *printerID );


	//=== user data manipulation =====
        // Alle folgenden Methoden arbeiten analog zu denen der Klasse "DateField".
        // (Siehe Beschreibungen in "DateFld.H".)

	virtual boolean setTime( char hour, char minute );
	virtual void getTime( char *hour, char *minute );

        virtual void clearTime();

protected:
	Time time;

	boolean filledIn;
};


#endif