/*****************************************************************************
**                                                                          **
**                                                                          **
**  DOS Form Designer                                                       **
**  =================                                                       **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  TFD Class                                                               **
**  ---------                                                               **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TFD                                                           **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: FD.CPP                                                     **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TDeskTop
#define Uses_TStatusLine
#define Uses_TStatusDef
#define Uses_TStatusItem
#define Uses_TKeys
#define Uses_ifpstream
#define Uses_ofpstream
#define Uses_fpstream
#define Uses_TEvent
#define Uses_MsgBox
#define Uses_TPalette
#include "FD.H"

#include "THandMgr.H"
#include "tvFDMain.H"
#include "Gadgets.H"
#include "HelpCtx.H"

#include <Help.H>


int main()
{
	TFD fd;
	fd.run();
	return 0;
}


TFD::TFD() :
	TProgInit( &TFD::initStatusLine,
			   &TFD::initMenuBar,
			   &TFD::initDeskTop )
{
	TRect r = getExtent();
	r.a.x = r.b.x - 9;
	r.b.y = r.a.y + 1;
	insert( clock = new TClockView( r ) );

#ifndef RELEASE
	r = getExtent();
	r.a.x = r.b.x - 13;
	r.a.y = r.b.y - 1;
	insert( heapStatus = new THeapView( r ) );
#endif

#ifdef RELEASE
	messageBoxRect( TRect( 21, 5, 59, 18 ),
				mfWarning | mfOKButton, "%s\n%s\n%s\n%s\n%s\n%s\n%s",
				"FormDesigner Beta Version",
				"อออออออออออออออออออออออออ",
				" ",
				"Da dies eine Vorabversion ist,",
				"wird empfohlen, laufend Sicher-",
				"heitskopien der Daten (*.FLD)",
				"herzustellen." );
#endif

	ifpstream mainFldFile( "Main.Fld", ios::nocreate );
	if( !mainFldFile )
		{
		handleMgr = new THandleMgr();
		mainFld = new tvFDMainFolder();
		}
	else
		{
		mainFldFile >> handleMgr;
		mainFldFile >> mainFld;
		mainFldFile.close();
		}

	mainFld->tvOpen();
}


TFD::~TFD()
{
	ofpstream mainFldFile( "Main.Fld", ios::trunc );
	mainFldFile << handleMgr;
	mainFldFile << mainFld;
	mainFldFile.close();

	delete handleMgr;
	destroy( mainFld );

#ifndef RELEASE
	remove( heapStatus );
	destroy( heapStatus );
#endif

	remove( clock );
	destroy( clock );
}


void TFD::getEvent( TEvent& event )
{
	TWindow *w;
	THelpFile *hFile;
	fpstream *helpStrm;
	static Boolean helpInUse = False;

	TApplication::getEvent( event );
	switch( event.what )
		{
		case evCommand:
			if( (event.message.command == cmHelp) && (helpInUse == False) )
				{
				helpInUse = True;
				helpStrm = new fpstream( "FD.HLP", ios::in | ios::binary );
				hFile = new THelpFile( *helpStrm );
				if( !helpStrm )
					{
					messageBox( "Hilfe-Datei kann nicht ge”ffnet werden!",
								mfError | mfOKButton );
					delete hFile;
					}
				else
					{
					w = new THelpWindow( hFile, getHelpCtx() );
					if( validView( w ) != 0 )
						{
						execView( w );
						destroy( w );
						}
					clearEvent( event );
					}
				helpInUse = False;
				}
			break;

		case evMouseDown:
			if( event.mouse.buttons != 1 )
				event.what = evNothing;
			break;
		}
}


void TFD::idle()
{
	TApplication::idle();
	clock->update();

#ifndef RELEASE
	heapStatus->update();
#endif
}


TPalette& TFD::getPalette() const
{
	static TPalette newcolor ( cpColor cHelpColor, sizeof( cpColor cHelpColor )-1 );
	static TPalette newblackwhite( cpBlackWhite cHelpBlackWhite, sizeof( cpBlackWhite cHelpBlackWhite)-1 );
	static TPalette newmonochrome( cpMonochrome cHelpMonochrome, sizeof( cpMonochrome cHelpMonochrome)-1 );
	static TPalette *palettes[] =
		{
		&newcolor,
		&newblackwhite,
		&newmonochrome
		};
	return *(palettes[appPalette]);
}


TStatusLine *TFD::initStatusLine( TRect r )
{
	r.a.y = r.b.y - 1;
	return new TStatusLine( r,
				*new TStatusDef( 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe",
								  kbF1, cmHelp ) +

				*new TStatusDef( hcMovingObject, hcMovingObject ) +
				*new TStatusItem( "Verschieben....   ณ", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe",
								  kbF1, cmHelp ) +
				*new TStatusItem( "~Enter~ Objekt platzieren", 0, 0 ) +

				*new TStatusDef( hcMainFolder, hcMainFolder ) +
				*new TStatusItem( "Hauptordner       ณ", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe",
								  kbF1, cmHelp ) +

				*new TStatusDef( hcProject, hcProject ) +
				*new TStatusItem( "Applikation       ณ", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe",
								  kbF1, cmHelp ) +

				*new TStatusDef( hcFieldsFolder, hcFieldsFolder ) +
				*new TStatusItem( "Felder            ณ", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe",
								  kbF1, cmHelp ) +

				*new TStatusDef( hcFormFolder, hcFormFolder ) +
				*new TStatusItem( "Formular/Etikette ณ", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe",
								  kbF1, cmHelp ) +

				*new TStatusDef( hcField, hcField ) +
				*new TStatusItem( "Feld              ณ", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe",
								  kbF1, cmHelp ) +

				*new TStatusDef( hcFormTextField, hcFormTextField ) +
				*new TStatusItem( "Text              ณ", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe",
								  kbF1, cmHelp ) +

				*new TStatusDef( hcFormStaticText, hcFormStaticText ) +
				*new TStatusItem( "Fester Text       ณ", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe",
								  kbF1, cmHelp )
				);

//				*new TStatusItem( "~Alt-F4~ Schliessen",
//								  kbAltF4, cmClose )
}
