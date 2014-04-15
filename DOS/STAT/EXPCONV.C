// ****************************
// ***	 Exportfile Conv.   ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"
#include "ExpConv.H"


MSG  InfoProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

BYTE ExportFileConversion( VOID );

BOOL GetTMSFileSize( VOID );
BOOL AllocMem( VOID );
BOOL FreeMem( VOID );
BOOL BuildFileHeader( CHAR *DestinationFileName, CHAR *ArchiveFileName );
BOOL CheckNumDays( BYTE AnzTage );
BYTE ConvertData( WORD AnzPersonen, BYTE AnzTage );

BYTE OpenDataFile( struct DateiKopf FAR *DateiKopf, WORD Jahr, BYTE Monat );
BYTE ReadPersonenInfo( struct PersonenInfo FAR *PersonenInfo );
BYTE ReadTage( struct Tag FAR *Tage );
BYTE ResetDataFile( VOID );
BYTE DeleteDataFile( VOID );

extern HWND Desktop;
extern HWND Bottomline;

extern HFILE PathFile;


HWND  Progressbar;

HFILE TMSFile;
HFILE JSTmpFile;

CHAR  JSTmpFileName[] = JSTMPFILENAME;

CHAR  CompressProgName[] = COMPRESSPROGNAME;
CHAR  CompressParams[] = COMPRESSPARAMS;
CHAR  DecompressProgName[] = DECOMPRESSPROGNAME;
CHAR  DecompressParams[] = DECOMPRESSPARAMS;

SDWORD TMSDateiLaenge;

struct SatzAnfang FAR *TMSSatzAnfang;
struct SatzMitte  FAR *TMSSatzMitte;
struct SatzEnde   FAR *TMSSatzEnde;

struct DateiKopf FAR *JSDateiKopf;
struct PersonenInfo FAR *JSPersonenInfo;
struct Tag FAR *JSTag;

HWND Info;

BOOL FilePtrAtPersonenInfo;
WORD Year;
BYTE Month;
HFILE DataFile;

