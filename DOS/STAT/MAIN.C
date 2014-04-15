// ****************************
// ***	       Main	    ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"
#include <process.h>

BOOL InitConfigData( VOID );
BOOL ReadConfigData( VOID );
BOOL WriteConfigData( VOID );

BOOL OpenPathFile( VOID );
BOOL ReadPathFileEntry( BYTE Number, CHAR *Entry, BOOL NoPath );
BOOL ClosePathFile( VOID );

BOOL CreateList( HFILE File, BYTE Type );
BOOL SortList( BYTE Type );
BOOL LoadList( BYTE Type );
BOOL FreeList( BYTE Type );


MSG  MenuProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  MenuArrowsProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  BottomlineProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

MSG  InactiveProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );



HWND Desktop;
HWND Menu;
HWND MenuArrows;
HWND Bottomline;
HWND Panel;

struct ConfigData FAR *ConfigData;

WORD NumBegruendungen;
WORD NumAbteilungen;
WORD NumZeitKonti;
struct Eintrag FAR *Begruendungen;
struct Eintrag FAR *Abteilungen;
struct Eintrag FAR *ZeitKonti;

HFILE PathFile;



VOID _cdecl Main( WORD NumArgs, CHAR *Args[], CHAR *EnvStrings[] )
    {
    MSG     Msg;
    WORD    Key;

    CHAR FileName[65];
    CHAR PrinterPort[65];

    HFILE TMSBegrFile;
    HFILE TMSAbtFile;
    HFILE TMSZKontFile;

    DWORD EffTime;

    WinInitialize( MAXNUMWINDOWS );
    WinCreateWindow( Desktop, &Desktop, NULL, 0, 0, 0, 0, 0, 0 );

    WinHideCursor();
    WinColor( Desktop, NORMAL, 0, 0, WinGetx2( Desktop ), WinGety2( Desktop ) );

    WinCreateWindow( Desktop, &Bottomline, BottomlineProc, 0, 0, BOTTOMLINEX1, BOTTOMLINEY1, BOTTOMLINEX2, BOTTOMLINEY2 );

    if( !ReadConfigData() )
	{
	static struct HelpKey HelpKeys[NUMLAUFWERKHELPKEYS] =
	    { {	0,   0, "</>    Wert erhîhen/erniedrigen" },
	      { 0,   1, "<Enter>  Wert akzeptieren" },
	      { 40,  1, "<Esc>    Programm verlassen" } };

	HWND TMSLaufwerk;
	BOOL LaufwerkOK;

	WinFill( Desktop, 'ƒ',	0, 22, 79, 22 );
	InitConfigData();

	WinString( Desktop, "TMS Laufwerk", CENTER, 0, 7 );
	WinString( Desktop, "ÕÕÕÕÕÕÕÕÕÕÕÕ", CENTER, 0, 8 );
	WinColor( Desktop, HIGHLIGHT, 33, 7, 46, 7 );
	WinCreateWindow( Desktop, &TMSLaufwerk, TMSLaufWerkProc, 0, 0, 37, 10, 40, 10 );
	WinString( Desktop, "Geben Sie bitte an, in welchem Laufwerk sich TMS befindet.", CENTER, 0, 14 );

	WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMLAUFWERKHELPKEYS );

	WinSendMsg( TMSLaufwerk, WM_SHOW, 0, 0 );
	WinSendMsg( TMSLaufwerk, WM_SETFOCUS, 0, 0 );

	do
	    {
	    LaufwerkOK = TRUE;
	    do
		{
		Key = BiosGetKey();
		Msg = WinSendMsg( TMSLaufwerk, WM_CHAR, (MPARAM)Key, 0 );
		}
	    while( (WORD)Msg != KBENTER && (WORD)Msg != KBESC );

	    if( (WORD)Msg == KBESC )
		{
		DosFreeFarMem( ConfigData );

		WinDestroyWindow( TMSLaufwerk );
		WinDestroyWindow( Bottomline );
		WinDestroyWindow( Desktop );
		return;
		}

	    if( !OpenPathFile() )
		{
		LaufwerkOK = FALSE;
		}
	    }
	while( !LaufwerkOK );

	ClosePathFile();
	WinDestroyWindow( TMSLaufwerk );
	WinColor( Desktop, NORMAL, 0, 0, WinGetx2( Desktop ), 21 );
	WinFill( Desktop, SPACECHAR, 0, 0, WinGetx2( Desktop ), WinGety2( Desktop ) );
	}

    switch( NumArgs )
	{
	case 2:
	    StdStrLwr( Args[1] );
	    if( StdStrCmp( Args[1], "exportfile" ) == 0 ||
		StdStrCmp( Args[1], "export" ) == 0 )
		{
		WinFill( Desktop, 'ƒ',	0, 22, 79, 22 );
		ExportFileConversion();
		}
	    else
		{
		; // Debug!!!!
		}
	    break;

	case 1:
	    if( !OpenPathFile() )
		; // Debug!!!!!

	    ReadPathFileEntry( TMSBEGRUENDNO, FileName, FALSE );

	    DosOpen( FileName, &TMSBegrFile, OPEN_RDONLY );
	    DosLastModTime( TMSBegrFile, &EffTime );
	    if( ConfigData->TMSBegruendungsDatum != EffTime )
		{
		if( !CreateList( TMSBegrFile, BEGRUENDUNGEN ) )
		    {
		    WinString( Desktop, "In TMS sind 0 BegrÅndungen verzeichnet!", LEFT, 0, 0 );
		    return; // Debug-Version!!!!!
		    }

		SortList( BEGRUENDUNGEN );
		ConfigData->TMSBegruendungsDatum = EffTime;
		StdFarMemSet( ConfigData->BegrCheckListe, TRUE, sizeof( ConfigData->BegrCheckListe ) );
		}
	    DosClose( TMSBegrFile );

	    ReadPathFileEntry( TMSABTEILNO, FileName, FALSE );

	    DosOpen( FileName, &TMSAbtFile, OPEN_RDONLY );
	    DosLastModTime( TMSAbtFile, &EffTime );
	    if( ConfigData->TMSAbteilungsDatum != EffTime )
		{
		if( !CreateList( TMSAbtFile, ABTEILUNGEN ) )
		    {
		    WinString( Desktop, "In TMS sind 0 Abteilungen verzeichnet!", LEFT, 0, 0 );
		    return; // Debug-Version!!!!!
		    }
		SortList( ABTEILUNGEN );
		ConfigData->TMSAbteilungsDatum = EffTime;
		StdFarMemSet( ConfigData->AbtCheckListe, TRUE, sizeof( ConfigData->AbtCheckListe ) );
		}
	    DosClose( TMSAbtFile );

	    ReadPathFileEntry( TMSZEITKNO, FileName, FALSE );

	    DosOpen( FileName, &TMSZKontFile, OPEN_RDONLY );
	    DosLastModTime( TMSZKontFile, &EffTime );
	    if( ConfigData->TMSZeitKontiDatum != EffTime )
		{
		if( !CreateList( TMSZKontFile, ZEITKONTI ) )
		    {
		    WinString( Desktop, "In TMS sind 0 Zeitkonti verzeichnet!", LEFT, 0, 0 );
		    return; // Debug-Version!!!!!
		    }
		// SortList( ZEITKONTI );
		ConfigData->TMSZeitKontiDatum = EffTime;
		StdFarMemSet( ConfigData->ZKontCheckListe, TRUE, sizeof( ConfigData->ZKontCheckListe ) );
		}
	    DosClose( TMSZKontFile );

	    ReadPathFileEntry( TMSPRINTERINFONO, FileName, FALSE );
	    ReadPathFileEntry( TMSPRINTERPORTNO, PrinterPort, TRUE );
	    GetPrinterInfo( FileName, PrinterPort );

	    ClosePathFile();

	    LoadList( BEGRUENDUNGEN );
	    LoadList( ABTEILUNGEN );
	    LoadList( ZEITKONTI );

	    WinString( Desktop, "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø", CENTER, 0,  3 );
	    WinString( Desktop, "≥                                    ≥", CENTER, 0,  4 );
	    WinString( Desktop, "≥      Statistik - Generierung       ≥", CENTER, 0,  5 );
	    WinString( Desktop, "≥      ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ       ≥", CENTER, 0,  6 );
	    WinString( Desktop, "≥                und                 ≥", CENTER, 0,  7 );
	    WinString( Desktop, "≥                ƒƒƒ                 ≥", CENTER, 0,  8 );
	    WinString( Desktop, "≥     Verwaltung der Exportdaten     ≥", CENTER, 0,  9 );
	    WinString( Desktop, "≥     ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ     ≥", CENTER, 0, 10 );
	    WinString( Desktop, "≥                                    ≥", CENTER, 0, 11 );
	    WinString( Desktop, "≥              von TMS               ≥", CENTER, 0, 12 );
	    WinString( Desktop, "≥                                    ≥", CENTER, 0, 13 );
	    WinString( Desktop, "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ", CENTER, 0, 14 );

	    WinString( Desktop, " (c) Copyright 1992, 1993 J.Skripsky  ", CENTER, 0, 16 );

	    WinString( Desktop, "      Designed and Developed by       ", CENTER, 0, 18 );
	    WinString( Desktop, "           Juraj Skripsky             ", CENTER, 0, 19 );
	    WinString( Desktop, "         CH-8952 Schlieren            ", CENTER, 0, 20 );

	    BiosGetKey();
	    WinFill( Desktop, SPACECHAR, 0, 0, WinGetx2( Desktop ), WinGety2( Desktop ) );

	    WinFill( Desktop, 'ƒ', 0, 22, 79, 22 );

	    WinFill( Desktop, '≥', 27,	0, 27, 21 );
	    WinFill( Desktop, 'ƒ',  0, 22, 79, 22 );
	    WinCreateWindow( Desktop, &Menu, MenuProc, 0, 0, 1, 1, 25, 20 );

	    WinSendMsg( Menu, WM_SHOW, 0, 0 );
	    WinSendMsg( Menu, WM_SETFOCUS, 0, 0 );

	    do
		{
		Key = BiosGetKey();
		Msg = WinSendMsg( Menu, WM_CHAR, (MPARAM)Key, 0 );
		}
	    while( (WORD)Msg != KBESC );


	    FreeList( BEGRUENDUNGEN );
	    FreeList( ABTEILUNGEN );
	    FreeList( ZEITKONTI );

	    FreePrinterInfo();

	    WinDestroyWindow( Menu );
	    break;
	 }

    if( !WriteConfigData() )
	; // Debug!!!!!

    WinDestroyWindow( Bottomline );
    WinDestroyWindow( Desktop );
    WinTerminate();
    }


