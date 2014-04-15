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
**  TSpeedWindow Class                                                      **
**  ------------------                                                      **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TSpeedWindow                                                  **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TSWINDOW.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TSWINDOW
#define TSWINDOW

#define Uses_TWindow
#include <TV.H>


class TSpeedWindow : public TWindow
{
public:
	TSpeedWindow( const TRect& bounds, Boolean open, ushort duration );
	~TSpeedWindow();

protected:
	Boolean grow( TRect& endBounds );

	virtual void sizeLimits( TPoint& min, TPoint& max );
};


#endif
