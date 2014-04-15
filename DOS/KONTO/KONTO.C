// ************************
// *** Konto - Programm ***
// ***			***
// ***	   Mainmodul	***
// ************************
// ***			***
// ************************

#include "constant.h"

void ScrWriteInstructions( const char *firststring, const char *secondstring );
void ScrWriteStatus( const char *string );
void ScrWritePossibleKeys( const char *string );

word ProductInfoProc( byte message, word parameter );

word KontiverzeichnisProc( byte message, word parameter );
word DruckerportProc( byte message, word parameter );
word StartProc( byte message, word parameter );

bool Datenauswertung( void );
void Monatsauswertung( file ExportFile, byte days, byte start, byte end );

byte TageProMonat[12] = { 31, 28, 31, 30, 31, 30,
			  31, 31, 30, 31, 30, 31 };

struct frame ProductInfo =	{ 15,  3, 64, 21, "",			 HIGHLIGHT };

struct frame Kontiverzeichnis = { 42,  4, 67, 18, " Kontiverzeichnis: ", HIGHLIGHT };
struct frame Druckerport =	{ 13,  8, 31, 11, " Drucker ",		 HIGHLIGHT };
struct frame Start =		{  9, 13, 35, 15, "",			 HIGHLIGHT };

const char StandartInstructions[] = "<Tab> - Wechseln des Bildschirmbereichs. <Esc> - Programm verlassen.";

struct KontiVerzeichnisEintrag KontiVerzeichnis[KONTIANZAHL];
byte DPort;
byte ErfJahr;
byte ErfMonat;

struct SatzAnfang SatzAnfang;
struct SatzMitte SatzMitte;
struct SatzEnde SatzEnde;

konto (_far *Konti)[20];

char Abteilungen[1000][5];
word AnzahlAbteilungen;

void Main( void )
    {

    file konfigfile;
    byte bcounter;
    word wcounter;

    word key;

    word (*ObjectProc[NUMOFOBJECTS])( byte message, word parameter ) =
	{ KontiverzeichnisProc, DruckerportProc, StartProc };

    byte selection = 2;

    ScrSetMode();
    ScrSetCursor( 0, 25 );

    ProductInfoProc( INIT, (word)&ProductInfo );
    ProductInfoProc( PAINTFRAME, 0 );
    ProductInfoProc( SETFOCUS, 0 );

    while( BiosGetKey() != KBENTER );
    ScrClr( BACKGROUND );

    ScrBoxChgColor( 0, 22, 79, 22, STATUS );
    ScrBoxChgColor( 0, 23, 79, 24, INSTRUCTIONS );

    konfigfile = DosOpenFile( DOS_ACCESS_RDONLY, KONFIGFILENAME );
    if( DosGetErrorcode() )
	{
	for( bcounter = 0; bcounter < KONTIANZAHL; bcounter++ )
	    {
	    KontiVerzeichnis[bcounter].Beruecksichtigen = FALSE;
	    BinToAscii( bcounter + 1, 2, KontiVerzeichnis[bcounter].Kontonummer, LEFT, 2 );
	    KontiVerzeichnis[bcounter].Beschreibung[0] = 0;
	    }

	KontiVerzeichnis[0].Beruecksichtigen = TRUE;

	DPort = 0;

	ErfJahr = 0;
	ErfMonat = 0;
	}
	else
	{
	DosReadFile( konfigfile, sizeof( KontiVerzeichnis ), (void _far *)KontiVerzeichnis );
	DosReadFile( konfigfile, sizeof( DPort ), (void _far *)&DPort );
	DosReadFile( konfigfile, sizeof( ErfJahr ), (void _far *)&ErfJahr );
	DosReadFile( konfigfile, sizeof( ErfMonat ), (void _far *)&ErfMonat );
	}

    KontiverzeichnisProc( INIT, (word)&Kontiverzeichnis );
    DruckerportProc( INIT, (word)&Druckerport );
    StartProc( INIT, (word)&Start );

    for( bcounter = 0; bcounter < NUMOFOBJECTS; bcounter++ )
	ObjectProc[bcounter]( PAINTFRAME, 0 );

    ObjectProc[selection]( SETFOCUS, 0 );

    do
	{
	key = BiosGetKey();

	key = ObjectProc[selection]( KEY, key );
	if( key )
	    switch( key )
		{
		case KBTAB:
		    ObjectProc[selection]( CLEARFOCUS, 0 );
		    selection++;
		    if( selection == NUMOFOBJECTS )
			selection = 0;
		    ObjectProc[selection]( SETFOCUS, 0 );
		    break;
		case KBSHTAB:
		    ObjectProc[selection]( CLEARFOCUS, 0 );
		    if( selection == 0 )
			selection = NUMOFOBJECTS - 1;
		    else
			selection--;
		    ObjectProc[selection]( SETFOCUS, 0 );
		    break;

		case KBESC:
		    break;
		}
	}
    while( key != KBESC	);

    for( bcounter = 0; bcounter < NUMOFOBJECTS; bcounter++ )
	ObjectProc[bcounter]( DESTROY, 0 );


    konfigfile = DosCreateFile( DOS_ATTRIB_NORMAL, KONFIGFILENAME );

    DosWriteFile( konfigfile, sizeof( KontiVerzeichnis ), (void _far *)KontiVerzeichnis );
    DosWriteFile( konfigfile, sizeof( DPort ), (void _far *)&DPort );
    DosWriteFile( konfigfile, sizeof( ErfJahr ), (void _far *)&ErfJahr );
    DosWriteFile( konfigfile, sizeof( ErfMonat ), (void _far *)&ErfMonat );

    ScrRestoreMode();
    }