BOOL InitConfigData( VOID )
    {
    BYTE Counter;
    BYTE Drive;

    ConfigData = DosAllocFarMem( sizeof( *ConfigData ) );

    DosCurrentDrive( &Drive );
    ConfigData->TMSLaufWerk = (CHAR)(Drive + (BYTE)'A');

    ConfigData->ArbeitsTag = 8 * 60;

    ConfigData->AbtFeldNr = 1;

    ConfigData->ZeitAngModus = STDMIN;

    ConfigData->Grenzwert = 60;

    ConfigData->TMSAbteilungsDatum = 0;
    ConfigData->TMSBegruendungsDatum = 0;
    ConfigData->TMSZeitKontiDatum = 0;

    StdFarMemSet( ConfigData->Name, 0, sizeof( ConfigData->Name ) );
    StdFarMemSet( ConfigData->PersonalNr, 0, sizeof( ConfigData->PersonalNr ) );
    StdFarMemSet( ConfigData->Kriterium, 0, sizeof( ConfigData->Kriterium ) );

    for( Counter = 0; Counter < NUMCONTROLPANEL; Counter++ )
	StdFarStrCpy( ConfigData->AbtSchluessel[Counter], "*****" );

    StdFarMemSet( ConfigData->AbtCheckListe, TRUE, sizeof( ConfigData->AbtCheckListe ) );
    StdFarMemSet( ConfigData->BegrCheckListe, TRUE, sizeof( ConfigData->BegrCheckListe ) );
    StdFarMemSet( ConfigData->ZKontCheckListe, TRUE, sizeof( ConfigData->ZKontCheckListe ) );

    for( Counter = 0; Counter < NUMPERIODEPANEL; Counter++ )
	{
	ConfigData->Perioden[Counter].AnfTag = 1;
	ConfigData->Perioden[Counter].AnfMonat = 1;
	ConfigData->Perioden[Counter].AnfJahr = 1992;
	ConfigData->Perioden[Counter].EndTag = 1;
	ConfigData->Perioden[Counter].EndMonat = 1;
	ConfigData->Perioden[Counter].EndJahr = 1992;
	}

    return( TRUE );
    }


