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
**  TObjDlg Class                                                           **
**  -------------                                                           **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TObjDlg                                                       **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TOBJDLG.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TInputLine
#define Uses_TLabel
#include "TObjDlg.H"
#include "tvObject.H"
#include "TNotCtrl.H"


TObjDlg::TObjDlg( const TRect& bounds, tvObject *anOwner ) :
	TWindowInit( &TObjDlg::initFrame ),
	TStdDlg( bounds ),
	owner( anOwner ),
	titleLine( 0 )
	{}


void TObjDlg::handleNotification( TView *view )
{
	if( view == this )
		{
		TView *v = first();
		do
			{
			if( v->dataSize() > 0 )
				owner->handleNotification( v );

			v = v->nextView();
			}
		while( v );
		}
	else
		owner->handleNotification( view );
}


void TObjDlg::undo()
{
	owner->undoDlg();
}


void TObjDlg::close()
{
	owner->tvClose();
}


void TObjDlg::setupDialog()
{
	addTitleLine( 2 );
	TStdDlg::setupDialog();
}


void TObjDlg::addTitleLine( int y )
{
	TRect tlRect = getAreaByLen( y + 1, 1 );
	int lineLength = tlRect.b.x - tlRect.a.x;
	if( lineLength > maxTitleLength + 3 )
		tlRect.b.x -= lineLength - (maxTitleLength + 3);

	titleLine = new TNInputLine( tlRect, maxTitleLength + 1 );
	insert( titleLine );

	tlRect = getAreaByLen( y, 1 );
	tlRect.a.x--;
	insert( new TLabel( tlRect, "~T~itel", titleLine ) );
}
