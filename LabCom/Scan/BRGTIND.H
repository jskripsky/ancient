// Copyright (c) 1995 Juraj Skripsky.
// Revision: 0.5
// Date: xx.11.1995

#ifndef BRGTIND
#define BRGTIND

#define Uses_TView
#include <TV.H>


/*
*/

class TBrightnessIndicator : public TView
{
public:
	TBrightnessIndicator( const TRect&, ushort aRange );

	virtual void setData( void *rec );
	virtual void getData( void *rec );

	virtual ushort dataSize()
		{ return sizeof( position ); }

protected:
	virtual void draw();
	virtual TPalette& getPalette() const;

	ushort range;
	ushort position;
};

#endif