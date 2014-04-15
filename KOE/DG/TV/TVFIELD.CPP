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

#define Uses_TInputLine
#define Uses_TListBox
#include "tvField.H"
#include "TFldDlg.H"
#include "TObjColl.H"
#include "FormDlg.H"
#include "tvKey.H"
#include "tvDGMain.H"
#include "TCard.H"


// -----------------------
// Basic tvObject Protocol
// -----------------------

tvField::tvField( tvFolder *aFolder, const char *aTitle ) :
	tvObject( aFolder, aTitle ),
	init( True )
{
	card = ((tvDGMainFolder *)mainFolder)->getCard();

	for( int i1 = 0; i1 < 2; i1++ )
		for( int i2 = 0; i2 < numDistinctKeys; i2++ )
			{
			keys[i1][i2].handle = 0;
			keys[i1][i2].times = 0;

			registerShadowHandle( &keys[i1][i2].handle );
			}
}


// ---------------
// Dialog Protocol
// ---------------

Boolean tvField::handleNotification( TView *view )
{
	if( tvObject::handleNotification( view ) )
		return True;

	TFieldDlg *dlg = (TFieldDlg *)tvObject::dlg;

	int i1, i2;

	for( i1 = 0; i1 < 2; i1++ )
		for( i2 = 0; i2 < numDistinctKeys; i2++ )
			if( view == dlg->keyLines[i1][i2].keySel )
				{
				view->getData( &keys[i1][i2].handle );
				return True;
				}

	for( i1 = 0; i1 < 2; i1++ )
		for( i2 = 0; i2 < numDistinctKeys; i2++ )
			if( view == dlg->keyLines[i1][i2].timesLine )
				{
				view->getData( &keys[i1][i2].times );
				return True;
				}

	return False;
}


void tvField::fillDlg()
{
	tvObject::fillDlg();
	TFieldDlg *dlg = (TFieldDlg *)tvObject::dlg;

	for( int i1 = 0; i1 < 2; i1++ )
		for( int i2 = 0; i2 < numDistinctKeys; i2++ )
			{
			if( dlg->keyLines[i1][i2].keySel )
				dlg->keyLines[i1][i2].keySel->setData(
					&keys[i1][i2].handle );

			if( dlg->keyLines[i1][i2].timesLine )
				dlg->keyLines[i1][i2].timesLine->setData(
					&keys[i1][i2].times );
			}
}


void tvField::write( FormDevice *formDevice )
{
	for( int i = 0; i < numDistinctKeys; i++ )
			{
			tvKey *key;
			if( keys[Before][i].handle != 0 )
				key = (tvKey *)tvObject::getObject( keys[Before][i].handle );

			for( int t = 0; t < keys[Before][i].times; t++ )
				key->write( formDevice );
			}

	writeDataField( formDevice );

	for( i = 0; i < numDistinctKeys; i++ )
			{
			tvKey *key;
			if( keys[After][i].handle != 0 )
				key = (tvKey *)tvObject::getObject( keys[After][i].handle );

			for( int t = 0; t < keys[After][i].times; t++ )
				key->write( formDevice );
			}
}


// ---------------
// Shadow Protocol
// ---------------

void tvField::invalidateShadow( tvObject *shadow )
{
	int handle = shadow->getHandle();

	for( int i1 = 0; i1 < 2; i1++ )
		for( int i2 = 0; i2 < numDistinctKeys; i2++ )
			if( keys[i1][i2].handle == handle )
				{
				keys[i1][i2].handle = 0;
				keys[i1][i2].times = 0;
				return;
				}
}


// --------------------
// TStreamable Protocol
// --------------------

tvField::tvField( StreamableInit ) :
	tvObject( streamableInit ),
	init( False )
{
	card = ((tvDGMainFolder *)mainFolder)->getCard();

	for( int i1 = 0; i1 < 2; i1++ )
		for( int i2 = 0; i2 < numDistinctKeys; i2++ )
			registerShadowHandle( &keys[i1][i2].handle );
}


void tvField::write( opstream& os )
{
	tvObject::write( os );

	os << (int)0x0100;

	for( int i1 = 0; i1 < 2; i1++ )
		for( int i2 = 0; i2 < numDistinctKeys; i2++ )
			{
			os << keys[i1][i2].handle;
			os << keys[i1][i2].times;
			}
}


void *tvField::read( ipstream& is )
{
	tvObject::read( is );

	int version;
	is >> version;

	for( int i1 = 0; i1 < 2; i1++ )
		for( int i2 = 0; i2 < numDistinctKeys; i2++ )
			{
			is >> keys[i1][i2].handle;
			is >> keys[i1][i2].times;
			}
	return this;
}
