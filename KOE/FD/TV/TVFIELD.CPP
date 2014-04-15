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
**  tvField Class                                                           **
**  -------------                                                           **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvField                                                       **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFIELD.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_TInputLine
#define Uses_TCheckBoxes
#define Uses_TRadioButtons
#define Uses_MsgBox
#include "tvField.H"
#include "TFldDlg.H"
#include "HelpCtx.H"
#include "tvFldFld.H"
#include "TrackTab.H"
#include "FrmPrn.H"
#include "TObjColl.H"

#include <String.H>
#include <StdLib.H>


PrintMode tvField::printMode = Blockung;


tvField::tvField( tvFolder *aFolder ) :
	tvObject( aFolder, "Feld" ),
	length( 1 ),
	offset( 0 ),
	dumpable( False ),
	autoPos( True ),
	restriction( None )
	{}


Boolean tvField::handleNotification( TView *view )
{
	if( tvObject::handleNotification( view ) )
		return True;

	TFieldDlg *dlg = (TFieldDlg *)tvObject::dlg;

	if( view == dlg->dumpable )
		{
		view->getData( &dumpable );
		dlg->disablePosSel( dumpable );
		dlg->disableTrackPos( dumpable );
		dlg->disableRestr( dumpable );
		if( !dumpable )
			handleNotification( dlg->posSel );
		return True;
		}

	if( view == dlg->posSel )
		{
		view->getData( &autoPos );
		autoPos = (Boolean)!autoPos;
		dlg->disableTrackPos( autoPos );
		return True;
		}

	if( (view == dlg->length) ||
		(view == dlg->offset) ||
		(view == dlg->track) ||
		(view == dlg->pos) ||
		(view == dlg->restr ) )
		{
		dlg->length->getData( &length );
		dlg->offset->getData( &offset );

		dlg->track->getData( &(pos.y) );
		dlg->pos->getData( &(pos.x) );
		pos.x--;
		pos.y--;

		dlg->restr->getData( &restriction );
		return True;
		}

	return False;
}


void tvField::fillDlg()
{
	tvObject::fillDlg();
	TFieldDlg *dlg = (TFieldDlg *)tvObject::dlg;

	dlg->length->setData( &length );
	dlg->offset->setData( &offset );

	dlg->dumpable->setData( &dumpable );
	Boolean manualPos = (Boolean)!autoPos;
	dlg->posSel->setData( &manualPos );

	pos.x++;
	pos.y++;
	dlg->track->setData( &(pos.y) );
	dlg->pos->setData( &(pos.x) );

	dlg->restr->setData( &restriction );

	handleNotification( dlg->restr );
	handleNotification( dlg->posSel );
	handleNotification( dlg->dumpable );
}


/*	if( !((tvFieldsFolder *)folder)->getTrackTable()->reorder() )
		{
		messageBox( "Buffer ist berfllt oder Feldkollision!",
					mfInformation | mfOKButton );
		return False;
		}
	else
		return True;
*/


TObjDlg *tvField::createDlg()
{
	return( new TFieldDlg( TRect( 33, 1, 77, 22 ), this ) );
}


ushort tvField::getHelpCtx()
	{ return  hcField; }


int tvField::getIndex()
{
	return( folder->getObjects()->indexOf( this ) + 1 );
}


void tvField::write( FormDevice *formDevice )
{
	pos.x++;
	pos.y++;
	switch( printMode )
		{
		case Blockung:
			formDevice->writeNumber( offset + 1 );
			formDevice->writeNumber( length );
			formDevice->writeNumber( pos.y );
			formDevice->writeNumber( pos.x );
			break;

		case Felder:
			formDevice->writeNumber( pos.y );
			formDevice->writeNumber( pos.x );
			formDevice->writeNumber( length );
			break;
		}
	pos.x--;
	pos.y--;

	char *comment = new char[strlen( title ) + 8];
	strcpy( comment, title );

	char index[4];
	itoa( getIndex(), index, 16 );

	strcat( comment, " -- " );
	strcat( comment, index );

	formDevice->writeComment( comment );
	delete[] comment;

	formDevice->newLine();
}


const char *const near tvField::name = "tvField";

TStreamableClass RtvField( tvField::name,
						   tvField::build,
						   __DELTA( tvField )
						   );


tvField::tvField( StreamableInit ) :
	tvObject( streamableInit )
	{}


TStreamable *tvField::build()
{
	return new tvField( streamableInit );
}


void tvField::write( opstream& os )
{
	tvObject::write( os );

	os << (int)0x0100;

	os << length;
	os << offset;

	os << (int)dumpable;
	os << (int)autoPos;
	os << (int)restriction;
	os << pos.x;
	os << pos.y;
}


void *tvField::read( ipstream& is )
{
	tvObject::read( is );

	int version;
	is >> version;

	is >> length;
	is >> offset;

	is >> (int)dumpable;
	is >> (int)autoPos;
	is >> (int)restriction;
	is >> pos.x;
	is >> pos.y;
	return this;
}