BOOL ReadConfigData( VOID )
    {
    HFILE	ConfigFile;

    if( DosOpen( CONFIGFILENAME, &ConfigFile, OPEN_RDONLY ) )
	return( FALSE );

    ConfigData = DosAllocFarMem( sizeof( *ConfigData ) );

    DosRead( ConfigFile, ConfigData, sizeof( *ConfigData ), NULL );
    DosClose( ConfigFile );

    return( TRUE );
    }


BOOL WriteConfigData( VOID )
    {
    HFILE	ConfigFile;

    DosCreate( CONFIGFILENAME, &ConfigFile, FILE_NORMAL );
    DosWrite( ConfigFile, ConfigData, sizeof( *ConfigData ), NULL );
    DosClose( ConfigFile );

    DosFreeFarMem( ConfigData );
    return( TRUE );
    }


BOOL OpenPathFile( VOID )
    {
    CHAR PathFileName[65];

    PathFileName[0] = ConfigData->TMSLaufWerk;
    PathFileName[1] = ':';
    StdStrCpy( &PathFileName[2], TMSPATH );
    StdStrCat( PathFileName, TMSPATHFILENAME );

    if( DosOpen( PathFileName, &PathFile, OPEN_RDONLY ) )
	return( FALSE );

    return( TRUE );
    }


