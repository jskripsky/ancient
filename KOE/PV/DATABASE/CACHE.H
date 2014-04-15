/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database Cache Include File		    	*/
/*												*/
/*----------------------------------------------*/

#ifndef DBCACHE
#define DBCACHE

#define Uses_TObject

class TDBFile;
class RecordDescriptor;
class TNSCollection;

#include <TV.H>


class TDBCache : public TObject
{
public:
	TDBCache( TDBFile *, ushort aLimit );
	virtual ~TDBCache();

	virtual void insertIntoFile( RecordDescriptor *, void * );
	virtual void removeFromFile( RecordDescriptor * );

	virtual void *getItem( RecordDescriptor * );

	virtual void flush();

	void setUpdateFlag( void *item );

protected:
	virtual RecordDescriptor *get( RecordDescriptor * );

	virtual void flushItem( void * );
	virtual void flushItem( RecordDescriptor * );
//	virtual void setLimit( ushort newLimit );

	TDBFile *file;
	ushort limit;

	TNSCollection *descriptors;
	TNSCollection *items;
};


#endif