#ifndef SELFLD
#define SELFLD


#include "ListFld.H"


class SelectionField : public ListField
{
public:
	//=== constructors and destructor =====
	SelectionField();
	virtual ~SelectionField();

	virtual const char *getClassName();

	//=== general data handling =====
	virtual void initializeData();

	boolean isFilledIn();

	virtual const char *getString();

	virtual void setToDefault();
	virtual boolean validate();

	virtual void hasChanged();


	//=== data storage =====
	virtual void writeData( StorageUnit& );
	virtual void readData( StorageUnit& );

	//=== field presentation =====
	virtual Window *createWindow( void *parent );
	virtual Printer *createPrinter( const char *printerID );


	//=== data manipulation =====
	void setSelection( long number );
	long getSelection( long number );

protected:
	long selection;


protected:
	//=== form design / metadata =====
	long defaultSelection;
	long noSelection;

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );

};


#endif