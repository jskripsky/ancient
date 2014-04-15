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
**  Defined classes:                                                        **
**    - Class TDlg                                                          **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TDLG.CPP                                                   **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TFrame
#include "TDlg.H"

#include <String.H>

#define maxTitleLength		40


TDlg::TDlg( const TRect& bounds, const char *aTitle ) :
	TWindowInit( &TDlg::initFrame ),
	TDialog( bounds, "                                        " )
{
	if( aTitle )
		strncpy( (char *)title, aTitle, maxTitleLength );
	else
		strcpy( (char *)title, " " );
}


void TDlg::setTitle( const char *newTitle )
{
	strncpy( (char *)title, newTitle, maxTitleLength );
	frame->drawView();
}


TRect TDlg::getAreaByLen( int y, int length, int xBorder )
{
	TRect r;
	r.a.x = xBorder;
	r.b.x = size.x - xBorder;

	if( length > 0 )
		{
		if( y >= 0 )
			r.a.y = y;
		else
			r.a.y = size.y + y - 1;

		r.b.y = r.a.y + length;
		if( r.b.y >= size.y )
			r.b.y = size.y - 1;
		}
	else
		{
		if( y >= 0 )
			r.b.y = y + 1;
		else
			r.b.y = size.y + y;

		r.a.y = r.b.y + length;
		if( r.a.y < 0 )
			r.a.y = 1;
		}

	return r;
}


TRect TDlg::getAreaByPos( int ay, int by, int xBorder )
{
	TRect r;
	r.a.x = xBorder;
	r.b.x = size.x - xBorder;

	if( ay >= 0 )
		r.a.y = ay;
	else
		r.a.y = size.y + ay - 1;

	if( by >= 0 )
		r.b.y = by;
	else
		r.b.y = size.y + by - 1;

	if( r.b.y >= size.y )
		r.b.y = size.y - 1;

	return r;
}
