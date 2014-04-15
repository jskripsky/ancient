/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Person Include File		    			*/
/*												*/
/*----------------------------------------------*/

#ifndef PERSON
#define PERSON


#include "DataBase\Record.H"


enum CreationInit { creationInit };
class TBuffer;

class TPerson : public TDBRecord
{
public:
	TPerson( const TPerson& person );
	TPerson( CreationInit );
	~TPerson();

	void initData();

	TPerson& operator = ( const TPerson& );

	void *getData();
	static ushort dataSize();


protected:
	void *data;

	static TBuffer *buffer;
	static int instances;

public:
	TPerson( StreamableInit );

	static const char *const name;
	static TStreamable *build();

//protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


inline void *TPerson::getData()
	{ return data; }


inline ipstream& operator >> ( ipstream& is, TPerson& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TPerson*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TPerson& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TPerson* cl )
	{ return os << (TStreamable *) cl; }


#endif