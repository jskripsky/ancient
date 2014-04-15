#ifndef PERSLIST
#define PERSLIST

#include "Persist.H"

class PersonDlist;



class PersonList : public PersistentObject
{
public:
	//=== constructors and destructor =====
	PersonList();
	virtual ~PersonList();


protected:
        PersonDlist *list;


protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


#endif