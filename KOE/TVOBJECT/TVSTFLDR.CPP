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
**  tvStaticTitleFolder Class                                               **
**  -------------------------                                               **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvStaticTitleFolder                                           **
**    - Class TSTFolderDlg                                                  **
**                                                                          **
**                                                                          **
**  Module Name: TVSTFLDR.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TScrollBar
#define Uses_TListBox
#define Uses_TStreamableClass
#include "tvSTFldr.H"
#include "TObjColl.H"


TObjDlg *tvStaticTitleFolder::createDlg()
{
	return( new TSTFolderDlg( TRect( 1, 1, 27, 22 ), this ) );
}



const char *const near tvStaticTitleFolder::name = "tvStaticTitleFolder";

TStreamableClass RtvStaticTitleFolder( tvStaticTitleFolder::name,
									   tvStaticTitleFolder::build,
									   __DELTA( tvStaticTitleFolder )
									 );


tvStaticTitleFolder::tvStaticTitleFolder( StreamableInit ) :
	tvFolder( streamableInit )
	{}


TStreamable *tvStaticTitleFolder::build()
{
	return new tvStaticTitleFolder( streamableInit );
}


void tvStaticTitleFolder::write( opstream& os )
{
	tvFolder::write( os );

	os << (int)0x0100;
}


void *tvStaticTitleFolder::read( ipstream& is )
{
	tvFolder::read( is );

	int version;
	is >> version;

	return this;
}


TListBox *TSTFolderDlg::createListBox( TScrollBar *sb )
{
	TListBox *lb = TFolderDlg::createListBox( sb );
	TRect tr = lb->getBounds();
	tr.a.y -= 3;
	lb->locate( tr );
	return lb;
}


TScrollBar *TSTFolderDlg::createScrollBar()
{
	TScrollBar *sb = TFolderDlg::createScrollBar();
	TRect tr = sb->getBounds();
	tr.a.y -= 3;
	sb->locate( tr );
	return sb;
}


void TSTFolderDlg::addTitleLine( int y )
{
	y;
}
