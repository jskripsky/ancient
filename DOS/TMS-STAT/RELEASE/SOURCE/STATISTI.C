// ****************************
// *** Statistik - Programm ***
// ***	    Statistik	    ***
// ****************************
// ***			    ***
// ****************************

#include "constant.h"

void Jahresstatistik();
void Teilstatistik();
void Statistik( byte begin, byte end, byte type );
void Print( word entries, byte begin, byte end, byte month, byte year, byte type );

bool MitarbeiterOK( char *abteilkey, char _far *abteilungsnummer );
void Cleanup();

word AsciiToBin( byte length, char _far *number );
byte BinToAscii( dword number, byte length, char _far *string, byte direction, byte zeros );
dword Divide( dword dividend, word divisor );

char SatzKontrolliert[] = "099";

char Newline[2] = { '\r', '\n' };
char Formfeed = 0x0C;

bool flag_begruend_cfg = FALSE;
bool flag_abteil_cfg = FALSE;
bool flag_exportfile = FALSE;
bool flag_output = FALSE;
bool flag_internaloutfile = FALSE;
bool flag_inputfile = FALSE;
bool flag_begruendung = FALSE;
bool flag_abteilung = FALSE;
bool flag_Saetze = FALSE;
bool flag_summe = FALSE;
bool flag_dschnitt = FALSE;

file begruend_cfg;
file abteil_cfg;
file exportfile;
file output;
file internaloutfile;
file inputfile;

word arbeiter;
word marbeiter;
word farbeiter;

struct begruendung _far *begruendung;
struct abteilung _far *abteilung;

struct Satz_Anfang _far *Satz_Anfang;
struct Satz_Mitte _far *Satz_Mitte;
struct Satz_Ende _far *Satz_Ende;

dword _far *summe;
dword _far *dschnitt;


char Firmenname[] = "Industrielle Werke Basel";
char Titel[] = "Abwesenheits-Statistik";

char Monthtitle[] = "Monatsstatistik ";
char Parttitle[] = "Teilstatistik ";
char Yeartitle[] = "Jahresstatistik ";

char Monate[12][10] = { "Januar", "Februar", "Maerz", "April", "Mai", "Juni",
			"Juli", "August", "September", "Oktober", "November", "Dezember" };

byte Size_Monate[12] = { 5, 7, 5, 5, 3, 4, 4, 6, 9, 7, 8, 8 };


