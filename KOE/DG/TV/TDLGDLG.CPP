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
**  TDialogDlg Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TDialogDlg                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TDLGDLG.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TScrollBar
#define Uses_TEvent
#define Uses_TSItem
#define Uses_TLabel
#include "TDlgDlg.H"
#include "TBtnBar.H"
#include "TNotCtrl.H"
#include "TNInputL.H"


TDialogDlg::TDialogDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TDialogDlg::initFrame ),
	TFolderDlg( bounds, anOwner ),
	numberLine( 0 ),
	keySwitch( 0 )
	{}


TListBox *TDialogDlg::createListBox( TScrollBar *sb )
{
	TListBox *lb = TFolderDlg::createListBox( sb );
	TRect tr = lb->getBounds();
#ifndef ULRICH
	tr.a.y += 2;
#endif
	lb->locate( tr );
	return lb;
}


TScrollBar *TDialogDlg::createScrollBar()
{
	TScrollBar *sb = TFolderDlg::createScrollBar();
	TRect tr = sb->getBounds();
#ifndef ULRICH
	tr.a.y += 2;
#endif
	sb->locate( tr );
	return sb;
}


void TDialogDlg::addTitleLine( int y )
{
	TFolderDlg::addTitleLine( y );
	TRect tl = titleLine->getBounds();
#ifndef ULRICH
	tl.b.x -= 10;
#endif
	titleLine->locate( tl );

	TRect nl = getAreaByLen( y + 3, 1 );
	nl.a.x += 4;
	nl.b.x = nl.a.x + 4;

	insert( numberLine = new TNNumericInputLine( nl, 2 ) );

#ifndef ULRICH
	nl = getAreaByLen( y + 3, 1 );
	nl.b.x = nl.a.x + 4;
	nl.a.x--;
	insert( new TLabel( nl, "Nr.", numberLine ) );
#else
	numberLine->hide();
#endif

	TRect ks = getAreaByLen( y + 1, 3 );
	ks.a.x = ks.b.x - 8;

	insert( keySwitch = new TNRadioButtons( ks,
		new TSItem( "-",
		new TSItem( "S1",
		new TSItem( "S2", 0 ))) ) );

#ifndef ULRICH
	ks.a.y--; ks.a.x--;
	ks.b.y = ks.a.y + 1;

	insert( new TLabel( ks, "Shift", keySwitch ) );
#else
	keySwitch->hide();
#endif
}
