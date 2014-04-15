// Copyright (c) 1995 Juraj Skripsky.
// Revision: 0.5
// Date: xx.11.1995

#ifndef PRCNTTXT
#define PRCNTTXT

#define Uses_TView
#include <TV.H>


/*
*/

class TPercentageText : public TView
{
public:
	TPercentageText( const TRect&, ushort aPrecisionDigits = 0 );

	virtual void setData( void *rec );
	virtual void getData( void *rec );

	virtual ushort dataSize()
		{ return sizeof( percentage ); }

protected:
	virtual void draw();
	virtual TPalette& getPalette() const;

	ushort precisionDigits;
	double percentage;
};

#endif