#ifndef FIELDWIN
#define FIELDWIN


#include "FldPres.H"


class FieldPrint : public FieldPresentation
{
public:
	//=== constructors and destructor =====
	FieldPrint( Field * );
	virtual ~FieldPrint();


	virtual void print() = 0;


protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


#endif