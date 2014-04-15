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
**  tvDialog Class                                                          **
**  --------------                                                          **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvDialog                                                      **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVDIALOG.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_TRadioButtons
#define Uses_TInputLine
#define Uses_TNSCollection
#include "tvDialog.H"
#include "TDlgDlg.H"
#include "HelpCtx.H"
#include "TObjColl.H"
#include "tvSField.H"
#include "tvDField.H"
#include "tvMCRFld.H"
#include "FormDlg.H"

#include <String.H>
#include <StdLib.H>


// -----------------------
// Basic tvObject Protocol
// -----------------------

tvDialog::tvDialog( tvFolder *aFolder ) :
#ifndef ULRICH
	tvFolder( aFolder, "Dialog", False ),
#else
	tvFolder( aFolder, "Ausgabeformat", False ),
#endif
	number( 1 ),
	key( NoKey )
{
}


// --------------------------
// Object Management Protocol
// --------------------------

void tvDialog::insertObject( tvObject * )
{
#ifndef ULRICH
	TNSCollection *classes = new TNSCollection( 2, 1 );
	classes->insert( "Einfaches Feld" );
	classes->insert( "Doppeltes Feld" );

	tvObject *obj;
	switch( selectClass( classes ) )
		{
		case 1:
			obj = new tvSingleField( this );
			break;

		case 2:
			obj = new tvDoubleField( this );
			break;

		default:
			obj = 0;
			break;
		}

	if( obj )
		tvFolder::insertObject( obj );

	delete classes;
#else
	tvFolder::insertObject( new tvMCReaderField( this ) );
#endif
}


// ---------------
// Dialog Protocol
// ---------------

Boolean tvDialog::handleNotification( TView *view )
{
	if( tvFolder::handleNotification( view ) )
		return True;

	TDialogDlg *dlg = (TDialogDlg *)tvObject::dlg;

	if( view == dlg->numberLine )
		{
		dlg->numberLine->getData( &number );
		return True;
		}

	if( view == dlg->keySwitch )
		{
		dlg->keySwitch->getData( &key );
		return True;
		}

	return False;
}


void tvDialog::fillDlg()
{
	tvFolder::fillDlg();

	TDialogDlg *dlg = (TDialogDlg *)tvObject::dlg;
	dlg->numberLine->setData( &number );
	dlg->keySwitch->setData( &key );
}


TObjDlg *tvDialog::createDlg()
{
	return( new TDialogDlg( TRect( 3, 2, 29, 22 ), this ) );
}


ushort tvDialog::getHelpCtx()
	{ return hcDialog; }


// ---------------
// Folder Protocol
// ---------------

int tvDialog::compareWith( tvObject& obj )
{
	tvDialog *dlgObj = (tvDialog *)&obj;

	int keyDelta = key - dlgObj->key;
	if( keyDelta != 0 )
		return keyDelta;
	else
		return (number - dlgObj->number);
}


void tvDialog::write( FormDevice *formDevice )
{
	char blockTitle[11];
	strcpy( blockTitle, "formular" );
	itoa( number + (5 * (int)key), &blockTitle[strlen( blockTitle )], 10 );

	formDevice->openBlock( blockTitle );

	for( int i = 0; i < objects->getCount(); i++ )
		{
		tvField *formObj = (tvField *)objects->at( i );
		if( formObj )
			formObj->write( formDevice );
		formObj;
		}

	formDevice->closeBlock();
}



// --------------------
// TStreamable Protocol
// --------------------

const char *const near tvDialog::name = "tvDialog";

TStreamableClass RtvDialog( tvDialog::name,
							tvDialog::build,
							__DELTA( tvDialog )
						  );


tvDialog::tvDialog( StreamableInit ) :
	tvFolder( streamableInit )
	{}


TStreamable *tvDialog::build()
{
	return new tvDialog( streamableInit );
}


void tvDialog::write( opstream& os )
{
	tvFolder::write( os );

	os << (int)0x0100;

	os << number;
	os << (int)key;
}


void *tvDialog::read( ipstream& is )
{
	tvFolder::read( is );

	int version;
	is >> version;

	is >> number;
	is >> (int)key;
	return this;
}
