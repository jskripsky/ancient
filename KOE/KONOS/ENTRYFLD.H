#ifndef ENTRYFLD
#define ENTRYFLD


#include "Field.H"


// Das EntryField entspricht einem einfachen Textfeld.


class EntryField : public Field
{
public:
	//=== constructors and destructor =====
	EntryField();
	virtual ~EntryField();

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
//	virtual FieldPrinter *createPrinter( const char *printerID );


	//=== data manipulation =====
	virtual void setText( const char *newText );
	virtual const char *getText();
        // Setzt und liefert der aktuellen Text des Feldes.

	virtual long getMaxTextLength();
        // Liefert die maximale Textl„nge, die dieses Feld erlaubt.

protected:
	char *text;


protected:
	//=== form design / metadata =====
	long maxTextLength;
        char *defaultText;

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


#endif