BOOL ReadPathFileEntry( BYTE Number, CHAR *Entry, BOOL NoPath )
    {
    SDWORD Distance;
    CHAR   ReadEntry[80];
    BYTE   CharNumber;
    CHAR   *CharPointer;

    memset( Entry, 0, 65 );

    Distance = 82 * Number;
    DosSetFilePtr( PathFile, &Distance, FILE_BEGIN, NULL );

    DosRead( PathFile, ReadEntry, sizeof( ReadEntry ), NULL );
    CharNumber = 4;

    CharPointer = StdStrChr( &ReadEntry[CharNumber], ' ' );
    *CharPointer = 0;

    if( NoPath )
	{
	strcat( Entry, &ReadEntry[CharNumber] );
	return( TRUE );
	}


    if( ReadEntry[CharNumber + 1] == ':' )
	{
	memcpy( &Entry[0], &ReadEntry[CharNumber], 2 );
	CharNumber += 2;
	}
    else
	{
	Entry[0] = ConfigData->TMSLaufWerk;
	Entry[1] = ':';
	}


    if( ReadEntry[CharNumber] != '\\' )
	strcat( Entry, TMSPATH );
    else
	{
	Entry[2] = '\\';
	CharNumber += 1;
	}

    strcat( Entry, &ReadEntry[CharNumber] );

    return( TRUE );
    }


BOOL ClosePathFile( VOID )
    {
    if( DosClose( PathFile ) )
	return( FALSE );

    return( TRUE );
    }


