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
**  TKeyDlg Class                                                           **
**  -------------                                                           **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TKeyDlg                                                       **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TKEYDLG.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TLabel
#define Uses_TStaticText
#define Uses_TScrollBar
#define Uses_TSItem
#include "TKeyDlg.H"
#include "TNotCtrl.H"
#include "TNInputL.H"
#include "TLBCol.H"
#include "tvDGMain.H"


TKeyDlg::TKeyDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TKeyDlg::initFrame ),
	TObjDlg( bounds, anOwner )
	{}


void TKeyDlg::setupDialog()
{
	TObjDlg::setupDialog();

	insert( typeSwitch = new TNRadioButtons( TRect( 3, 5, 20, 7 ),
		new TSItem( "Character",
		new TSItem( "Scancode", 0 )) ) );

	TScrollBar *SB = new TScrollBar( TRect( 28, 9, 29, 14 ) );
	insert( SB );

	insert( characterBox = new TNListBox( TRect( 3, 9, 28, 14 ), 1, SB ) );
	characterBox->newList( ((tvDGMainFolder *)mainFolder)->getCharacters() );

	insert( new TStaticText( TRect( 4, 8, 7, 9 ), "Hex" ) );
	insert( new TStaticText( TRect( 8, 8, 11, 9 ), "Dez" ) );
	insert( new TStaticText( TRect( 13, 8, 20, 9 ), "Zeichen" ) );

	insert( scanCodeLine =
		new TNHexInputLine( TRect( 12, 15, 17, 16 ), 3 ) );

	insert( scanCodeLineLabel =
		new TLabel( TRect( 2, 15, 12, 16 ), "Scancode", scanCodeLine ) );
}

void TKeyDlg::disableCharacterBox( Boolean disable )
{
	characterBox->setState( sfDisabled, disable );
}


void TKeyDlg::disableScanCodeLine( Boolean disable )
{
	scanCodeLine->setState( sfDisabled, disable );
	scanCodeLineLabel->setState( sfDisabled, disable );
}