void Jahresstatistik()
    {
    box StatusBox = { FRAME, 10, 10, 69, 12, MENU, CHOICE, DOUBLE, FALSE, FALSE, "" };
    box OKButton = { BUTTON, 36, 14, 43, 16, MENU, CHOICE, DOUBLE, FALSE, FALSE, "OK" };

    byte lastfound = 0;
    byte filecounter;
    char filename[] = "Mon-01??.Dat";

    byte monthcounter;

    char abteilkey[KEYLENGTH];
    word entries;
    word wcounter;

    char numbertext[10];

    for( filecounter = 76; filecounter <= 99; filecounter++ )
	{
	filename[6] = (filecounter / 10) + ZERO;
	filename[7] = (filecounter % 10) + ZERO;

	inputfile = DosOpenFile( DOS_ACCESS_RDONLY, filename );
	if( DosGetErrorcode() == 0 )
	    {
	    lastfound = filecounter;
	    DosCloseFile( inputfile );
	    }
	}

    if( lastfound == 0 )
	{
	ErrorMessage( "Nicht alle Monatsstatistiken vorhanden!" );
	Cleanup();
	return;
	}

    if( ReadAbteil( abteilkey, &abteilung, &entries ) == TRUE )
	{
	ErrorMessage( "Abteilungsauswahl kann nicht gelesen werden!" );
	Cleanup();
	return;
	}
    flag_abteilung = TRUE;

    if( ReadBegruend( &begruendung, &entries ) == TRUE )
	{
	ErrorMessage( "Begrndungsauswahl kann nicht gelesen werden!" );
	Cleanup();
	return;
	}
    flag_begruendung = TRUE;

    summe = DosAllocFarMem( entries * sizeof( *summe ) );
    flag_summe = TRUE;
    dschnitt = DosAllocFarMem( entries * sizeof( *dschnitt ) );
    flag_dschnitt = TRUE;
    for( wcounter = 0; wcounter < entries; wcounter++ )
	{
	summe[wcounter] = 0x00000000;
	dschnitt[wcounter] = 0x00000000;
	}

    filename[6] = (lastfound / 10) + ZERO;
    filename[7] = (lastfound % 10) + ZERO;

    BoxDraw( &StatusBox );
    BoxWrite( &StatusBox, 0, 0, CENTER, "Statistik wird generiert..." );

    for( monthcounter = 1; monthcounter <= 12; monthcounter++ )
	{
	filename[4] = (monthcounter / 10) + ZERO;
	filename[5] = (monthcounter % 10) + ZERO;

	inputfile = DosOpenFile( DOS_ACCESS_RDONLY, filename );
	if( DosGetErrorcode() )
	    {
	    ErrorMessage( "Nicht alle Monatsstatistiken vorhanden!" );
	    Cleanup();
	    return;
	    }
	flag_inputfile = TRUE;

	DosReadFile( inputfile, sizeof(arbeiter), (void _far *)&arbeiter );
	DosReadFile( inputfile, sizeof(marbeiter), (void _far *)&marbeiter );
	DosReadFile( inputfile, sizeof(farbeiter), (void _far *)&farbeiter );
	DosReadFile( inputfile, sizeof(summe) * entries, (void _far *)dschnitt );
	for( wcounter = 0; wcounter < entries; wcounter++ )
	    summe[wcounter] += dschnitt[wcounter];

	DosCloseFile( inputfile );
	flag_inputfile = FALSE;
	}

    for( wcounter = 0; wcounter < entries; wcounter++ )
	switch( begruendung[wcounter].genus )
	    {
	    case 'N':
		dschnitt[wcounter] = Divide( summe[wcounter], arbeiter );
		break;

	    case 'M':
		if( marbeiter != 0 )
		    dschnitt[wcounter] = Divide( summe[wcounter], marbeiter );
		break;

	    case 'F':
		if( farbeiter != 0 )
		    dschnitt[wcounter] = Divide( summe[wcounter], farbeiter );
		break;
	    }

    BoxDraw( &StatusBox );
    BoxWrite( &StatusBox, 0, 0, CENTER, "Statistik abgeschlossen." );
    Statusline( "", "<Enter>" );
    ButtonMenu( 1, 1, &OKButton, NULL );

    ScrClr( BACKGROUND );
    Print( entries, 0, 0, 0, lastfound, YEAR );

    Cleanup();
    ScrClr( BACKGROUND );
    }


void Teilstatistik()
    {
    byte begin = 1;
    byte end = 31;
    bool flag_begin = TRUE;
    bool flag_end = FALSE;

    word input;

    char status[] = "Vom --. bis zum --.";
    box InputBox =
	{ FRAME, 18, 7, 61, 14, MENU, CHOICE, DOUBLE, FALSE, FALSE, "" };

    Statusline( "Teilstatistik", "</> <\x1B/\x1A> <Esc> <Enter>" );
    BoxDraw( &InputBox );
    BoxWrite( &InputBox, 0, 1, CENTER, "Bereich der Teilstatistik bestimmen," );
    BoxWrite( &InputBox, 0, 2, CENTER, "mit Enter abschliessen." );

    BoxMark( &InputBox, 15, 4, 16, 4 );

    do
	{
	status[4] = (begin / 10) + ZERO;
	status[5] = (begin % 10) + ZERO;
	status[16] = (end / 10) + ZERO;
	status[17] = (end % 10) + ZERO;
	BoxWrite( &InputBox, 0, 4, CENTER, status );

	input = BiosGetKey();

	switch( input )
	    {
	    case KBLEFT:
		BoxUnMark( &InputBox, 15, 4, 28, 4 );
		flag_begin = TRUE;
		flag_end = FALSE;
		BoxMark( &InputBox, 15, 4, 16, 4 );
		break;

	    case KBRIGHT:
		BoxUnMark( &InputBox, 15, 4, 28, 4 );
		flag_begin = FALSE;
		flag_end = TRUE;
		BoxMark( &InputBox, 27, 4, 28, 4 );
		break;

	    case KBUP:
		if( flag_end )
		    {
		    if( end != 31 )
			end++;
		    break;
		    }

		if( flag_begin )
		    {
		    if( begin != 31 )
			begin++;
		    break;
		    }
		break;

	    case KBDOWN:
		if( flag_end )
		    {
		    if( end != 1 )
			end--;
		    break;
		    }

		if( flag_begin )
		    {
		    if( begin != 1 )
			begin--;
		    break;
		    }
		break;

	    case KBESC:
		ScrClr( BACKGROUND );
		return;
	    }
	}
    while( (input != KBENTER) || (begin > end) );

    ScrClr( BACKGROUND );

    Statistik( begin, end, PART );
    }

