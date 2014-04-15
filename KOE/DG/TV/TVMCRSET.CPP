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
**  tvMCReaderSettings Class                                                **
**  ------------------------                                                **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvMCReaderSettings                                            **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVMCRSET.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_TCheckBoxes
#define Uses_TRadioButtons
#include "tvMCRSet.H"
#include "TMCSTDlg.H"
#include "FormDlg.H"
#include "HelpCtx.H"

#include <String.H>


// -----------------------
// Basic tvObject Protocol
// -----------------------

tvMCReaderSettings::tvMCReaderSettings( tvFolder *aFolder ) :
	tvObject( aFolder, "Systemeinstellungen" ),
	mcReaderType( Track1 )
{
	for( int i = 0; i < NumTracks; i++ )
		tracks[i] = True;
}


// ---------------
// Dialog Protocol
// ---------------

Boolean tvMCReaderSettings::handleNotification( TView *view )
{
	if( tvObject::handleNotification( view ) )
		return True;

	TMCRSettingsDlg *dlg = (TMCRSettingsDlg *)tvObject::dlg;

	if( view == dlg->typeSwitch )
		{
		view->getData( &mcReaderType );
		return True;
		}

	if( view == dlg->trackSwitches )
		{
		int switches;
		view->getData( &switches );

		for( int i = 0; i < NumTracks; i++ )
			if( switches & (1 << i) )
				tracks[i] = True;
			else
				tracks[i] = False;

		return True;
		}

	return False;
}


void tvMCReaderSettings::fillDlg()
{
	tvObject::fillDlg();
	TMCRSettingsDlg *dlg = (TMCRSettingsDlg *)tvObject::dlg;

	dlg->typeSwitch->setData( &mcReaderType );

	int switches = 0;
	for( int i = 0; i < NumTracks; i++ )
		if( tracks[i] )
			switches |= 1 << i;

	dlg->trackSwitches->setData( &switches );
}


TObjDlg *tvMCReaderSettings::createDlg()
{
	return( new TMCRSettingsDlg( TRect( 33, 1, 77, 22 ), this ) );
}


ushort tvMCReaderSettings::getHelpCtx()
	{ return hcMCReaderSettings; }


void tvMCReaderSettings::write( FormDevice *formDevice )
{
	formDevice->openBlock( "leser_type" );
	formDevice->registerCustomBlockClosing(
		&tvMCReaderSettings::blockClosing );

	int type;
	switch( mcReaderType )
		{
		case Track1:
			type = 1;
			break;

		case Track2:
			type = 2;
			break;

		case Track3:
			type = 3;
			break;

		case Track12:
			type = 12;
			break;

		case Track23:
			type = 23;
			break;

		case Track123:
			type = 123;
			break;
		}

	formDevice->writeNumber( type );
	formDevice->closeBlock();

	char blockTitle[13];
	strcpy( blockTitle, "enable_spur0" );

	for( int i = 0; i < NumTracks; i++ )
		{
		blockTitle[11] = i + '1';
		formDevice->openBlock( blockTitle );

		formDevice->registerCustomBlockClosing(
			&tvMCReaderSettings::blockClosing );

		if( tracks[i] )
			formDevice->writeNumber( 1 );
		else
			formDevice->writeNumber( 0 );

		formDevice->closeBlock();
		}
}


void tvMCReaderSettings::blockClosing( FormDevice * )
{
}


// --------------------
// TStreamable Protocol
// --------------------

const char *const near tvMCReaderSettings::name = "tvMCReaderSettings";

TStreamableClass RtvMCReaderSettings( tvMCReaderSettings::name,
									  tvMCReaderSettings::build,
									  __DELTA( tvMCReaderSettings )
									);


tvMCReaderSettings::tvMCReaderSettings( StreamableInit ) :
	tvObject( streamableInit )
	{}


TStreamable *tvMCReaderSettings::build()
{
	return new tvMCReaderSettings( streamableInit );
}


void tvMCReaderSettings::write( opstream& os )
{
	tvObject::write( os );

	os << (int)0x0100;

	os << (int)mcReaderType;

	for( int i = 0; i < NumTracks; i++ )
		os << (int)tracks[i];
}


void *tvMCReaderSettings::read( ipstream& is )
{
	tvObject::read( is );

	int version;
	is >> version;

	is >> (int)mcReaderType;

	for( int i = 0; i < NumTracks; i++ )
		is >> (int)tracks[i];

	return this;
}
