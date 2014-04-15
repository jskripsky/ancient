/*****************************************************************************
**                                                                          **
**                                                                          **
**  Form Designer                                                           **
**  =============                                                           **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  Gadget Classes                                                          **
**  --------------                                                          **
**                                                                          **
**  Declared classes:                                                       **
**    - Class THeapView                                                     **
**    - Class TClockView                                                    **
**                                                                          **
**                                                                          **
**  Module Name: GADGETS.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef GADGETS
#define GADGETS


#define Uses_TView
#include <TV.H>


class THeapView : public TView
{
public:
	THeapView( TRect& r );
	virtual void update();
	virtual void draw();
	virtual long heapSize();

private:
	long oldMem, newMem;
	char heapStr[16];
};


class TClockView : public TView
{
public:
	TClockView( TRect& r );
	virtual void draw();
	virtual void update();

private:
	char lastTime[9];
	char curTime[9];
};


#endif