void Statistik( byte begin, byte end, byte type )
    {

    box StatusBox = { FRAME, 10, 7, 69, 9, MENU, CHOICE, DOUBLE, FALSE, FALSE, "" };
    box CounterBox = { FRAME, 10, 11, 69, 15, MENU, CHOICE, DOUBLE, FALSE, FALSE, "" };
    box OKButton = { BUTTON, 36, 17, 43, 19, MENU, CHOICE, DOUBLE, FALSE, FALSE, "OK" };

    char abteilkey[KEYLENGTH];
    word entries;

    char outputfilename[] = "Mon-0101.Dat";

    byte filebegin = 100;
    byte fileend = 0;

    word percent;

    byte bcounter01;
    byte bcounter02;
    byte bcounter03;
    word wcounter;
    word wtemp;

    char outputquantity[6];
    bool flag01;
    char numbertext[10];

    arbeiter = 0;
    marbeiter = 0;
    farbeiter = 0;


    Satz_Anfang = DosAllocFarMem( sizeof( struct Satz_Anfang ) );
    Satz_Mitte = DosAllocFarMem( sizeof( struct Satz_Mitte ) );
    Satz_Ende = DosAllocFarMem( sizeof( struct Satz_Ende ) );
    flag_Saetze = TRUE;

    if( ReadAbteil( abteilkey, &abteilung, &entries ) == TRUE )
	{
	ErrorMessage( "Abteilungsauswahl kann nicht gelesen werden!" );
	Cleanup();
	return;
	}
    flag_abteilung = TRUE;

    if( ReadBegruend( &begruendung, &entries ) == TRUE )
	{
	ErrorMessage( "Begrndungsauswahl kann nicht gelesen werden!" );
	Cleanup();
	return;
	}
    flag_begruendung = TRUE;

    exportfile = DosOpenFile( DOS_ACCESS_RDONLY, EXPORTFILE );
    if( DosGetErrorcode() )
	{
	ErrorMessage( "Exportdatei kann nicht ge”ffnet werden!" );
	Cleanup();
	return;
	}
    flag_exportfile = TRUE;

    DosReadFile( exportfile, sizeof( struct Satz_Anfang ), Satz_Anfang );
    if( Satz_Anfang->Flag != 'T' )
	{
	ErrorMessage( "Exportdateiformat fehlerhaft!" );
	Cleanup();
	return;
	}

    BoxDraw( &StatusBox );
    BoxWrite( &StatusBox, 0, 0, CENTER, "Statistik wird generiert..." );

    for( ; ; )
	{
	DosReadFile( exportfile, sizeof( struct Satz_Mitte ), Satz_Mitte );
	if( Satz_Mitte->Flag != 'D' )
	    break;

	if( (byte)AsciiToBin( 2, (char _far *)Satz_Mitte->Stempelung ) < filebegin )
	    filebegin = (byte)AsciiToBin( 2, (char _far *)Satz_Mitte->Stempelung );

	if( (byte)AsciiToBin( 2, (char _far *)Satz_Mitte->Stempelung ) > fileend )
	    fileend = (byte)AsciiToBin( 2, (char _far *)Satz_Mitte->Stempelung );
	}

    if( type == MONTH )
	{
	begin = filebegin;
	end = fileend;
	}

    if( type == PART )
	if( (filebegin > begin) || (fileend < end) )
	    {
	    ErrorMessage( "Nicht alle Tage vorhanden!" );
	    Cleanup();
	    return;
	    }

    DosResetFile( exportfile );

    summe = DosAllocFarMem( entries * sizeof( *summe ) );
    flag_summe = TRUE;
    dschnitt = DosAllocFarMem( entries * sizeof( *dschnitt ) );
    flag_dschnitt = TRUE;
    for( wcounter = 0; wcounter < entries; wcounter++ )
	{
	summe[wcounter] = 0x00000000;
	dschnitt[wcounter] = 0x00000000;
	}

    BoxDraw( &CounterBox );
    BoxWrite( &CounterBox, 0, 0, CENTER, "Anzahl erfasster Mitarbeiter:" );

    for( ; ; )
	{
	if( BiosCheckKeybBuffer() )
	    if( BiosGetKey() == KBESC )
		{
		ErrorMessage( "Statistikvorgang wurde abgebrochen!" );
		Cleanup();
		return;
		}

	BinToAscii( (dword)arbeiter, 5, (char _far *)&outputquantity, RIGHT, 1 );
	outputquantity[5] = 0;
	BoxWrite( &CounterBox, 0, 2, CENTER, outputquantity );

	if( DosReadFile( exportfile, sizeof( struct Satz_Anfang ), Satz_Anfang ) != sizeof( struct Satz_Anfang ) )
	    break;
	if( Satz_Anfang->Flag != 'T' )
	    break;

	if( !MitarbeiterOK( abteilkey, (char _far *)(Satz_Anfang->Felder[ABTEILUNG]) ) )
	    {
	    for( bcounter01 = 0; bcounter01 < fileend - filebegin + 1; bcounter01++ )
		DosReadFile( exportfile, sizeof( struct Satz_Mitte ), Satz_Mitte );
	    DosReadFile( exportfile, sizeof( struct Satz_Ende ), Satz_Ende );
	    continue;
	    }

	arbeiter++;

	percent = AsciiToBin( 3, (char _far *)Satz_Anfang->Beschaeftigungsgrad );
	switch( Satz_Anfang->Felder[GESCHLECHT][0])
	    {
	    case 'M':
		marbeiter++;
		break;
	    case 'm':
		marbeiter++;
		break;
	    case 'F':
		farbeiter++;
		break;
	    case 'f':
		farbeiter++;
		break;
	    }

	for( bcounter01 = 0; bcounter01 < begin - filebegin; bcounter01++ )
	    DosReadFile( exportfile, sizeof( struct Satz_Mitte ), Satz_Mitte );

	for( bcounter01 = 0; bcounter01 < end - begin + 1; bcounter01++ )
	    {
	    DosReadFile( exportfile, sizeof( struct Satz_Mitte ), Satz_Mitte );

	    for( bcounter02 = 0; bcounter02 < 21; bcounter02++ )
		for( wcounter = 0; wcounter < entries; wcounter++ )
		    {
		    flag01 = TRUE;

		    for( bcounter03 = 0; bcounter03 < 0x03; bcounter03++ )
			if( Satz_Mitte->Begruendungen[bcounter02].Code[bcounter03] != begruendung[wcounter].number[bcounter03] )
			    flag01 = FALSE;

		    if( flag01 )
			{
			for( bcounter03 = 0; bcounter03 < 0x03; bcounter03++ )
			    if( Satz_Mitte->Kontrolle[bcounter03] != SatzKontrolliert[bcounter03] )
				{
				ErrorMessage( "Ein unkontrollierter Eintrag wurde gefunden!" );
				Cleanup();
				return;
				}

			wtemp = AsciiToBin( 4, (char _far *)(Satz_Mitte->Begruendungen[bcounter02].Dauer) );
			summe[wcounter] += (word)Divide( (wtemp * percent), 100 );
			}
		    }
	    }

	for( bcounter01 = 0; bcounter01 < fileend - end; bcounter01++ )
	    DosReadFile( exportfile, sizeof( struct Satz_Mitte ), Satz_Mitte );

	DosReadFile( exportfile, sizeof( struct Satz_Ende ), Satz_Ende );
	}

    DosCloseFile( exportfile );
    flag_exportfile = FALSE;

    if( arbeiter == 0 )
	{
	ScrClr( BACKGROUND );
	Statusline( "", "<Enter>" );

	ErrorMessage( "Keine Mitarbeiter gefunden!" );
	Cleanup();
	return;
	}

    for( wcounter = 0; wcounter < entries; wcounter++ )
	switch( begruendung[wcounter].genus )
	    {
	    case 'N':
		dschnitt[wcounter] = Divide( summe[wcounter], arbeiter );
		break;

	    case 'M':
		if( marbeiter != 0 )
		    dschnitt[wcounter] = Divide( summe[wcounter], marbeiter );
		break;

	    case 'F':
		if( farbeiter != 0 )
		    dschnitt[wcounter] = Divide( summe[wcounter], farbeiter );
		break;
	    }

    for( bcounter01 = 0; bcounter01 < 2; bcounter01++ )
	{
	outputfilename[4 + bcounter01] = Satz_Mitte->Monat[bcounter01];
	outputfilename[6 + bcounter01] = Satz_Mitte->Jahr[bcounter01];
	}

    if( type == MONTH )
	{
	internaloutfile = DosCreateFile( DOS_ATTRIB_NORMAL, outputfilename );
	flag_internaloutfile = TRUE;
	DosWriteFile( internaloutfile, sizeof(arbeiter), (void _far *)&arbeiter );
	DosWriteFile( internaloutfile, sizeof(marbeiter), (void _far *)&marbeiter );
	DosWriteFile( internaloutfile, sizeof(farbeiter), (void _far *)&farbeiter );
	DosWriteFile( internaloutfile, sizeof(summe) * entries, (void _far *)summe );
	DosWriteFile( internaloutfile, sizeof(dschnitt) * entries, (void _far *)dschnitt );
	DosCloseFile( internaloutfile );
	flag_internaloutfile = FALSE;
	}

    BoxDraw( &StatusBox );
    BoxWrite( &StatusBox, 0, 0, CENTER, "Statistik abgeschlossen." );
    Statusline( "", "<Enter>" );
    ButtonMenu( 1, 1, &OKButton, NULL );

    ScrClr( BACKGROUND );
    Print( entries, begin, end, (byte)AsciiToBin( 2, Satz_Mitte->Monat), (byte)AsciiToBin( 2, Satz_Mitte->Jahr ), type );

    Cleanup();
    ScrClr( BACKGROUND );
    }

