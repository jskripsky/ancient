// ***************************************
// *** Abwesensheitstabelle - Programm ***
// ***				       ***
// ***		   Mainmodul	       ***
// ***************************************
// ***				       ***
// ***************************************

#include "constant.h"

void ScrWriteInstructions( const char *firststring, const char *secondstring );
void ScrWriteStatus( const char *string );
void ScrWritePossibleKeys( const char *string );

dword Divide( dword dividend, word divisor );
byte BinToAscii( dword number, byte length, char _far *string, byte direction, byte zeros );
word AsciiToBin( byte length, char _far *number );


word PersonenauswahlProc( byte message, word parameter );
word KrankheitscodesProc( byte message, word parameter );
word UnfallcodesProc( byte message, word parameter );
word DruckerportProc( byte message, word parameter );
word ArbeitstagProc( byte message, word parameter );
word StartProc( byte message, word parameter );

word CodelistProc( byte number, byte message, word parameter );

bool Jahr( void );
bool JahresTabelle( void );
void PrintTab( struct MonatsSpalte *MonatsSpalte, file Printer );

bool Monat( void );


byte TageProMonat[12] = { 31, 28, 31, 30, 31, 30,
			  31, 31, 30, 31, 30, 31 };

struct frame Personenauswahl = { 4,   2, 75,  9, " Personenauswahl: ", HIGHLIGHT };
struct frame Krankheitscodes = { 36, 11, 54, 19, " Krankheitscodes ",  HIGHLIGHT };
struct frame Unfallcodes =     { 57, 11, 75, 19, " Unfallcodes ",      HIGHLIGHT };
struct frame Druckerport =     {  4, 11, 21, 14, " Drucker ",	       HIGHLIGHT };
struct frame Arbeitstag =      { 24, 11, 33, 13, " Tag ",	       HIGHLIGHT };
struct frame Start =	       {  4, 16, 33, 19, "",		       HIGHLIGHT };

    char JFAbteilung[5];
    char JFPersonalnummer[9];
    char JFName[30];

const char StandartInstructions[] = "<Tab> - Wechseln des Bildschirmbereichs. <Esc> - Programm verlassen.";

char Abteilung[6];
char Personalnummer[10];
char Name[31];
byte Personenauswahlmodus;

char KCodes[MAXCODES][CODELENGTH];
char UCodes[MAXCODES][CODELENGTH];
word KCodesquant;
word UCodesquant;

word ATag;
byte DPort;

bool Monate[12];
byte ErfassteJahre[MAXJAHRE];
byte ErfJahreNum;


void Main( void )
    {

    file konfigfile;
    file monatsfile;
    byte bcounter;
    word wcounter;

    word key;

    word (*ObjectProc[NUMOFOBJECTS])( byte message, word parameter ) =
	{ PersonenauswahlProc, UnfallcodesProc, KrankheitscodesProc,
	  ArbeitstagProc ,StartProc, DruckerportProc };

    byte selection = 4;


    ScrSetMode();
    ScrSetCursor( 0, 25 );

    ScrBoxChgColor( 0, 22, 79, 22, STATUS );
    ScrBoxChgColor( 0, 23, 79, 24, INSTRUCTIONS );

    konfigfile = DosOpenFile( DOS_ACCESS_RDONLY, KONFIGFILENAME );
    if( DosGetErrorcode() )
	{
	Abteilung[0] = 0;
	Personalnummer[0] = 0;
	Name[0] = 0;
	Personenauswahlmodus = 0;

	KCodesquant = 0;
	UCodesquant = 0;

	ATag = 480;
	DPort = 0;

	for( bcounter = 0; bcounter < 12; bcounter++ )
	    Monate[bcounter] = FALSE;

	ErfJahreNum = 0;

	}
    else
	{
	DosReadFile( konfigfile, sizeof( Abteilung ), (void _far *)Abteilung );
	DosReadFile( konfigfile, sizeof( Personalnummer ), (void _far *)Personalnummer );
	DosReadFile( konfigfile, sizeof( Name ), (void _far *)Name );
	DosReadFile( konfigfile, sizeof( Personenauswahlmodus ), (void _far *)&Personenauswahlmodus );
	DosReadFile( konfigfile, sizeof( ATag ), (void _far *)&ATag );
	DosReadFile( konfigfile, sizeof( KCodesquant ), (void _far *)&KCodesquant );
	DosReadFile( konfigfile, sizeof( UCodesquant ), (void _far *)&UCodesquant );
	DosReadFile( konfigfile, sizeof( KCodes ), (void _far *)KCodes );
	DosReadFile( konfigfile, sizeof( UCodes ), (void _far *)UCodes );
	DosReadFile( konfigfile, sizeof( DPort ), (void _far *)&DPort );
	DosReadFile( konfigfile, sizeof( ErfJahreNum ), (void _far *)&ErfJahreNum );
	DosReadFile( konfigfile, sizeof( ErfassteJahre ), (void _far *)ErfassteJahre );
	DosReadFile( konfigfile, sizeof( Monate ), (void _far *)Monate );
	}
    PersonenauswahlProc( INIT, (word)&Personenauswahl );
    KrankheitscodesProc( INIT, (word)&Krankheitscodes );
    UnfallcodesProc( INIT, (word)&Unfallcodes );
    DruckerportProc( INIT, (word)&Druckerport );
    ArbeitstagProc( INIT, (word)&Arbeitstag );
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

    DosWriteFile( konfigfile, sizeof( Abteilung ), (void _far *)Abteilung );
    DosWriteFile( konfigfile, sizeof( Personalnummer ), (void _far *)Personalnummer );
    DosWriteFile( konfigfile, sizeof( Name ), (void _far *)Name );
    DosWriteFile( konfigfile, sizeof( Personenauswahlmodus ), (void _far *)&Personenauswahlmodus );
    DosWriteFile( konfigfile, sizeof( ATag ), (void _far *)&ATag );
    DosWriteFile( konfigfile, sizeof( KCodesquant ), (void _far *)&KCodesquant );
    DosWriteFile( konfigfile, sizeof( UCodesquant ), (void _far *)&UCodesquant );
    DosWriteFile( konfigfile, sizeof( KCodes ), (void _far *)KCodes );
    DosWriteFile( konfigfile, sizeof( UCodes ), (void _far *)UCodes );
    DosWriteFile( konfigfile, sizeof( DPort ), (void _far *)&DPort );
    DosWriteFile( konfigfile, sizeof( ErfJahreNum ), (void _far *)&ErfJahreNum );
    DosWriteFile( konfigfile, sizeof( ErfassteJahre ), (void _far *)ErfassteJahre );
    DosWriteFile( konfigfile, sizeof( Monate ), (void _far *)Monate );

    ScrRestoreMode();
    }


