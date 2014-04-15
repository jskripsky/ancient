#ifndef FLDPRES
#define FLDPRES


#include "Present.H"

class Field;


class FieldPresentation : virtual public Presentation
{
public:
	//=== constructors and destructor =====
	FieldPresentation( DataObject * );
	virtual ~FieldPresentation();


protected:
	Field *getField();


protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


inline Field *FieldPresentation::getField()
	{ return (Field *)getDataObject(); }


#endif