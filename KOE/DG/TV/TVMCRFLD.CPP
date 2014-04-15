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
**  tvMCReaderField Class                                                   **
**  ---------------------                                                   **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvMCReaderField                                               **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVMCRFLD.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_TInputLine
#define Uses_TRadioButtons
#define Uses_TCheckBoxes
#define Uses_MsgBox
#include "tvMCRFld.H"
#include "TMCRFDlg.H"
#include "HelpCtx.H"
#include "TObjColl.H"
#include "FormDlg.H"
#include "TCard.H"


// -----------------------
// Basic tvObject Protocol
// -----------------------

tvMCReaderField::tvMCReaderField( tvFolder *aFolder ) :
	tvField( aFolder, "Feld" ),
	track( 0 ),
	start( 0 ),
	end( 0 )
{
}


// ---------------
// Dialog Protocol
// ---------------

Boolean tvMCReaderField::handleNotification( TView *view )
{
	if( tvField::handleNotification( view ) )
		return True;

	TMCReaderFieldDlg *dlg = (TMCReaderFieldDlg *)tvObject::dlg;

	if( view == dlg->trackSel )
		{
		view->getData( &track );
		return True;
		}

	if( view == dlg->startLine )
		{
		view->getData( &start );
		start--;
		return True;
		}

	if( view == dlg->endLine )
		{
		view->getData( &end );
		if( end > 150 )
			{
			end = 150;
			view->setData( &end );
			}
		end--;

		return True;
		}

	return False;
}


void tvMCReaderField::fillDlg()
{
	tvField::fillDlg();
	TMCReaderFieldDlg *dlg = (TMCReaderFieldDlg *)tvObject::dlg;

	dlg->trackSel->setData( &track );

	start++;
	dlg->startLine->setData( &start );
	start--;

	end++;
	dlg->endLine->setData( &end );
	end--;

	handleNotification( dlg->trackSel );
}


TObjDlg *tvMCReaderField::createDlg()
{
	return( new TMCReaderFieldDlg( TRect( 33, 1, 77, 22 ), this ) );
}


ushort tvMCReaderField::getHelpCtx()
	{ return hcMCReaderField; }


void tvMCReaderField::writeDataField( FormDevice *formDevice )
{
	((FormDialog *)formDevice)->sendMCReaderField(
		track + 1, start + 1, end + 1 );
}


// --------------------
// TStreamable Protocol
// --------------------

const char *const near tvMCReaderField::name = "tvMCReaderField";

TStreamableClass RtvMCReaderField( tvMCReaderField::name,
								   tvMCReaderField::build,
								   __DELTA( tvMCReaderField )
								 );


tvMCReaderField::tvMCReaderField( StreamableInit ) :
	tvField( streamableInit )
	{}


TStreamable *tvMCReaderField::build()
{
	return new tvMCReaderField( streamableInit );
}


void tvMCReaderField::write( opstream& os )
{
	tvField::write( os );

	os << (int)0x0100;

	os << track;
	os << start << end;
}


void *tvMCReaderField::read( ipstream& is )
{
	tvField::read( is );

	int version;
	is >> version;

	is >> track;
	is >> start >> end;

	return this;
}
