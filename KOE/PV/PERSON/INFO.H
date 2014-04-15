/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Person Info Include File		    	*/
/*												*/
/*----------------------------------------------*/

#ifndef INFO
#define INFO


#include "InfoHead.H"
#include "DataBase\Entry.H"
#include "Person\Person.H"

class TBuffer;

class TInfo : public TDBEntry
{
public:
	TInfo();
	virtual ~TInfo();

	void init();

	TInfo& operator = ( const TInfo& );

	char *at( ccIndex index );
	virtual void getKey( char *rec, ushort maxLen );
	virtual char *getKey();

	void getString( char *rec, ushort level, ushort maxLen );
	char *firstString( ushort level );

	int getAccessCode();
	void setAccessCode( int code );

protected:
	char **strings;

	static TBuffer **buffers;
	static int instances;

	int access;

public:
	TInfo( StreamableInit );

	static const char *const name;
	static TStreamable *build();

//protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


inline int TInfo::getAccessCode()
	{ return access; }

inline void TInfo::setAccessCode( int code )
	{ access = code; }


inline ipstream& operator >> ( ipstream& is, TInfo& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TInfo*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TInfo& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TInfo* cl )
	{ return os << (TStreamable *) cl; }


#endif