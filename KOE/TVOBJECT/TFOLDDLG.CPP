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
**  TFolderDlg Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TFolderDlg                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFOLDDLG.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TScrollBar
#define Uses_TEvent
#define Uses_TKeys
#define Uses_MsgBox
#include "TFoldDlg.H"
#include "tvFolder.H"
#include "TBtnBar.H"
#include "TObjLBox.H"
#include "HelpCtx.H"


TFolderDlg::TFolderDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TFolderDlg::initFrame ),
	TObjDlg( bounds, anOwner ),
	listBox( 0 )
	{}


void TFolderDlg::setState( ushort aState, Boolean enable )
{
	TObjDlg::setState( aState, enable );
	if( (aState & sfVisible) && enable )
		listBox->select();
}


void TFolderDlg::handleEvent( TEvent& event )
{
	static Boolean objMove = False;
	static ushort oldHelpCtx;

	switch( event.what )
		{
		case evKeyboard:
			if( (event.keyDown.keyCode == kbEnter) ||
				(event.keyDown.keyCode == kbGrayPlus) )
				{
				if( !objMove )
					{
					((tvFolder *)owner)->editObject();
					listBox->select();
					}
				else
					{
					objMove = False;
					helpCtx = oldHelpCtx;
					actionBar->disable( False );
					buttonBar->disable( False );
					redraw();
					((tvFolder *)owner)->endMoveObject();
					}

				clearEvent( event );
				return;
				}

		case evCommand:
			if( (event.message.command == cmClose) && objMove )
				{
				clearEvent( event );
				return;
				}
			break;
		}

	TObjDlg::handleEvent( event );
	if( event.what == evCommand )
		{
		switch( event.message.command )
			{
			case cmInsert:
				((tvFolder *)owner)->insertObject( 0 );
				clearEvent( event );
				break;

			case cmEdit:
				((tvFolder *)owner)->editObject();
				clearEvent( event );
				break;

			case cmMove:
				if( ((tvFolder *)owner)->startMoveObject() )
					{
					objMove = True;
					oldHelpCtx = helpCtx;
					helpCtx = hcMovingObject;
					actionBar->disable( True );
					buttonBar->disable( True );
					redraw();
					}
				clearEvent( event );
				break;

			case cmDelete:
				if( ((tvFolder *)owner)->isObjectDeletable() &&
					(messageBox(
						"Soll dieses Objekt wirklich gel”scht werden?",
						mfConfirmation | mfYesButton | mfNoButton ) ==
						cmYes) )
					((tvFolder *)owner)->deleteObject();
				clearEvent( event );
				break;
			}
		listBox->select();
		}
}


void TFolderDlg::setupDialog()
{
	addTitleLine( 2 );
	TScrollBar *sb;
	sb = createScrollBar();
	insert( listBox = createListBox( sb ) );
	insert( sb );
	actionBar = createActionBar();
	setupActionBar();

	TStdDlg::setupDialog();
}


TListBox *TFolderDlg::createListBox( TScrollBar *scrollBar )
{
	TRect lb = getAreaByPos( 5, -8 );
	return( new TObjListBox( lb, scrollBar ) );
}


TScrollBar *TFolderDlg::createScrollBar()
{
	TRect sb = getAreaByPos( 5, -8 );
	sb.a.x = sb.b.x - 1;
	return( new TScrollBar( sb ) );
}


TButtonBar *TFolderDlg::createActionBar()
{
	TRect r = getAreaByLen( -7, 4, 2 );
	return( new TButtonBar( this, r ) );
}


void TFolderDlg::setupActionBar()
{
	int objectActions = ((tvFolder *)owner)->getObjectActions();
	if( objectActions & oaNew )
		addNewButton();

	if( objectActions & oaEdit )
		addEditButton();

	if( objectActions & oaMove )
		addMoveButton();

	if( objectActions & oaDelete )
		addDeleteButton();
}


void TFolderDlg::addNewButton()
{
	actionBar->insert( new TButton( TRect( 0, 0, 7, 2 ), "~N~eu",
									cmInsert, bfNormal ) );
}


void TFolderDlg::addEditButton()
{
	actionBar->insert( new TButton( TRect( 0, 0, 10, 2 ), "™~f~fnen",
									cmEdit, bfNormal ) );
}


void TFolderDlg::addMoveButton()
{
	actionBar->insert( new TButton( TRect( 0, 0, 11, 2 ), "~V~ersch.",
									cmMove, bfNormal ) );

}


void TFolderDlg::addDeleteButton()
{
	actionBar->insert( new TButton( TRect( 0, 0, 11, 2 ), "~L~”schen",
									cmDelete, bfNormal ) );
}


void TFolderDlg::setupButtons()
{
	addCloseButton( True );
//	addUndoButton( False );
}
