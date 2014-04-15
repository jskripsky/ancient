// ****************************
// ***	     Zeitkonti	    ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"

extern HWND Bottomline;


MSG  ZeitKontiProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );


MSG  ZeitKontiSumProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

MSG  ZeitKontiPersonInfoProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
BYTE ZeitKontiSummierung( HWND HWnd );

BYTE ZeitKontiMonatsAuswertung( HWND HWnd, SDWORD (FAR *ZKontiZaehler)[20],
				BYTE Beginn, BYTE Ende, BYTE BeginnProzent, BYTE EndeProzent );

BYTE ZeitKontiDruck( SDWORD (FAR *ZKontiZaehler)[20] );

extern struct ConfigData FAR *ConfigData;

struct DateiKopf FAR *DateiKopf;
struct PersonenInfo FAR *PersonenInfo;
struct Tag FAR *Tage;

extern WORD NumBegruendungen;
extern WORD NumAbteilungen;
extern WORD NumZeitKonti;
extern struct Eintrag FAR *Begruendungen;
extern struct Eintrag FAR *Abteilungen;
extern struct Eintrag FAR *ZeitKonti;

HWND   PersonInfo;
HWND   Progressbar;


MSG  ZeitKontiProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static struct HelpKey HelpKeys[NUMCHECKLSTHELPKEYS] =
	{ {  0,  0, "</>    Eintrag anwÑhlen" },
	  {  0,	 1, "<Leer>   Eintrag ein-/ausschalten" },
	  { 40,  1, "<Esc>    Schalttafel verlassen" } };

    static HWND SubPanel;

    switch( Msg )
	{
	case WM_CREATE:
	    WinCreateWindow( HWnd, &SubPanel, CheckListeProc, (MPARAM)ZEITKONTI, MP2, 0, 3, 42, 15 );
	    return( WM_PROCESSED );

	case WM_DESTROY:
	    WinDestroyWindow( SubPanel );
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    WinColor( HWnd, PANEL, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    WinColor( HWnd, PANEL, 0, 0, 8, 0 );
	    WinString( HWnd, "Zeitkonti", LEFT, 1, 0 );
	    WinString( HWnd, "ÕÕÕÕÕÕÕÕÕ", LEFT, 1, 1 );

	    WinString( HWnd, "ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 2) );
	    WinString( HWnd, "Schalttafel zur Auswahl aller zu berÅck-", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 1) );
	    WinString( HWnd, "sichtigender Abteilungen." , LEFT, 1, (BYTE)(WinGety2( HWnd ) - 0) );

	    WinSendMsg( SubPanel, WM_SHOW, 0, 0 );

	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, 0, 10, 0 );

	    WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMCHECKLSTHELPKEYS );
	    WinSendMsg( SubPanel, WM_SETFOCUS, 0, 0 );
	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, PANEL, 0, 0, 10, 0 );

	    WinSendMsg( SubPanel, WM_CLEARFOCUS, 0, 0 );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    if( WinSendMsg( SubPanel, Msg, MP1, MP2 ) == WM_PROCESSED )
		return( WM_PROCESSED );

	    switch( (WORD)MP1 )
		{
		case KBENTER:
			WinFill( HWnd, SPACECHAR, 0, 2, WinGetx2( HWnd ), WinGety2( HWnd ) );
			ZeitKontiSummierung( HWnd );
			WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Summierung abgeschlossen.", (MPARAM)"" );
			break;

		case KBTAB:
		case KBSHTAB:
		    return( WM_PROCESSED );

		default:
		    return( MP1 );
		}
	    return( WM_PROCESSED );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


