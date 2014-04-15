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
**  tvDoubleField Class                                                     **
**  -------------------                                                     **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvDoubleField                                                 **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVDFIELD.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_TInputLine
#define Uses_TListBox
#define Uses_MsgBox
#include "tvDField.H"
#include "TSFldDlg.H"
#include "HelpCtx.H"
#include "TObjColl.H"
#include "FormDlg.H"
#include "TCard.H"


// -----------------------
// Basic tvObject Protocol
// -----------------------

tvDoubleField::tvDoubleField( tvFolder *aFolder ) :
	tvField( aFolder, "Doppeltes Feld" ),
	maxLength( 1 )
{
	dataFields[0] = dataFields[1] = 0;
}


// ---------------
// Dialog Protocol
// ---------------

Boolean tvDoubleField::handleNotification( TView *view )
{
	if( tvField::handleNotification( view ) )
		return True;

	TDoubleFieldDlg *dlg = (TDoubleFieldDlg *)tvObject::dlg;

	if( (view == dlg->dataFieldSel[0]) ||
		(view == dlg->dataFieldSel[1]) )
		{
		int oldDataFields[2];
		oldDataFields[0] = dataFields[0];
		oldDataFields[1] = dataFields[1];

		dlg->dataFieldSel[0]->getData( &dataFields[0] );
		dlg->dataFieldSel[1]->getData( &dataFields[1] );

		if( (dataFields[0] != oldDataFields[0]) ||
			(dataFields[1] != oldDataFields[1]) || init )
			{
			cardFields[0] = (CardField *)card->at( dataFields[0] );
			cardFields[1] = (CardField *)card->at( dataFields[1] );
			int maxLength = cardFields[0]->length + cardFields[1]->length;

			dlg->lengthLine->setData( &maxLength );

			handleNotification( dlg->lengthLine );
			init = False;
			}
		return True;
		}

	if( view == dlg->lengthLine )
		{
		view->getData( &maxLength );
		return True;
		}

	return False;
}


void tvDoubleField::fillDlg()
{
	tvField::fillDlg();
	TDoubleFieldDlg *dlg = (TDoubleFieldDlg *)tvObject::dlg;

	dlg->dataFieldSel[0]->setData( &dataFields[0] );
	dlg->dataFieldSel[1]->setData( &dataFields[1] );

	dlg->lengthLine->setData( &maxLength );

	handleNotification( dlg->dataFieldSel[0] );
}


TObjDlg *tvDoubleField::createDlg()
{
	return( new TDoubleFieldDlg( TRect( 33, 1, 77, 22 ), this ) );
}


ushort tvDoubleField::getHelpCtx()
	{ return hcDoubleField; }


void tvDoubleField::writeDataField( FormDevice *formDevice )
{
	cardFields[0] = (CardField *)card->at( dataFields[0] );
	cardFields[1] = (CardField *)card->at( dataFields[1] );

	int fieldTag[2];
	fieldTag[0] = cardFields[0]->tag;
	fieldTag[1] = cardFields[1]->tag;

	((FormDialog *)formDevice)->sendCompoundField(
		fieldTag[0], fieldTag[1], maxLength );
}


// --------------------
// TStreamable Protocol
// --------------------

const char *const near tvDoubleField::name = "tvDoubleField";

TStreamableClass RtvDoubleField( tvDoubleField::name,
								 tvDoubleField::build,
								 __DELTA( tvDoubleField )
								 );


tvDoubleField::tvDoubleField( StreamableInit ) :
	tvField( streamableInit )
	{}


TStreamable *tvDoubleField::build()
{
	return new tvDoubleField( streamableInit );
}


void tvDoubleField::write( opstream& os )
{
	tvField::write( os );

	os << (int)0x0100;

	os << dataFields[0] << dataFields[1];
	os << maxLength;
}


void *tvDoubleField::read( ipstream& is )
{
	tvField::read( is );

	int version;
	is >> version;

	is >> dataFields[0] >> dataFields[1];
	is >> maxLength;

	return this;
}