word ProductInfoProc( byte message, word parameter )
    {
    static struct frame *frame;
    switch( message )
	{
	case INIT:
	    frame = (void *)parameter;
	    return( 0 );

	case PAINTFRAME:
	    ScrDrawFrame( frame, SINGLE );
	    ProductInfoProc( PAINT, 0 );
	    return( 0 );

	case PAINT:
	    ScrFrameWriteCenter( frame, 2, "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø" );
	    ScrFrameWriteCenter( frame, 3, "≥                                    ≥" );
	    ScrFrameWriteCenter( frame, 4, "≥      Zeitkonti Summierung 1.0      ≥" );
	    ScrFrameWriteCenter( frame, 5, "≥                                    ≥" );
	    ScrFrameWriteCenter( frame, 6, "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ" );

	    ScrFrameWriteCenter( frame, 8, "(c) Copyright 1992 Juraj Skripsky" );
	    ScrFrameWriteCenter( frame, 10, "Designed and Developed by" );
	    ScrFrameWriteCenter( frame, 11, "Juraj Skripsky" );
	    ScrFrameWriteCenter( frame, 12, "CH-8952 Schlieren" );
	    ScrFrameWriteCenter( frame, 15, "Bitte drÅcken sie ENTER," );
	    ScrFrameWriteCenter( frame, 16, "um fortzufahren." );
	    return( 0 );

	case SETFOCUS:
	    ScrDrawFrame( frame, DOUBLE );
	    return( 0 );

	default:
	    return( parameter );
	}
    }


