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

#define Uses_TLabel
#define Uses_TScrollBar
#define Uses_TStaticText
#include "TFldDlg.H"
#include "TNotCtrl.H"
#include "TNInputL.H"
#include "TObjLBox.H"
#include "TObjColl.H"
#include "TLBCol.H"
#include "tvFolder.H"
#include "tvProj.H"
#include "tvDGMain.H"
#include "TCard.H"

#include <String.H>


TFieldDlg::TFieldDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TFieldDlg::initFrame ),
	TObjDlg( bounds, anOwner )
{
	for( int i1 = 0; i1 < 2; i1++ )
		for( int i2 = 0; i2 < numDistinctKeys; i2++ )
			{
			keyLines[i1][i2].keySel = 0;
			keyLines[i1][i2].timesLine = 0;
			}

}


void TFieldDlg::setupDialog()
{
	TObjDlg::setupDialog();

	addFieldControls();

	insert( new TStaticText( TRect( 4, 9, 8, 10 ), "Anz." ) );
	insert( new TStaticText( TRect( 12, 9, 17, 10 ), "Taste" ) );

	TPoint p;
	p.x = 3; p.y = 10;
	for( int i = 0; i < 3; i++, p.y++ )
		addKeyLine( &keyLines[Before][i], p );

	TRect line = getAreaByLen( 13, 1 );

	int lineLength = line.b.x - line.a.x;
	char *lineString = new char[lineLength + 1];
	memset( lineString, 'Ä', lineLength );
	lineString[lineLength] = 0;

	insert( new TStaticText( line, lineString ) );
	delete[] lineString;

	p.x = 3; p.y = 14;
	for( i = 0; i < 3; i++, p.y++ )
		addKeyLine( &keyLines[After][i], p );

	insert( new TLabel( TRect( 12, 13, 21, 14 ), " ~V~or ",
						keyLines[Before][0].keySel ) );

	insert( new TLabel( TRect( 29, 13, 39, 14 ), " ~N~ach ",
						keyLines[After][0].keySel ) );

//	insert( new TLabel( TRect( 12, 14, 19, 15 ), " ~v~or",
//						keyLines[Before][0].keySel ) );
//
//	insert( new TLabel( TRect( 31, 14, 39, 15 ), " ~n~ach",
//						keyLines[After][0].keySel ) );
}


void TFieldDlg::addDataFieldSelection( TListBox **sel, char *label, int y )
{
	TCard *card = ((tvDGMainFolder *)mainFolder)->getCard();

	TRect fs = getAreaByLen( y, 1 );
	fs.a.x += strlen( label ) + 1;
	fs.b.x = fs.a.x + 24;

	TScrollBar *SB = new TScrollBar( fs );
	insert( SB );

	fs.a.x++; fs.b.x--;

	insert( *sel = new TNListBox( fs, 1, SB ) );
	(*sel)->newList( card );

	fs = getAreaByLen( y, 1 );
	fs.b.x = fs.a.x + strlen( label ) + 1;
	fs.a.x--;
	insert( new TLabel( fs, label, *sel ) );
}


void TFieldDlg::addKeyLine( KeyLine *keyLine, TPoint p )
{
	TRect tl;
	tl.a = p;
	tl.b.x = tl.a.x + 5;
	tl.b.y = tl.a.y + 1;

	insert( keyLine->timesLine = new TNNumericInputLine( tl, 3 ) );

	TRect ks = getAreaByLen( p.y, 1 );
	ks.a.x = tl.b.x + 2;

	tvFolder *keyFolder =
		((tvProject *)owner->folder->folder)->getKeyFolder();
	TObjCollection *objCol = keyFolder->getObjects();

	TScrollBar *SB = new TScrollBar( ks );
	insert( SB );

	ks.a.x++; ks.b.x--;

	insert( keyLine->keySel = new TObjListBox( ks, SB ) );
	keyLine->keySel->newList( (TCollection *)objCol );
}