MSG  ZeitKontiSumProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static struct HelpKey HelpKeys[NUMUEBERSHELPKEYS] =
	{ {  0,  0, "<Enter>  Statistik generieren" },
	  { 40,  0, "<Esc>    Schalttafel verlassen" } };

    switch( Msg )
	{
	case WM_SHOW:
	    {
	    WinColor( HWnd, PANEL, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    WinString( HWnd, "Zeitkontisummierung", LEFT, 1, 0 );
	    WinString( HWnd, "ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕ", LEFT, 1, 1 );

	    WinString( HWnd, "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø", LEFT, 1,  4 );
	    WinString( HWnd, "≥                                        ≥", LEFT, 1,  5 );
	    WinString( HWnd, "≥  Abt.  SOLLZEIT   ISTZEIT   FERIEN ... ≥", LEFT, 1,  6 );
	    WinString( HWnd, "≥  ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ  ≥", LEFT, 1,  7 );
	    WinString( HWnd, "≥  D       729.40    486.32    25.12 ... ≥", LEFT, 1,  8 );
	    WinString( HWnd, "≥  DS     4091.39   1434.36     0.00 ... ≥", LEFT, 1,  9 );
	    WinString( HWnd, "≥  E      8710.51   8001.12    71.33 ... ≥", LEFT, 1, 10 );
	    WinString( HWnd, "≥  .          .         .        .       ≥", LEFT, 1, 11 );
	    WinString( HWnd, "≥  .          .         .        .       ≥", LEFT, 1, 12 );
	    WinString( HWnd, "≥                                        ≥", LEFT, 1, 13 );
	    WinString( HWnd, "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ", LEFT, 1, 14 );

	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, 0, 20, 0 );

	    WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMDURCHSCHHELPKEYS );
	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, PANEL, 0, 0, 20, 0 );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    switch( (WORD)MP1 )
		{
		    case KBENTER:
			WinFill( HWnd, SPACECHAR, 0, 2, WinGetx2( HWnd ), WinGety2( HWnd ) );
			ZeitKontiSummierung( HWnd );
			WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Summierung abgeschlossen.", (MPARAM)"" );
			break;

		    case KBUP:
		    case KBDOWN:
		    case KBRIGHT:
		    case KBLEFT:
		    case KBTAB:
		    case KBSHTAB:
			return( WM_PROCESSED );

		    default:
			return( MP1 );
		}
	    return( WM_PROCESSED );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


