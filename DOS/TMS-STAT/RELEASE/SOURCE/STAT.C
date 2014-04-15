// ****************************
// *** Statistik - Programm ***
// ***	    Mainmodul	    ***
// ****************************
// ***			    ***
// ****************************

#include "constant.h"


void Statusline( const char *lstring, const char *rstring );

void Main( void )
    {
    box TitleBox = { FRAME, 14, 3, 65, 21, MENU, CHOICE, DOUBLE, FALSE, FALSE, "" };

    byte choice;
    byte counter;
    word temp;
    word _far *timer = (word _far *)0x0040006C;

    ScrSetMode();
    ScrSetCursor( 0, 25);
    ScrClr( BACKGROUND );

    for( counter = 0; counter <= 24; counter += 3 )
	{
	temp = *timer;
	TitleBox.x1 = 38 - counter;
	TitleBox.x2 = 41 + counter;
	BoxDraw( &TitleBox );
	while( !(*timer - temp) );
	}

    BoxWrite( &TitleBox, 0, 2, CENTER, "ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿" );
    BoxWrite( &TitleBox, 0, 3, CENTER, "³                                    ³" );
    BoxWrite( &TitleBox, 0, 4, CENTER, "³  Absence Statistics Generator 1.0  ³" );
    BoxWrite( &TitleBox, 0, 5, CENTER, "³                                    ³" );
    BoxWrite( &TitleBox, 0, 6, CENTER, "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ" );
    BoxWrite( &TitleBox, 0, 8, CENTER, "(c) Copyright 1992 Juraj Skripsky" );
    BoxWrite( &TitleBox, 0, 10, CENTER, "Designed and Developed by" );
    BoxWrite( &TitleBox, 0, 11, CENTER, "Juraj Skripsky" );
    BoxWrite( &TitleBox, 0, 12, CENTER, "CH-8952 Schlieren" );
    BoxWrite( &TitleBox, 0, 15, CENTER, "Bitte drcken Sie ENTER," );
    BoxWrite( &TitleBox, 0, 16, CENTER, "um fortzufahren" );
    while( BiosGetKey() != KBENTER );
    ScrClr( BACKGROUND );

    do
	{
	choice = Mainmenu();

	switch( choice )
	    {
	    case 1:
		Statistik( 0, 0, MONTH );
		break;

	    case 2:
		Jahresstatistik();
		break;

	    case 3:
		Teilstatistik();
		break;

	    case 4:
		Konfigmenu();
		break;
	    }
	}
    while( choice != 5 );

    ScrRestoreMode();
    }

void Statusline( const char *lstring, const char *rstring )
    {
    ScrChgColor( 0, 24, 80, STATUSLINE );
    ScrWrite( 1, 24, lstring );
    ScrWriteRight( 78, 24, rstring );
    }