BOOL CreateList( HFILE File, BYTE Type )
    {
    struct Eintrag Eintrag;

    DWORD Distance;
    WORD  NumEntries;
    WORD  NumEffEntries;
    DWORD FileLength;
    DWORD FilePos;

    CHAR  PresentMark;
    BYTE  LengthMark;
    BYTE  EndMark;

    WORD  BytesRead;

    BYTE  CodeLength;
    WORD  Counter;
    HFILE OutFile;

    Distance = 0;
    DosSetFilePtr( File, &Distance, FILE_END, &FileLength );

    Distance = 0x80;
    DosSetFilePtr( File, &Distance, FILE_BEGIN, &FilePos );
    NumEntries = 0;
    NumEffEntries = 0;

    while( FilePos < FileLength )
	{
	DosRead( File, &PresentMark, sizeof( PresentMark ), &BytesRead );
	FilePos += BytesRead;

	NumEntries++;
	if( PresentMark == '@' )
	    NumEffEntries++;

	DosRead( File, &LengthMark, sizeof( LengthMark ), &BytesRead );
	FilePos += BytesRead;

	Distance = LengthMark;
	DosSetFilePtr( File, &Distance, FILE_CURRENT, &FilePos );
	DosRead( File, &EndMark, sizeof( EndMark ), &BytesRead );
	if( Type == ZEITKONTI )
	    DosRead( File, &EndMark, sizeof( EndMark ), &BytesRead );

	FilePos += BytesRead;
	}

    switch( Type )
	{
	case BEGRUENDUNGEN:
	    CodeLength = BEGRUENDCODELENGTH;
	    DosCreate( BEGRUENDFILENAME, &OutFile, FILE_NORMAL );
	    break;

	case ABTEILUNGEN:
	    CodeLength = ABTEILCODELENGTH;
	    DosCreate( ABTEILFILENAME, &OutFile, FILE_NORMAL );
	    break;

	case ZEITKONTI:
	    CodeLength = ZEITKCODELENGTH;
	    DosCreate( ZEITKFILENAME, &OutFile, FILE_NORMAL );
	    break;
	}

    Distance = 0x80;
    DosSetFilePtr( File, &Distance, FILE_BEGIN, &FilePos );

    if( Type == ABTEILUNGEN )
	{
	DosRead( File, &PresentMark, sizeof( PresentMark ), &BytesRead );
	DosRead( File, &LengthMark, sizeof( LengthMark ), &BytesRead );

	DosRead( File, Eintrag.Code, CodeLength, NULL );
	DosRead( File, Eintrag.Description, BESCHREIBUNGSLENGTH, NULL );

	Distance = LengthMark - BESCHREIBUNGSLENGTH - CodeLength;
	DosSetFilePtr( File, &Distance, FILE_CURRENT, NULL );

	DosRead( File, &EndMark, sizeof( EndMark ), &BytesRead );
	if( Type == ZEITKONTI )
	    DosRead( File, &EndMark, sizeof( EndMark ), &BytesRead );

	NumEntries--;
	NumEffEntries--;
	}

    if( Type == ZEITKONTI )
	{
	NumEntries--;
	NumEffEntries--;
	}

    DosWrite( OutFile, &NumEffEntries, sizeof( NumEffEntries ), NULL );

    for( Counter = 0; Counter < NumEntries; Counter++ )
	{
	memset( &Eintrag, SPACECHAR, sizeof( Eintrag ) );

	DosRead( File, &PresentMark, sizeof( PresentMark ), &BytesRead );
	DosRead( File, &LengthMark, sizeof( LengthMark ), &BytesRead );

	DosRead( File, Eintrag.Code, CodeLength, NULL );
	DosRead( File, Eintrag.Description, BESCHREIBUNGSLENGTH, NULL );

	Eintrag.Code[JSCODELENGTH] = 0;
	Eintrag.CodeLength = JSCODELENGTH;

	while( Eintrag.Code[Eintrag.CodeLength - 1] == SPACECHAR && Eintrag.CodeLength > 0 )
	    {
	    Eintrag.Code[Eintrag.CodeLength - 1] = 0;
	    Eintrag.CodeLength--;
	    }

	Eintrag.Description[BESCHREIBUNGSLENGTH] = 0;
	Eintrag.DescriptionLength = BESCHREIBUNGSLENGTH;

	while( Eintrag.Description[Eintrag.DescriptionLength - 1] == SPACECHAR && Eintrag.DescriptionLength > 0 )
	    {
	    Eintrag.Description[Eintrag.DescriptionLength - 1] = 0;
	    Eintrag.DescriptionLength--;
	    }

	Distance = LengthMark - BESCHREIBUNGSLENGTH - CodeLength;
	DosSetFilePtr( File, &Distance, FILE_CURRENT, NULL );

	DosRead( File, &EndMark, sizeof( EndMark ), &BytesRead );
	if( Type == ZEITKONTI )
	    DosRead( File, &EndMark, sizeof( EndMark ), &BytesRead );

	if( PresentMark == '@' )
	    DosWrite( OutFile, &Eintrag, sizeof( Eintrag ), NULL );
	}

    DosClose( OutFile );

    if( NumEffEntries == 0 )
	return( FALSE );
    else
	return( TRUE );
    }


