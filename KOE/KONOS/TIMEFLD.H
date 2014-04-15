#ifndef TIMEFLD
#define TIMEFLD


#include "Field.H"
#include "Time.H"


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

	virtual const char *getString();

	virtual void setToDefault();


	//=== data storage =====
	virtual void writeData( StorageUnit& );
	virtual void readData( StorageUnit& );

	//=== field presentation =====
	virtual Window *createWindow( void *parent );
	virtual Printer *createPrinter( const char *printerID );


	//=== data manipulation =====
	virtual boolean setTime( char hour, char minute );
	virtual void getTime( char *hour, char *minute );

protected:
	Time time;

	boolean filledIn;
};


#endif