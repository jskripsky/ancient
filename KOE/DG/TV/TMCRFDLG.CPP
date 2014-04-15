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
**  TMCReaderFieldDlg Class                                                 **
**  -----------------------                                                 **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TMCReaderFieldDlg                                             **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TMCRFDLG.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TSItem
#define Uses_TLabel
#include "TMCRFDlg.H"
#include "TNotCtrl.H"
#include "TNInputL.H"



TMCReaderFieldDlg::TMCReaderFieldDlg( const TRect& bounds,
									  tvObject *anOwner ) :
	TWindowInit( &TMCReaderFieldDlg::initFrame ),
	TFieldDlg( bounds, anOwner )
	{}


void TMCReaderFieldDlg::addFieldControls()
{
//	addDataFieldSelection( &dataFieldSel, "Feld", 5 );

	insert( trackSel = new TNRadioButtons( TRect( 14, 5, 36, 6 ),
			new TSItem( "1",
			new TSItem( "2",
			new TSItem( "3", 0 ))) ) );

	insert( new TLabel( TRect( 2, 5, 13, 6 ), "Magnetspur", trackSel ) );

	insert( startLine =
		new TNNumericInputLine( TRect( 7, 7, 12, 8 ), 3 ) );
	insert( new TLabel( TRect( 2, 7, 6, 8 ), "Von", startLine ) );

	insert( endLine =
		new TNNumericInputLine( TRect( 18, 7, 24, 8 ), 4 ) );
	insert( new TLabel( TRect( 13, 7, 17, 8 ), "bis", endLine ) );

//	insert( numericBox =
//		new TNCheckBoxes( TRect( 25, 7, 41, 8 ),
//						  new TSItem( "Numerisch", 0 ) ) );
}
