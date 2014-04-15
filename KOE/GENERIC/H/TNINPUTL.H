/*****************************************************************************
**                                                                          **
**                                                                          **
**  DOS Form Designer                                                       **
**  =================                                                       **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  TNInputLine Classes                                                     **
**  -------------------                                                     **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TNRightJustInputLine                                          **
**    - Class TNNumericInputLine                                            **
**                                                                          **
**                                                                          **
**  Module Name: TNINPUTL.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TNINPUTL
#define TNINPUTL

#include "TNotCtrl.H"

class TNRightJustInputLine : public TNInputLine
{
public:
	TNRightJustInputLine( const TRect& bounds, int aMaxLen ) :
		TNInputLine( bounds, aMaxLen )
		{}

protected:
	virtual void draw();
};


class TNNumericInputLine : public TNRightJustInputLine
{
public:
	TNNumericInputLine( const TRect& bounds, int aMaxLen,
						int aFractionDigits = 0 );

	virtual ushort dataSize();
	virtual void getData( void *rec );
	virtual void setData( void *rec );

protected:
	int fractionDigits;

	virtual void handleEvent( TEvent& event );
};


inline ushort TNNumericInputLine::dataSize()
	{ return sizeof( int ); }


class TNHexInputLine : public TNRightJustInputLine
{
public:
	TNHexInputLine( const TRect& bounds, int aMaxLen );

	virtual ushort dataSize();
	virtual void getData( void *rec );
	virtual void setData( void *rec );

protected:
	virtual void handleEvent( TEvent& event );
};


inline ushort TNHexInputLine::dataSize()
	{ return sizeof( int ); }

#endif
