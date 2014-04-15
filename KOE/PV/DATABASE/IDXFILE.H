/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database IndexFile Include File		    */
/*												*/
/*----------------------------------------------*/

#ifndef DBIDXFILE
#define DBIDXFILE


#include "Database\File.H"

class fpstream;


class TDBIndexFile : public TDBFile
{
public:
	TDBIndexFile( const char *aFileName, ccIndex aMaxSpareRecs );

protected:
	virtual void *readRecord( fpstream&, void *cacheSystem );
	virtual void writeRecord( fpstream&, void * );

	virtual int getRecordSize();

public:
	TDBIndexFile( StreamableInit );

	static const char *const name;
	static TStreamable *build();

private:
	virtual const char *streamableName() const
		{ return name; }
};


inline ipstream& operator >> ( ipstream& is, TDBIndexFile& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TDBIndexFile*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TDBIndexFile& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TDBIndexFile* cl )
	{ return os << (TStreamable *) cl; }


#endif