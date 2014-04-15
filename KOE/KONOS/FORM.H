 #ifndef FORM
#define FORM


#include "DataObj.H"
#include "Contain.H"

class FormWindow;
class Field;

class Form : public DataObject
{
public:
	//=== constructors and destructor =====
	Form();
	virtual ~Form();

	virtual const char *getClassName();

	virtual void insert( Field * );


protected:
	Container fields;

	virtual Window *createWindow( void *parent );


protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


#endif