/*****************************************************************************
**                                                                          **
**                                                                          **
**  DOS Dialog Generator                                                    **
**  ====================                                                    **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  TtvDG Class                                                             **
**  -----------                                                             **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TtvDG                                                         **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TTVDG.H                                                    **
**                                                                          **
*****************************************************************************/

#ifndef TTVDG
#define TTVDG

#include "TtvAppl.H"


class TtvDG : public TtvApplication
{
public:
	TtvDG();

protected:
	static tvMainFolder *initMainFolder();

	static Boolean isHeapStatusToBeEnabled();
	static void aboutDialog();

	static TStatusLine *initStatusLine( TRect );
};


#endif