BYTE ExportFileConversion( VOID )
    {
    static struct HelpKey HelpKeys[NUMEXPCONVHELPKEYS] =
	{ {  0,	0, "<Esc>    Aufnahme abbrechen" } };

    CHAR TMSFileName[65];
    CHAR DestinationFileName[13];
    CHAR ArchiveFileName[13];

    BYTE ErrorCode;
    BYTE ReturnCode = TRUE;

    WinColor( Desktop, NORMAL, 0, 0, WinGetx2( Desktop ), 4 );
    WinString( Desktop, "Aufnahme der TMS Exportdatei", LEFT, 2, 1 );
    WinString( Desktop, "ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕ", LEFT, 2, 2 );
    WinColor( Desktop, HIGHLIGHT, 1, 1, 30, 1 );

    WinCreateWindow( Desktop, &Progressbar, ProgressbarProc, 0, 0, 2, 18, 77, 20 );

    if( !OpenPathFile() )
	{
	WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"TMS Datei ""FILEPATH.DAT"" kann nicht geîffnet werden!", (MPARAM)"<Enter>" );
	BiosGetKey();
	return( FALSE );
	}

    ReadPathFileEntry( TMSEXPORTFILENO, TMSFileName, FALSE );
    ClosePathFile();

    if( DosOpen( TMSFileName, &TMSFile, OPEN_RDONLY ) )
	{
	WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"TMS Exportdatei kann nicht geîffnet werden!", (MPARAM)"<Enter>" );
	BiosGetKey();
	return( FALSE );
	}

    if( DosCreate( JSTmpFileName, &JSTmpFile, FILE_NORMAL ) )
	; // Debug!!

    GetTMSFileSize();
    if( TMSDateiLaenge == 0 )
	{
	WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"LÑnge der TMS Exportdatei ist ungÅltig!", (MPARAM)"<Enter>" );
	BiosGetKey();
	ReturnCode = FALSE;
	}

    if( ReturnCode == TRUE )
	AllocMem();

    if( ReturnCode == TRUE )
	{
	BuildFileHeader( DestinationFileName, ArchiveFileName );

	WinCreateWindow( Desktop, &Info, InfoProc, 0, 0, 2, 4, 77, 16 );
	WinSendMsg( Info, WM_SHOW, MONATJAHR, 0 );
	WinSendMsg( Info, WM_SHOW, ANZPERSONTAG, 0 );

	WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMEXPCONVHELPKEYS );
	}

    if( ReturnCode == TRUE )
	if( !CheckNumDays( JSDateiKopf->AnzTage ) )
	    {
	    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"In der TMS Export sind nicht alle Tage vorhanden!", (MPARAM)"<Enter>" );
	    BiosGetKey();
	    ReturnCode = FALSE;
	    }

    if( ReturnCode == TRUE )
	if( TMSDateiLaenge % ((JSDateiKopf->AnzTage + 2) * sizeof( *TMSSatzMitte )) != 0 )
	    {
	    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Anzahl Tage stimmt mit der LÑnge der TMS Exportdatei nicht Åberein!", (MPARAM)"<Enter>" );
	    BiosGetKey();
	    ReturnCode = FALSE;
	    }

    if( ReturnCode == TRUE )
	DosWrite( JSTmpFile, JSDateiKopf, sizeof( *JSDateiKopf ), NULL );

    if( ReturnCode == TRUE )
	{
	ErrorCode = ConvertData( JSDateiKopf->AnzPersonen, JSDateiKopf->AnzTage );
	if( ErrorCode != OK );
	    switch( ErrorCode )
		{
		case UNKONTROLLIERT:
		    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Exportdatei enthÑlt unkontrollierte Daten!", (MPARAM)"<Enter>" );
		    BiosGetKey();
		    ReturnCode = FALSE;
		    break;

		case ABGEBROCHEN:
		    ReturnCode = FALSE;
		    break;
		}
	}

    FreeMem();
    DosClose( TMSFile );
    // Debug!!!!! DosDelete( TMSFileName );
    DosClose( JSTmpFile );

    DosRename( JSTmpFileName, DestinationFileName );

    if( ReturnCode == TRUE )
	{
	WinSendMsg( Desktop, WM_RESTOREVIDEOMODE, 0, 0 );
	spawnl( P_WAIT, CompressProgName, CompressProgName, CompressParams, ArchiveFileName, DestinationFileName, NULL );
	WinSendMsg( Desktop, WM_SETVIDEOMODE, 0, 0 );
	}

    DosDelete( DestinationFileName );

    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Aufnahme abgeschlossen.", (MPARAM)"<Enter>  Programm verlassen" );
    BiosGetKey();

    WinDestroyWindow( Progressbar );
    }



BOOL GetTMSFileSize( VOID )
    {
    SDWORD FilePtrDistance;

    FilePtrDistance = 0;
    DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_END, &TMSDateiLaenge );

    FilePtrDistance = 0;
    DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_BEGIN, NULL );

    return( TRUE );
    }

BOOL AllocMem( VOID )
    {
    TMSSatzAnfang = DosAllocFarMem( sizeof( *TMSSatzAnfang ) );
    TMSSatzMitte = DosAllocFarMem( sizeof( *TMSSatzMitte ) );
    TMSSatzEnde = DosAllocFarMem( sizeof( *TMSSatzEnde ) );

    JSDateiKopf = DosAllocFarMem( sizeof( *JSDateiKopf ) );
    JSPersonenInfo = DosAllocFarMem( sizeof( *JSPersonenInfo ) );
    JSTag = DosAllocFarMem( sizeof( *JSTag ) );

    return( TRUE );
    }

