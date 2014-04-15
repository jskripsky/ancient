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
**  tvSystem Class                                                          **
**  --------------                                                          **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvSystem                                                      **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVSYSTEM.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_TInputLine
#define Uses_TListBox
#define Uses_TCheckBoxes
#include "tvSystem.H"
#include "TSysDlg.H"
#include "FormDlg.H"
#include "HelpCtx.H"
#include "SysImp.H"

#include <String.H>


// -----------------------
// Basic tvObject Protocol
// -----------------------

tvSystem::tvSystem( tvFolder *aFolder ) :
#ifndef ULRICH
	tvObject( aFolder, "System" )
#else
	tvObject( aFolder, "Terminal" )
#endif
{
	ID[0] = 0;

	for( int i = 0; i < NumCharacters; i++ )
		{
		for( int b = 0; b < BytesPerCharacter; b++ )
			characters[i].bytes[b] = 0;

		characters[i].shift = False;
		characters[i].comment[0] = 0;
		}
}


void tvSystem::tvOpen()
{
	character = 0;
	charsUndoData = new char[sizeof( characters )];
	memcpy( charsUndoData, characters, sizeof( characters ) );

	tvObject::tvOpen();
}


Boolean tvSystem::tvClose()
{
	if( tvObject::tvClose() )
		{
		delete[] charsUndoData;
		return True;
		}
	else
		return False;
}


// ---------------
// Dialog Protocol
// ---------------

Boolean tvSystem::handleNotification( TView *view )
{
	if( tvObject::handleNotification( view ) )
		return True;

	TSystemDlg *dlg = (TSystemDlg *)tvObject::dlg;

	if( view == dlg->IDLine )
		{
		view->getData( ID );
		return True;
		}

	if( view == dlg->characterBox )
		{
		view->getData( &character );

		for( int b = 0; b < BytesPerCharacter; b++ )
			dlg->byteLines[b]->setData( &characters[character].bytes[b] );

		dlg->shiftSwitch->setData( &characters[character].shift );
		dlg->commentLine->setData( characters[character].comment );

		return True;
		}

	if( view == dlg->commentLine )
		{
		view->getData( characters[character].comment );
		return True;
		}

	if( view == dlg->shiftSwitch )
		{
		view->getData( &characters[character].shift );
		return True;
		}

	for( int b = 0; b < BytesPerCharacter; b++ )
		if( view == dlg->byteLines[b] )
			{
			view->getData( &characters[character].bytes[b] );
			return True;
			}

	return False;
}


void tvSystem::fillDlg()
{
	tvObject::fillDlg();
	TSystemDlg *dlg = (TSystemDlg *)tvObject::dlg;

	dlg->IDLine->setData( ID );
	dlg->characterBox->setData( &character );

	handleNotification( dlg->characterBox );
}


void tvSystem::undoDlg()
{
	tvObject::undoDlg();
	TSystemDlg *dlg = (TSystemDlg *)tvObject::dlg;

	memcpy( characters, charsUndoData, sizeof( characters ) );
	handleNotification( dlg->characterBox );
}


TObjDlg *tvSystem::createDlg()
{
	return( new TSystemDlg( TRect( 33, 1, 77, 22 ), this ) );
}


ushort tvSystem::getHelpCtx()
	{ return hcSystem; }


void tvSystem::importSystem()
{
	if( !tvClose() )
		return;

	SystemImport *sysImp = new SystemImport( ID, characters );
	sysImp->import();

	delete sysImp;

	tvOpen();
}


void tvSystem::write( FormDevice *formDevice )
{
	char blockTitle[81];
	strcpy( blockTitle, "scancode_" );
	strcat( blockTitle, ID );

	formDevice->openBlock( blockTitle );
	formDevice->registerCustomBlockClosing( &tvSystem::blockClosing );

	formDevice->disableZeroConversion();

	for( int i = 0; i < NumCharacters; i++ )
		{
		((FormDialog *)formDevice)->registerScanCode(
			(uchar *)characters[i].bytes, characters[i].shift );
		formDevice->newLine();
		}

	formDevice->enableZeroConversion();

	formDevice->closeBlock();
}


void tvSystem::blockClosing( FormDevice * )
{
}


// --------------------
// TStreamable Protocol
// --------------------

const char *const near tvSystem::name = "tvSystem";

TStreamableClass RtvSystem( tvSystem::name,
							tvSystem::build,
							__DELTA( tvSystem )
						  );


tvSystem::tvSystem( StreamableInit ) :
	tvObject( streamableInit )
	{}


TStreamable *tvSystem::build()
{
	return new tvSystem( streamableInit );
}


void tvSystem::write( opstream& os )
{
	tvObject::write( os );

	os << (int)0x0100;

	os.writeString( ID );

	for( int i = 0; i < sizeof( characters ) / sizeof( Character ); i++ )
		{
		for( int b = 0; b < BytesPerCharacter; b++ )
			os << characters[i].bytes[b];

		os << (int)characters[i].shift;
		os.writeString( characters[i].comment );
		}
}


void *tvSystem::read( ipstream& is )
{
	tvObject::read( is );

	int version;
	is >> version;

	is.readString( ID, sizeof( ID ) );

	for( int i = 0; i < sizeof( characters ) / sizeof( Character ); i++ )
		{
		for( int b = 0; b < BytesPerCharacter; b++ )
			is >> characters[i].bytes[b];

		is >> (int)characters[i].shift;
		is.readString( characters[i].comment,
					   sizeof( characters[i].comment ) );
		}
	return this;
}
