/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Page Include File		    			*/
/*												*/
/*----------------------------------------------*/

#ifndef PAGE
#define PAGE


#include "Gadgets\TransGrp.H"
#include "Field\StdFlds.H"
#include "Field\NumFlds.H"
#include "Field\DateFlds.H"
#include "Field\SpecFlds.H"
#include "Field\ListFld.H"

#include "Field\PNField.H"
#include "Field\CtrlFld.H"


class TOutputDevice;


const ushort titleLength = 20;


class TPage : private TCollection
{
public:
	TPage( char *aTitle );

	char *title();

	void setDataOffSet( ushort );

	void move( TPoint );
	void registerInfo( TInfoHead& );
	void setInfo( TInfo& );
	void setAccessCode( TInfo& );
	void print( TOutputDevice& );
	Boolean checkFields();

	virtual ushort dataSize();
	virtual void setData( void *data );
	virtual void getData( void *data );

	virtual void insert( TField * );
	TField *first();
	TField *at( ccIndex index );

	void insertInto( TGroup * );
	void removeFrom( TGroup * );

	TField *lastInserted;

protected:
	char pageTitle[titleLength + 1];
	ushort dataOffSet;

	TTransGroup page;


public:
	TPage( StreamableInit );

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


inline char *TPage::title()
	{ return pageTitle; }

inline void TPage::setDataOffSet( ushort aOffSet )
	{ dataOffSet = aOffSet; }

inline ushort TPage::dataSize()
	{ return page.dataSize(); }

inline TField *TPage::first()
	{ return (TField *)TCollection::at( 0 ); }

inline TField *TPage::at( ccIndex index )
	{ return (TField *)TCollection::at( index ); }


inline ipstream& operator >> ( ipstream& is, TPage& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TPage*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TPage& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TPage* cl )
	{ return os << (TStreamable *) cl; }


#endif