word KontiverzeichnisProc( byte message, word parameter )
    {
    static struct frame *frame;
    static byte xselection;
    static byte yselection;
    byte counter;

    switch( message )
	{
	case INIT:
	    frame = (void *)parameter;
	    xselection = TEXT;
	    yselection = 0;
	    return( 0 );

	case PAINTFRAME:
	    ScrDrawFrame( frame, SINGLE );
	    KontiverzeichnisProc( PAINT, 0 );
	    return( 0 );

	case PAINT:
	    for( counter = 0; counter < KONTIANZAHL; counter++ )
		{
		if( KontiVerzeichnis[counter].Beruecksichtigen )
		    ScrFrameCharacter( frame, 2, (byte)(1 + 2 * counter), CHECKCHAR );
		else
		    ScrFrameCharacter( frame, 2, (byte)(1 + 2 * counter), SPACECHAR );

		ScrFrameWrite( frame, 5, (byte)(1 + 2 * counter), KontiVerzeichnis[counter].Kontonummer );
		ScrFrameWrite( frame, 9, (byte)(1 + 2 * counter), KontiVerzeichnis[counter].Beschreibung );
		}

	    return( 0 );

	case SETFOCUS:
	    ScrDrawFrame( frame, DOUBLE );
	    ScrWriteStatus( "Kontiverzeichnis" );
	    ScrWritePossibleKeys( "</> <Leertaste> <Enter> <Tab> <Esc>" );
	    ScrWriteInstructions( "<Leertaste> - Konto ein-/ausschalten. <Enter> - Feld editieren.", StandartInstructions );

	    switch( xselection )
		{
		case TEXT:
		    ScrFrameChgColor( frame, 8, (byte)(1 + 2 * yselection), 19, (byte)(1 + 2 * yselection), HIGHLIGHT );
		    break;

		case KONTONUMBER:
		    ScrFrameChgColor( frame, 4, (byte)(1 + 2 * yselection), 7, (byte)(1 + 2 * yselection), HIGHLIGHT );
		    break;
		}

	    return( 0 );

	case CLEARFOCUS:
	    ScrDrawFrame( frame, SINGLE );
	    ScrWriteStatus( "" );
	    ScrWritePossibleKeys( "" );
	    ScrWriteInstructions( "", "" );

	    ScrFrameChgColor( frame, 4, 1, 19, 12, BACKGROUND );
	    return( 0 );

	case KEY:
	    switch( parameter )
		{
		case KBDOWN:
		    KontiverzeichnisProc( CLEARFOCUS, 0 );
		    if( yselection == KONTIANZAHL - 1 )
			yselection = 0;
		    else
			yselection++;
		    KontiverzeichnisProc( SETFOCUS, 0 );
		    return( 0 );

		case KBUP:
		    KontiverzeichnisProc( CLEARFOCUS, 0 );
		    if( yselection == 0 )
			yselection = KONTIANZAHL - 1;
		    else
			yselection--;
		    KontiverzeichnisProc( SETFOCUS, 0 );
		    return( 0 );

		case KBRIGHT:
		    KontiverzeichnisProc( CLEARFOCUS, 0 );
		    if( xselection == TEXT )
			xselection = 0;
		    else
			xselection++;
		    KontiverzeichnisProc( SETFOCUS, 0 );
		    return( 0 );

		case KBLEFT:
		    KontiverzeichnisProc( CLEARFOCUS, 0 );
		    if( xselection == 0 )
			xselection = TEXT;
		    else
			xselection--;
		    KontiverzeichnisProc( SETFOCUS, 0 );
		    return( 0 );

		case KBSPACE:
		    KontiVerzeichnis[yselection].Beruecksichtigen = !KontiVerzeichnis[yselection].Beruecksichtigen;
		    KontiverzeichnisProc( CLEARFOCUS, 0 );
		    KontiverzeichnisProc( PAINT, 0 );
		    KontiverzeichnisProc( SETFOCUS, 0 );
		    return( 0 );

		case KBENTER:
		    switch( xselection )
			{
			case KONTONUMBER:
			    ScrWriteStatus( "Eingabe der Kontonummer" );
			    ScrWritePossibleKeys( "<0,1,2...> <Enter>" );
			    ScrWriteInstructions( "Eingabe der Kontonummer.", "<Enter> - Eingabe abschliessen." );

			    ScrFrameInput( frame, 5, (byte)(1 + 2 * yselection), KontiVerzeichnis[yselection].Kontonummer, 1, (byte)(sizeof( KontiVerzeichnis[yselection].Kontonummer ) - 1), NUM );
			    if( KontiVerzeichnis[yselection].Kontonummer[1] == 0 )
				{
				KontiVerzeichnis[yselection].Kontonummer[1] = KontiVerzeichnis[yselection].Kontonummer[0];
				KontiVerzeichnis[yselection].Kontonummer[0] = ZEROCHAR;
				}

			    break;
			case TEXT:
			    ScrWriteStatus( "Eingabe des Kontobeschreibung" );
			    ScrWritePossibleKeys( "<A,B,C...> <Enter>" );
			    ScrWriteInstructions( "Eingabe der Kontobeschreibung.", "<Enter> - Eingabe abschliessen." );

			    ScrFrameInput( frame, 9, (byte)(1 + 2 * yselection), KontiVerzeichnis[yselection].Beschreibung, 0, (byte)(sizeof( KontiVerzeichnis[yselection].Beschreibung ) - 1), ALPHA );
			    break;
			}

		    KontiverzeichnisProc( CLEARFOCUS, 0 );
		    KontiverzeichnisProc( PAINT, 0 );
		    KontiverzeichnisProc( SETFOCUS, 0 );
		    return( 0 );

		default:
		    return( parameter );
		}

	case DESTROY:
	    return( 0 );

	}
    }


