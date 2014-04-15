#ifndef FORM
#define FORM


#include "DataObj.H"

class FormWindow;
class Field;
class FieldSlist;
class FieldSlistIter;

class Form : public DataObject
{
public:
	//=== constructors and destructor =====
	Form();
	virtual ~Form();

	virtual const char *getClassName();

	virtual void attachField( Field * );
        virtual Field *getFieldByID( char *ID );

        FieldSlistIter *getFieldsIterator();

        Window *getFormWindow();
        // Methode zu internen Zwecken ("Field::getFormWindow").

protected:
	FieldSlist *fields;

	virtual Window *createWindow( void *parent );


protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


#endif