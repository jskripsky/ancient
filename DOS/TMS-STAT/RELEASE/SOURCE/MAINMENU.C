// ****************************
// *** Statistik - Programm ***
// ***	     Mainmenu	    ***
// ****************************
// ***			    ***
// ****************************

#include "constant.h"


void MainButtoninfo( byte choice );


const char MainTitle[5][30] =
    { "Monatsstatistik...",
      "Jahresstatistik...",
      "Teilstatistik...",
      "Konfiguration...",
      "Programm verlassen" };

box MainInfo =
    { INFO, 41, 6, 72, 18, MENU, CHOICE, DOUBLE, FALSE, FALSE, "" };

box MainButton[5] =
    { { BUTTON, 7,  6, 37,  8, MENU, CHOICE, SINGLE, FALSE,  TRUE, MainTitle[0] },
      { BUTTON, 7,  8, 37, 10, MENU, CHOICE, SINGLE,  TRUE,  TRUE, MainTitle[1] },
      { BUTTON, 7, 10, 37, 12, MENU, CHOICE, SINGLE,  TRUE, FALSE, MainTitle[2] },
      { BUTTON, 7, 14, 37, 16, MENU, CHOICE, SINGLE, FALSE,  TRUE, MainTitle[3] },
      { BUTTON, 7, 16, 37, 18, MENU, CHOICE, SINGLE,  TRUE, FALSE, MainTitle[4] } };

const char MainDescription[5][7][30] =
    { { "Statistik vom ersten bis zum",
	"letzen Tag des Vormonates.",
	"Ausdruck und Datei werden",
	"erzeugt.",
	"Ä¿ ÚÄÄÄÄÄÄÄ Mai ÄÄÄÄÄÄÄÄ¿ ÚÄ",
	" ³ ³ 1, 2, 3 ... 30, 31 ³ ³ ",
	"ÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ÀÄ" },
      { "Statistik vom ersten bis zum",
	"letzten erfassten Monat des",
	"laufenden Jahres. Ein Aus-",
	"druck wird erzeugt.",
	"Ä¿ ÚÄÄÄÄÄÄÄ 1991 ÄÄÄÄÄÄÄ¿ ÚÄ",
	" ³ ³ Jan., Feb. .. Dez. ³ ³ ",
	"ÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ÀÄ" },
      { "Statistik vom Tag X bis Y",
	"des laufenden Monates.",
	"Es wird ein Ausdruck aber",
	"keine Datei erzeugt.",
	"ÄÄÄÂÄÄÄÄÄÄÄ Mai ÄÄÄÄÄÄÄÄÂÄÄÄ",
	" 5 ³ 6, 7, 8 ... 12, 13 ³ 14",
	"ÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄ" },
      { "Auswahl der zu berck-",
	"sichtigenden Begrndungen",
	"und Abteilungen. Bestimmung",
	"der L„nge des Arbeitstages.",
	"",
	"",
	"" },
      { "",
	"Verlassen dieses Programmes.",
	"",
	"",
	" ====>   ÚÄÄÄÄÄ¿",
	" =====>  ³ DOS ³",
	" ====>   ÀÄÄÄÄÄÙ" } };


byte Mainmenu( void )
    {
    byte choice;
    choice = ButtonMenu( 5, 1, MainButton, MainButtoninfo );
    ScrClr( BACKGROUND );
    return( choice );
    }

void MainButtoninfo( byte choice )
    {
    byte counter;

    Statusline( "Hauptmenu", "</> <Enter>" );

    MainInfo.title = MainTitle[choice];
    BoxDraw( &MainInfo );

    for( counter = 0; counter < 4; counter++ )
	BoxWrite( &MainInfo, 1, (byte)(counter + 1), LEFT, MainDescription[choice][counter] );
    for( counter = 0; counter < 3; counter++ )
	BoxWrite( &MainInfo, 0, (byte)(counter + 6), CENTER, MainDescription[choice][counter + 4] );
    }
