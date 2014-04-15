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
**  tvFormText Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvFormText                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFRMTXT.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TListBox
#include "tvFrmTxt.H"
#include "TFTxtDlg.H"
#include "FrmPrn.H"
#include "PSpace.H"


tvFormText::tvFormText( tvFolder *aFolder, const char *aTitle ) :
	tvFormObj( aFolder, aTitle ),
	font( 0 )
	{}


Boolean tvFormText::handleNotification( TView *view )
{
	if( tvFormObj::handleNotification( view ) )
		return True;

	TFormObjDlg *dlg = (TFormObjDlg *)tvObject::dlg;
	if( view == dlg->fontSel )
		{
		view->getData( &font );
		return True;
		}

	return False;
}


void tvFormText::fillDlg()
{
	TFormObjDlg *dlg = (TFormObjDlg *)tvObject::dlg;
	dlg->fontSel->setData( &font );
}


TObjDlg *tvFormText::createDlg()
{
	return( new TFormTextDlg( TRect( 33, 1, 77, 22 ), this ) );
}


void tvFormText::write( FormDevice *formDevice )
{
	((FormPrinter *)formDevice)->getPaperSpace()->setFont( font );
}


tvFormText::tvFormText( StreamableInit ) :
	tvFormObj( streamableInit )
	{}


void tvFormText::write( opstream& os )
{
	os << (int)0x0100;

	os << font;
}


void *tvFormText::read( ipstream& is )
{
	int version;
	is >> version;

	is >> font;

	return this;
}