BOOL FreeMem( VOID )
    {
    DosFreeFarMem( TMSSatzAnfang );
    DosFreeFarMem( TMSSatzMitte );
    DosFreeFarMem( TMSSatzEnde );

    DosFreeFarMem( JSDateiKopf );
    DosFreeFarMem( JSPersonenInfo );
    DosFreeFarMem( JSTag );

    return( TRUE );
    }

BOOL BuildFileHeader( CHAR *DestinationFileName, CHAR *ArchiveFileName )
    {
    BYTE AnzTage[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    SDWORD FilePtrDistance;

    StdFarMemSet( JSDateiKopf, 0, sizeof( *JSDateiKopf ) );
    StdFarMemCpy( JSDateiKopf->IdMarke, (CHAR FAR *)JSFILEIDMARKE, sizeof( JSFILEIDMARKE ) );
    JSDateiKopf->GrVersion = JSFILEGRVERSION;
    JSDateiKopf->KlVersion = JSFILEKLVERSION;

    FilePtrDistance = sizeof( *TMSSatzAnfang );
    DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_BEGIN, NULL );
    DosRead( TMSFile, TMSSatzMitte, sizeof( *TMSSatzMitte ), NULL );

    JSDateiKopf->Jahr = (WORD)StdAsciiToBin( (BYTE)sizeof( TMSSatzMitte->Jahr ), TMSSatzMitte->Jahr );
    if( JSDateiKopf->Jahr >= 50 )
	JSDateiKopf->Jahr += 1900;
    else
	JSDateiKopf->Jahr += 2000;
    JSDateiKopf->Monat = (BYTE)StdAsciiToBin( (BYTE)sizeof( TMSSatzMitte->Monat ), TMSSatzMitte->Monat );

    if( (JSDateiKopf->Jahr % 4 == 0) && (JSDateiKopf->Monat == 2) )
	AnzTage[2 - 1]++;

    JSDateiKopf->AnzTage = AnzTage[JSDateiKopf->Monat - 1];
    JSDateiKopf->AnzPersonen = (WORD)(TMSDateiLaenge / (sizeof( *TMSSatzAnfang ) + (JSDateiKopf->AnzTage * sizeof( *TMSSatzMitte )) + sizeof( *TMSSatzEnde )));
    JSDateiKopf->Kontrolliert = TRUE;

    FilePtrDistance = 0;
    DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_BEGIN, NULL );

    StdStrCpy( DestinationFileName, DATAFILENAMETEMPL );
    StdBinToAscii( JSDateiKopf->Monat, 2, &DestinationFileName[0], LEFT, 2 );

    StdStrCpy( ArchiveFileName, ARCHIVEFILENAMETEMPL );
    StdBinToAscii( JSDateiKopf->Jahr, 4, &ArchiveFileName[0], LEFT, 4 );

    return( TRUE );
    }

BOOL CheckNumDays( BYTE AnzTage )
    {
    SDWORD FilePtrDistance;
    CHAR   TmpFlag;
    BOOL   AlleTageVorhanden;
    BYTE   TageZaehler;

    FilePtrDistance = sizeof( *TMSSatzAnfang );
    DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_BEGIN, NULL );

    AlleTageVorhanden = TRUE;
    FilePtrDistance = (SDWORD)((SDWORD)sizeof( *TMSSatzMitte ) - (SDWORD)sizeof( TMSSatzMitte->Flag ));
    for( TageZaehler = 2; TageZaehler <= AnzTage; TageZaehler++ )
	{
	DosRead( TMSFile, (VOID FAR *)&TmpFlag, sizeof( TMSSatzMitte->Flag ), NULL );
	if( TmpFlag != 'D' )
	    {
	    AlleTageVorhanden = FALSE;
	    break;
	    }

	DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_CURRENT, NULL );
	}

    FilePtrDistance = 0;
    DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_BEGIN, NULL );

    if( !AlleTageVorhanden )
	return( FALSE );
    else
	return( TRUE );
    }

