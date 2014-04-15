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
**  TFormTextDlg Class                                                      **
**  ------------------                                                      **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TFormTextDlg												    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFTXTDLG.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TLabel
#define Uses_TScrollBar
#define Uses_TNSCollection

#include "TFTxtDlg.H"
#include "EPSpace.H"
#include "TNotCtrl.H"
#include "TLBCol.H"


TFormTextDlg::TFormTextDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TFormObjDlg::initFrame ),
	TFormObjDlg( bounds, anOwner )
	{}


void TFormTextDlg::setupDialog()
{
	addFontSelection( 12 );
}


void TFormTextDlg::addFontSelection( int y )
{
	TLBCollection *lbCol = new TLBCollection( 10, 2 );
	TNSCollection *fonts = EpsonPaperSpace::getFontTitles();
	for( int i = 0; i < fonts->getCount(); i++ )
		lbCol->insert( fonts->at( i ) );

	TRect fsRect = getAreaByLen( y, 1 );
	fsRect.a.x += 8;
	fsRect.b.x = fsRect.a.x + 20;

	TScrollBar *SB = new TScrollBar( fsRect );
	insert( SB );

	fsRect = getAreaByLen( y, 1 );
	fsRect.a.x += 9;
	fsRect.b.x = fsRect.a.x + 18;

	insert( fontSel = new TNListBox( fsRect, 1, SB ) );
	fontSel->newList( lbCol );

	fsRect = getAreaByLen( y, 1 );
	fsRect.b.x = fsRect.a.x + 7;
	fsRect.a.x--;
	insert( new TLabel( fsRect, "Schrift", fontSel ) );
}