BOOL SortList( BYTE Type )
    {
    struct Eintrag FAR *Eintraege;

    HFILE File;
    WORD  NumEntries;

    BOOL  Sorted;

    switch( Type )
	{
	case BEGRUENDUNGEN:
	    DosOpen( BEGRUENDFILENAME, &File, OPEN_RDONLY );
	    break;

	case ABTEILUNGEN:
	    DosOpen( ABTEILFILENAME, &File, OPEN_RDONLY );
	    break;

	case ZEITKONTI:
	    DosOpen( ZEITKFILENAME, &File, OPEN_RDONLY );
	    break;
	}

    DosRead( File, &NumEntries, sizeof( NumEntries ), NULL );

    Eintraege = DosAllocFarMem( sizeof( *Eintraege ) * (NumEntries + 1) );
    DosRead( File, Eintraege, sizeof( *Eintraege ) * NumEntries, NULL );
    DosClose( File );

    do
	{
	WORD Counter;
	Sorted = TRUE;

	for( Counter = 0; Counter < NumEntries - 1; Counter++ )
	    if( StdFarMemCmp( Eintraege[Counter].Code, Eintraege[Counter + 1].Code, sizeof( Eintraege[Counter].Code ) ) > 0 )
		{
		Sorted = FALSE;
		StdFarMemCpy( &Eintraege[NumEntries], &Eintraege[Counter], sizeof( Eintraege[Counter] ) );
		StdFarMemCpy( &Eintraege[Counter], &Eintraege[Counter + 1], sizeof( Eintraege[Counter] ) );
		StdFarMemCpy( &Eintraege[Counter + 1], &Eintraege[NumEntries], sizeof( Eintraege[Counter] ) );
		}
	}
    while( !Sorted );

    switch( Type )
	{
	case BEGRUENDUNGEN:
	    DosCreate( BEGRUENDFILENAME, &File, FILE_NORMAL );
	    break;

	case ABTEILUNGEN:
	    DosCreate( ABTEILFILENAME, &File, FILE_NORMAL );
	    break;

	case ZEITKONTI:
	    DosCreate( ZEITKFILENAME, &File, FILE_NORMAL );
	    break;
	}

    DosWrite( File, &NumEntries, sizeof( NumEntries ), NULL );
    DosWrite( File, Eintraege, sizeof( *Eintraege ) * NumEntries, NULL );

    DosClose( File );
    DosFreeFarMem( Eintraege );

    return( TRUE );
    }


BOOL LoadList( BYTE Type )
    {
    HFILE File;

    switch( Type )
	{
	case BEGRUENDUNGEN:
	    if( DosOpen( BEGRUENDFILENAME, &File, OPEN_RDONLY ) )
		; // Debug!!!!!

	    DosRead( File, &NumBegruendungen, sizeof( NumBegruendungen ), NULL );
	    Begruendungen = DosAllocFarMem( sizeof( *Begruendungen ) * NumBegruendungen );

	    DosRead( File, Begruendungen, sizeof( *Begruendungen ) * NumBegruendungen, NULL );
	    DosClose( File );
	    break;

	case ABTEILUNGEN:
	    if( DosOpen( ABTEILFILENAME, &File, OPEN_RDONLY ) )
		; // Debug!!!!!

	    DosRead( File, &NumAbteilungen, sizeof( NumAbteilungen ), NULL );
	    Abteilungen = DosAllocFarMem( sizeof( *Abteilungen ) * NumAbteilungen );

	    DosRead( File, Abteilungen, sizeof( *Abteilungen ) * NumAbteilungen, NULL );
	    DosClose( File );
	    break;

	case ZEITKONTI:
	    if( DosOpen( ZEITKFILENAME, &File, OPEN_RDONLY ) )
		; // Debug!!!!!

	    DosRead( File, &NumZeitKonti, sizeof( NumZeitKonti ), NULL );
	    ZeitKonti = DosAllocFarMem( sizeof( *ZeitKonti ) * NumZeitKonti );

	    DosRead( File, ZeitKonti, sizeof( *ZeitKonti ) * NumZeitKonti, NULL );
	    DosClose( File );
	    break;
	}

    return( TRUE );
    }


BOOL FreeList( BYTE Type )
    {
	switch( Type )
	{
	case BEGRUENDUNGEN:
	    DosFreeFarMem( Begruendungen );
	    break;

	case ABTEILUNGEN:
	    DosFreeFarMem( Abteilungen );
	    break;
	}

    return( TRUE );
    }


