/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database Include File		    		*/
/*												*/
/*----------------------------------------------*/

#ifndef DATABASE
#define DATABASE

#define Uses_TSortedCollection

#include "DataBase\DataFile.H"
#include "DataBase\IdxFile.H"
#include "DataBase\Record.H"
#include "DataBase\Entry.H"

#include <TV.H>

class TDBCache;
class TBuffer;
struct RecordDescriptor;

class TDataBase : public TSortedCollection
{
	friend TDBEntry;

public:
	TDataBase( const char *aIndexFileName, const char *aDataFileName,
			   ccIndex aMaxSpareRecords = 20 );
	virtual ~TDataBase();

	void *entryAt( ccIndex index );

	virtual ccIndex insert( void * );
	virtual void *keyOf( void *item );

	virtual ccIndex reOrder( ccIndex );

	void setUpdateFlag( void *item, void *cacheSystem );


protected:
	TDBRecord *loadRecord( TDBEntry * );

private:
	virtual void freeItem( void * );
	virtual int compare( void *, void * );

	TDBFile *indexFile;
	TDBFile *dataFile;

	TDBCache *indexCache;
	TDBCache *dataCache;

	TBuffer *buffer;
    int numBufferItems;

public:
	TDataBase( StreamableInit );

	static const char *const name;
	static TStreamable *build();

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual void writeItem( void *, opstream& );
	virtual void *readItem( ipstream& );

	virtual const char *streamableName() const
		{ return name; }
};


inline ipstream& operator >> ( ipstream& is, TDataBase& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TDataBase*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TDataBase& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TDataBase* cl )
	{ return os << (TStreamable *) cl; }


#endif