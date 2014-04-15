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
**  tvFormTextField Class                                                   **
**  ---------------------                                                   **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvFormTextField                                               **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFRMTF.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_TListBox
#define Uses_TInputLine
#include "tvFrmTF.H"
#include "TFTFDlg.H"
#include "tvField.H"
#include "FrmSpace.H"
#include "FrmPrn.H"
#include "HelpCtx.H"


tvFormTextField::tvFormTextField( tvFolder *aFolder, const char *aTitle ) :
	tvFormObj( aFolder, aTitle ),
	tvFormField( aFolder, aTitle ),
	tvFormText( aFolder, aTitle )
	{}


void tvFormTextField::tvOpen()
{
	tvFormObj::tvOpen();
	tvFormText::tvOpen();
	tvFormField::tvOpen();
}


Boolean tvFormTextField::tvClose()
{
	if( tvFormObj::tvClose() &&
		tvFormText::tvClose() &&
		tvFormField::tvClose() )
		return True;
	else
		return False;
}


void tvFormTextField::tvDelete()
{
	tvFormText::tvDelete();
	tvFormField::tvDelete();
	tvFormObj::tvDelete();
}


Boolean tvFormTextField::handleNotification( TView *view )
{
	Boolean result = False;

	if( tvFormObj::handleNotification( view ) ||
		tvFormField::handleNotification( view ) ||
		tvFormText::handleNotification( view ) )
		result = True;

	TFormObjDlg *dlg = (TFormObjDlg *)tvObject::dlg;
	if( (view == dlg->fontSel) || (view == dlg->fieldSel) )
		{
		int length;
		if( !field )
			length = 0;
		else
			length =
				((tvField *)tvObject::getObject( field ))->getRealLength();

		Pos pos = EpsonPaperSpace::getTextMetrics( font, length );

		size = pos;

		tvFormObj::handleNotification( dlg->leftPos );
		tvFormObj::handleNotification( dlg->bottomPos );
		return True;
		}

	return result;
}


void tvFormTextField::fillDlg()
{
	tvFormObj::fillDlg();
	tvFormField::fillDlg();
	tvFormText::fillDlg();

	TFormObjDlg *dlg = (TFormObjDlg *)tvObject::dlg;
	handleNotification( dlg->fontSel );
}


TObjDlg *tvFormTextField::createDlg()
{
	return( new TFormTextFieldDlg( TRect( 33, 1, 77, 22 ), this ) );
}


ushort tvFormTextField::getHelpCtx()
	{ return  hcFormTextField; }


void tvFormTextField::write( FormDevice *formDevice )
{
	if( !field )
		return;

	tvFormObj::write( formDevice );
	tvFormText::write( formDevice );

	FormSpace *formSpace =
		(FormSpace *)((FormPrinter *)formDevice)->getPaperSpace();

	formSpace->printTextField(
		((tvField *)TUnique::getObject( field ))->getIndex() );

	formDevice->newLine();
}


const char *const near tvFormTextField::name = "tvFormTextField";

TStreamableClass RtvFormTextField( tvFormTextField::name,
								   tvFormTextField::build,
								   __DELTA( tvFormTextField )
								 );


tvFormTextField::tvFormTextField( StreamableInit ) :
	tvFormObj( streamableInit ),
	tvFormField( streamableInit ),
	tvFormText( streamableInit )
	{}


TStreamable *tvFormTextField::build()
{
	return new tvFormTextField( streamableInit );
}


void tvFormTextField::write( opstream& os )
{
	tvFormObj::write( os );
	tvFormField::write( os );
	tvFormText::write( os );

	os << (int)0x0100;

}


void *tvFormTextField::read( ipstream& is )
{
	tvFormObj::read( is );
	tvFormField::read( is );
	tvFormText::read( is );

	int version;
	is >> version;

	return this;
}
