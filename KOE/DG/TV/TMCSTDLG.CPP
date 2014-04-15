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
**  TMCRSettingsDlg Class                                                   **
**  ---------------------                                                   **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TMCRSettingsDlg											 	**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TMCSTDLG.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TLabel
#define Uses_TSItem
#include "TMCSTDlg.H"
#include "TNotCtrl.H"


TMCRSettingsDlg::TMCRSettingsDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TMCRSettingsDlg::initFrame ),
	TStaticTitleObjDlg( bounds, anOwner )
	{}


void TMCRSettingsDlg::setupDialog()
{
	TStaticTitleObjDlg::setupDialog();

	insert( typeSwitch = new TNRadioButtons( TRect( 3, 3, 18, 9 ),
		new TSItem( "Spur 1",
		new TSItem( "Spur 2",
		new TSItem( "Spur 3",
		new TSItem( "Spur 12",
		new TSItem( "Spur 23",
		new TSItem( "Spur 123", 0 )))))) ) );

	insert( new TLabel( TRect( 2, 2, 19, 3 ), "Magnetlesertype",
						typeSwitch ) );

	insert( trackSwitches = new TNCheckBoxes( TRect( 3, 12, 16, 15 ),
		new TSItem( "Spur 1",
		new TSItem( "Spur 2",
		new TSItem( "Spur 3", 0 ))) ) );

	insert( new TLabel( TRect( 2, 11, 28, 12 ), "Magnetspuren einschalten",
						trackSwitches ) );
}