MSG MenuProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static struct MenuPoint MenuPoints[NUMMENUPOINTS] =
	{ { DOT,  0, "Einstellungen", EinstellungenProc, NULL },
	  { 0,	  0, "", NULL, NULL },
	  { 0,	  0, "", NULL, NULL },
	  { 0,	  0, "Durchschnitt", DurchschnittProc, NULL },
	  { 0,	  0, "ÕÕÕÕÕÕÕÕÕÕÕÕ", NULL, NULL },
	  { DOT,  1, "Periode", PeriodeProc, NULL },
	  { DOT,  1, "Abteilungen", AbteilungenProc, NULL },
	  { DOT,  1, "BegrÅndungen", BegruendungenProc, NULL },
	  { 0,	  0, "", NULL, NULL },

	  { 0,	  0, "öbersicht", UebersichtProc, NULL },
	  { 0,	  0, "ÕÕÕÕÕÕÕÕÕ", NULL, NULL },
	  { DOT,  1, "Periode", PeriodeProc, NULL },
	  { DOT,  1, "Person(en)", PersonenProc, NULL },
	  { DOT,  1, "BegrÅndungen", BegruendungenProc, NULL },
	  { 0,	  0, "", NULL, NULL },

	  { 0,	  0, "Grenzwerte Åberschritten", UeberzeitProc, NULL },
	  { 0,	  0, "ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕ", NULL, NULL },
	  { DOT,  1, "Periode", PeriodeProc, NULL },
	  { DOT,  1, "Abteilungen", AbteilungenProc, NULL },
	  { DOT,  1, "BegrÅndungen", PMBegruendungenProc, NULL },
	  { 0,	  0, "", NULL, NULL },

	  { 0,	  0, "Summierung Zeitkonti", ZeitKontiSumProc, NULL },
	  { 0,	  0, "ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕ", NULL, NULL },
	  { DOT,  1, "Periode", PeriodeProc, NULL },
	  { DOT,  1, "Zeitkonti", ZeitKontiProc, NULL } };

    static struct HelpKey HelpKeys[NUMMENUHELPKEYS] =
	{ {  0,  0, "</>    MenÅpunkt anwÑhlen" },
	  {  0,  1, "<Enter>  MenÅpunkt ausfÅhren" },
	  { 40,  1, "<Esc>    Programm verlassen" } };

    static BYTE Selection;
    static BYTE TopLine;

    static BOOL PanelFocus;

    switch( Msg )
	{
	case WM_CREATE:
	    {

	    MenuPoints[5].Data = &ConfigData->Perioden[0];
	    MenuPoints[11].Data = &ConfigData->Perioden[1];
	    MenuPoints[17].Data = &ConfigData->Perioden[2];
	    MenuPoints[23].Data = &ConfigData->Perioden[3];

	    MenuPoints[6].Data = (VOID FAR *)0;
	    MenuPoints[12].Data = (VOID FAR *)1;
	    MenuPoints[18].Data = (VOID FAR *)2;

	    MenuPoints[7].Data = (VOID FAR *)0;
	    MenuPoints[13].Data = (VOID FAR *)1;
	    MenuPoints[19].Data = (VOID FAR *)2;

	    MenuPoints[24].Data = (VOID FAR *)3;
	    WinCreateWindow( HWnd, &MenuArrows, MenuArrowsProc, 0, 0, 25, -1, 25, 20 );
	    Selection = 0;
	    TopLine = 0;
	    PanelFocus = FALSE;
	    return( WM_PROCESSED );
	    }

	case WM_SHOW:
	    {
	    BYTE LineCounter;

	    WinColor( HWnd, MENU, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    for( LineCounter = 0; LineCounter <= WinGety2( HWnd ); LineCounter++ )
		{
		if( LineCounter + TopLine == NUMMENUPOINTS )
		    break;

		if( MenuPoints[LineCounter + TopLine].Style & DOT )
		    {
		    WinString( HWnd, "˛ ", LEFT, (BYTE)(MenuPoints[LineCounter + TopLine].Indent + 1), LineCounter );
		    WinString( HWnd, MenuPoints[LineCounter + TopLine].Text, LEFT, (BYTE)(MenuPoints[LineCounter + TopLine].Indent + 3), LineCounter );
		    }
		else
		    WinString( HWnd, MenuPoints[LineCounter + TopLine].Text, LEFT, (BYTE)(MenuPoints[LineCounter + TopLine].Indent + 1), LineCounter );
		}

	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    {
	    BYTE Length;

	    WinSendMsg( MenuArrows, WM_SET, (TopLine == 0 ? FALSE : TRUE ),
					    ((BYTE)(NUMMENUPOINTS - 1 - TopLine) <= WinGety2( HWnd ) ? FALSE : TRUE ) );

	    WinSendMsg( MenuArrows, WM_SHOW, 0, 0 );

	    Length = (BYTE)strlen( MenuPoints[Selection].Text );
	    if( MenuPoints[Selection].Style & DOT )
		Length += 2;

	    WinColor( HWnd, HIGHLIGHT, (BYTE)(MenuPoints[Selection].Indent), (BYTE)(Selection - TopLine), (BYTE)(MenuPoints[Selection].Indent + Length + 1), (BYTE)(Selection - TopLine) );

	    WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMMENUHELPKEYS );

	    WinCreateWindow( HWnd, &Panel, MenuPoints[Selection].Proc, SEG(MenuPoints[Selection].Data), OFS(MenuPoints[Selection].Data), PANELX1, PANELY1, PANELX2, PANELY2 );
	    WinSendMsg( Panel, WM_SHOW, 0, 0 );
	    return( WM_PROCESSED );
	    }

	case WM_CLEARFOCUS:
	    WinDestroyWindow( Panel );
	    WinColor( HWnd, MENU, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    if( PanelFocus )
		if( WinSendMsg( Panel, Msg, MP1, MP2 ) == WM_PROCESSED )
		    return( WM_PROCESSED );

	    switch( (WORD)MP1 )
		{
		case KBDOWN:
		case KBRIGHT:
		case KBTAB:
		    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );
		    do
			{
			if( Selection == NUMMENUPOINTS - 1)
			    break;

			Selection++;

			if( Selection - TopLine > WinGety2( HWnd ) )
			    {
			    TopLine++;
			    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
			    }
			}
		    while( MenuPoints[Selection].Proc == NULL );

		    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
		    break;

		case KBUP:
		case KBLEFT:
		case KBSHTAB:
		    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );
		    do
			{
			if( Selection == 0)
			    break;

			Selection--;

			if( Selection < TopLine )
			    {
			    TopLine--;
			    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
			    }
			}
		    while( MenuPoints[Selection].Proc == NULL );

		    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
		    break;

		case KBHOME:
		    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );

		    TopLine = 0;
		    Selection = 0;

		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
		    break;

		case KBEND:
		    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );

		    Selection = NUMMENUPOINTS - 1;
		    if( NUMMENUPOINTS - 1 < WinGety2( HWnd ) )
			TopLine = 0;
		    else
			TopLine = (BYTE)(NUMMENUPOINTS - 1 - WinGety2( HWnd ));

		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
		    break;

		case KBENTER:
		    if( !PanelFocus )
			{
			WinSendMsg( Panel, WM_SETFOCUS, 0, 0 );
			PanelFocus = TRUE;
			return( WM_PROCESSED );
			}
		    else
			WinSendMsg( HWnd, WM_CHAR, (MPARAM)KBESC, 0 );


		case KBESC:
		    if( PanelFocus )
			{
			WinSendMsg( Panel, WM_CLEARFOCUS, 0, 0 );
			PanelFocus = FALSE;
			WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
			return( WM_PROCESSED );
			}

		default:
		    return( MP1 );
		}
	    return( WM_PROCESSED );

	case WM_DESTROY:
	    WinDestroyWindow( MenuArrows );
	    return( WM_PROCESSED );

	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


