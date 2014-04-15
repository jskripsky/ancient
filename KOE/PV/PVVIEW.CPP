/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		PV View Source File    			    	*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "PV.Use"

#define Uses_TStatusLine
#define Uses_TStatusDef
#define Uses_TStatusItem
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TKeys
#define Uses_TPalette
#define Uses_fpstream

#include <TV.H>
#include <Help.H>
#include "PV.H"
#include "Defs\Commands.H"
#include "Defs\HelpCtx.H"


/*---- Private Methods -------------------------*/

TStatusLine *TPV::initStatusLine( TRect rect )
{
	rect.a.y = rect.b.y - 1;
	return new TStatusLine( rect,
		*new TStatusDef( hcFormDefInit, hcFormDefInit ) +
		*new TStatusItem( "Formular-Vorlage wird geladen...", 0, 0 ) +

		*new TStatusDef( hcEnter, hcEnter ) +
		*new TStatusItem( "~Enter~", 0, 0 ) +
		*new TStatusItem( 0, kbAltI, cmIntRevision ) +
		*new TStatusItem( 0, kbAltH, cmHeapView ) +

		*new TStatusDef( hcListWin, hcListWin ) +
//		*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +
		*new TStatusItem( "~Alt-V~ Programm verlassen", kbAltV, cmQuit ) +

		*new TStatusDef( hcFormDlg, hcFormDlg ) +
//		*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +
		*new TStatusItem( "~Tab~ N„chstes Feld", 0, 0 ) +
		*new TStatusItem( "~F6~ Kontrollfl„che", 0, 0 ) +
		*new TStatusItem( "~Enter~ N„chste Seite", kbEnter, cmNextPage )+

		*new TStatusDef( hcFormDlgControl, hcFormDlgControl ) +
//		*new TStatusItem( "~F1~ Hilfe", kbF1, cmHelp ) +
		*new TStatusItem( "~Tab~ N„chstes Feld", 0, 0 ) +
		*new TStatusItem( "~F6~ Formular", 0, 0 ) +
		*new TStatusItem( "~Enter~ N„chste Seite", kbEnter, cmNextPage )
		);
}


TMenuBar *TPV::initMenuBar( TRect rect )
{
	rect.b.y = rect.a.y + 1;

	return new TMenuBar( rect,
		*new TSubMenu( "~O~ptionen", kbAltO, hcSMOptions ) +
			*new TMenuItem( "~S~chnittstellen...", cmMIPrinter, (ushort)0,
							hcMIPrinter )
		);
}


/*---- Public Methods --------------------------*/

TPalette& TPV::getPalette() const
{
	static TPalette newcolor( cpColor cHelpColor,
						sizeof( cpColor cHelpColor ) - 1 );
	static TPalette newblackwhite( cpBlackWhite cHelpBlackWhite,
						sizeof( cpBlackWhite cHelpBlackWhite ) - 1 );
	static TPalette newmonochrome( cpMonochrome cHelpMonochrome,
						sizeof( cpMonochrome cHelpMonochrome ) - 1 );
	static TPalette *palettes[] =
		{
		&newcolor,
		&newblackwhite,
		&newmonochrome
		};
	return *(palettes[appPalette]);
}