void Cleanup()
    {

    if( flag_begruend_cfg )
	{
	DosCloseFile( begruend_cfg );
	flag_begruend_cfg = FALSE;
	}

    if( flag_abteil_cfg )
	{
	DosCloseFile( abteil_cfg );
	flag_abteil_cfg = FALSE;
	}

    if( flag_exportfile )
	{
	DosCloseFile( exportfile );
	flag_exportfile = FALSE;
	}

    if( flag_output )
	{
	DosCloseFile( output );
	flag_output = FALSE;
	}

    if( flag_internaloutfile )
	{
	DosCloseFile( internaloutfile );
	flag_internaloutfile = FALSE;
	}

    if( flag_begruendung )
	{
	DosFreeFarMem( begruendung );
	flag_begruendung = FALSE;
	}

    if( flag_abteilung )
	{
	DosFreeFarMem( abteilung );
	flag_abteilung = FALSE;
	}

    if( flag_Saetze )
	{
	DosFreeFarMem( Satz_Anfang );
	DosFreeFarMem( Satz_Mitte );
	DosFreeFarMem( Satz_Ende );
	flag_Saetze = FALSE;
	}

    if( flag_summe )
	{
	DosFreeFarMem( summe );
	flag_summe = FALSE;
	}

    if( flag_dschnitt )
	{
	DosFreeFarMem( dschnitt	);
	flag_dschnitt = FALSE;
	}

    ScrClr( BACKGROUND );
    }


