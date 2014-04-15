/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Form Include File		    			*/
/*												*/
/*----------------------------------------------*/

#ifndef FORM
#define FORM


#include "Page.H"


class TForm : private TCollection
{
public:
	TForm();

	ushort pageCount();
	void adjust( TPoint );
	void registerInfo( TInfoHead& );

	static ushort dataSize();

	virtual void insert( TPage * );
	TPage *at( ccIndex );

protected:
	static ushort usDataSize;


public:
	TForm( StreamableInit ) :
		TCollection( streamableInit )
		{ }

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


inline ushort TForm::pageCount()
	{ return count; }

inline ushort TForm::dataSize()
	{ return usDataSize; }

inline TPage *TForm::at( ccIndex index )
	{ return (TPage *)TCollection::at( index ); }


inline ipstream& operator >> ( ipstream& is, TForm& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TForm*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TForm& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TForm* cl )
	{ return os << (TStreamable *) cl; }


#endif