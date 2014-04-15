#ifndef NUMINPTL
#define NUMINPTL


#define Uses_TInputLine
#include <TV.H>


class TRightJustInputLine : public TInputLine
{
public:
	TRightJustInputLine( const TRect& bounds, int aMaxLen ) :
		TInputLine( bounds, aMaxLen )
		{}

protected:
	virtual void draw();
};


class TNumericInputLine : public TRightJustInputLine
{
public:
	TNumericInputLine( const TRect& bounds, int aMaxLen,
				    int aFractionDigits = 0 );

	virtual ushort dataSize();
	virtual void getData( void *rec );
	virtual void setData( void *rec );

protected:
	int fractionDigits;

	virtual void handleEvent( TEvent& event );
};


inline ushort TNumericInputLine::dataSize()
	{ return sizeof( int ); }


#endif
