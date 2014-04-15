#ifndef FIELD
#define FIELD


#include "DataObj.H"

class FieldWindow;
class FieldPrinter;
class Form;
class FormWindow;
class Printer;


class Field : public DataObject
{
public:
	//=== constructors and destructor =====
	Field();
	virtual ~Field();

	//=== general data handling =====
	virtual void initializeData() = 0;
        // Initialisiert die Variablen, die die effektiven Daten des Feldes
        // speichern.

	virtual boolean isFilledIn() = 0;
        // Liefert True, falls das Feld ausgefÅllt ist, sonst False.
        // (Liefert ein obligatorisches Feld hier False, erscheint eine
        // Fehlermeldung.)

	virtual const char *getString() = 0;
        // Liefert den die Daten des Feldes in Textform, als String.

	virtual void setToDefault() = 0;
        // Setzt die Daten zurÅck zu ihrem Default.

	virtual boolean validate();
        // Liefert True, falls die Daten plausibel sind, sonst False.

	virtual void hasChanged();


	//=== data storage =====
	virtual void writeData( StorageUnit& ) = 0;
	virtual void readData( StorageUnit& ) = 0;

	//=== field presentation =====
        virtual Window *createWindow( void *parent ) = 0;
	virtual Printer *createPrinter( const char *printerID ) = 0;

	void destroyPrinter();

	//=== form =====
	void attachToForm( Form * );


protected:
	Form *form;
        Printer *printer;

protected:
	//=== form design / metadata =====
	boolean obligatory;
        // Gibt an, ob dies ein obligatorisches oder fakultatives Feld ist.

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );

};


#endif