BYTE ConvertData( WORD AnzPersonen, BYTE AnzTage )
    {
    SDWORD FilePtrDistance;
    WORD   PersZaehler;
    BYTE   TageZaehler;
    BYTE   FeldZaehler;
    BYTE   ZKontiZaehler;
    BYTE   BegruendungenZaehler;
    BYTE   StempelungenZaehler;

    for( PersZaehler = 0; PersZaehler < AnzPersonen; PersZaehler++ )
	{
	WinSendMsg( Progressbar, WM_SHOW, (MPARAM)StdDivide( ((DWORD)PersZaehler + 1) * 100, AnzPersonen ), 0 );
	DosRead( TMSFile, TMSSatzAnfang, sizeof( *TMSSatzAnfang ), NULL );

	StdFarMemSet( JSPersonenInfo, 0, sizeof( *JSPersonenInfo ) );
	JSPersonenInfo->Personalnummer = StdAsciiToBin( 9, TMSSatzAnfang->Personalnummer );

	JSPersonenInfo->LaengeName = sizeof( TMSSatzAnfang->Name );
	while( TMSSatzAnfang->Name[JSPersonenInfo->LaengeName - 1] == SPACECHAR && JSPersonenInfo->LaengeName > 0 )
	    JSPersonenInfo->LaengeName--;

	StdFarMemCpy( JSPersonenInfo->Name, TMSSatzAnfang->Name, JSPersonenInfo->LaengeName );

	JSPersonenInfo->JahrAnstellung = (WORD)StdAsciiToBin( 2, &(TMSSatzAnfang->Anstellung[0]) );
	if( JSPersonenInfo->JahrAnstellung >= 50 )
	    JSPersonenInfo->JahrAnstellung += 1900;
	else
	    JSPersonenInfo->JahrAnstellung += 2000;
	JSPersonenInfo->MonatAnstellung = (BYTE)StdAsciiToBin( 2, &(TMSSatzAnfang->Anstellung[2]) );
	JSPersonenInfo->TagAnstellung =   (BYTE)StdAsciiToBin( 2, &(TMSSatzAnfang->Anstellung[4]) );
	if( JSPersonenInfo->MonatAnstellung == 0 || JSPersonenInfo->TagAnstellung == 0 )
	    {
	    JSPersonenInfo->JahrAnstellung = 0;
	    JSPersonenInfo->MonatAnstellung = 0;
	    JSPersonenInfo->TagAnstellung = 0;
	    }

	JSPersonenInfo->JahrAustritt = (WORD)StdAsciiToBin( 2, &(TMSSatzAnfang->Austritt[0]) );
	if( JSPersonenInfo->JahrAustritt >= 50 )
	    JSPersonenInfo->JahrAustritt += 1900;
	else
	    JSPersonenInfo->JahrAustritt += 2000;
	JSPersonenInfo->MonatAustritt = (BYTE)StdAsciiToBin( 2, &(TMSSatzAnfang->Austritt[2]) );
	JSPersonenInfo->TagAustritt =	(BYTE)StdAsciiToBin( 2, &(TMSSatzAnfang->Austritt[4]) );
	if( JSPersonenInfo->MonatAustritt == 0 || JSPersonenInfo->TagAustritt == 0 )
	    {
	    JSPersonenInfo->JahrAustritt = 0;
	    JSPersonenInfo->MonatAustritt = 0;
	    JSPersonenInfo->TagAustritt = 0;
	    }

	JSPersonenInfo->Beschaeftigungsgrad = (BYTE)StdAsciiToBin( (BYTE)sizeof( TMSSatzAnfang->Beschaeftigungsgrad ), TMSSatzAnfang->Beschaeftigungsgrad );

	JSPersonenInfo->LaengeFunktion = sizeof( TMSSatzAnfang->Funktion );
	while( TMSSatzAnfang->Funktion[JSPersonenInfo->LaengeFunktion - 1] == SPACECHAR && JSPersonenInfo->LaengeFunktion > 0 )
	    JSPersonenInfo->LaengeFunktion--;

	StdFarMemCpy( JSPersonenInfo->Funktion, TMSSatzAnfang->Funktion, JSPersonenInfo->LaengeFunktion );

	for( FeldZaehler = 0; FeldZaehler < 7; FeldZaehler++ )
	    {
	    JSPersonenInfo->Felder[FeldZaehler].LaengeFeld = sizeof( TMSSatzAnfang->Felder[FeldZaehler] );
	    while( TMSSatzAnfang->Felder[FeldZaehler][JSPersonenInfo->Felder[FeldZaehler].LaengeFeld - 1] == SPACECHAR && JSPersonenInfo->Felder[FeldZaehler].LaengeFeld > 0 )
		JSPersonenInfo->Felder[FeldZaehler].LaengeFeld--;

	    StdFarMemCpy( JSPersonenInfo->Felder[FeldZaehler].Feld, TMSSatzAnfang->Felder[FeldZaehler], JSPersonenInfo->Felder[FeldZaehler].LaengeFeld );

	    if( JSPersonenInfo->Felder[FeldZaehler].LaengeFeld > 0 )
		{
		JSPersonenInfo->BenutzteFelder |= 1 << FeldZaehler;
		JSPersonenInfo->AnzFelder++;
		}
	    }

	DosWrite( JSTmpFile, JSPersonenInfo, sizeof( *JSPersonenInfo ), NULL );

	WinSendMsg( Info, WM_SHOW, PERSON, (MPARAM)(PersZaehler + 1) );

	for( TageZaehler = 0; TageZaehler < AnzTage; TageZaehler++ )
	    {
	    WinSendMsg( Info, WM_SHOW, TAG, (MPARAM)(TageZaehler + 1) );

	    DosRead( TMSFile, TMSSatzMitte, sizeof( *TMSSatzMitte ), NULL );
	    StdFarMemSet( JSTag, 0, sizeof( *JSTag ) );

	    for( StempelungenZaehler = 0; StempelungenZaehler < 20; StempelungenZaehler++ )
		if( StdFarMemCmp( TMSSatzMitte->Stempelungen[StempelungenZaehler], (CHAR FAR *)"00000", 5 ) == 0 )
		    continue;
		else
		    {
		    JSTag->Stempelungen[StempelungenZaehler].EinAusgang = (WORD)StdAsciiToBin( 1, &(TMSSatzMitte->Stempelungen[StempelungenZaehler][0]) ) - 1;
		    JSTag->Stempelungen[StempelungenZaehler].Zeit = (WORD)StdAsciiToBin( 4, &(TMSSatzMitte->Stempelungen[StempelungenZaehler][1]) );
		    JSTag->AnzStempelungen++;
		    }

	    for( BegruendungenZaehler = 0; BegruendungenZaehler < 21; BegruendungenZaehler++ )
		if( StdFarMemCmp( TMSSatzMitte->Begruendungen[BegruendungenZaehler].Code, (CHAR FAR *)"000", 3 ) == 0 )
		    continue;
		else
		    {
		    JSTag->Begruendungen[BegruendungenZaehler].Code = (WORD)StdAsciiToBin( 3, TMSSatzMitte->Begruendungen[BegruendungenZaehler].Code );
		    JSTag->Begruendungen[BegruendungenZaehler].Typ = (WORD)StdAsciiToBin( 1, &TMSSatzMitte->Begruendungen[BegruendungenZaehler].Typ ) - 1;
		    JSTag->Begruendungen[BegruendungenZaehler].Herkunft = (WORD)StdAsciiToBin( 1, &(TMSSatzMitte->Begruendungen[BegruendungenZaehler].Herkunft[0]) ) - 1;
		    JSTag->Begruendungen[BegruendungenZaehler].Dauer = (WORD)StdAsciiToBin( 4, TMSSatzMitte->Begruendungen[BegruendungenZaehler].Dauer );
		    JSTag->AnzBegruendungen++;
		    }

	    for( ZKontiZaehler = 0; ZKontiZaehler < 20; ZKontiZaehler++ )
		if( StdFarMemCmp( TMSSatzMitte->Zeitkonti[ZKontiZaehler], (CHAR FAR *)"0000", 4 ) == 0 )
		    continue;
		else
		    {
		    JSTag->Zeitkonti[ZKontiZaehler] = (SWORD)StdAsciiToBin( 4, &(TMSSatzMitte->Zeitkonti[ZKontiZaehler][0]) );
		    if( TMSSatzMitte->Zeitkonti[ZKontiZaehler][4] == '-' )
			JSTag->Zeitkonti[ZKontiZaehler] = -(JSTag->Zeitkonti[ZKontiZaehler]);

		    JSTag->BenutzteZeitkonti |= 1 << ZKontiZaehler;
		    JSTag->AnzZeitkonti++;
		    }

	    DosWrite( JSTmpFile, JSTag, sizeof( *JSTag ), NULL );
	    if( StdFarMemCmp( TMSSatzMitte->Kontrolle, "099", sizeof( "099" ) - 1) != 0 )
		return( UNKONTROLLIERT );
	    }

	FilePtrDistance = (SDWORD)sizeof( *TMSSatzEnde );
	DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_CURRENT, NULL );

	if( BiosIsKeyInBuffer() )
	    if( BiosGetKey() == KBESC )
		{
		WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Aufnahme wurde abgebrochen.", (MPARAM)"" );
		return( ABGEBROCHEN );
		}
	}

    FilePtrDistance = 0;
    DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_BEGIN, NULL );
    return( OK );
    }


