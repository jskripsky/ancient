/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Version Header Include File		    	*/
/*												*/
/*----------------------------------------------*/

#ifndef VERHEAD
#define VERHEAD


class TVersionHeader : private TObject, private TStreamable
{
public:
	TVersionHeader( const char *, ushort );

	char dataDescription[32];
	ushort number;


public:
	TVersionHeader( StreamableInit )
		{ }

	static const char *const name;
	static TStreamable *build();

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


inline ipstream& operator >> ( ipstream& is, TVersionHeader& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TVersionHeader*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TVersionHeader& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TVersionHeader* cl )
	{ return os << (TStreamable *) cl; }


#endif