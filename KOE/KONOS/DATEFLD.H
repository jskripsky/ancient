#ifndef DATEFLD
#define DATEFLD


#include "Field.H"
#include "Date.H"


class DateField : public Field
{
public:
	//=== constructors and destructor =====
	DateField();
	virtual ~DateField();

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
	virtual boolean setDate( long year, Month month, char day );
	virtual void getDate( long *year, Month *month, char *day );

protected:
	Date date;

	boolean filledIn;
};


#endif