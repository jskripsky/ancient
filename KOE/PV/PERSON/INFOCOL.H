/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Person Info Collection Include File		*/
/*												*/
/*----------------------------------------------*/

#ifndef INFOCOL
#define INFOCOL


#define Uses_TCollection
#include <TV.H>

class TBuffer;

class TInfoCollection : public TCollection
{
public:
	TInfoCollection();
	virtual ~TInfoCollection();

	void init();

	char *at( ccIndex index );


protected:
	static int instances;
	static TBuffer *buffers[10];


public:
	TInfoCollection( StreamableInit );

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


inline char *TInfoCollection::at( ccIndex index )
	{ return (char *)TCollection::at( index ); }


inline ipstream& operator >> ( ipstream& is, TInfoCollection& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TInfoCollection*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TInfoCollection& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TInfoCollection* cl )
	{ return os << (TStreamable *) cl; }


#endif