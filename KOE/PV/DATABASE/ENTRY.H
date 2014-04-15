/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database Entry Include File		    	*/
/*												*/
/*----------------------------------------------*/

#ifndef DBENTRY
#define DBENTRY


#include "Database\Record.H"
#include "Database\File.H"

class TDataBase;


class TDBEntry : public TDBRecord
{
	friend TDataBase;

public:
	TDBEntry();

	virtual void getKey( char *rec, ushort maxLen ) = 0;
    virtual char *getKey() = 0;

	TDBRecord *getRecord();
	void attachRecord( TDBRecord * );

protected:
	TDBRecord *record;

	RecordDescriptor recordDescriptor;


public:
	TDBEntry::TDBEntry( StreamableInit ) :
		TDBRecord( streamableInit )
		{}

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const = 0;
};


inline ipstream& operator >> ( ipstream& is, TDBEntry& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TDBEntry*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TDBEntry& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TDBEntry* cl )
	{ return os << (TStreamable *) cl; }


#endif