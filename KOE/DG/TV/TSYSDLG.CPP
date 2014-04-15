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
**  TSystemDlg Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TSystempDlg                                                   **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TSYSDLG.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TLabel
#define Uses_TStaticText
#define Uses_TScrollBar
#define Uses_TSItem
#define Uses_TEvent
#define Uses_TKeys
#include "TSysDlg.H"
#include "TNotCtrl.H"
#include "TNInputL.H"
#include "TLBCol.H"
#include "tvSystem.H"
#include "tvDGMain.H"


TSystemDlg::TSystemDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TSystemDlg::initFrame ),
	TObjDlg( bounds, anOwner )
	{}


void TSystemDlg::setupDialog()
{
	TObjDlg::setupDialog();

	insert( IDLine = new TNInputLine( TRect( 6, 5, 29, 6 ), 21 ) );
	insert( new TLabel( TRect( 2, 5, 6, 6 ), "ID", IDLine ) );

	TScrollBar *SB = new TScrollBar( TRect( 28, 8, 29, 11 ) );
	insert( SB );

	insert( characterBox = new TNListBox( TRect( 3, 8, 28, 11 ), 1, SB ) );
	characterBox->newList( ((tvDGMainFolder *)mainFolder)->getCharacters() );

	insert( new TStaticText( TRect( 4, 7, 7, 8 ), "Hex" ) );
	insert( new TStaticText( TRect( 8, 7, 11, 8 ), "Dez" ) );
	insert( new TStaticText( TRect( 13, 7, 20, 8 ), "Zeichen" ) );

	TRect bl( 3, 13, 8, 14 );
	for( int i = 0; i < BytesPerCharacter; i++ )
		{
		insert( byteLines[i] = new TNHexInputLine( bl, 3 ) );
		bl.move( 6, 0 );
		}

	insert( new TLabel( TRect( 2, 12, 12, 13 ), "Scancode", byteLines[0] ) );

	bl.move( 1, 0 );
	bl.b.x = bl.a.x + 12;

	insert( shiftSwitch = new TNCheckBoxes( bl,
		new TSItem( "Shift", 0 ) ) );

	insert( commentLine = new TNInputLine( TRect( 3, 16, 36, 17 ), 31 ) );
	insert( new TLabel( TRect( 2, 15, 13, 16 ), "Bemerkung", commentLine ) );
}


void TSystemDlg::handleEvent( TEvent& event )
{
	if( event.what == evKeyDown )
		switch( event.keyDown.keyCode )
			{
			case kbAltI:
				clearEvent( event );
				((tvSystem *)owner)->importSystem();
				return;
			}

	TObjDlg::handleEvent( event );
}