word DruckerportProc( byte message, word parameter )
    {
    static struct frame *frame;
    static byte selection;

    switch( message )
	{
	case INIT:
	    frame = (void *)parameter;
	    selection = DPort;
	    return( 0 );

	case PAINTFRAME:
	    ScrDrawFrame( frame, SINGLE );
	    DruckerportProc( PAINT, 0 );
	    return ( 0 );

	case PAINT:
	    ScrFrameWrite( frame, 2, 0, "  Parallel 1 " );
	    ScrFrameWrite( frame, 2, 1, "  Parallel 2 " );
	    switch( DPort )
		{
		case 0:
		    ScrFrameCharacter( frame, 2, 0, CHECKCHAR );
		    break;
		case 1:
		    ScrFrameCharacter( frame, 2, 1, CHECKCHAR );
		    break;
		}
	     return( 0 );

	case SETFOCUS:
	    ScrDrawFrame( frame, DOUBLE );
	    ScrWriteStatus( "Druckerportauswahl" );
	    ScrWritePossibleKeys( "</> <Leertaste> <Tab> <Esc>" );
	    ScrWriteInstructions( "<Leertaste> - Druckerport markieren.", StandartInstructions );

	    switch( selection )
		{
		case 0:
		    ScrFrameChgColor( frame, 1, 0, (byte)(frame->x2 - frame->x1 - 3), 0, HIGHLIGHT );
		    break;
		case 1:
		    ScrFrameChgColor( frame, 1, 1, (byte)(frame->x2 - frame->x1 - 3), 1, HIGHLIGHT );
		    break;
		}

	    return( 0 );

	case CLEARFOCUS:
	    ScrDrawFrame( frame, SINGLE );
	    ScrWriteStatus( "" );
	    ScrWritePossibleKeys( "" );
	    ScrWriteInstructions( "", "" );

	    ScrFrameChgColor( frame, 1, 0, (byte)(frame->x2 - frame->x1 - 3), 1, BACKGROUND );
	    return( 0 );

	case KEY:
	    switch( parameter )
		{
		case KBDOWN:
		    DruckerportProc( CLEARFOCUS, 0 );
		    if( selection == 1 )
			selection = 0;
		    else
			selection++;
		    DruckerportProc( SETFOCUS, 0 );
		    return( 0 );

		case KBUP:
		    DruckerportProc( CLEARFOCUS, 0 );
		    if( selection == 0 )
			selection = 1;
		    else
			selection--;
		    DruckerportProc( SETFOCUS, 0 );
		    return( 0 );

		case KBSPACE:
		    DPort = selection;
		    DruckerportProc( CLEARFOCUS, 0 );
		    DruckerportProc( PAINT, 0 );
		    DruckerportProc( SETFOCUS, 0 );
		    return( 0 );

		default:
		    return( parameter );
		}

	case DESTROY:
	    return( 0 );
	}
    }


