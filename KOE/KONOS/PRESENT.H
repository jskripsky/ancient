#ifndef PRESENT
#define PRESENT


#include "Persist.H"


class DataObject;


class Presentation : virtual public PersistentObject
{
public:
	//=== constructors and destructor =====
	Presentation( DataObject * );
	virtual ~Presentation();


protected:
	DataObject *dataObject;
        // Pointer auf das DataObject-Objekt (Null, falls keines existiert).

	DataObject *getDataObject();


protected:
	//=== storage (PersistentObject) =====
//	virtual void write( StorageUnit& );
//	virtual void read( StorageUnit& );
};


inline DataObject *Presentation::getDataObject()
	{ return dataObject; }


#endif