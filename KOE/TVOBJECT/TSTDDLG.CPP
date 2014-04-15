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
**  TStdDlg Class                                                           **
**  -------------                                                           **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TStdDlg                                                       **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TSTDDLG.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStaticText
#define Uses_TFrame
#define Uses_TEvent
#define Uses_TKeys
#define Uses_TWindow
#define Uses_TProgram
#define Uses_TDeskTop
#include "TStdDlg.H"
#include "TBtnBar.H"
#include "TNotCtrl.H"
#include "TSWindow.H"

#include <String.H>
#include <DOS.H>


#define cmUndo 100


TStdDlg::TStdDlg( const TRect& bounds, const char *aTitle ) :
	TWindowInit( &TStdDlg::initFrame ),
	TDlg( bounds, aTitle )
{
	state &= ~sfVisible;
}


TStdDlg::~TStdDlg()
{
	delete buttonBar;
}


void TStdDlg::setup()
{
	setupDialog();
	buttonBar = createButtonBar();
	setupButtons();
}


void TStdDlg::setState( ushort aState, Boolean enable )
{
	if( aState & sfVisible )
		{
		if( enable )
			{
			selectNext( False );

			TSpeedWindow *sw = new TSpeedWindow( getBounds(), True, 0 );
			TDlg::setState( aState, enable );
			destroy( sw );
			return;
			}
		else
			{
			TProgram::deskTop->lock();
			TDlg::setState( aState, enable );
			TSpeedWindow *sw = new TSpeedWindow( getBounds(), False, 0 );
			destroy( sw );
			return;
			}
		}

	TDlg::setState( aState, enable );
}


void TStdDlg::handleEvent( TEvent& event )
{
	if( event.what == evKeyboard )
		switch( event.keyDown.keyCode )
			{
			case kbEsc:
				undo();
				close();
				clearEvent( event );
				break;

			case kbGrayMinus:
				close();
				clearEvent( event );
				break;
			}

	TDlg::handleEvent( event );
	switch( event.what )
		{
		case evCommand:
			switch( event.message.command )
				{
				case cmNotification:
					handleNotification( (TView *)event.message.infoPtr );
					clearEvent( event );
					break;

				case cmClose:
					close();
					clearEvent( event );
					break;

				case cmUndo:
					undo();
					clearEvent( event );
					break;
				}
			break;
		}
}


void TStdDlg::setupDialog()
{
	addLine( -3 );
}


void TStdDlg::addLine( int y )
{
	TRect line = getAreaByLen( y, 1, 2 );

	int lineLength = line.b.x - line.a.x;

	char *lineString = new char[lineLength + 1];
	memset( lineString, 'Ä', lineLength );
	lineString[lineLength] = 0;
	insert( new TStaticText( line, lineString ) );
	delete[] lineString;
}


TButtonBar *TStdDlg::createButtonBar()
{
	return( new TButtonBar( this, getAreaByLen( -2, aInfinite, 2 ) ) );
}


void TStdDlg::setupButtons()
{
	addCloseButton();
	addUndoButton();
}


void TStdDlg::addUndoButton( Boolean longForm )
{
	char *t = ( longForm ? "~R~ckg„ngig"       : "~R~ckg."           );
	TRect r = ( longForm ? TRect( 0, 0, 14, 2 ) : TRect( 0, 0, 10, 2 ) );

	buttonBar->insert( new TButton( r, t, cmUndo, bfNormal ) );
}


void TStdDlg::addCloseButton( Boolean longForm )
{
	char *t = ( longForm ? "~S~chliessen"       : "~S~chl."            );
	TRect r = ( longForm ? TRect( 0, 0, 14, 2 ) : TRect( 0, 0,  9, 2 ) );

	buttonBar->insert( new TButton( r, t, cmClose, bfNormal ) );
}
