#ifndef LISTFLD
#define LISTFLD


#include "Field.H"
#include "StrCntr.H"


class ListField : public Field
{
public:
	//=== constructors and destructor =====
	ListField();
	virtual ~ListField();


	//=== data manipulation =====
	virtual StringContainer& getList();

protected:
	StringContainer list;


protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );

};


#endif