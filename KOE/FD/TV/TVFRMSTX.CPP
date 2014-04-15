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
**  tvFormStaticText Class                                                  **
**  ----------------------                                                  **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvFormStaticText                                              **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFRMSTX.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_TInputLine
#define Uses_TListBox
#include "tvFrmSTx.H"
#include "TFSTxDlg.H"
#include "EPSpace.H"
#include "FrmPrn.H"
#include "HelpCtx.H"

#include <DOS.H>
#include <String.H>


tvFormStaticText::tvFormStaticText( tvFolder *aFolder, const char *aTitle ) :
	tvFormObj( aFolder, aTitle ),
	tvFormText( aFolder, aTitle ),
	text( new char[81] )
{
	text[0] = 0;
}


tvFormStaticText::~tvFormStaticText()
{
	delete[] text;
}


void tvFormStaticText::tvOpen()
{
	tvFormText::tvOpen();
	tvFormObj::tvOpen();
}


void tvFormStaticText::tvDelete()
{
	tvFormText::tvDelete();
	tvFormObj::tvDelete();
}


Boolean tvFormStaticText::handleNotification( TView *view )
{
	if( tvFormObj::handleNotification( view ) ||
		tvFormText::handleNotification( view ) )
		return True;

	TFormObjDlg *dlg = (TFormObjDlg *)tvObject::dlg;

	if( (view == dlg->fontSel) || (view == dlg->textLine) )
		{
		if( view == dlg->fontSel )
			tvFormText::handleNotification( view );

		dlg->textLine->getData( text );
		Pos pos = EpsonPaperSpace::getTextMetrics( font, strlen( text ) );

		size = pos;

		tvFormObj::handleNotification( dlg->leftPos );
		tvFormObj::handleNotification( dlg->bottomPos );
		return True;
		}

	return False;
}


void tvFormStaticText::fillDlg()
{
	tvFormObj::fillDlg();
	tvFormText::fillDlg();

	TFormObjDlg *dlg = (TFormObjDlg *)tvObject::dlg;
	dlg->textLine->setData( text );

	handleNotification( dlg->fontSel );
}


TObjDlg *tvFormStaticText::createDlg()
{
	return( new TFormStaticTextDlg( TRect( 33, 1, 77, 22 ), this ) );
}


ushort tvFormStaticText::getHelpCtx()
	{ return  hcFormStaticText; }


void tvFormStaticText::write( FormDevice *formDevice )
{
	tvFormObj::write( formDevice );
	tvFormText::write( formDevice );

	((FormPrinter *)formDevice)->getPaperSpace()->writeText( text );

	formDevice->newLine();
}


const char *const near tvFormStaticText::name = "tvFormStaticText";

TStreamableClass RtvFormStaticText( tvFormStaticText::name,
									tvFormStaticText::build,
									__DELTA( tvFormStaticText )
								  );


tvFormStaticText::tvFormStaticText( StreamableInit ) :
	tvFormObj( streamableInit ),
	tvFormText( streamableInit ),
	text( new char[81] )
	{}


TStreamable *tvFormStaticText::build()
{
	return new tvFormStaticText( streamableInit );
}


void tvFormStaticText::write( opstream& os )
{
	tvFormObj::write( os );
	tvFormText::write( os );

	os << (int)0x0100;

	os.writeString( text );
}


void *tvFormStaticText::read( ipstream& is )
{
	tvFormObj::read( is );
	tvFormText::read( is );

	int version;
	is >> version;

	is.readString( text, 81 );

	return this;
}
