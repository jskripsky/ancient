#ifndef CONTAIN
#define CONTAIN


#include "Persist.H"

#define NO_INDEX -1


class Container : public PersistentObject
{
public:
	//=== constructors and destructor =====
	Container();
	virtual ~Container();

	virtual const char *getClassName();

	virtual long insert( void * );
	virtual void remove( void * );
	virtual void removeAt( long index );

	virtual void *at( long index );
	virtual void *&operator[]( long index );

	virtual long getIndexOf( void * );

	long getCount();


protected:
	void **items;

	long count;
	long bufferSize;

	void resizeBuffer( long newBufferSize );

	//=== item storage (Container) =====
	virtual void writeItem( void *, StorageUnit& );
	virtual void *readItem( StorageUnit& );

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );

};


#endif
