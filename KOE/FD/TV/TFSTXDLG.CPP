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
**  TFormStaticTextDlg Class                                                **
**  ------------------------                                                **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TFormStaticTextDlg											**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFSTXDLG.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TLabel
#include "TFSTXDLG.H"
#include "TNotCtrl.H"


TFormStaticTextDlg::TFormStaticTextDlg( const TRect& bounds,
										tvObject *anOwner ) :
	TWindowInit( &TFormObjDlg::initFrame ),
	TFormObjDlg( bounds, anOwner ),
	TFormTextDlg( bounds, anOwner )
	{}


void TFormStaticTextDlg::setupDialog()
{
	TFormObjDlg::setupDialog();
	addTextLine( 10 );
	TFormTextDlg::setupDialog();
}


void TFormStaticTextDlg::addTextLine( int y )
{
	TRect tlRect = getAreaByLen( y, 1 );
	tlRect.a.x += 8;
	tlRect.b.x = tlRect.a.x + 20;

	insert( textLine = new TNInputLine( tlRect, 81 ) );

	tlRect = getAreaByLen( y, 1 );
	tlRect.b.x = tlRect.a.x + 7;
	tlRect.a.x--;
	insert( new TLabel( tlRect, "Text", textLine ) );
}
