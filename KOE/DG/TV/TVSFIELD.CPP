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
**  tvSingleField Class                                                     **
**  -------------------                                                     **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvSingleField                                                 **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVSFIELD.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_TInputLine
#define Uses_TListBox
#define Uses_TCheckBoxes
#define Uses_MsgBox
#include "tvSField.H"
#include "TSFldDlg.H"
#include "HelpCtx.H"
#include "TObjColl.H"
#include "FormDlg.H"
#include "TCard.H"


// -----------------------
// Basic tvObject Protocol
// -----------------------

tvSingleField::tvSingleField( tvFolder *aFolder ) :
	tvField( aFolder, "Einfaches Feld" ),
	dataField( 0 ),
	start( 0 ),
	end( 0 ),
	numeric( False )
{
}


// ---------------
// Dialog Protocol
// ---------------

Boolean tvSingleField::handleNotification( TView *view )
{
	if( tvField::handleNotification( view ) )
		return True;

	TSingleFieldDlg *dlg = (TSingleFieldDlg *)tvObject::dlg;

	if( view == dlg->dataFieldSel )
		{
		int oldDataField = dataField;
		view->getData( &dataField );

		if( (dataField != oldDataField) || init )
			{
			cardField = (CardField *)card->at( dataField );
			int length = cardField->length;

			dlg->endLine->setData( &length );
			start = 1;
			dlg->startLine->setData( &start );

			handleNotification( dlg->startLine );
			handleNotification( dlg->endLine );

			init = False;
			}
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
		end--;
		return True;
		}

	if( view == dlg->numericBox )
		{
		view->getData( &numeric );
		return True;
		}


	return False;
}


void tvSingleField::fillDlg()
{
	tvField::fillDlg();
	TSingleFieldDlg *dlg = (TSingleFieldDlg *)tvObject::dlg;

	dlg->dataFieldSel->setData( &dataField );

	start++;
	dlg->startLine->setData( &start );
	start--;

	end++;
	dlg->endLine->setData( &end );
	end--;

	dlg->numericBox->setData( &numeric );

	handleNotification( dlg->dataFieldSel );
}


TObjDlg *tvSingleField::createDlg()
{
	return( new TSingleFieldDlg( TRect( 33, 1, 77, 22 ), this ) );
}


ushort tvSingleField::getHelpCtx()
	{ return hcSingleField; }


void tvSingleField::writeDataField( FormDevice *formDevice )
{
	cardField = (CardField *)card->at( dataField );
	int fieldTag = cardField->tag;

	if( !numeric )
		((FormDialog *)formDevice)->sendField(
			fieldTag, start + 1, end + 1 );
	else
		((FormDialog *)formDevice)->sendNumericField(
			fieldTag, start + 1, end + 1 );
}



// --------------------
// TStreamable Protocol
// --------------------

const char *const near tvSingleField::name = "tvSingleField";

TStreamableClass RtvSingleField( tvSingleField::name,
								 tvSingleField::build,
								 __DELTA( tvSingleField )
								 );


tvSingleField::tvSingleField( StreamableInit ) :
	tvField( streamableInit )
	{}


TStreamable *tvSingleField::build()
{
	return new tvSingleField( streamableInit );
}


void tvSingleField::write( opstream& os )
{
	tvField::write( os );

	os << (int)0x0100;

	os << dataField;
	os << start << end;
	os << (int)numeric;
}


void *tvSingleField::read( ipstream& is )
{
	tvField::read( is );

	int version;
	is >> version;

	is >> dataField;
	is >> start >> end;
	is >> (int)numeric;

	return this;
}
