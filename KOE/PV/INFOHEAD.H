/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Person Info Header Include File		    */
/*												*/
/*----------------------------------------------*/

#ifndef INFOHEAD
#define INFOHEAD


const INFOLENGTH = 80;


const ushort ilShort    = 1;
const ushort ilNormal   = 2;
const ushort ilDetailed = 3;


struct stringItem
{
	ushort level;
	ushort maxLen;
};


class TInfoHead : public TCollection
{
public:
	TInfoHead();
	~TInfoHead();

	stringItem *at( ccIndex );
	ccIndex append( ushort level, ushort maxLen );

public:
	TInfoHead( StreamableInit ) :
		TCollection( streamableInit )
		{ shouldDelete = False; }

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


inline ipstream& operator >> ( ipstream& is, TInfoHead& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TInfoHead*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TInfoHead& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TInfoHead* cl )
	{ return os << (TStreamable *) cl; }


#endif