word StartProc( byte message, word parameter )
    {
    static struct frame *frame;
    word key;

    switch( message )
	{
	case INIT:
	    frame = (void *)parameter;
	    return( 0 );

	case PAINTFRAME:
	    ScrDrawFrame( frame, SINGLE );
	    StartProc( PAINT, 0 );
	    return ( 0 );

	case PAINT:
	    ScrFrameWrite( frame, 2, 0, "  Daten auswerten..." );
	    return( 0 );

	case SETFOCUS:
	    ScrDrawFrame( frame, DOUBLE );
	    ScrWriteStatus( "" );
	    ScrWritePossibleKeys( "<Enter> <Tab> <Esc>" );
	    ScrWriteInstructions( "<Enter> - Befehl ausfÅhren.", StandartInstructions );

	    ScrFrameChgColor( frame, 2, 0, (byte)(frame->x2 - frame->x1 - 4), 0, HIGHLIGHT );
	    return( 0 );

	case CLEARFOCUS:
	    ScrDrawFrame( frame, SINGLE );
	    ScrWriteStatus( "" );
	    ScrWritePossibleKeys( "" );
	    ScrWriteInstructions( "", "" );

	    ScrFrameChgColor( frame, 1, 0, (byte)(frame->x2 - frame->x1 - 3), 0, BACKGROUND );
	    return( 0 );

	case KEY:
	    switch( parameter )
		{
		case KBENTER:
		    StartProc( CLEARFOCUS, 0 );

		    if( Datenauswertung() )
			{
			ScrWriteStatus( "Datenauswertung" );
			ScrWritePossibleKeys( "<Enter> <Esc>" );
			ScrWriteInstructions( "Datenauswertung erfolgreich abgeschlossen.", "<Enter> - ZurÅck zum Programm. <Esc> - Programm verlassen." );

			do
			    key = BiosGetKey();
			while( (key != KBENTER) && (key != KBESC) );

			if( key == KBESC )
			    return( KBESC );
			}

		    StartProc( SETFOCUS, 0 );
		    return( 0 );

		default:
		    return( parameter );
		}

	case DESTROY:
	    return( 0 );
	}
    }


