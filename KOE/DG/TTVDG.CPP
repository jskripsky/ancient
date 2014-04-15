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
**  TtvDG Class                                                             **
**  -----------                                                             **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TtvDG                                                         **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TTVDG.CPP                                                  **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStatusLine
#define Uses_TStatusDef
#define Uses_TStatusItem
#define Uses_TKeys
#define Uses_MsgBox
#define Uses_TDeskTop
#include "TtvDG.H"

#include "tvDGMain.H"
#include "TAbout.H"
#include "HelpCtx.H"


int main()
{
	TtvDG dg;
	dg.run();
	return 0;
}


TtvDG::TtvDG() :
	TProgInit( &TtvDG::initStatusLine,
			   0,
			   &TtvDG::initDeskTop ),
#ifndef ULRICH
	TtvApplication( &TtvDG::initMainFolder, "DG.Fld", "DG.Hlp",
#else
	TtvApplication( &TtvDG::initMainFolder, "DGMC.Fld", "DGMC.Hlp",
#endif
					&TtvDG::isHeapStatusToBeEnabled,
					&TtvDG::aboutDialog )
{
}


tvMainFolder *TtvDG::initMainFolder()
{
	return new tvDGMainFolder();
}


Boolean TtvDG::isHeapStatusToBeEnabled()
{
	// mainFolder->.....
	return False;
}


void TtvDG::aboutDialog()
{
	TView *aboutDlg = new TAboutDlg();
	deskTop->insert( aboutDlg );

	aboutDlg->show();
	deskTop->execView( aboutDlg );
	aboutDlg->hide();

	deskTop->remove( aboutDlg );
	destroy( aboutDlg );
}


TStatusLine *TtvDG::initStatusLine( TRect r )
{
	r.a.y = r.b.y - 1;
	return new TStatusLine( r,
				*new TStatusDef( hcNoCxt, hcNoCxt ) +
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +

				*new TStatusDef( hcHelp, hcHelp ) +
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +
				*new TStatusItem( "~Alt-F10~ Vergr”ssern", kbAltF10, cmZoom ) +

				*new TStatusDef( hcAbout, hcAbout ) +
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +

				*new TStatusDef( hcMovingObject,
								 hcMovingObject ) +
				*new TStatusItem( "Verschieben....   ³", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +
				*new TStatusItem( "~Enter~ Objekt platzieren", 0, 0 ) +

				*new TStatusDef( hcMainFolder, hcMainFolder ) +
				*new TStatusItem( "Hauptordner       ³", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +

				*new TStatusDef( hcSystemsFolder, hcSystemsFolder ) +
#ifndef ULRICH
				*new TStatusItem( "Systeme           ³", 0, 0 ) +
#else
				*new TStatusItem( "Terminalauswahl   ³", 0, 0 ) +
#endif
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +

				*new TStatusDef( hcSystem, hcSystem ) +
#ifndef ULRICH
				*new TStatusItem( "System            ³", 0, 0 ) +
#else
				*new TStatusItem( "Terminal          ³", 0, 0 ) +
#endif
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +

				*new TStatusDef( hcProject, hcProject ) +
				*new TStatusItem( "Applikation       ³", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +

				*new TStatusDef( hcKeyFolder, hcKeyFolder ) +
#ifndef ULRICH
				*new TStatusItem( "Tasten            ³", 0, 0 ) +
#else
				*new TStatusItem( "Tastendefinitionen³", 0, 0 ) +
#endif
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +

				*new TStatusDef( hcKey, hcKey ) +
				*new TStatusItem( "Taste             ³", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +

				*new TStatusDef( hcDialog, hcDialog ) +
#ifndef ULRICH
				*new TStatusItem( "Dialog            ³", 0, 0 ) +
#else
				*new TStatusItem( "Ausgabeformat     ³", 0, 0 ) +
#endif
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +

				*new TStatusDef( hcMCReaderField, hcMCReaderField ) +
				*new TStatusItem( "Feld              ³", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +

				*new TStatusDef( hcSingleField, hcSingleField ) +
				*new TStatusItem( "Einfaches Feld    ³", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +

				*new TStatusDef( hcDoubleField, hcDoubleField ) +
				*new TStatusItem( "Doppeltes Feld    ³", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +

				*new TStatusDef( hcMCReaderSettings, hcMCReaderSettings ) +
				*new TStatusItem( "Systemeinstellung ³", 0, 0 ) +
				*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp )
				);
}