MSG  InfoProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    switch( Msg )
	{
	case WM_CREATE:
	    {
	    WinString( HWnd, "Person        aus      :", LEFT, 1, 3 );
	    WinString( HWnd, "ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ", LEFT, 1, 4 );

	    WinString( HWnd, "Name:", LEFT, 1, 6 );
	    WinString( HWnd, "Personalnummer:", LEFT, 1, 7 );

	    WinString( HWnd, "ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ", LEFT, 1, 9 );

	    WinString( HWnd, "Tag           aus      ", LEFT, 1, 11 );
	    WinString( HWnd, "ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ", LEFT, 1, 12 );

	    return( WM_PROCESSED );
	    }

	case WM_SHOW:
	    switch( (BYTE)MP1 )
		{
		case MONATJAHR:
		    {
		    CHAR MonatJahr[20];
		    CHAR String[6];

		    StdStrCpy( MonatJahr, StdMonthName( JSDateiKopf->Monat ) );
		    StdStrCpy( String, " 0000" );
		    StdBinToAscii( JSDateiKopf->Jahr, 4, (CHAR FAR *)&String[1], RIGHT, 1 );
		    StdStrCat( MonatJahr, String );

		    WinString( HWnd, MonatJahr, LEFT, 1, 0 );
		    WinFill( HWnd, 'ƒ', 1, 1, (BYTE)StdStrLen( MonatJahr ), 1 );
		    WinColor( HWnd, HIGHLIGHT, 0, 0, (BYTE)(StdStrLen( MonatJahr ) + 1), 0 );
		    break;
		    }


		case ANZPERSONTAG:
		    {
		    CHAR String[5];

		    StdStrCpy( String, "    " );
		    StdBinToAscii( JSDateiKopf->AnzPersonen, 4, (CHAR FAR *)String, RIGHT, 1 );
		    WinString( HWnd, String, LEFT, 20, 3 );

		    StdStrCpy( String, "    " );
		    StdBinToAscii( JSDateiKopf->AnzTage, 4, (CHAR FAR *)String, RIGHT, 1 );
		    WinString( HWnd, String, LEFT, 20, 11 );

		    break;
		    }

		case PERSON:
		    {
		    CHAR String[31];

		    StdStrCpy( String, "   0" );
		    StdBinToAscii( (WORD)MP2, 4, (CHAR FAR *)String, RIGHT, 1 );
		    WinString( HWnd, String, RIGHT, 12, 3 );

		    StdFarStrCpy( String, JSPersonenInfo->Name );
		    WinFill( HWnd, SPACECHAR, 18, 6, 47, 6 );
		    WinString( HWnd, String, RIGHT, 47, 6 );

		    StdStrCpy( String, "000000000" );
		    StdBinToAscii( JSPersonenInfo->Personalnummer, 9, (CHAR FAR *)String, RIGHT, 9 );
		    WinFill( HWnd, SPACECHAR, 18, 7, 47, 7 );
		    WinString( HWnd, String, RIGHT, 47, 7 );
		    break;
		    }

		case TAG:
		    {
		    CHAR String[3];

		    StdStrCpy( String, " 0" );
		    StdBinToAscii( (BYTE)MP2, 2, (CHAR FAR *)String, RIGHT, 1 );

		    WinString( HWnd, String, RIGHT, 12, 11 );
		    break;
		    }
		}
	    return( WM_PROCESSED );

	}
    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


