/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database Record Include File		    */
/*												*/
/*----------------------------------------------*/

#ifndef DBRECORD
#define DBRECORD

#define Uses_TObject
#define Uses_TStreamable

#include <TV.H>

class TDataBase;

class TDBRecord : public TObject, public TStreamable
{
	friend TDataBase;

public:
	TDBRecord() :
		dataBase( 0 )
		{}

	void connectToCache( void *aCache );
	void setUpdateFlag();

	TDataBase *dataBase;

protected:
	void *cache;


public:
	TDBRecord( StreamableInit )
		{}

private:
	virtual const char *streamableName() const = 0;

protected:
	virtual void *read( ipstream& ) = 0;
	virtual void write( opstream& ) = 0;
};


inline void TDBRecord::connectToCache( void *aCache )
	{ cache = aCache; }


inline ipstream& operator >> ( ipstream& is, TDBRecord& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TDBRecord*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TDBRecord& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TDBRecord* cl )
	{ return os << (TStreamable *) cl; }


#endif