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
**  TFD Class                                                               **
**  ---------                                                               **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TFD                                                           **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: FD.H                                                       **
**                                                                          **
*****************************************************************************/

#ifndef FD
#define FD

#define Uses_TApplication
#include <TV.H>


class tvMainFolder;
class THeapView;
class TClockView;

class TFD : public TApplication
{
public:
	TFD();
	~TFD();

protected:
	virtual void getEvent( TEvent& event );
	virtual void idle();

	virtual TPalette& getPalette() const;

	tvMainFolder *mainFld;

	THeapView *heapStatus;
	TClockView *clock;

	static TStatusLine *initStatusLine( TRect );
};


#endif