BYTE OpenDataFile( struct DateiKopf FAR *DateiKopf, WORD Jahr, BYTE Monat )
    {
    CHAR ArchiveFileName[13];
    CHAR DataFileName[13];

    StdStrCpy( ArchiveFileName, ARCHIVEFILENAMETEMPL );
    StdBinToAscii( Jahr, 4, &ArchiveFileName[0], LEFT, 4 );

    StdStrCpy( DataFileName, DATAFILENAMETEMPL );
    StdBinToAscii( Monat, 2, &DataFileName[0], LEFT, 2 );

    WinSendMsg( Desktop, WM_RESTOREVIDEOMODE, 0, 0 );
    if( spawnl( P_WAIT, DecompressProgName, DecompressProgName, DecompressParams, ArchiveFileName, DataFileName, NULL ) != 0 )
	{
	WinSendMsg( Desktop, WM_SETVIDEOMODE, 0, 0 );
	return( ERROR );
	}

    WinSendMsg( Desktop, WM_SETVIDEOMODE, 0, 0 );

    DosRename( DataFileName, JSTmpFileName );

    DosOpen( JSTmpFileName, &DataFile, OPEN_RDONLY );
    DosRead( DataFile, DateiKopf, sizeof( *DateiKopf ), NULL );

    Month = Monat;
    Year = Jahr;
    FilePtrAtPersonenInfo = TRUE;
    return( OK );
    }


