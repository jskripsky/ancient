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
**  TtvApplication Class                                                    **
**  --------------------                                                    **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TtvApplication                                                **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TTVAPPL.CPP                                                **
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
#include "TtvAppl.H"

#include "tvMainFl.H"
#include "THandMgr.H"
#include "Gadgets.H"
#include "HelpCtx.H"

#include <Help.H>


TtvApplication::TtvApplication( tvMainFolder *(*cMainFolder)(),
								char *aMainFolderFileName,
								char *aHelpFileName,
								Boolean (*enableHeapStatus)(),
								void (*aboutDialog)() ) :
	TProgInit( &TtvApplication::initStatusLine, 0,
			   &TtvApplication::initDeskTop ),
	mainFolderFileName( aMainFolderFileName ),
	helpFileName( aHelpFileName ),
	heapStatus( 0 )
{
	TRect r = getExtent();
	r.a.x = r.b.x - 10;
	r.a.y = r.b.y - 1;
	insert( clock = new TClockView( r ) );

	if( aboutDialog )
		{
		statusLine->hide();
		aboutDialog();
		statusLine->show();
		}


	ifpstream mainFldFile( mainFolderFileName, ios::nocreate );
	if( !mainFldFile )
		{
		handleMgr = new THandleMgr();
		mainFld = cMainFolder();
		}
	else
		{
		int version;
		mainFldFile >> version;

		mainFldFile >> handleMgr;
		mainFldFile >> mainFld;
		mainFldFile.close();
		}


	Boolean heapView;

#ifdef RELEASE
	heapView = enableHeapStatus();
#else
	enableHeapStatus;
	heapView = True;
#endif
	if( heapView )
		{
		r = getExtent();
		r.b.x -= 10;
		r.a.x = r.b.x - 13;
		r.a.y = r.b.y - 1;
		insert( heapStatus = new THeapView( r ) );
		}


	mainFld->tvOpen();
}


TtvApplication::~TtvApplication()
{
	ofpstream mainFldFile( mainFolderFileName, ios::trunc );
	mainFldFile << (int)0x0100;

	mainFldFile << handleMgr;
	mainFldFile << mainFld;
	mainFldFile.close();

	delete handleMgr;
	destroy( mainFld );

	if( heapStatus )
		{
		remove( heapStatus );
		destroy( heapStatus );
		}

	remove( clock );
	destroy( clock );
}


Boolean TtvApplication::isHeapStatusToBeEnabled()
{
	return False;
}


void TtvApplication::getEvent( TEvent& event )
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
				helpStrm = new fpstream( helpFileName,
										 ios::in | ios::binary );
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
						w->helpCtx = hcHelp;
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


void TtvApplication::idle()
{
	TApplication::idle();
	clock->update();

	if( heapStatus )
		heapStatus->update();
}


TDeskTop *TtvApplication::initDeskTop( TRect r )
{
//	r.b.y--;
	return new TDeskTop( r );
}


TPalette& TtvApplication::getPalette() const
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