word PersonenauswahlProc( byte message, word parameter )
    {
    static struct frame *frame;
    static byte selection;

    switch( message )
	{
	case INIT:
	    frame = (void *)parameter;
	    selection = Personenauswahlmodus;
	    return( 0 );

	case PAINTFRAME:
	    ScrDrawFrame( frame, SINGLE );
	    PersonenauswahlProc( PAINT, 0 );
	    return ( 0 );

	case PAINT:
	    ScrFrameWrite( frame, 2, 1, "  Abteilung:      " );
	    ScrFrameWrite( frame, 2, 3, "  Personalnummer: " );
	    ScrFrameWrite( frame, 2, 4, "  Name:           " );
	    ScrFrameWrite( frame, 21, 1, Abteilung );
	    ScrFrameWrite( frame, 21, 3, Personalnummer );
	    ScrFrameWrite( frame, 21, 4, Name );
	    switch( Personenauswahlmodus )
		{
		case 0:
		    ScrFrameCharacter( frame, 2, 1, CHECKCHAR );
		    break;
		case 1:
		    ScrFrameCharacter( frame, 2, 3, CHECKCHAR );
		    break;
		case 2:
		    ScrFrameCharacter( frame, 2, 4, CHECKCHAR );
		    break;
		}

	    return ( 0 );

	case SETFOCUS:
	    ScrDrawFrame( frame, DOUBLE );
	    ScrWriteStatus( "Personenauswahl" );
	    ScrWritePossibleKeys( "</> <Leertaste> <Enter> <Tab> <Esc>" );
	    ScrWriteInstructions( "<Leertaste> - Kriterium markieren. <Enter> - Kriterium editieren.", StandartInstructions );

	    switch( selection )
		{
		case 0:
		    ScrFrameChgColor( frame, 1, 1, (byte)(frame->x2 - frame->x1 - 3), 1, HIGHLIGHT );
		    break;
		case 1:
		    ScrFrameChgColor( frame, 1, 3, (byte)(frame->x2 - frame->x1 - 3), 3, HIGHLIGHT );
		    break;
		case 2:
		    ScrFrameChgColor( frame, 1, 4, (byte)(frame->x2 - frame->x1 - 3), 4, HIGHLIGHT );
		    break;
		}

	    return( 0 );

	case CLEARFOCUS:
	    ScrDrawFrame( frame, SINGLE );
	    ScrWriteStatus( "" );
	    ScrWritePossibleKeys( "" );
	    ScrWriteInstructions( "", "" );

	    ScrFrameChgColor( frame, 1, 1, (byte)(frame->x2 - frame->x1 - 3), 4, BACKGROUND );
	    return( 0 );

	case KEY:
	    switch( parameter )
		{
		case KBDOWN:
		    PersonenauswahlProc( CLEARFOCUS, 0 );
		    if( selection == 2 )
			selection = 0;
		    else
			selection++;
		    PersonenauswahlProc( SETFOCUS, 0 );
		    return( 0 );

		case KBUP:
		    PersonenauswahlProc( CLEARFOCUS, 0 );
		    if( selection == 0 )
			selection = 2;
		    else
			selection--;
		    PersonenauswahlProc( SETFOCUS, 0 );
		    return( 0 );

		case KBSPACE:
		    Personenauswahlmodus = selection;
		    PersonenauswahlProc( CLEARFOCUS, 0 );
		    PersonenauswahlProc( PAINT, 0 );
		    PersonenauswahlProc( SETFOCUS, 0 );
		    return( 0 );

		case KBENTER:
		    switch( selection )
			{
			case 0:
			    ScrWriteStatus( "Abteilungswahl" );
			    ScrWritePossibleKeys( "<0,1,2...> <Enter>" );
			    ScrWriteInstructions( "Eingabe des neuen Abteilungscodes.", "<Enter> - Eingabe abschliessen." );

			    ScrFrameInput( frame, 21, 1, Abteilung, ABTEILCODEMIN, (byte)(sizeof( Abteilung ) - 1), ALPHA );
			    break;
			case 1:
			    ScrWriteStatus( "Eingabe der Personalnummer" );
			    ScrWritePossibleKeys( "<0,1,2...> <Enter>" );
			    ScrWriteInstructions( "Eingabe der neuen Personalnummer.", "<Enter> - Eingabe abschliessen." );

			    ScrFrameInput( frame, 21, 3, Personalnummer, (byte)(sizeof( Personalnummer ) - 1), (byte)(sizeof( Personalnummer ) - 1), NUM );
			    break;
			case 2:
			    ScrWriteStatus( "Eingabe des Namen" );
			    ScrWritePossibleKeys( "<A,B,C...> <Enter>" );
			    ScrWriteInstructions( "Eingabe des neuen Namen und Vornamen.", "<Enter> - Eingabe abschliessen." );

			    ScrFrameInput( frame, 21, 4, Name, 0, (byte)(sizeof( Name ) - 1), ALPHA );
			    break;
			}

		    PersonenauswahlProc( CLEARFOCUS, 0 );
		    PersonenauswahlProc( PAINT, 0 );
		    PersonenauswahlProc( SETFOCUS, 0 );
		    return( 0 );

		default:
		    return( parameter );
		}

	case DESTROY:
	    return( 0 );

	}
    }

word KrankheitscodesProc( byte message, word parameter )
    {

    switch( message )
	{
	case INIT:
	    CodelistProc( KRANKHEIT, INIT, parameter );
	    CodelistProc( KRANKHEIT, INITCODELIST, (word)KCodes );
	    CodelistProc( KRANKHEIT, INITQUANTITY, (word)&KCodesquant );
	    return( 0 );
	default:
	    CodelistProc( KRANKHEIT, message, parameter );
	}

    }

word UnfallcodesProc( byte message, word parameter )
    {

    switch( message )
	{
	case INIT:
	    CodelistProc( UNFALL, INIT, parameter );
	    CodelistProc( UNFALL, INITCODELIST, (word)UCodes );
	    CodelistProc( UNFALL, INITQUANTITY, (word)&UCodesquant );
	    return( 0 );
	default:
	    return( CodelistProc( UNFALL, message, parameter ) );
	}

    }


