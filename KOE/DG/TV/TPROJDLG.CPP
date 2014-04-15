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
**  TProjectDlg Class                                                       **
**  -----------------                                                       **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TProjectDlg                                                   **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TPROJDLG.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TEvent
#define Uses_TListBox
#define Uses_TButton
#include "TProjDlg.H"
#include "TBtnBar.H"
#include "tvProj.h"


#define cmGenerateFile 120


TProjectDlg::TProjectDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TProjectDlg::initFrame ),
	TFolderDlg( bounds, anOwner )
	{}


void TProjectDlg::handleEvent( TEvent& event )
{
	TFolderDlg::handleEvent( event );
	if( event.what == evCommand )
		{
		switch( event.message.command )
			{
			case cmGenerateFile:
				((tvProject *)owner)->write();
				clearEvent( event );
				break;
			}
		listBox->select();
		}
}


void TProjectDlg::setupButtons()
{
	addGenerateFileButton();
	addCloseButton( False );
}


void TProjectDlg::addGenerateFileButton()
{
	buttonBar->insert( new TButton( TRect( 0, 0, 12, 2 ), "~D~ownload",
									cmGenerateFile, bfNormal ) );
}