BYTE ZeitKontiSummierung( HWND HWnd )
    {
    SDWORD (FAR *ZKontiZaehler)[20];

    BYTE AnzMonate;
    BYTE MonatsZaehler;

    WORD AbtZaehler;

    WORD Counter;

    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Daten werden ausgewertet...", (MPARAM)"Personenliste wird erstellt..." );

    DateiKopf = DosAllocFarMem( sizeof( *DateiKopf ) );
    PersonenInfo = DosAllocFarMem( sizeof( *PersonenInfo ) );
    Tage = DosAllocFarMem( sizeof( *Tage ) * 31 );

    AnzMonate = (BYTE)(( ConfigData->Perioden[ZKONTI].EndJahr
			 - ConfigData->Perioden[ZKONTI].AnfJahr
			 + 1 ) * 12
		     - ( ConfigData->Perioden[ZKONTI].AnfMonat - 1 )
		     - ( 12 - ConfigData->Perioden[ZKONTI].EndMonat ));

    ZKontiZaehler = DosAllocFarMem( NumAbteilungen * sizeof( ZKontiZaehler[20] ) );
    StdFarMemSet( ZKontiZaehler, 0, NumAbteilungen * sizeof( ZKontiZaehler[20] ) );

    WinCreateWindow( HWnd, &PersonInfo, ZeitKontiPersonInfoProc, 0, 0, 0, 5, 47, 15 );

    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Daten werden ausgewertet...", (MPARAM)"" );
    WinCreateWindow( HWnd, &Progressbar, ProgressbarProc, 0, 0, 1, 17, 47, 19 );

    OpenDataFile( DateiKopf,
	    (WORD)(ConfigData->Perioden[ZKONTI].AnfJahr),
	    (BYTE)(ConfigData->Perioden[ZKONTI].AnfMonat) );

    if( AnzMonate == 1 )
	{
	ZeitKontiMonatsAuswertung( HWnd, ZKontiZaehler,
				   ConfigData->Perioden[ZKONTI].AnfTag,
				   ConfigData->Perioden[ZKONTI].EndTag,
				   0, 100 );

	DeleteDataFile();
	}
    else
	for( MonatsZaehler = 0; MonatsZaehler < AnzMonate; MonatsZaehler++ )
	    {
	    if( MonatsZaehler > 0 )
		if( OpenDataFile( DateiKopf,
		    (WORD)(ConfigData->Perioden[ZKONTI].AnfJahr + (ConfigData->Perioden[ZKONTI].AnfMonat + MonatsZaehler - 1) / 12),
		    (BYTE)((ConfigData->Perioden[ZKONTI].AnfMonat + MonatsZaehler) % 12) ) != OK )
		    continue;

	    if( MonatsZaehler == 0 && ConfigData->Perioden[ZKONTI].AnfTag > 1 )
		{
		ZeitKontiMonatsAuswertung( HWnd, ZKontiZaehler,
				  (BYTE)ConfigData->Perioden[ZKONTI].AnfTag,
				  0,
				  (BYTE)StdDivide( (MonatsZaehler) * 100, AnzMonate ),
				  (BYTE)StdDivide( (MonatsZaehler + 1) * 100, AnzMonate ) );
		DeleteDataFile();
		continue;
		}

	    if( (MonatsZaehler == (BYTE)(AnzMonate - 1)) && (ConfigData->Perioden[ZKONTI].EndTag < StdMonthNumDays( ConfigData->Perioden[ZKONTI].EndMonat, ConfigData->Perioden[ZKONTI].EndJahr )) )
		{
		ZeitKontiMonatsAuswertung( HWnd, ZKontiZaehler,
				  0,
				  (BYTE)ConfigData->Perioden[ZKONTI].EndTag,
				  (BYTE)StdDivide( (MonatsZaehler) * 100, AnzMonate ),
				  (BYTE)StdDivide( (MonatsZaehler + 1) * 100, AnzMonate ) );
		DeleteDataFile();
		continue;
		}

	    ZeitKontiMonatsAuswertung( HWnd, ZKontiZaehler,
			      0, 0,
			      (BYTE)StdDivide( (MonatsZaehler) * 100, AnzMonate ),
			      (BYTE)StdDivide( (MonatsZaehler + 1) * 100, AnzMonate ) );
	    DeleteDataFile();
	    }

    WinSendMsg( Progressbar, WM_SHOW, 100, 0 );

    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Auswertung abgeschlossen.", (MPARAM)"<Enter> Drucken  -  <Esc> Abbrechen" );

    if( BiosGetKey() == KBENTER )
	ZeitKontiDruck( ZKontiZaehler );
    else
	WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Ausdruck wurde abgebrochen.", (MPARAM)"" );

    WinDestroyWindow( Progressbar );
    WinDestroyWindow( PersonInfo );

    DosFreeFarMem( ZKontiZaehler );

    DosFreeFarMem( Tage );
    DosFreeFarMem( PersonenInfo );
    DosFreeFarMem( DateiKopf );
    return( TRUE );
    }