BYTE ReadPersonenInfo( struct PersonenInfo FAR *PersonenInfo )
    {
    SDWORD FilePtrDistance;

    if( !FilePtrAtPersonenInfo )
	{
	FilePtrDistance = sizeof( struct Tag ) * StdMonthNumDays( Month, Year );
	DosSetFilePtr( DataFile, &FilePtrDistance, FILE_CURRENT, NULL );
	}

    DosRead( DataFile, PersonenInfo, sizeof( *PersonenInfo ), NULL );

    FilePtrAtPersonenInfo = FALSE;
    }


BYTE ReadTage( struct Tag FAR *Tage )
    {
    DosRead( DataFile, Tage, sizeof( *Tage ) * StdMonthNumDays( Month, Year ), NULL );

    FilePtrAtPersonenInfo = TRUE;
    }


BYTE ResetDataFile( VOID )
    {
    SDWORD FilePtrDistance;

    FilePtrDistance = sizeof( struct DateiKopf );
    DosSetFilePtr( DataFile, &FilePtrDistance, FILE_BEGIN, NULL );

    FilePtrAtPersonenInfo = TRUE;
    }


BYTE DeleteDataFile( VOID )
    {
    DosClose( DataFile );
    DosDelete( JSTmpFileName );

    return( OK );
    }