bool Datenauswertung( void )
{
    file ExportFile;

    char ExportFilename[] = EXPORTFILENAME;
    char VormonatsFilename[] = VORMONFILENAME;

    byte dayscounter;
    byte stringcounter;

    word scancounter;

    bool neueabteilung;
    bool idstring;

    byte bcounter;
    word wcounter;

    konto konto;

    char PeriodenString[] = "16.xx.xx - 15.xx.xx";

    file Printer;
    char DPortName[2][13] = { "LPT1", "Printer.$$$" }; // DEBUG!!!!!!
    word AbteilCounter;
    byte SpaltenCounter;
    char String[SPALTENBREITE + 1] = "-999999.59  ";
    byte Kontonummer;
    byte EffLength;
    bool NegNumber;
    byte LineCounter;

    if( ErfMonat == 0 )
	{
	ExportFile = DosOpenFile( DOS_ACCESS_RDONLY, ExportFilename );
	if( DosGetErrorcode() )
	    {
	    ScrWriteStatus( "FEHLER!" );
	    ScrWritePossibleKeys( "<Enter>" );
	    ScrWriteInstructions( "Exportdatei kann nicht geîffnet werden!", "<Enter> - Monatserfassung abbrechen." );

	    while( BiosGetKey() != KBENTER );

	    return( FALSE );
	    }

	DosReadFile( ExportFile, sizeof( SatzAnfang ), (void _far *)&SatzAnfang );
	DosReadFile( ExportFile, sizeof( SatzMitte ), (void _far *)&SatzMitte );
	DosCloseFile( ExportFile );

	ErfMonat = (byte)AsciiToBin( 2, (char _far *)SatzMitte.Monat );
	ErfJahr = (byte)AsciiToBin( 2, (char _far *)SatzMitte.Jahr );

	DosRenameFile( ExportFilename, VormonatsFilename );

	return( TRUE );
	}

    ScrWriteStatus( "Datenauswertung" );
    ScrWritePossibleKeys( "" );
    ScrWriteInstructions( "Datenauswertung. Bitte warten...", "<Enter> - ZurÅck zum Programm. <Esc> - Programm verlassen." );

    ExportFile = DosOpenFile( DOS_ACCESS_RDONLY, ExportFilename );
    if( DosGetErrorcode() )
	{
	ScrWriteStatus( "FEHLER!" );
	ScrWritePossibleKeys( "<Enter>" );
	ScrWriteInstructions( "Exportdatei kann nicht geîffnet werden!", "<Enter> - Monatserfassung abbrechen." );

	while( BiosGetKey() != KBENTER );

	return( FALSE );
	}

    DosReadFile( ExportFile, sizeof( SatzAnfang ), (void _far *)&SatzAnfang );

    dayscounter = 0;
    do
	{
	DosReadFile( ExportFile, sizeof( SatzMitte ), (void _far *)&SatzMitte );
	dayscounter++;
	}
    while( SatzMitte.Flag == 'D' );
    dayscounter--;

    DosResetFile( ExportFile );

    AnzahlAbteilungen = 0;

    while( DosReadFile( ExportFile, sizeof( SatzAnfang ), (void _far *)&SatzAnfang ) == sizeof( SatzAnfang ) )
	{
	neueabteilung = TRUE;
	for( scancounter = 0; scancounter < AnzahlAbteilungen; scancounter++ )
	    {
	    idstring = TRUE;
	    for( stringcounter = 0; stringcounter < 5; stringcounter++ )
		if( Abteilungen[scancounter][stringcounter] != SatzAnfang.Felder[ABTEILFELD][stringcounter] )
		    {
		    idstring = FALSE;
		    break;
		    }

	    if( idstring )
		neueabteilung = FALSE;
	    }

	if( neueabteilung )
	    {

	    for( stringcounter = 0; stringcounter < 5; stringcounter++ )
		Abteilungen[AnzahlAbteilungen][stringcounter] = SatzAnfang.Felder[ABTEILFELD][stringcounter];

	    AnzahlAbteilungen++;
	    }


	for( bcounter = 0; bcounter < dayscounter; bcounter++ )
	    DosReadFile( ExportFile, sizeof( SatzMitte ), (void _far *)&SatzMitte );

	DosReadFile( ExportFile, sizeof( SatzEnde ), (void _far *)&SatzEnde );
	}

    DosResetFile( ExportFile );

    *Konti = DosAllocFarMem( AnzahlAbteilungen * sizeof( *Konti ) );
    for( wcounter = 0; wcounter < AnzahlAbteilungen; wcounter++ )
	for( bcounter = 0; bcounter < 20; bcounter++ )
	    (Konti[wcounter])[bcounter] = 0;

    Monatsauswertung( ExportFile, dayscounter, 1, 15 );
    DosCloseFile( ExportFile );

    ExportFile = DosOpenFile( DOS_ACCESS_RDONLY, VormonatsFilename );

    DosReadFile( ExportFile, sizeof( SatzAnfang ), (void _far *)&SatzAnfang );

    dayscounter = 0;
    do
	{
	DosReadFile( ExportFile, sizeof( SatzMitte ), (void _far *)&SatzMitte );
	dayscounter++;
	}
    while( SatzMitte.Flag == 'D' );
    dayscounter--;

    DosResetFile( ExportFile );
    Monatsauswertung( ExportFile, dayscounter, 16, dayscounter );
    DosCloseFile( ExportFile );

    Printer = DosCreateFile( DOS_ATTRIB_NORMAL, DPortName[DPort] );
    DosWriteFile( Printer, 2, (void _far *)"E" );
    DosWriteFile( Printer, 5, (void _far *)"&l1O" );

    DosWriteFile( Printer, 20, (void _far *)"Summe der Zeitkonti " );

    BinToAscii( ErfMonat, 2, (char _far *)&(PeriodenString[3]), RIGHT, 2 );
    BinToAscii( ErfJahr, 2, (char _far *)&(PeriodenString[6]), RIGHT, 2 );

    if( ErfMonat == 12 )
	{
	BinToAscii( 1, 2, (char _far *)&(PeriodenString[14]), RIGHT, 2 );
	BinToAscii( ErfJahr + 1, 2, (char _far *)&(PeriodenString[17]), RIGHT, 2 );
	}
    else
	{
	BinToAscii( ErfMonat + 1, 2, (char _far *)&(PeriodenString[14]), RIGHT, 2 );
	BinToAscii( ErfJahr, 2, (char _far *)&(PeriodenString[17]), RIGHT, 2 );
	}

    DosWriteFile( Printer, sizeof( PeriodenString ) - 1, (void _far *)PeriodenString );
    DosWriteFile( Printer, 6, (void _far *)"\n\r\n\r\n\r" );

    DosWriteFile( Printer, 14, (void _far *)"Abteilung     " );
    for( SpaltenCounter = 0; SpaltenCounter < KONTIANZAHL; SpaltenCounter++ )
	{
	if( !KontiVerzeichnis[SpaltenCounter].Beruecksichtigen )
		continue;

	stringcounter = 0;
	while( KontiVerzeichnis[SpaltenCounter].Beschreibung[stringcounter] )
	    stringcounter++;

	DosWriteFile( Printer, stringcounter, (void _far *)KontiVerzeichnis[SpaltenCounter].Beschreibung );

	for( ; stringcounter < SPALTENBREITE; stringcounter++ )
	    DosWriteFile( Printer, 1, (void _far *)" " );
	}

    DosWriteFile( Printer, 4, (void _far *)"\r\n\r\n" );

    LineCounter = 5;
    for( wcounter = 0; wcounter < 40; wcounter++ ) // DEBUG!!!!!!
    for( AbteilCounter = 0; AbteilCounter < AnzahlAbteilungen; AbteilCounter++ )
	{
	if( LineCounter == 20 )
	    {
	    DosWriteFile( Printer, 1, (void _far *)"\f" );
	    LineCounter = 0;
	    }

	DosWriteFile( Printer, 5, (void _far *)Abteilungen[AbteilCounter] );
	DosWriteFile( Printer, 5, (void _far *)"     " );

	for( SpaltenCounter = 0; SpaltenCounter < KONTIANZAHL; SpaltenCounter++ )
	    {
	    if( !KontiVerzeichnis[SpaltenCounter].Beruecksichtigen )
		continue;

	    Kontonummer = AsciiToBin( 2, (char _far *)KontiVerzeichnis[SpaltenCounter].Kontonummer );

	    for( stringcounter = 0; stringcounter < SPALTENBREITE; stringcounter++ )
		String[stringcounter] = SPACECHAR;

	    if( (Konti[AbteilCounter])[Kontonummer - 1] < 0 )
		{
		NegNumber = TRUE;
		konto = -((Konti[AbteilCounter])[Kontonummer - 1]);
		}
	    else
		{
		NegNumber = FALSE;
		konto = (Konti[AbteilCounter])[Kontonummer - 1];
		}

	    EffLength = BinToAscii( (dword)(konto / 60), 6, (char _far *)&(String[1]), RIGHT, 1 );
	    String[7] = '.';
	    BinToAscii( (dword)(konto % 60), 2, (char _far *)&(String[8]), RIGHT, 2 );

	    if( NegNumber )
		String[6 - EffLength] = '-';

	    DosWriteFile( Printer, SPALTENBREITE, (void _far *)String );

	    }
	DosWriteFile( Printer, 2, (void _far *)"\r\n" );
	LineCounter++;

	}
    DosWriteFile( Printer, 1, (void _far *)"\f" );
    DosWriteFile( Printer, 2, (void _far *)"E" );
    DosCloseFile( Printer );

    DosFreeFarMem( *Konti );
    DosDeleteFile( VormonatsFilename );

    ExportFile = DosOpenFile( DOS_ACCESS_RDONLY, ExportFilename );
    DosReadFile( ExportFile, sizeof( SatzAnfang ), (void _far *)&SatzAnfang );
    DosReadFile( ExportFile, sizeof( SatzMitte ), (void _far *)&SatzMitte );
    DosCloseFile( ExportFile );

    ErfMonat = (byte)AsciiToBin( 2, (char _far *)SatzMitte.Monat );
    ErfJahr = (byte)AsciiToBin( 2, (char _far *)SatzMitte.Jahr );

    DosRenameFile( ExportFilename, VormonatsFilename );
    return( TRUE );
}


