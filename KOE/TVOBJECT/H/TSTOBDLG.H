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
**  TStaticTitleObjDlg Class                                             	**
**  ------------------------                                                **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TStaticTitleObjDlg                                            **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TSTOBDLG.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TSTOBDLG
#define TSTOBDLG

#include "TObjDlg.H"


class TStaticTitleObjDlg : public TObjDlg
{
public:
	TStaticTitleObjDlg( const TRect& bounds, tvObject *anOwner ) :
		TWindowInit( &TStaticTitleObjDlg::initFrame ),
		TObjDlg( bounds, anOwner )
		{}

protected:
	virtual void addTitleLine( int y );
};


#endif
