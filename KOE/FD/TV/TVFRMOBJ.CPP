/*****************************************************************************
**                                                                          **
**                                                                          **
**  Form Designer                                                           **
**  =============                                                           **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  tvFormObj Class                                                         **
**  ---------------                                                         **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvFormObj                                                     **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFRMOBJ.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TInputLine
#include "tvFrmObj.H"
#include "TFObjDlg.H"
#include "FrmPrn.H"
#include "PSpace.H"


tvFormObj::tvFormObj( tvFolder *aFolder, const char *aTitle ) :
	tvObject( aFolder, aTitle )
{
	pos.x = pos.y = 0;
	size.x = size.y = 0;
}


Boolean tvFormObj::handleNotification( TView *view )
{
	if( tvObject::handleNotification( view ) )
		return True;

	TFormObjDlg *dlg = (TFormObjDlg *)tvObject::dlg;
	int temp;
	if( view == dlg->leftPos )
		{
		view->getData( &(pos.x) );
		temp = pos.x + size.x;
		dlg->rightPos->setData( &temp );
		dlg->rightPos->drawView();
		return True;
		}

	if( view == dlg->bottomPos )
		{
		view->getData( &(pos.y) );
		temp = pos.y - size.y;
		dlg->topPos->setData( &temp );
		dlg->topPos->drawView();
		return True;
		}

	if( view == dlg->rightPos )
		{
		view->getData( &temp );
		temp -= size.x;
		pos.x = temp;
		dlg->leftPos->setData( &temp );
		dlg->leftPos->drawView();
		return True;
		}

	if( view == dlg->topPos )
		{
		view->getData( &temp );
		temp += size.y;
		pos.y = temp;
		dlg->bottomPos->setData( &temp );
		dlg->bottomPos->drawView();
		return True;
		}

	return False;
}


void tvFormObj::fillDlg()
{
	tvObject::fillDlg();

	TFormObjDlg *dlg = (TFormObjDlg *)tvFormObj::dlg;
	dlg->leftPos->setData( &(pos.x) );
	dlg->bottomPos->setData( &(pos.y) );

	handleNotification( dlg->leftPos );
	handleNotification( dlg->bottomPos );
}


int tvFormObj::compareWith( tvObject& obj )
{
	tvFormObj *formObj = (tvFormObj *)&obj;
	int yDelta = (pos.y - size.y) - (formObj->pos.y - formObj->size.y);
	if( yDelta != 0 )
		return yDelta;
	else
		return (pos.x - formObj->pos.x);
}


TObjDlg *tvFormObj::createDlg()
{
	return( new TFormObjDlg( TRect( 33, 1, 77, 22 ), this ) );
}


void tvFormObj::write( FormDevice *formDevice )
{
	((FormPrinter *)formDevice)->getPaperSpace()->moveTo( pos );
}


tvFormObj::tvFormObj( StreamableInit ) :
	tvObject( streamableInit )
	{}


void tvFormObj::write( opstream& os )
{
	tvObject::write( os );

	os << (int)0x0100;

	os << pos.x;
	os << pos.y;
	os << size.x;
	os << size.y;
}


void *tvFormObj::read( ipstream& is )
{
	tvObject::read( is );

	int version;
	is >> version;

	is >> pos.x;
	is >> pos.y;
	is >> size.x;
	is >> size.y;

	return this;
}
