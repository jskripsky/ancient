#ifndef FORM
#define FORM


#include "DataObj.H"

class FormWindow;
class Field;
class FieldSlist;
class FieldSlistIter;

class FieldPrint;
class FieldPrintSlist;


class Form : public DataObject
{
public:
	//=== constructors and destructor =====
	Form();
	virtual ~Form();

	virtual const char *getClassName();

	virtual void attachField( Field * );
	virtual Field *getFieldByID( char *ID );

	virtual void attachFieldPrint( FieldPrint * );
	virtual void print();

	void newPerson();

	FieldSlistIter *getFieldsIterator();

	FormWindow *getFormWindow();
		  // Methode zu internen Zwecken ("Field::getFormWindow").

protected:
	FieldSlist *fields;
   FieldPrintSlist *fieldPrints;

	virtual Window *createWindow( zWindow *parent );


protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


inline FormWindow *Form::getFormWindow()
	{ return (FormWindow *)window; }


#endif