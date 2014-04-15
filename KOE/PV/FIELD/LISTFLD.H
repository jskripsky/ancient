/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		ListFld Include File    				*/
/*												*/
/*----------------------------------------------*/

#ifndef LISTFLD
#define LISTFLD

#define Uses_TSortedListBox

#include <TV.H>

#include "Field\StdFlds.H"

class TListField : public TField
{
public:
	TListField( TMeasurements&, const char *aLabel, ushort aStringLength,
				const char *aListFilename, int visibleLines,
				ushort options = 0 );
	virtual ~TListField();

	virtual void createControl( TMeasurements& );

	virtual void getString( char * );
	virtual void print( TOutputDevice& );
	virtual void setInfo( TInfo& );

	virtual Boolean isEmpty();

protected:
	char listFilename[13];
	TCollection *list;


private:
	static TPoint controlSize();

public:
	TListField( StreamableInit );

	static const char *const name;
	static TStreamable *build();

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


class TFieldListBox : public TListBox
{
public:
	TFieldListBox( const TRect& bounds, TScrollBar *aScrollBar );

//	virtual void handleEvent( TEvent& event );

	virtual ushort dataSize();
	virtual void getData( void *rec );
	virtual void setData( void *rec );

protected:
	int maxLen;

public:
	TFieldListBox( StreamableInit );

	static const char *const name;
	static TStreamable *build();

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


inline ipstream& operator >> ( ipstream& is, TFieldListBox& cl )
	{ return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TFieldListBox*& cl )
	{ return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TFieldListBox& cl )
	{ return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TFieldListBox* cl )
	{ return os << (TStreamable *)cl; }


class TFieldListCollection : public TCollection
{
public:
	TFieldListCollection( ccIndex aLimit, ccIndex aDelta );

private:
	virtual void *readItem( ipstream& ) { return 0; }
	virtual void writeItem( void *, opstream& ) { }
};



#endif