word CodelistProc( byte number, byte message, word parameter )
    {
    static struct frame *frame[2];

    static byte selection[2];
    static byte firstcode[2];

    static byte columns[2];
    static byte rows[2];

    word wcounter;
    byte bcounter;
    byte entries;

    static char (*Codelist[2])[MAXCODES][CODELENGTH];
    static word *Quantity[2];

    switch( message )
	{
	case INIT:
	    frame[number] = (void *)parameter;
	    columns[number] = (byte)((frame[number]->x2 - frame[number]->x1 - 1) / 5);
	    rows[number] = (byte)(frame[number]->y2 - frame[number]->y1 - 3);
	    selection[number] = 0;
	    firstcode[number] = 0;
	    return( 0 );

	case INITQUANTITY:
	    Quantity[number] = (word *)parameter;
	    return( 0 );

	case INITCODELIST:
	    Codelist[number] = (void *)parameter;
	    return( 0 );

	case PAINTFRAME:
	    ScrDrawFrame( frame[number], SINGLE );
	    CodelistProc( number, PAINT, 0 );
	    return( 0 );

	case PAINT:
	    for( bcounter = 0; bcounter < frame[number]->y2 - frame[number]->y1 - 2; bcounter++ )
		ScrCharFill( (byte)(frame[number]->x1 + 1), (byte)(frame[number]->y1 + 2 + bcounter), (byte)(frame[number]->x2 - frame[number]->x1 - 1), 0 );

	    if( *(Quantity[number]) == 0 )
		return( 0 );

	    entries = (byte)(columns[number] * rows[number]);
	    if( *(Quantity[number]) - firstcode[number] < entries )
		entries = *(Quantity[number]) - firstcode[number];

	    for( bcounter = 0; bcounter < entries; bcounter++ )
		ScrFrameWrite( frame[number], (byte)(2 + 5 * (bcounter / rows[number])), (byte)(1 + (bcounter % rows[number])), (*Codelist[number])[firstcode[number] + bcounter] );

	    return( 0 );

	case SETFOCUS:
	    ScrDrawFrame( frame[number], DOUBLE );
	    ScrWriteStatus( "Abwesenheitscodes" );
	    ScrWritePossibleKeys( "</> <Ins> <Del> <Tab> <Esc>" );
	    ScrWriteInstructions( "<Ins> - Neuen Code einfÅgen. <Del> - Code Lîschen.", StandartInstructions );

	    if( *(Quantity[number]) == 0 )
		{
		ScrFrameChgColor( frame[number], 1, 1, 5, 1, HIGHLIGHT );
		return( 0 );
		}

	    ScrFrameChgColor( frame[number], (byte)(((selection[number] - firstcode[number]) / rows[number]) * 5 + 1),
					     (byte)(((selection[number] - firstcode[number]) % rows[number]) + 1),
					     (byte)(((selection[number] - firstcode[number]) / rows[number]) * 5 + 5),
					     (byte)(((selection[number] - firstcode[number]) % rows[number]) + 1), HIGHLIGHT );

	    return( 0 );

	case CLEARFOCUS:
	    ScrDrawFrame( frame[number], SINGLE );
	    ScrFrameChgColor( frame[number], 0, 0, (byte)(frame[number]->x2 - frame[number]->x1 - 2), (byte)(frame[number]->y2 - frame[number]->y1 - 2), BACKGROUND );

	    ScrWriteStatus( "" );
	    ScrWritePossibleKeys( "" );
	    ScrWriteInstructions( "", "" );

	    return( 0 );

	case KEY:
	    switch( parameter )
		{
		case KBDOWN:
		    if( selection[number] + 1 < *(Quantity[number]) )
			selection[number]++;
		    else
			return( 0 );

		    if( selection[number] - firstcode[number] == rows[number] * columns[number] )
			firstcode[number]++;

		    CodelistProc( number, CLEARFOCUS, 0 );
		    CodelistProc( number, PAINT, 0 );
		    CodelistProc( number, SETFOCUS, 0 );
		    return( 0 );

		case KBUP:
		    if( selection[number] != 0 )
			selection[number]--;
		    else
			return( 0 );

		    if( selection[number] < firstcode[number] )
			firstcode[number]--;

		    CodelistProc( number, CLEARFOCUS, 0 );
		    CodelistProc( number, PAINT, 0 );
		    CodelistProc( number, SETFOCUS, 0 );
		    return( 0 );

		case KBLEFT:
		    for( bcounter = 0; bcounter < rows[number]; bcounter++ )
			CodelistProc( number, KEY, KBUP );
		    return( 0 );

		case KBRIGHT:
		    for( bcounter = 0; bcounter < rows[number]; bcounter++ )
			CodelistProc( number, KEY, KBDOWN );
		    return( 0 );

		case KBDEL:
		    if( *(Quantity[number]) == 0 )
			return( 0 );
		    (*(Quantity[number]))--;
		    if( *(Quantity[number]) == 0 )
			(*Codelist[number])[0][0] = 0;
		    else
			for( wcounter = selection[number]; wcounter <= *(Quantity[number]) - 1; wcounter++ )
			    for( bcounter = 0; bcounter < CODELENGTH; bcounter++ )
				(*Codelist[number])[wcounter][bcounter] = (*Codelist[number])[wcounter + 1][bcounter];

		    if( *(Quantity[number]) == firstcode[number] + selection[number] )
			CodelistProc( number, KEY, KBUP );

		    CodelistProc( number, CLEARFOCUS, 0 );
		    CodelistProc( number, PAINT, 0 );
		    CodelistProc( number, SETFOCUS, 0 );
		    return( 0 );

		case KBINS:
		    (*(Quantity[number]))++;
		    for( wcounter = *(Quantity[number]) - 1; wcounter >= selection[number] + 2; wcounter-- )
			for( bcounter = 0; bcounter < CODELENGTH; bcounter++ )
			    (*Codelist[number])[wcounter][bcounter] = (*Codelist[number])[wcounter - 1][bcounter];

		    if( *(Quantity[number]) == 1 )
			(*Codelist[number])[selection[number]][0] = 0;
		    else
			(*Codelist[number])[selection[number] + 1][0] = 0;
		    CodelistProc( number, KEY, KBDOWN );
		    ScrWriteStatus( "Codeeingabe" );
		    ScrWritePossibleKeys( "<0,1,2...> <Enter>" );
		    ScrWriteInstructions( "Eingabe des neuen Abwesenheitscodes.", "<Enter> - Eingabe abschliessen." );
		    ScrFrameInput( frame[number], (byte)(((selection[number] - firstcode[number]) / rows[number]) * 5 + 2),
						  (byte)(((selection[number] - firstcode[number]) % rows[number]) + 1),
						  (*Codelist[number])[selection[number]], 3, 3, NUM );

		    CodelistProc( number, CLEARFOCUS, 0 );
		    CodelistProc( number, PAINT, 0 );
		    CodelistProc( number, SETFOCUS, 0 );
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


word ArbeitstagProc( byte message, word parameter )
    {
    static struct frame *frame;
    char ATagString[] = " 0.00h";

    switch( message )
	{
	case INIT:
	    frame = (void *)parameter;
	    return( 0 );

	case PAINTFRAME:
	    ScrDrawFrame( frame, SINGLE );
	    ArbeitstagProc( PAINT, 0 );
	    return ( 0 );

	case PAINT:
	    BinToAscii( ATag / 60, 2, (char _far *)&(ATagString[0]), RIGHT, 1 );
	    BinToAscii( ATag % 60, 2, (char _far *)&(ATagString[3]), RIGHT, 2 );
	    ScrFrameWriteCenter( frame, 0, ATagString );
	    return ( 0 );

	case SETFOCUS:
	    ScrDrawFrame( frame, DOUBLE );
	    ScrWriteStatus( "Arbeitstag" );
	    ScrWritePossibleKeys( "</> <Tab> <Esc>" );
	    ScrWriteInstructions( "</> - LÑnge des Arbeitstages einstellen.", StandartInstructions );

	    ScrFrameChgColor( frame, 1, 0, (byte)(frame->x2 - frame->x1 - 3), 0, HIGHLIGHT );
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
		case KBDOWN:
		    if( ATag == 1 )
			ATag = 12 * 60 - 1;
		    else
			ATag--;
		    ArbeitstagProc( CLEARFOCUS, 0 );
		    ArbeitstagProc( PAINT, 0 );
		    ArbeitstagProc( SETFOCUS, 0 );
		    return( 0 );

		case KBUP:
		    ATag++;
		    if( ATag == 12 * 60 )
			ATag = 1;

		    ArbeitstagProc( CLEARFOCUS, 0 );
		    ArbeitstagProc( PAINT, 0 );
		    ArbeitstagProc( SETFOCUS, 0 );
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
    static byte selection;
    word key;

    switch( message )
	{
	case INIT:
	    frame = (void *)parameter;
	    selection = 0;
	    return( 0 );

	case PAINTFRAME:
	    ScrDrawFrame( frame, SINGLE );
	    StartProc( PAINT, 0 );
	    return ( 0 );

	case PAINT:
	    ScrFrameWrite( frame, 2, 0, "  Monat erfassen..." );
	    ScrFrameWrite( frame, 2, 1, "  Jahrestabelle..." );
	    return( 0 );

	case SETFOCUS:
	    ScrDrawFrame( frame, DOUBLE );
	    ScrWriteStatus( "" );
	    ScrWritePossibleKeys( "</> <Enter> <Tab> <Esc>" );
	    ScrWriteInstructions( "<Enter> - Befehls ausfÅhren.", StandartInstructions );

	    switch( selection )
		{
		case 0:
		    ScrFrameChgColor( frame, 2, 0, (byte)(frame->x2 - frame->x1 - 4), 0, HIGHLIGHT );
		    break;
		case 1:
		    ScrFrameChgColor( frame, 2, 1, (byte)(frame->x2 - frame->x1 - 4), 1, HIGHLIGHT );
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
		    StartProc( CLEARFOCUS, 0 );
		    if( selection == 1 )
			selection = 0;
		    else
			selection++;
		    StartProc( SETFOCUS, 0 );
		    return( 0 );

		case KBUP:
		    StartProc( CLEARFOCUS, 0 );
		    if( selection == 0 )
			selection = 1;
		    else
			selection--;
		    StartProc( SETFOCUS, 0 );
		    return( 0 );

		case KBENTER:
		    StartProc( CLEARFOCUS, 0 );

		    switch( selection )
			{
			case 0:
			    if( Monat() )
				{
				ScrWriteStatus( "Monatserfassung" );
				ScrWritePossibleKeys( "<Enter> <Esc>" );
				ScrWriteInstructions( "Monatserfassung erfolgreich abgeschlossen.", "<Enter> - ZurÅck zum Programm. <Esc> - Programm verlassen." );

				do
				    key = BiosGetKey();
				while( (key != KBENTER) && (key != KBESC) );

				if( key == KBESC )
				    return( KBESC );
				}

			    StartProc( SETFOCUS, 0 );
			    break;
			case 1:
			    if( Jahr() )
				{
				ScrWriteStatus( "Jahrestabelle" );
				ScrWritePossibleKeys( "<Enter> <Esc>" );
				ScrWriteInstructions( "Jahrestabelle(n) wurden ausgedruckt.", "<Enter> - ZurÅck zum Programm. <Esc> - Programm verlassen." );

				do
				    key = BiosGetKey();
				while( (key != KBENTER) && (key != KBESC) );

				if( key == KBESC )
				    return( KBESC );
				}

			    StartProc( SETFOCUS, 0 );
			    break;
			}

		    return( 0 );

		default:
		    return( parameter );
		}

	case DESTROY:
	    return( 0 );
	}
    }


bool Jahr( void )
    {
    char MFAbteilung[5];
    char MFPersonalnummer[9];
    char MFName[30];

    file MonatsFile;
    file JahresFile;

    char JahresFileName[] = "Jahr-00.TAB";
    char MonatsFileName[] = "Mon-0000.TAB";

    byte Jahresnummer;

    byte _far *TempBuffer;

    static struct MonatsSpalte KMonatsSpalte[12];
    static struct MonatsSpalte UMonatsSpalte[12];

    bool AnzahlMitarbeiterOK = TRUE;

    word Mitarbeiter = 0;
    word Tempword;

    byte Tempbyte;

    word key;

    word counter;

    byte bcounter;
    word wcounter;
    byte moncounter;

    bool ErfasstesJahr;

    ScrWriteStatus( "Jahreserfassung..." );
    ScrWritePossibleKeys( "" );
    ScrWriteInstructions( "", "Jahr wird erfasst. Bitte warten..." );

    ErfasstesJahr = FALSE;
    for( bcounter = 0; bcounter < ErfJahreNum; bcounter++ )
	if( (ErfassteJahre[bcounter]) == (DosYear() % 100) - 1 )
	    ErfasstesJahr = TRUE;

    if( ErfasstesJahr )
	return( JahresTabelle() );

    for( moncounter = 0; moncounter < 12; moncounter++ )
	{
	BinToAscii( moncounter + 1, 2, (char _far *)&(MonatsFileName[4]), RIGHT, 2 );
	BinToAscii( (DosYear() % 100) - 1, 2, (char _far *)&(MonatsFileName[6]), RIGHT, 2 );

	MonatsFile = DosOpenFile( DOS_ACCESS_RDONLY, MonatsFileName );
	if( DosGetErrorcode() )
	    {
	    ScrWriteStatus( "FEHLER!" );
	    ScrWritePossibleKeys( "<Enter>" );
	    ScrWriteInstructions( "Eine Monatsdatei kann nicht geîffnet werden!", "<Enter> - Jahreserfassung abbrechen." );
	    while( BiosGetKey() != KBENTER );

	    return( FALSE );
	    }

	if( Mitarbeiter == 0 )
	    DosReadFile( MonatsFile, sizeof( Mitarbeiter ), (void _far *)&Mitarbeiter );
	else
	    {
	    DosReadFile( MonatsFile, sizeof( Tempword ), (void _far *)&Tempword );
	    if( Tempword !=Mitarbeiter )
		AnzahlMitarbeiterOK = FALSE;
	    }

	DosCloseFile( MonatsFile );
	}

    if( !AnzahlMitarbeiterOK )
	{
	ScrWriteStatus( "FEHLER!" );
	ScrWritePossibleKeys( "<Enter>" );
	ScrWriteInstructions( "Monatsdaten wurden mit verschieden Einstellungen exportiert!", "<Enter> - Jahreserfassung abbrechen." );
	while( BiosGetKey() != KBENTER );

	return( FALSE );
	}

    BinToAscii( (DosYear() % 100) - 1, 2, (char _far *)&(JahresFileName[5]), RIGHT, 2 );
    JahresFile = DosCreateFile( DOS_ATTRIB_NORMAL, JahresFileName );

    DosWriteFile( JahresFile, sizeof( Mitarbeiter ), (void _far *)&Mitarbeiter );

    TempBuffer = DosAllocFarMem( 2 * sizeof( word ) * 31 + sizeof( MFPersonalnummer ) + sizeof( MFName ) + sizeof( MFAbteilung ) );

    for( counter = 0; counter < Mitarbeiter; counter++ )
	{
	ScrBoxChgColor( 0, 24, (byte)Divide( (dword)(79 * counter), (word)Mitarbeiter ), 24, PROGRESSBAR );

	for( moncounter = 0; moncounter < 12; moncounter++ )
	    {
	    BinToAscii( moncounter + 1, 2, (char _far *)&(MonatsFileName[4]), RIGHT, 2 );
	    BinToAscii( (DosYear() % 100) - 1, 2, (char _far *)&(MonatsFileName[6]), RIGHT, 2 );

	    MonatsFile = DosOpenFile( DOS_ACCESS_RDONLY, MonatsFileName );
	    DosReadFile( MonatsFile, sizeof( Mitarbeiter ), (void _far *)&Mitarbeiter );
	    DosReadFile( MonatsFile, sizeof( KMonatsSpalte[moncounter].AnzahlTage ), (void _far *)&KMonatsSpalte[moncounter].AnzahlTage );
	    UMonatsSpalte[moncounter].AnzahlTage = KMonatsSpalte[moncounter].AnzahlTage;

	    for( wcounter = 0; wcounter < counter; wcounter++ )
		DosReadFile( MonatsFile, 2 * sizeof( word ) * 31 + sizeof( MFPersonalnummer ) + sizeof( MFName ) + sizeof( MFAbteilung ), (void _far *)TempBuffer );

	    DosReadFile( MonatsFile, sizeof( MFPersonalnummer ), (void _far *)MFPersonalnummer );
	    DosReadFile( MonatsFile, sizeof( MFName ), (void _far *)MFName );
	    DosReadFile( MonatsFile, sizeof( MFAbteilung ), (void _far *)MFAbteilung );

	    for( bcounter = 0; bcounter < 31; bcounter++ )
		{
		DosReadFile( MonatsFile, sizeof( KMonatsSpalte[moncounter].Tag[bcounter].AbwDauer ), (void _far *)&(KMonatsSpalte[moncounter].Tag[bcounter].AbwDauer) );
		DosReadFile( MonatsFile, sizeof( UMonatsSpalte[moncounter].Tag[bcounter].AbwDauer ), (void _far *)&(UMonatsSpalte[moncounter].Tag[bcounter].AbwDauer) );
		}

	    DosCloseFile( MonatsFile );
	    }

	DosWriteFile( JahresFile, sizeof( MFPersonalnummer ), (void _far *)MFPersonalnummer );
	DosWriteFile( JahresFile, sizeof( MFName ), (void _far *)MFName );
	DosWriteFile( JahresFile, sizeof( MFAbteilung ), (void _far *)MFAbteilung );

	DosWriteFile( JahresFile, sizeof( KMonatsSpalte ), (void _far *)KMonatsSpalte );
	DosWriteFile( JahresFile, sizeof( UMonatsSpalte ), (void _far *)UMonatsSpalte );

	ScrBoxChgColor( 0, 24, 79, 24, INSTRUCTIONS );
	}


    for( moncounter = 0; moncounter < 12; moncounter++ )
	    {
	    BinToAscii( moncounter + 1, 2, (char _far *)&(MonatsFileName[4]), RIGHT, 2 );
	    BinToAscii( (DosYear() % 100) - 1, 2, (char _far *)&(MonatsFileName[6]), RIGHT, 2 );
	    Endversion:
	    DosDeleteFile( MonatsFileName );
	    }

    DosFreeFarMem( TempBuffer );

    if( ErfJahreNum == 40 )
	ErfJahreNum = 0;
    ErfassteJahre[ErfJahreNum] = (DosYear() % 100) - 1;
    ErfJahreNum++;

    DosCloseFile( JahresFile );

    ScrBoxChgColor( 0, 24, 79, 24, INSTRUCTIONS );

    ScrWriteStatus( "Jahreserfassung" );
    ScrWritePossibleKeys( "<Enter> <Esc>" );
    ScrWriteInstructions( "Jahreserfassung erfolgreich abgeschlossen.", "<Enter> - Jahrestabelle(n) nun drucken. <Esc> - ZurÅck zum Programm." );

    do
	key = BiosGetKey();
    while( (key != KBENTER) && (key != KBESC) );

    if( key == KBENTER	)
	return( JahresTabelle() );
    else
	return( TRUE );
    }


bool JahresTabelle( void )
{

    char DPortName[2][13] = { "LPT1", "LPT2" };

    file JahresFile;
    file Printer;

    char JahresFileName[] = "Jahr-00.TAB";
    byte Jahresnummer;

    static struct MonatsSpalte KMonatsSpalte[12];
    static struct MonatsSpalte UMonatsSpalte[12];

    word Mitarbeiter = 0;

    bool EintragErfassen;

    word counter;
    byte bcounter;
    word wcounter;

    dword monatstotal;
    byte monatstotalprozent;

    byte stringcounter;

    ScrWriteStatus( "Jahrestabellen..." );
    ScrWritePossibleKeys( "" );
    ScrWriteInstructions( "", "Jahrestabellen werden gedruckt. Bitte warten..." );

    BinToAscii( (DosYear() % 100) - 1, 2, (char _far *)&(JahresFileName[5]), RIGHT, 2 );
    JahresFile = DosOpenFile( DOS_ACCESS_RDONLY, JahresFileName );
    if( DosGetErrorcode() )
	{
	ScrWriteStatus( "FEHLER!" );
	ScrWritePossibleKeys( "<Enter>" );
	ScrWriteInstructions( "Jahresdatei kann nicht geîffnet werden!", "<Enter> - Jahrestabellendruck abbrechen." );
	while( BiosGetKey() != KBENTER );

	return( FALSE );
	}

    DosReadFile( JahresFile, sizeof( Mitarbeiter ), (void _far *)&Mitarbeiter );

    Printer = DosCreateFile( DOS_ATTRIB_NORMAL, DPortName[DPort] );
    DosWriteFile( Printer, 2, (void _far *)"E" );
    DosWriteFile( Printer, 5, (void _far *)"&l1O" );

    for( counter = 0; counter < Mitarbeiter; counter++ )
	{
	DosReadFile( JahresFile, sizeof( JFPersonalnummer ), (void _far *)JFPersonalnummer );
	DosReadFile( JahresFile, sizeof( JFName ), (void _far *)JFName );
	DosReadFile( JahresFile, sizeof( JFAbteilung ), (void _far *)JFAbteilung );

	DosReadFile( JahresFile, sizeof( KMonatsSpalte ), (void _far *)KMonatsSpalte );
	DosReadFile( JahresFile, sizeof( UMonatsSpalte ), (void _far *)UMonatsSpalte );

	EintragErfassen = TRUE;

	switch( Personenauswahlmodus )
	    {
	    case 0:
		for( stringcounter = 0; stringcounter < sizeof( JFAbteilung ); stringcounter++ )
		    if( Abteilung[stringcounter] == 0 )
			break;
		    else
			if( JFAbteilung[stringcounter] != Abteilung[stringcounter] )
			    EintragErfassen = FALSE;
		break;

	    case 1:
		for( stringcounter = 0; stringcounter < sizeof( JFPersonalnummer ); stringcounter++ )
		    if( JFPersonalnummer[stringcounter] != Personalnummer[stringcounter] )
			EintragErfassen = FALSE;
		break;

	    case 2:
		for( stringcounter = 0; stringcounter < sizeof( JFName ); stringcounter++ )
		    if( Name[stringcounter] == 0 )
			break;
		    else
			if( JFName[stringcounter] != Name[stringcounter] )
			    EintragErfassen = FALSE;
		break;
	    }

	if( !EintragErfassen )
	    continue;

	DosWriteFile( Printer, 30, (void _far *)"Abwesenheiten Krankheitscodes " );
	PrintTab( KMonatsSpalte, Printer );

	DosWriteFile( Printer, 30, (void _far *)"Abwesenheiten Unfallcodes " );
	PrintTab( UMonatsSpalte, Printer );

	}
    DosWriteFile( Printer, 2, (void _far *)"E" );

    DosCloseFile( JahresFile );
    DosCloseFile( Printer );

    return( TRUE );
}

void PrintTab( struct MonatsSpalte *MonatsSpalte, file Printer )
    {
    char MonatsString[12][SPALTENLAENGE + 1] =
	{ " Januar      ", " Februar     ",
	  " Maerz       ", " April       ",
	  " Mai         ", " Juni        ",
	  " Juli        ", " August      ",
	  " September   ", " Oktober     ",
	  " November    ", " Dezember    " };

    byte monatscounter;
    byte tagescounter;

    char string[SPALTENLAENGE + 1];
    char tagstring[TAGSPALTE + 1];

    char tempstring[10];

    dword monatstotal;
    byte monatstotalprozent;

    byte stringcounter;

    BinToAscii( DosYear() - 1, 4, (char _far *)tempstring, LEFT, 2 );
    DosWriteFile( Printer, 4, (void _far *)tempstring );
    DosWriteFile( Printer, 6, (void _far *)"\n\r\n\r\n\r" );

    DosWriteFile( Printer, 6, (void _far *)"Name: " );
    DosWriteFile( Printer, sizeof( JFName ), (void _far *)JFName );
    DosWriteFile( Printer, 5, (void _far *)"     " );
    DosWriteFile( Printer, 13, (void _far *)"Personalnr.: " );
    DosWriteFile( Printer, sizeof( JFPersonalnummer ), (void _far *)JFPersonalnummer );
    DosWriteFile( Printer, 26, (void _far *)"                          " );
    DosWriteFile( Printer, 11, (void _far *)"Abteilung: " );
    DosWriteFile( Printer, sizeof( JFAbteilung ), (void _far *)JFAbteilung );
    DosWriteFile( Printer, 6, (void _far *)"\n\r\n\r\n\r" );
    DosWriteFile( Printer, 5, (void _far *)"&k2S" );

    for( stringcounter = 0; stringcounter < TAGSPALTE; stringcounter++ )
	tagstring[stringcounter] = SPACECHAR;
    DosWriteFile( Printer, TAGSPALTE, (void _far *)tagstring );
    for( monatscounter = 0; monatscounter < 12; monatscounter++ )
	DosWriteFile( Printer, SPALTENLAENGE, (void _far *)MonatsString[monatscounter] );
    DosWriteFile( Printer, 2, (void _far *)"\n\r" );

    DosWriteFile( Printer, TAGSPALTE, (void _far *)tagstring );
    for( monatscounter = 0; monatscounter < 12; monatscounter++ )
	DosWriteFile( Printer, SPALTENLAENGE, (void _far *)" ---------   " );
    DosWriteFile( Printer, 4, (void _far *)"\n\r\n\r" );

    tagstring[TAGSPALTE - 4] = '.';

    for( tagescounter = 0; tagescounter < 31; tagescounter++ )
	{
	BinToAscii( tagescounter + 1, 2, (char _far *)&(tagstring[TAGSPALTE - 6]), RIGHT, 1 );
	DosWriteFile( Printer, TAGSPALTE, (void _far *)tagstring );

	for( monatscounter= 0; monatscounter < 12; monatscounter++ )
	    {
	    for( stringcounter = 0; stringcounter < SPALTENLAENGE; stringcounter++ )
		string[stringcounter] = SPACECHAR;

	    if( (MonatsSpalte[monatscounter].AnzahlTage - 1 < monatscounter) || (MonatsSpalte[monatscounter].Tag[tagescounter].AbwDauer == 0) )
		{
		DosWriteFile( Printer, SPALTENLAENGE, (void _far *)string );
		continue;
		}

	    BinToAscii( MonatsSpalte[monatscounter].Tag[tagescounter].AbwDauer / 60, 2, (char _far *)&(string[0]), RIGHT, 1 );
	    string[2] = '.';
	    BinToAscii( MonatsSpalte[monatscounter].Tag[tagescounter].AbwDauer % 60, 2, (char _far *)&(string[3]), RIGHT, 2 );

	    MonatsSpalte[monatscounter].Tag[tagescounter].AbwProzent = (byte)Divide( 100 * MonatsSpalte[monatscounter].Tag[tagescounter].AbwDauer, ATag );
	    BinToAscii( MonatsSpalte[monatscounter].Tag[tagescounter].AbwProzent, 3, (char _far *)&(string[6]), RIGHT, 1 );
	    string[9] = '%';


	    DosWriteFile( Printer, SPALTENLAENGE, (void _far *)string );
	    }

	DosWriteFile( Printer, 2, (void _far *)"\n\r" );
	}

    DosWriteFile( Printer, 2, (void _far *)"\n\r" );
    DosWriteFile( Printer, TAGSPALTE, (void _far *)"Total:   ");
    for( monatscounter= 0; monatscounter < 12; monatscounter++ )
	{
	monatstotal = 0;
	for( tagescounter = 0; tagescounter < MonatsSpalte[monatscounter].AnzahlTage; tagescounter++ )
	monatstotal += MonatsSpalte[monatscounter].Tag[tagescounter].AbwDauer;

	for( stringcounter = 0; stringcounter < SPALTENLAENGE; stringcounter++ )
	    string[stringcounter] = SPACECHAR;

	BinToAscii( monatstotal / 60, 3, (char _far *)&(string[0]), RIGHT, 1 );
	string[3] = '.';
	BinToAscii( monatstotal % 60, 2, (char _far *)&(string[4]), RIGHT, 2 );

	monatstotalprozent = (byte)Divide( (dword)(100 * monatstotal), (word)(ATag * MonatsSpalte[monatscounter].AnzahlTage) );

	BinToAscii( monatstotalprozent, 3, (char _far *)&(string[6]), RIGHT, 1 );
	string[9] = '%';

	DosWriteFile( Printer, SPALTENLAENGE, (void _far *)string );
	}
    DosWriteFile( Printer, 2, (void _far *)"\n\r" );

    DosWriteFile( Printer, 5, (void _far *)"&k0S" );
    DosWriteFile( Printer, 1, (void _far *)"\f" );

    }


bool Monat( void )
    {
    file ExportFile;
    file MonatsFile;

    char MonatsFileName[] = "Mon-0000.TAB";

    struct SatzAnfang _far *SatzAnfang;
    struct SatzMitte _far *SatzMitte;
    struct SatzEnde _far *SatzEnde;

    word KCounter = 0;
    word UCounter = 0;

    word key;

    byte Monatsnummer;
    byte Jahresnummer;
    byte Anfangstag = 0;
    byte Endtag;
    word Mitarbeiter = 0;

    byte bcounter;
    word wcounter;

    word codecounter;
    byte stringcounter;

    word counter;
    word subcounter;

    bool StringIdentical;
    bool KontrollierterSatz;
    char KontrollierterSatzCode[] = "099";

    ScrWriteStatus( "Monatserfassung..." );
    ScrWritePossibleKeys( "" );
    ScrWriteInstructions( "", "Monat wird erfasst. Bitte warten..." );

    ExportFile = DosOpenFile( DOS_ACCESS_RDONLY, EXPORTFILENAME );
    if( DosGetErrorcode() )
	{
	ScrWriteStatus( "FEHLER!" );
	ScrWritePossibleKeys( "<Enter>" );
	ScrWriteInstructions( "Exportdatei kann nicht geîffnet werden!", "<Enter> - Monatserfassung abbrechen." );

	while( BiosGetKey() != KBENTER );

	return( FALSE );
	}

    SatzAnfang = DosAllocFarMem( sizeof( *SatzAnfang ) );
    SatzMitte = DosAllocFarMem( sizeof( *SatzMitte ) );
    SatzEnde = DosAllocFarMem( sizeof( *SatzEnde ) );


    DosReadFile( ExportFile, sizeof( *SatzAnfang ), (void _far *)SatzAnfang );

    for( ; ; )
	{
	DosReadFile( ExportFile, sizeof( *SatzMitte ), (void _far *)SatzMitte );
	if( SatzMitte->Flag == 'F' )
	    break;

	if( Anfangstag == 0 )
	    Anfangstag = (byte)AsciiToBin( (byte)sizeof( SatzMitte->Stempelung ), (char _far *)SatzMitte->Stempelung );

	Endtag = (byte)AsciiToBin( (byte)sizeof( SatzMitte->Stempelung ), (char _far *)SatzMitte->Stempelung );
	}

    DosResetFile( ExportFile );
    DosReadFile( ExportFile, sizeof( *SatzAnfang ), (void _far *)SatzAnfang );
    DosReadFile( ExportFile, sizeof( *SatzMitte ), (void _far *)SatzMitte );

    Jahresnummer = AsciiToBin( 2, (char _far *)SatzMitte->Jahr );
    Monatsnummer = AsciiToBin( 2, (char _far *)SatzMitte->Monat );

    if( Jahresnummer % 4 == 0 )
	TageProMonat[1] = 29;

    if( (Anfangstag != 1) || (Endtag != TageProMonat[Monatsnummer - 1]) )
	{
	DosCloseFile( ExportFile );
	DosFreeFarMem( SatzAnfang );
	DosFreeFarMem( SatzMitte );
	DosFreeFarMem( SatzEnde );

	ScrWriteStatus( "FEHLER!" );
	ScrWritePossibleKeys( "<Enter>" );
	ScrWriteInstructions( "Monat in Exportdatei ist nicht vollstÑndig!", "<Enter> - Monatserfassung abbrechen." );

	while( BiosGetKey() != KBENTER );

	return( FALSE );
	}

    DosResetFile( ExportFile );
    while( DosReadFile( ExportFile, sizeof( *SatzAnfang ), (void _far *)SatzAnfang ) == sizeof( *SatzAnfang ) )
	{
	Mitarbeiter++;
	for( bcounter = 0; bcounter < Endtag - Anfangstag + 1; bcounter++ )
	    DosReadFile( ExportFile, sizeof( *SatzMitte ), (void _far *)SatzMitte );

	DosReadFile( ExportFile, sizeof( *SatzEnde ), (void _far *)SatzEnde );
	}


    BinToAscii( (dword)Monatsnummer, 2, (char _far *)&(MonatsFileName[4]), LEFT, 2 );
    BinToAscii( (dword)Jahresnummer, 2, (char _far *)&(MonatsFileName[6]), LEFT, 2 );

    MonatsFile = DosCreateFile( DOS_ATTRIB_NORMAL, MonatsFileName );

    Monate[Monatsnummer - 1] = TRUE;

    DosWriteFile( MonatsFile, sizeof( Mitarbeiter ), (void _far *)&Mitarbeiter );
    DosWriteFile( MonatsFile, sizeof( Endtag ), (void _far *)&Endtag );

    DosResetFile( ExportFile );
    for( counter = 0; counter < Mitarbeiter; counter++ )
	{
	ScrBoxChgColor( 0, 24, (byte)Divide( (dword)(79 * counter), (word)Mitarbeiter ), 24, PROGRESSBAR );


	DosReadFile( ExportFile, sizeof( *SatzAnfang ), (void _far *)SatzAnfang );

	DosWriteFile( MonatsFile, sizeof( SatzAnfang->Personalnummer ), (void _far *)SatzAnfang->Personalnummer );
	DosWriteFile( MonatsFile, sizeof( SatzAnfang->Name ), (void _far *)SatzAnfang->Name );
	DosWriteFile( MonatsFile, sizeof( SatzAnfang->Felder[ABTEILFELD] ), (void _far *)SatzAnfang->Felder[ABTEILFELD] );

	for( subcounter = 0; subcounter < Endtag; subcounter++ )
	    {
	    KCounter = 0;
	    UCounter = 0;
	    DosReadFile( ExportFile, sizeof( *SatzMitte ), (void _far *)SatzMitte );

	    KontrollierterSatz = TRUE;
	    for( stringcounter = 0; stringcounter < 3; stringcounter++ )
		if( SatzMitte->Kontrolle[stringcounter] != KontrollierterSatzCode[stringcounter] )
		    KontrollierterSatz = FALSE;


	    if( !KontrollierterSatz )
		{
		ScrBoxChgColor( 0, 24, 79, 24, INSTRUCTIONS );
		ScrWriteStatus( "FEHLER!" );
		ScrWritePossibleKeys( "<Enter>" );
		ScrWriteInstructions( "Unkontrollierte Daten gefunden!", "<Enter> - Monatserfassung abbrechen.  2x <Esc> - Ignorieren." );

		do
		    key = BiosGetKey();
		while( (key != KBENTER) && (key != KBESC) );

		switch( key )
		    {
		    case KBESC:
			do
			    key = BiosGetKey();
			while( (key != KBENTER) && (key != KBESC) );

			if( key == KBESC )
			    {
			    ScrWriteStatus( "Monatserfassung..." );
			    ScrWritePossibleKeys( "" );
			    ScrWriteInstructions( "", "Monat wird erfasst. Bitte warten..." );

			    break;
			    }

		    default:
			DosCloseFile( ExportFile );
			DosFreeFarMem( SatzAnfang );
			DosFreeFarMem( SatzMitte );
			DosFreeFarMem( SatzEnde );

			return( FALSE );
		    }
		}

	    for( bcounter = 0; bcounter < 21; bcounter++ )
		{
		for( codecounter = 0; codecounter < KCodesquant; codecounter++ )
		    {
		    StringIdentical = TRUE;

		    for( stringcounter = 0; stringcounter < 3; stringcounter++ )
			if( SatzMitte->Begruendungen[bcounter].Code[stringcounter] != KCodes[codecounter][stringcounter] )
			    StringIdentical = FALSE;

		    if( StringIdentical )
			KCounter += (word)AsciiToBin( 4, (char _far *)SatzMitte->Begruendungen[bcounter].Dauer );
		    }

		for( codecounter = 0; codecounter < UCodesquant; codecounter++ )
		    {
		    StringIdentical = TRUE;

		    for( stringcounter = 0; stringcounter < 3; stringcounter++ )
			if( SatzMitte->Begruendungen[bcounter].Code[stringcounter] != UCodes[codecounter][stringcounter] )
			    StringIdentical = FALSE;

		    if( StringIdentical == TRUE )
			UCounter += (word)AsciiToBin( 4, (char _far *)SatzMitte->Begruendungen[bcounter].Dauer );
		    }
		}


	    DosWriteFile( MonatsFile, sizeof( KCounter ), (void _far *)&KCounter );
	    DosWriteFile( MonatsFile, sizeof( UCounter ), (void _far *)&UCounter );
	    }

	for( subcounter = Endtag; subcounter < 31; subcounter++ )
	    {
	    DosWriteFile( MonatsFile, sizeof( KCounter ), (void _far *)&KCounter );
	    DosWriteFile( MonatsFile, sizeof( UCounter ), (void _far *)&UCounter );
	    }

	DosReadFile( ExportFile, sizeof( *SatzEnde ), (void _far *)SatzEnde );
	ScrBoxChgColor( 0, 24, 79, 24, INSTRUCTIONS );
	}

    DosCloseFile( ExportFile );
    DosCloseFile( MonatsFile );

    DosFreeFarMem( SatzAnfang );
    DosFreeFarMem( SatzMitte );
    DosFreeFarMem( SatzEnde );

    ScrBoxChgColor( 0, 24, 79, 24, INSTRUCTIONS );

    return( TRUE );
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


word AsciiToBin( byte length, char _far *number )
    {
    word endnumber = 0;
    word tempnumber;
    byte counter;
    byte subcounter;

    for( counter = 0; counter < length; counter++ )
	{
	tempnumber = number[counter] - ZEROCHAR;
	for( subcounter = length - counter - 1; subcounter; subcounter-- )
	    tempnumber *= 10;
	endnumber += tempnumber;
	}

    return( endnumber );
    }


byte BinToAscii( dword number, byte length, char _far *string, byte direction, byte zeros )
    {
    byte counter;
    byte remainder;
    byte efflength = 0;

    for( counter = 0; counter < length; counter++ )
	{
	if( (number == 0) && (counter >= zeros) )
	    string[length - counter - 1] = SPACECHAR;
	else
	    {
	    remainder = number % 10;
	    string[length - counter - 1] = remainder + ZEROCHAR;
	    efflength++;
	    }
	number /= 10;
	}

    switch( direction )
	{
	case LEFT:
	    for( counter = 0; counter < efflength; counter++ )
		string[counter] = string[length - efflength + counter];
	    for( counter = 0; counter < length - efflength; counter++ )
		string[length - 1 - counter] = SPACECHAR;
	    break;
	case RIGHT:
	    break;
	}

    return( efflength );
    }


dword Divide( dword dividend, word divisor )
    {
    dword quotient;
    word divisor_half;

    quotient = dividend / divisor;
    divisor_half = divisor / 2;
    if( divisor % 2 == 1 )
	divisor_half++;

    if( dividend % divisor >= divisor_half )
	quotient++;

    return( quotient );
    }