BYTE ZeitKontiDruck( SDWORD (FAR *ZKontiZaehler)[20] )
    {
    CHAR Datum[9];
    WORD Counter;
    BYTE LinienZaehler;
    BYTE SpaltenZaehler;
    CHAR String[40];
    BYTE StringCounter;
    BYTE HPos;

    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Daten werden gedruckt...", (MPARAM)"" );

    OpenPrinter();

    WritePrinter( NORMALFONT, NULL );
    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    StdStrCpy( Datum, "  .  .  " );
    StdBinToAscii( DosQueryDay(), 2, &Datum[0], RIGHT, 1 );
    StdBinToAscii( DosQueryMonth(), 2, &Datum[3], RIGHT, 1 );
    StdBinToAscii( DosQueryYear() % 100, 2, &Datum[6], RIGHT, 1 );
    WritePrinter( DATA, Datum );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( DATA, FIRMATITLE );
    WritePrinter( NEWLINE, NULL );

    for( StringCounter = 0; StringCounter < StdStrLen( FIRMATITLE ); StringCounter++ )
	String[StringCounter] = '=';
    String[StringCounter] = 0;

    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( DATA, String );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( DATA, "STATISTIK  -  Summierung Zeitkonti" );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( DATA, "==================================" );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    StdStrCpy( Datum, "  .  .  " );
    StdBinToAscii( ConfigData->Perioden[ZKONTI].AnfTag, 2, &Datum[0], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[ZKONTI].AnfMonat, 2, &Datum[3], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[ZKONTI].AnfJahr % 100, 2, &Datum[6], RIGHT, 1 );
    WritePrinter( DATA, Datum );
    WritePrinter( DATA, " - " );

    StdStrCpy( Datum, "  .  .  " );
    StdBinToAscii( ConfigData->Perioden[ZKONTI].EndTag, 2, &Datum[0], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[ZKONTI].EndMonat, 2, &Datum[3], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[ZKONTI].EndJahr % 100, 2, &Datum[6], RIGHT, 1 );
    WritePrinter( DATA, Datum );
    WritePrinter( DATA, " " );

    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( STARTUNDERLINE, NULL );
    WritePrinter( DATA, "Summen der Zeitkonti in Std. und Min." );
    WritePrinter( ENDUNDERLINE, NULL );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    HPos = LEFTINDENT;
    WritePrinter( SETHPOS, (VOID FAR *)HPos );
    WritePrinter( DATA, "Abteilung" );
    HPos += 14;

    for( SpaltenZaehler = 0; SpaltenZaehler < 20; SpaltenZaehler++ )
	if( ConfigData->ZKontCheckListe[ZKONTI][SpaltenZaehler] )
	    {
	    CHAR String[11];
	    WritePrinter( SETHPOS, (VOID FAR *)HPos );

	    StdFarMemSet( String, 0, sizeof( String ) );
	    StdFarMemCpy( String, ZeitKonti[SpaltenZaehler].Description, sizeof( String ) - 1 );
	    WritePrinter( DATA, String );

	    HPos += 12;
	    }

    WritePrinter( NEWLINE, NULL );
    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( DATA, "--------------------------------------------------------------------------" );
    WritePrinter( NEWLINE, NULL );
    HPos = 0;

    for( Counter = 0; Counter < NumAbteilungen; Counter++ )
	{
	WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
	WritePrinter( DATA, Abteilungen[Counter].Code );

	HPos = LEFTINDENT + 14;

	for( SpaltenZaehler = 0; SpaltenZaehler < 20; SpaltenZaehler++ )
	    if( ConfigData->ZKontCheckListe[ZKONTI][SpaltenZaehler] )
		{
		CHAR String[11] = "       .  ";

		WritePrinter( SETHPOS, (VOID FAR *)HPos );

		if( ZKontiZaehler[Counter][SpaltenZaehler] < 0 )
		    {
		    ZKontiZaehler[Counter][SpaltenZaehler] *= -1;
		    String[0] = '-';
		    }

		StdBinToAscii( ZKontiZaehler[Counter][SpaltenZaehler] / 60, 6, &(String[1]), RIGHT, 1 );
		StdBinToAscii( ZKontiZaehler[Counter][SpaltenZaehler] % 60, 2, &(String[8]), RIGHT, 2 );
		WritePrinter( DATA, String );

		HPos += 12;
		}

	WritePrinter( NEWLINE, NULL );
	}

    ClosePrinter();
    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Ausdruck abgeschlossen.", (MPARAM)"" );

    return( TRUE );
    }



