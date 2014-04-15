/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database DataFile Include File		    */
/*												*/
/*----------------------------------------------*/

#ifndef DBDATAFILE
#define DBDATAFILE


#include "Database\File.H"

class fpstream;


class TDBDataFile : public TDBFile
{
public:
	TDBDataFile( const char *aFileName, ccIndex aMaxSpareRecs );

protected:
	virtual void *readRecord( fpstream&, void *cacheSystem );
	virtual void writeRecord( fpstream&, void * );

	virtual int getRecordSize();

public:
	TDBDataFile( StreamableInit );

	static const char *const name;
	static TStreamable *build();

private:
	virtual const char *streamableName() const
		{ return name; }
};


inline ipstream& operator >> ( ipstream& is, TDBDataFile& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TDBDataFile*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TDBDataFile& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TDBDataFile* cl )
	{ return os << (TStreamable *) cl; }


#endif