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
**  TFormFldDlg Class                                                       **
**  -----------------                                                       **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TFormFldDlg                                                   **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFORMDLG.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TScrollBar
#define Uses_TEvent
#define Uses_TSItem
#define Uses_TLabel
#include "TFormDlg.H"
#include "TBtnBar.H"
#include "TNotCtrl.H"
#include "TNInputL.H"


TFormFldDlg::TFormFldDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TFormFldDlg::initFrame ),
	TFolderDlg( bounds, anOwner ),
	typeSwitch( 0 ),
	formNumber( 0 )
	{}


void TFormFldDlg::addTitleLine( int y )
{
	TFolderDlg::addTitleLine( y );
	titleLine->hide();

	TRect ts = getAreaByLen( y, 2 );
	ts.b.x = ts.a.x + 14;

	insert( typeSwitch = new TNRadioButtons( ts,
		new TSItem( "Formular",
		new TSItem( "Etikette", 0 )) ) );

	TRect fn = ts;
	fn.a.y++;
	fn.a.x = fn.b.x + 1;
	fn.b.x = fn.a.x + 5;
	insert( formNumber = new TNNumericInputLine( fn, 3 ) );

	fn.a.y--; fn.b.y--;
	fn.a.x--;
	insert( new TLabel( fn, "Nr.", formNumber ) );
}
