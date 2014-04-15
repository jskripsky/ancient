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
**  TDlg Class                                                              **
**  ----------                                                              **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TDlg                                                          **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TDLG.H                                                     **
**                                                                          **
*****************************************************************************/

#ifndef TDLG
#define TDLG

#define Uses_TDialog
#include <TV.H>


#define aInfinite	0x100


class TDlg : public TDialog
{
public:
	TDlg( const TRect& bounds, const char *aTitle = 0 );

	void setTitle( const char *newTitle );

protected:
	TRect getAreaByLen( int y, int length, int xBorder = 3 );
	TRect getAreaByPos( int ay, int by, int xBorder = 3 );
};


#endif