void Print( word entries, byte begin, byte end, byte month, byte year, byte type )
    {
    byte choice;
    file Printer;

    file tag_cfg;
    word daylength;

    byte counter;
    word entrycounter;

    byte PageNo = 1;
    byte LinesPerPage = 60;
    byte Line = 0;
    bool PageStart = TRUE;

    word days;
    word centidays;
    char NumberString[10];
    byte NumberStringLength;

    box StatusBox = { FRAME, 10, 10, 69, 12, MENU, CHOICE, DOUBLE, FALSE, FALSE, "" };
    box OKButton = { BUTTON, 36, 14, 43, 16, MENU, CHOICE, DOUBLE, FALSE, FALSE, "OK" };

    box PortReqBox =
	{ INFO, 20, 2, 59, 11, MENU, CHOICE, DOUBLE, FALSE, FALSE, "Druckerport" };

    box PortReqButton[3] =
	{ { BUTTON, 28, 13, 51, 15, MENU, CHOICE, SINGLE, FALSE, TRUE,	"Parallel 1" },
	  { BUTTON, 28, 15, 51, 17, MENU, CHOICE, SINGLE, TRUE,	 FALSE, "Parallel 2" },
	  { BUTTON, 28, 19, 51, 21, MENU, CHOICE, SINGLE, FALSE, FALSE, "Abbrechen" } };

    BoxDraw( &PortReqBox );
    BoxWrite( &PortReqBox, 1, 1, LEFT, "W„hlen Sie bitte den Druckerport," );
    BoxWrite( &PortReqBox, 1, 2, LEFT, "an welchen der Ausdruck gesendet" );
    BoxWrite( &PortReqBox, 1, 3, LEFT, "werden soll. Stellen Sie sicher," );
    BoxWrite( &PortReqBox, 1, 4, LEFT, "dass der Drucker eingeschaltet ist." );
    Statusline( "", "</> <Enter>" );
    choice = ButtonMenu( 3, 1, PortReqButton, NULL );

    switch( choice )
	{
	case 1:
	    Printer = DosCreateFile( DOS_ATTRIB_NORMAL, "LPT1" );
	    break;
	case 2:
	    Printer = DosCreateFile( DOS_ATTRIB_NORMAL, "LPT2" );
	    break;
	case 3:
	    ScrClr( BACKGROUND );
	    return;
	}
    ScrClr( BACKGROUND );

    tag_cfg = DosOpenFile( DOS_ACCESS_RDONLY, TAG_CFG );
    if( DosGetErrorcode() )
	{
	ErrorMessage( "Konfigurationsdatei kann nicht ge”ffnet werden!" );
	return( TRUE );
	}

    DosReadFile( tag_cfg, sizeof(daylength), (void _far *)&daylength );
    DosCloseFile( tag_cfg );

    DosWriteFile( Printer, 5, (void _far *)"&l2E" );
    DosWriteFile( Printer, 5, (void _far *)"&a4L" );

    DosWriteFile( Printer, 5, (void _far *)"&a2R" );

    DosWriteFile( Printer, 41, (void _far *)"&10O(8U(s0P(s10H(s12V(s0S(s0B(s3T" );
    BinToAscii( (dword)DosDay(), 2, (char _far *)NumberString, RIGHT, 1 );
    DosWriteFile( Printer, 2, (void _far *)NumberString );
    DosWriteFile( Printer, 1, (void _far *)"." );
    BinToAscii( (dword)DosMonth(), 2, (char _far *)NumberString, RIGHT, 1 );
    DosWriteFile( Printer, 2, (void _far *)NumberString );
    DosWriteFile( Printer, 1, (void _far *)"." );
    BinToAscii( (dword)DosYear(), 4, (char _far *)NumberString, RIGHT, 1 );
    DosWriteFile( Printer, 4, (void _far *)NumberString );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );

    DosWriteFile( Printer, 41, (void _far *)"&10O(8U(s1P(s10H(s12V(s0S(s1B(s5T" );

    DosWriteFile( Printer, 6, (void _far *)"&a73C" );
    DosWriteFile( Printer, sizeof( Firmenname ), (void _far *)Firmenname );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );

    DosWriteFile( Printer, 6, (void _far *)"&a74C" );
    DosWriteFile( Printer, sizeof( Titel ), (void _far *)Titel );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );


    DosWriteFile( Printer, 41, (void _far *)"&10O(8U(s0P(s10H(s12V(s0S(s0B(s3T" );

    switch( type )
	{
	case MONTH:
	    DosWriteFile( Printer, sizeof( Monthtitle ), (void _far *)Monthtitle );
	    DosWriteFile( Printer, 1, (void _far *)" " );
	    DosWriteFile( Printer, Size_Monate[month-1], (void _far *)Monate[month-1] );
	    DosWriteFile( Printer, 3, (void _far *)" 19" );
	    BinToAscii( (dword)year, 2, (char _far *)NumberString, LEFT, 2 );
	    DosWriteFile( Printer, 2, (char _far *)NumberString );
	    break;
	case PART:
	    DosWriteFile( Printer, sizeof( Parttitle ), (void _far *)Parttitle );
	    DosWriteFile( Printer, 4, (void _far *)"vom " );
	    BinToAscii( (dword)begin, 2, (char _far *)NumberString, RIGHT, 0 );
	    DosWriteFile( Printer, 2, (char _far *)NumberString );
	    DosWriteFile( Printer, 10, (void _far *)". bis zum " );
	    BinToAscii( (dword)end, 2, (char _far *)NumberString, RIGHT, 0 );
	    DosWriteFile( Printer, 2, (char _far *)NumberString );
	    DosWriteFile( Printer, 2, (void _far *)". " );

	    DosWriteFile( Printer, Size_Monate[month-1], (void _far *)Monate[month-1] );
	    DosWriteFile( Printer, 3, (void _far *)" 19" );
	    BinToAscii( (dword)year, 2, (char _far *)NumberString, LEFT, 2 );
	    DosWriteFile( Printer, 2, (char _far *)NumberString );
	    break;
	case YEAR:
	    DosWriteFile( Printer, sizeof( Yeartitle ), (void _far *)Yeartitle );
	    DosWriteFile( Printer, 3, (void _far *)" 19" );
	    BinToAscii( (dword)year, 2, (char _far *)NumberString, LEFT, 2 );
	    DosWriteFile( Printer, 2, (char _far *)NumberString );
	    break;
	}
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );

    DosWriteFile( Printer, 30, (void _far *)"Anzahl erfasster Mitarbeiter: " );
    NumberStringLength = BinToAscii( (dword)arbeiter, 5, (char _far *)NumberString, LEFT, 1 );
    DosWriteFile( Printer, NumberStringLength, (void _far *)NumberString );
    DosWriteFile( Printer, 2, (void _far *)" (" );
    NumberStringLength = BinToAscii( (dword)marbeiter, 5, (char _far *)NumberString, LEFT, 1 );
    DosWriteFile( Printer, NumberStringLength, (void _far *)NumberString );
    DosWriteFile( Printer, 3, (void _far *)"M, " );
    NumberStringLength = BinToAscii( (dword)farbeiter, 5, (char _far *)NumberString, LEFT, 1 );
    DosWriteFile( Printer, NumberStringLength, (void _far *)NumberString );
    DosWriteFile( Printer, 2, (void _far *)"F)" );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );

    Line = 14;

    for( entrycounter = 0; entrycounter < entries; entrycounter++ )
	{
	if( !begruendung[entrycounter].checkmark )
	    continue;

	if( Line == LinesPerPage )
	    {
	    PageStart = TRUE;
	    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
	    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
	    DosWriteFile( Printer, 6, (void _far *)"&a73C" );
	    BinToAscii( (dword)PageNo, 2, (char _far *)NumberString, RIGHT, 1 );
	    DosWriteFile( Printer, 2, (void _far *)NumberString );
	    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );

	    DosWriteFile( Printer, 1, (void _far *)&Formfeed );
	    PageNo++;
	    DosWriteFile( Printer, 5, (void _far *)"&a2R" );
	    Line = 1;
	    }
	else
	    {
	    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
	    Line++;
	    }

	if( PageStart )
	    {
		DosWriteFile( Printer, 5, (void _far *)"&a4C" );
		DosWriteFile( Printer, 4, (void _far *)"Code" );
		DosWriteFile( Printer, 5, (void _far *)"&a9C" );
		DosWriteFile( Printer, 12, (void _far *)"Beschreibung" );
		DosWriteFile( Printer, 6, (void _far *)"&a51C" );
		DosWriteFile( Printer, 10, (void _far *)"Tage Total" );
		DosWriteFile( Printer, 6, (void _far *)"&a63C" );
		DosWriteFile( Printer, 12, (void _far *)"Tage/Mitarb." );

		DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
		DosWriteFile( Printer, 5, (void _far *)"&a4C" );
		DosWriteFile( Printer, 71, (void _far *)"-----------------------------------------------------------------------" );
		DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
		Line += 2;
		PageStart = FALSE;
	    }

	DosWriteFile( Printer, 5, (void _far *)"&a4C" );
	DosWriteFile( Printer, sizeof( begruendung[entrycounter].number ), (void _far *)begruendung[entrycounter].number );
	DosWriteFile( Printer, sizeof( begruendung[entrycounter].genus ), (void _far *)&begruendung[entrycounter].genus );
	DosWriteFile( Printer, 5, (void _far *)"&a9C" );
	DosWriteFile( Printer, 40, (void _far *)begruendung[entrycounter].description );
	DosWriteFile( Printer, 6, (void _far *)"&a51C" );

	days = summe[entrycounter] / daylength;
	BinToAscii( (dword)days, 7, (char _far *)NumberString, RIGHT, 1 );
	DosWriteFile( Printer, 7, (void _far *)NumberString );
	DosWriteFile( Printer, 1, (void _far *)"." );
	centidays = (word)Divide( (summe[entrycounter] % daylength) * 100, daylength );
	BinToAscii( (dword)centidays, 2, (char _far *)NumberString, RIGHT, 2 );
	DosWriteFile( Printer, 2, (void _far *)NumberString );
	DosWriteFile( Printer, 6, (void _far *)"&a65C" );

	days = dschnitt[entrycounter] / daylength;
	BinToAscii( (dword)days, 7, (char _far *)NumberString, RIGHT, 1 );
	DosWriteFile( Printer, 7, (void _far *)NumberString );
	DosWriteFile( Printer, 1, (void _far *)"." );
	centidays = (word)Divide( (dschnitt[entrycounter] % daylength) * 100, daylength );
	BinToAscii( (dword)centidays, 2, (char _far *)NumberString, RIGHT, 2 );
	DosWriteFile( Printer, 2, (void _far *)NumberString );
	}


    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );
    DosWriteFile( Printer, 6, (void _far *)"&a73C" );
    BinToAscii( (dword)PageNo, 2, (char _far *)NumberString, RIGHT, 1 );
    DosWriteFile( Printer, 2, (void _far *)NumberString );
    DosWriteFile( Printer, sizeof( Newline ), (void _far *)Newline );

    DosWriteFile( Printer, 1, (void _far *)&Formfeed );
    DosWriteFile( Printer, 2, (void _far *)"E" );

    DosCloseFile( Printer );

    BoxDraw( &StatusBox );
    BoxWrite( &StatusBox, 0, 0, CENTER, "Statistik wurde ausgedruckt." );

    Statusline( "", "<Enter>" );
    ButtonMenu( 1, 1, &OKButton, NULL );
    ScrClr( BACKGROUND );
    }


bool MitarbeiterOK( char *abteilkey, char _far *abteilungsnummer )
    {
    byte counter;

    for( counter = 0; counter < KEYLENGTH; counter++ )
	{
	if( abteilkey[counter] == 0 )
	    break;

	if( abteilkey[counter] == abteilungsnummer[counter] )
	    continue;
	else
	    return( FALSE );
	}

    return( TRUE );
    }


word AsciiToBin( byte length, char _far *number )
    {
    word endnumber = 0;
    word tempnumber;
    byte counter;
    byte subcounter;

    for( counter = 0; counter < length; counter++ )
	{
	tempnumber = number[counter] - ZERO;
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
	    string[length - counter - 1] = SPACE;
	else
	    {
	    remainder = number % 10;
	    string[length - counter - 1] = remainder + ZERO;
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
		string[length - 1 - counter] = SPACE;
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