MSG  MenuArrowsProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static BOOL UpArrow;
    static BOOL DownArrow;

    switch( Msg )
	{
	case WM_CREATE:
	    UpArrow = FALSE;
	    DownArrow = FALSE;
	    return( WM_PROCESSED );

	case WM_SET:
	    UpArrow = (BOOL)MP1;
	    DownArrow = (BOOL)MP2;
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    WinColor( HWnd, MENUARROWS, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    if( UpArrow )
		WinCharacter( HWnd, '', 0, 0 );
	    if( DownArrow )
		WinCharacter( HWnd, '', 0, WinGety2( HWnd ) );

	    return( WM_PROCESSED );
	    }

	case WM_DESTROY:
	    return( WM_PROCESSED );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


MSG  BottomlineProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {

    switch( Msg )
	{
	case WM_CREATE:
	    return( WM_PROCESSED );

	case WM_HELP:
	    {
	    struct HelpKey *HelpKeys;
	    BYTE LineCounter;

	    WinColor( HWnd, KEYHELP, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    HelpKeys = (struct HelpKey *)MP1;

	    for( LineCounter = 0; LineCounter < (BYTE)MP2; LineCounter++ )
		WinString( HWnd, HelpKeys[LineCounter].Text, LEFT, HelpKeys[LineCounter].x, HelpKeys[LineCounter].y );

	    return( WM_PROCESSED );
	    }
	case WM_MESSAGE:
	    {
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    if( (VOID *)MP1 != NULL )
		WinString( HWnd, (CHAR *)MP1, CENTER, 0, 0 );
	    if( (VOID *)MP2 != NULL )
		WinString( HWnd, (CHAR *)MP2, CENTER, 0, 1 );

	    return( WM_PROCESSED );
	    }
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


MSG  InactiveProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {

    switch( Msg )
	{
	case WM_CREATE:
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    WinColor( HWnd, PANEL, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    WinString( HWnd, "Dieser Menupunkt ist noch nicht aktiv.", LEFT, 0, 0 );
	    }

	case WM_CHAR:
	    return( MP1 );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }
