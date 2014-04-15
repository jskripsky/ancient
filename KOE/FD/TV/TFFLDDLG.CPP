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
**  TFormFieldDlg Class                                                     **
**  -------------------                                                     **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TFormFieldDlg												    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFFLDDLG.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TLabel
#define Uses_TScrollBar

#include "TFFldDlg.H"
#include "TNotCtrl.H"
#include "TObjColl.H"
#include "TObjLBox.H"
#include "tvFolder.H"
#include "tvProj.H"


TFormFieldDlg::TFormFieldDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TFormObjDlg::initFrame ),
	TFormObjDlg( bounds, anOwner )
	{}


void TFormFieldDlg::setupDialog()
{
	addFieldSelection( 10 );
}


void TFormFieldDlg::addFieldSelection( int y )
{
	tvFolder *fieldsFolder =
		((tvProject *)(owner->folder->folder))->getFieldsFolder();
	TObjCollection *objCol = fieldsFolder->getObjects();

	TRect fsRect = getAreaByLen( y, 1 );
	fsRect.a.x += 8;
	fsRect.b.x = fsRect.a.x + 20;

	TScrollBar *SB = new TScrollBar( fsRect );
	insert( SB );

	fsRect = getAreaByLen( y, 1 );
	fsRect.a.x += 9;
	fsRect.b.x = fsRect.a.x + 18;

	insert( fieldSel = new TObjListBox( fsRect, SB ) );
	fieldSel->newList( objCol );

	fsRect = getAreaByLen( y, 1 );
	fsRect.b.x = fsRect.a.x + 7;
	fsRect.a.x--;
	insert( new TLabel( fsRect, "Feld", fieldSel ) );
}
