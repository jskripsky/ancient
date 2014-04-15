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
**  TSingle-, TDoubleFieldDlg Classes                                       **
**  ---------------------------------                                       **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TSingleFieldDlg                                               **
**    - Class TDoubleFieldDlg                                               **
**                                                                          **
**                                                                          **
**  Module Name: TSFLDDLG.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TSItem
#define Uses_TLabel
#include "TSFldDlg.H"
#include "TNotCtrl.H"
#include "TNInputL.H"



TSingleFieldDlg::TSingleFieldDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TSingleFieldDlg::initFrame ),
	TFieldDlg( bounds, anOwner )
	{}


void TSingleFieldDlg::addFieldControls()
{
	addDataFieldSelection( &dataFieldSel, "Feld", 5 );

	insert( startLine =
		new TNNumericInputLine( TRect( 7, 7, 12, 8 ), 3 ) );
	insert( new TLabel( TRect( 2, 7, 6, 8 ), "Von", startLine ) );

	insert( endLine =
		new TNNumericInputLine( TRect( 18, 7, 23, 8 ), 3 ) );

	insert( new TLabel( TRect( 13, 7, 17, 8 ), "bis", endLine ) );

	insert( numericBox =
		new TNCheckBoxes( TRect( 25, 7, 41, 8 ),
						  new TSItem( "Numerisch", 0 ) ) );
}


TDoubleFieldDlg::TDoubleFieldDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TDoubleFieldDlg::initFrame ),
	TFieldDlg( bounds, anOwner )
	{}


void TDoubleFieldDlg::addFieldControls()
{
	addDataFieldSelection( &dataFieldSel[0], "Feld 1", 5 );
	addDataFieldSelection( &dataFieldSel[1], "Feld 2", 6 );

	insert( lengthLine =
		new TNNumericInputLine( TRect( 15, 7, 20, 8 ), 3 ) );

	insert( new TLabel( TRect( 2, 7, 15, 8 ), "Gesamtl„nge", lengthLine ) );
}
