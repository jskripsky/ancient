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
**  TFormObjDlg Class                                                       **
**  -----------------                                                       **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TFormObjDlg													**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFOBJDLG.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TSItem
#define Uses_TLabel
#define Uses_TStaticText
#include "TFObjDlg.H"
#include "TNotCtrl.H"
#include "TNInputL.H"


#define FrameLength 26


TFormObjDlg::TFormObjDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TFormObjDlg::initFrame ),
	TObjDlg( bounds, anOwner ),
	fontSel( 0 ),
	fieldSel( 0 )
	{}


void TFormObjDlg::setupDialog()
{
	TObjDlg::setupDialog();
	TRect rlCopy;
	TRect rcCopy;

	TRect rl = getAreaByLen( 5, 1 );
	rl.a.x--;

	TRect rc = getAreaByLen( 6, 3 );
	rc.b.x = rc.a.x + FrameLength;

	char *frame = new char[3 * (FrameLength + 1)];
	memset( frame, ' ', 3 * (FrameLength + 1) - 1 );

	char left;
	char middle;
	char right;

	for( int i = 0; i < 3; i++ )
		{
		switch( i )
			{
			case 0:
				left   = 'Ú';
				middle = 'Ä';
				right  = '¿';
				break;

			case 1:
				left = right = '³';
				middle = ' ';
				break;

			case 2:
				left   = 'À';
				middle = 'Ä';
				right  = 'Ù';
				break;
			}
		frame[i * (FrameLength + 1) + 3] = left;
		memset( &frame[i * (FrameLength + 1) + 4], middle, FrameLength - 8 );
		frame[(i + 1) * (FrameLength + 1) - 5] = right;
		frame[(i + 1) * (FrameLength + 1) - 1] = '\n';
		}
	frame[3 * (FrameLength + 1) - 1] = 0;
	insert( new TStaticText( rc, frame ) );
	delete[] frame;

	rc = getAreaByLen( 7, 1 );
	rc.b.x = rc.a.x + 8;
	insert( leftPos = new TNNumericInputLine( rc, 6, 1 ) );
	insert( posLabel = new TLabel( rl, "Position", leftPos ) );

	rc.move( 9, -1 );
	insert( topPos = new TNNumericInputLine( rc, 6, 1 ) );

	rc.move( 9, 1 );
	insert( rightPos = new TNNumericInputLine( rc, 6, 1 ) );

	rc.move( -9, 1 );
	insert( bottomPos = new TNNumericInputLine( rc, 6, 1 ) );


}