void Monatsauswertung( file ExportFile, byte days, byte start, byte end )
    {
    bool stringid;
    bool AbteilungOK;
    byte bcounter;
    byte bsubcounter;
    word wcounter;
    byte stringcounter;

    word Abteilnummer;


    while( DosReadFile( ExportFile, sizeof( SatzAnfang ), (void _far *)&SatzAnfang ) == sizeof( SatzAnfang ) )
	{
	for( wcounter = 0; wcounter < 1000; wcounter++ )
	    {
	    stringid = TRUE;
	    for( stringcounter = 0; stringcounter < 5; stringcounter++ )
		if( Abteilungen[wcounter][stringcounter] != SatzAnfang.Felder[ABTEILFELD][stringcounter] )
		    stringid = FALSE;

	    if( stringid )
		{
		AbteilungOK = TRUE;
		break;
		}
	    }

	Abteilnummer = wcounter;

	for( bcounter = 1; bcounter <= start - 1; bcounter++ )
	    DosReadFile( ExportFile, sizeof( SatzMitte ), (void _far *)&SatzMitte );


	for( bcounter = start; bcounter <= end; bcounter++ )
	    {
	    DosReadFile( ExportFile, sizeof( SatzMitte ), (void _far *)&SatzMitte );

	    for( bsubcounter = 0; bsubcounter < 20; bsubcounter++ )
		if( SatzMitte.Zeitkonti[bsubcounter][4] == '+' )
		    (Konti[Abteilnummer])[bsubcounter] += (konto)AsciiToBin( 4, (char _far *)&(SatzMitte.Zeitkonti[bsubcounter][0]) );
		else
		    (Konti[Abteilnummer])[bsubcounter] -= (konto)AsciiToBin( 4, (char _far *)&(SatzMitte.Zeitkonti[bsubcounter][0]) );
	    }


	for( bcounter = end + 1; bcounter <= days; bcounter++ )
	    DosReadFile( ExportFile, sizeof( SatzMitte ), (void _far *)&SatzMitte );

	DosReadFile( ExportFile, sizeof( SatzEnde ), (void _far *)&SatzEnde );

	}


    }

void ScrWriteInstructions( const char *firststring, const char *secondstring)
    {
    ScrCharFill( 0, 24, 80, SPACECHAR );
    ScrCharFill( 0, 23, 80, SPACECHAR );
    ScrWriteCenter( 0, 79, 23, firststring );
    ScrWriteCenter( 0, 79, 24, secondstring );
    }


void ScrWriteStatus( const char *string )
    {
    ScrCharFill( 0, 22, 30, SPACECHAR );
    ScrWrite( 0, 22, string );
    }


void ScrWritePossibleKeys( const char *string )
    {
    ScrCharFill( 30, 22, 50, SPACECHAR );
    ScrWriteRight( 79, 22, string );
    }
