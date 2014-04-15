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
**  TFieldDlg Class                                                         **
**  ---------------                                                         **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TFieldDlg                                                     **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFLDDLG.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TSItem
#define Uses_TLabel
#include "TFldDlg.H"
#include "TNotCtrl.H"
#include "TNInputL.H"


TFieldDlg::TFieldDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TObjDlg::initFrame ),
	TObjDlg( bounds, anOwner )
	{}


void TFieldDlg::setupDialog()
{
	TObjDlg::setupDialog();
	TRect rlCopy;
	TRect rcCopy;

	TRect rl( 2, 5, 12, 6 );
	TRect rc = rl;

	rc.move( 10, 0 );
	rc.b.x = rc.a.x + 6;
	rc.a.x++;
	insert( length = new TNNumericInputLine( rc, 3 ) );
	insert( lengthLabel = new TLabel( rl, "L„nge", length ) );
	rc.a.x--;

	rc.move( 0, 1 );
	rl.move( 0, 1 );
	insert( offset = new TNNumericInputLine( rc, 4 ) );
	insert( offsetLabel = new TLabel( rl, "Offset", offset ) );

	rcCopy = rc;
	rlCopy = rl;

	rc.move( 10, -1 );
	rc.b.x = rc.a.x + 15;
	insert( dumpable = new TNCheckBoxes( rc, new TSItem( "Unbenutzt", 0 ) ) );

	rl.move( 0, 2 );
	rl.b.x = rl.a.x + 20;
	rc = rl;
	rc.move( 1, 1 );
	rc.b.x = rc.a.x + 18;
	rc.b.y++;
	insert( posSel = new TNRadioButtons( rc,
							new TSItem( "Automatisch",
							new TSItem( "Benutzerwahl", 0 )) ) );
	insert( posSelLabel = new TLabel( rl, "Positionsauswahl", posSel ) );

	rcCopy.move( 22, 3 );
	rlCopy.move( 22, 3 );
	insert( track = new TNNumericInputLine( rcCopy, 4 ) );
	insert( trackLabel = new TLabel( rlCopy, "Spur", track ) );

	rcCopy.move( 0, 1 );
	rlCopy.move( 0, 1 );
	insert( pos = new TNNumericInputLine( rcCopy, 4 ) );
	insert( posLabel = new TLabel( rlCopy, "Position", pos ) );

	rc.move( 0, 4 );
	rc.b.y++;
	rc.b.x = rc.a.x + 25;
	rl.move( 0, 4 );
	insert( restr = new TNRadioButtons( rc,
						new TSItem( "keine",
						new TSItem( "Magnetspuren",
								new TSItem( "Anzeige-/Magnetspur", 0 ))) ) );
	insert( restrLabel = new TLabel( rl, "Einschr„nkung", restr ) );
}


void TFieldDlg::disablePosSel( Boolean disable )
{
	posSelLabel->setState( sfDisabled, disable );
	posSel->setState( sfDisabled, disable );
}


void TFieldDlg::disableTrackPos( Boolean disable )
{
	trackLabel->setState( sfDisabled, disable );
	track->setState( sfDisabled, disable );
	posLabel->setState( sfDisabled, disable );
	pos->setState( sfDisabled, disable );
}


void TFieldDlg::disableRestr( Boolean disable )
{
	restrLabel->setState( sfDisabled, disable );
	restr->setState( sfDisabled, disable );
}
