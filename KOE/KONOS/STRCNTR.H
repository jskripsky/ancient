#ifndef STRCNTR
#define STRCNTR


#include "Contain.H"


class StringContainer : public Container
{
public:
	virtual const char *getClassName();

protected:
	//=== item storage (Container) =====
	virtual void writeItem( void *, StorageUnit& );
	virtual void *readItem( StorageUnit& );
};


#endif
