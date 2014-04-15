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
**  tvKey Class                                                             **
**  -----------                                                             **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvKey                                                         **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVKEY.CPP                                                  **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_TInputLine
#define Uses_TListBox
#define Uses_TRadioButtons
#include "tvKey.H"
#include "TKeyDlg.H"
#include "FormDlg.H"
#include "HelpCtx.H"


// -----------------------
// Basic tvObject Protocol
// -----------------------

tvKey::tvKey( tvFolder *aFolder ) :
	tvObject( aFolder, "Taste" ),
	type( Character ),
	character( 0 ),
	scanCode( 0 )
{
}


// ---------------
// Dialog Protocol
// ---------------

Boolean tvKey::handleNotification( TView *view )
{
	if( tvObject::handleNotification( view ) )
		return True;

	TKeyDlg *dlg = (TKeyDlg *)tvObject::dlg;

	if( view == dlg->typeSwitch )
		{
		view->getData( &type );
		switch( type )
			{
			case Character:
				dlg->disableCharacterBox( False );
				dlg->disableScanCodeLine( True );
				break;

			case ScanCode:
				dlg->disableCharacterBox( True );
				dlg->disableScanCodeLine( False );
				break;
			}
		return True;
		}

	if( view == dlg->characterBox )
		{
		view->getData( &character );
		return True;
		}

	if( view == dlg->scanCodeLine )
		{
		view->getData( &scanCode );
		return True;
		}

	return False;
}


void tvKey::fillDlg()
{
	tvObject::fillDlg();
	TKeyDlg *dlg = (TKeyDlg *)tvObject::dlg;

	dlg->typeSwitch->setData( &type );
	dlg->characterBox->setData( &character );
	dlg->scanCodeLine->setData( &scanCode );

	handleNotification( dlg->typeSwitch );
}


TObjDlg *tvKey::createDlg()
{
	return( new TKeyDlg( TRect( 33, 1, 77, 22 ), this ) );
}


ushort tvKey::getHelpCtx()
	{ return hcKey; }


void tvKey::write( FormDevice *formDevice )
{
	switch( type )
		{
		case Character:
			((FormDialog *)formDevice)->sendKey( (char)character );
			break;

		case ScanCode:
			((FormDialog *)formDevice)->sendKeyByScanCode( (char)scanCode );
			break;
		}
}


// --------------------
// TStreamable Protocol
// --------------------

const char *const near tvKey::name = "tvKey";

TStreamableClass RtvKey( tvKey::name,
						 tvKey::build,
						 __DELTA( tvKey )
					   );


tvKey::tvKey( StreamableInit ) :
	tvObject( streamableInit )
	{}


TStreamable *tvKey::build()
{
	return new tvKey( streamableInit );
}


void tvKey::write( opstream& os )
{
	tvObject::write( os );

	os << (int)0x0100;

	os << (int)type;

	os << character;
	os << scanCode;
}


void *tvKey::read( ipstream& is )
{
	tvObject::read( is );

	int version;
	is >> version;

	is >> (int)type;

	is >> character;
	is >> scanCode;
	return this;
}