BYTE ZeitKontiMonatsAuswertung( HWND HWnd, SDWORD (FAR *ZKontiZaehler)[20],
				BYTE Beginn, BYTE Ende, BYTE BeginnProzent, BYTE EndeProzent )
    {
    WORD AbteilungsZaehler;
    BYTE KontoZaehler;
    BYTE TageZaehler;
    WORD PersonenZaehler;

    BOOL Aufnehmen;

    WinSendMsg( PersonInfo, WM_SHOW, MONATJAHR, 0 );

    if( Beginn == 0 )
	Beginn = 1;

    if( Ende == 0 )
	Ende = StdMonthNumDays( DateiKopf->Monat, DateiKopf->Jahr );

    for( PersonenZaehler = 0; PersonenZaehler < DateiKopf->AnzPersonen; PersonenZaehler++ )
	{
	if( !(BeginnProzent == 0 && EndeProzent == 0) )
	    WinSendMsg( Progressbar, WM_SHOW,
			(MPARAM)(BeginnProzent + StdDivide( (DWORD)PersonenZaehler * ((DWORD)EndeProzent - (DWORD)BeginnProzent), DateiKopf->AnzPersonen )), 0 );

	Aufnehmen = FALSE;
	ReadPersonenInfo( PersonenInfo );

	WinSendMsg( PersonInfo, WM_SHOW, PERSON, 0 );

	for( AbteilungsZaehler = 0; AbteilungsZaehler < NumAbteilungen; AbteilungsZaehler++ )
	    if( StdFarStrCmp( PersonenInfo->Felder[ConfigData->AbtFeldNr - 1].Feld, Abteilungen[AbteilungsZaehler].Code ) == 0 )
		{
		Aufnehmen = TRUE;
		break;
		}

	if( !Aufnehmen )
	    continue;

	ReadTage( Tage );

	for( TageZaehler = (BYTE)(Beginn - 1); TageZaehler <= (BYTE)(Ende - 1); TageZaehler++ )
	    for( KontoZaehler = 0; KontoZaehler < 20; KontoZaehler++ )
		ZKontiZaehler[AbteilungsZaehler][KontoZaehler] += Tage[TageZaehler].Zeitkonti[KontoZaehler];

	}

    if( !(BeginnProzent == 0 && EndeProzent == 0) )
	WinSendMsg( Progressbar, WM_SHOW,
	    (MPARAM)(BeginnProzent + StdDivide( (DWORD)PersonenZaehler * ((DWORD)EndeProzent - (DWORD)BeginnProzent), DateiKopf->AnzPersonen )), 0 );

    return( TRUE );
    }


MSG  ZeitKontiPersonInfoProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    switch( Msg )
	{
	case WM_CREATE:
	    {
	    WinString( HWnd, "Name:", LEFT, 1, 3 );
	    WinString( HWnd, "Personalnummer:", LEFT, 1, 4 );

	    return( WM_PROCESSED );
	    }

	case WM_SHOW:
	    switch( (BYTE)MP1 )
		{
		case MONATJAHR:
		    {
		    CHAR MonatJahr[20];
		    CHAR String[6];

		    WinFill( HWnd, SPACECHAR, 1, 0, 16, 1 );
		    StdStrCpy( MonatJahr, StdMonthName( DateiKopf->Monat ) );
		    StdStrCpy( String, " 0000" );
		    StdBinToAscii( DateiKopf->Jahr, 4, (CHAR FAR *)&String[1], RIGHT, 1 );
		    StdStrCat( MonatJahr, String );

		    WinString( HWnd, MonatJahr, LEFT, 1, 0 );
		    WinFill( HWnd, 'ƒ', 1, 1, (BYTE)StdStrLen( MonatJahr ), 1 );
		    break;
		    }

		case PERSON:
		    {
		    CHAR String[31];

		    StdFarStrCpy( String, PersonenInfo->Name );
		    WinFill( HWnd, SPACECHAR, 18, 3, 47, 3 );
		    WinString( HWnd, String, RIGHT, 47, 3 );

		    StdStrCpy( String, "000000000" );
		    StdBinToAscii( PersonenInfo->Personalnummer, 9, (CHAR FAR *)String, RIGHT, 9 );
		    WinFill( HWnd, SPACECHAR, 18, 4, 47, 4 );
		    WinString( HWnd, String, RIGHT, 47, 4 );
		    break;
		    }
		}
	    return( WM_PROCESSED );
	}
    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }
