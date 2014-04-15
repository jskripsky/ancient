/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database File Include File		    	*/
/*												*/
/*----------------------------------------------*/

#ifndef DBFILE
#define DBFILE


#define Uses_TObject
#define Uses_TStreamable
#include <TV.H>

class fpstream;


struct RecordDescriptor
{
	streampos position;
	Boolean update;
};


class TDBFile : public TObject, public TStreamable
{
public:
	TDBFile( const char *aFileName, ccIndex aMaxSpareRecs );
	~TDBFile();

	void createRecord( RecordDescriptor * );
	void deleteRecord( RecordDescriptor * );

	void writeRecord( RecordDescriptor *, void * );
	void *readRecord( RecordDescriptor *, void *cacheSystem );

protected:
	virtual void *readRecord( fpstream&, void *cacheSystem ) = 0;
	virtual void writeRecord( fpstream&, void * ) = 0;

    virtual int getRecordSize() = 0;

	char *fileName;
	fpstream *file;

	ccIndex maxSpareRecs;
	ccIndex spareRecCount;
	RecordDescriptor *spareRecs;

public:
	TDBFile( StreamableInit );

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );
};


inline ipstream& operator >> ( ipstream& is, TDBFile& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TDBFile*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TDBFile& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TDBFile* cl )
	{ return os << (TStreamable *) cl; }


#endif