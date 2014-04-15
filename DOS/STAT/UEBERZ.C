// ****************************
// ***	     Ueberzeit	    ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"


MSG  UeberzeitProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
BYTE Ueberzeit( HWND HWnd );
BYTE UeberzeitDruck( WORD AnzPersonen, struct UeberzeitZaehler FAR *UeberzZaehler );
BYTE UeberzeitMonatsAuswertung( HWND HWnd, WORD AnzPersonen, struct UeberzeitZaehler FAR *UeberzZaehler,
				BYTE Beginn, BYTE Ende, BYTE BeginnProzent, BYTE EndeProzent );

MSG  UeberzeitPersonInfoProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  GrenzwertProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

extern HWND Bottomline;

extern struct ConfigData FAR *ConfigData;

extern WORD NumBegruendungen;
extern WORD NumAbteilungen;
extern struct Eintrag FAR *Begruendungen;
extern struct Eintrag FAR *Abteilungen;

struct DateiKopf FAR *DateiKopf;
struct PersonenInfo FAR *PersonenInfo;
struct Tag FAR *Tage;

HWND   PersonInfo;
HWND   Progressbar;

struct UeberzeitZaehler
	{
	SDWORD	    Zaehler;
	SDWORD	    gekuerzterZaehler;
	DWORD	    Personalnummer;
	CHAR	    Abteilung[6];
	CHAR	    Name[31];
	};

MSG  UeberzeitProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static struct HelpKey HelpKeys[NUMUEBERZHELPKEYS] =
	{ {  0,  0, "</>    Min. erhîhen/erniedrigen" },
	  {  0,  1, "<Pg U/D> Std. erhîhen/erniedrigen" },
	  { 40,  0, "<Enter>  Statistik generieren" },
	  { 40,  1, "<Esc>    Schalttafel verlassen" } };

    static HWND Grenzwert;

    switch( Msg )
	{
	case WM_CREATE:
	    WinCreateWindow( HWnd, &Grenzwert, GrenzwertProc, 0, 0, 1, 6, 19, 6 );
	    return( WM_PROCESSED );

	case WM_DESTROY:
	    WinDestroyWindow( Grenzwert );
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    WinColor( HWnd, PANEL, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    WinString( HWnd, "Grenzwerte Åberschritten", LEFT, 1, 0 );
	    WinString( HWnd, "ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕ", LEFT, 1, 1 );

	    WinString( HWnd, "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø", LEFT, 1, 9 );
	    WinString( HWnd, "≥                                        ≥", LEFT, 1, 10 );
	    WinString( HWnd, "≥  Abt. Name          öberzeit  gekÅrzt  ≥", LEFT, 1, 11 );
	    WinString( HWnd, "≥  ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ  ≥", LEFT, 1, 12 );
	    WinString( HWnd, "≥  D    Franz Neumann    17.55    15.00  ≥", LEFT, 1, 13 );
	    WinString( HWnd, "≥  EL         .          19.00    17.50  ≥", LEFT, 1, 14 );
	    WinString( HWnd, "≥  F          .          12.66    12.66  ≥", LEFT, 1, 15 );
	    WinString( HWnd, "≥  .          .            .        .    ≥", LEFT, 1, 16 );
	    WinString( HWnd, "≥  .          .            .        .    ≥", LEFT, 1, 17 );
	    WinString( HWnd, "≥                                        ≥", LEFT, 1, 18 );
	    WinString( HWnd, "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ", LEFT, 1, 19 );

	    WinString( HWnd, "Grenzwert:", LEFT, 1, 4 );
	    WinString( HWnd, "ƒƒƒƒƒƒƒƒƒƒ", LEFT, 1, 5 );
	    WinSendMsg( Grenzwert, WM_SHOW, 0, 0 );
	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, 0, 25, 0 );

	    WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMUEBERZHELPKEYS );

	    WinSendMsg( Grenzwert, WM_SETFOCUS, 0, 0 );
	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, PANEL, 0, 0, 25, 0 );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    if( WinSendMsg( Grenzwert, Msg, MP1, MP2 ) == WM_PROCESSED )
		return( WM_PROCESSED );

	    switch( (WORD)MP1 )
		{
		    case KBENTER:
			WinSendMsg( Grenzwert, WM_CLEARFOCUS, 0, 0 );
			WinColor( HWnd, PANEL, 0, 2, WinGetx2( HWnd ), WinGety2( HWnd )	);
			WinFill( HWnd, SPACECHAR, 0, 2, WinGetx2( HWnd ), WinGety2( HWnd ) );
			Ueberzeit( HWnd );
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


BYTE Ueberzeit( HWND HWnd )
    {
    struct UeberzeitZaehler FAR *UeberzZaehler;

    BYTE AnzMonate;
    BYTE MonatsZaehler;

    WORD AnzPersonen;
    WORD PersonenZaehler;
    WORD PersonenZeiger;

    WORD AbtZaehler;

    WORD Counter;

    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Daten werden ausgewertet...", (MPARAM)"Personenliste wird erstellt..." );

    DateiKopf = DosAllocFarMem( sizeof( *DateiKopf ) );
    PersonenInfo = DosAllocFarMem( sizeof( *PersonenInfo ) );
    Tage = DosAllocFarMem( sizeof( *Tage ) * 31 );

    AnzMonate = (BYTE)(( ConfigData->Perioden[UEBERZEIT].EndJahr
			 - ConfigData->Perioden[UEBERZEIT].AnfJahr
			 + 1 ) * 12
		     - ( ConfigData->Perioden[UEBERZEIT].AnfMonat - 1 )
		     - ( 12 - ConfigData->Perioden[UEBERZEIT].EndMonat ));

    OpenDataFile( DateiKopf,
	    (WORD)(ConfigData->Perioden[UEBERZEIT].AnfJahr),
	    (BYTE)(ConfigData->Perioden[UEBERZEIT].AnfMonat) );

    /* Test:
    OpenDataFile( DateiKopf,
	    1992,
	    1 );
    DeleteDataFile();
    OpenDataFile( DateiKopf,
	    1992,
	    5 );
    DeleteDataFile(); */

    AnzPersonen = 0;

    for( PersonenZaehler = 0; PersonenZaehler < DateiKopf->AnzPersonen; PersonenZaehler++ )
	{
	ReadPersonenInfo( PersonenInfo );

	if( PersonInAbtListe( ConfigData->AbtCheckListe[UEBERZEIT], PersonenInfo ) )
	    AnzPersonen++;
	}

    UeberzZaehler = DosAllocFarMem( AnzPersonen * sizeof( *UeberzZaehler ) );

    ResetDataFile();
    PersonenZeiger = 0;

    WinCreateWindow( HWnd, &PersonInfo, UeberzeitPersonInfoProc, 0, 0, 0, 5, 47, 15 );

    for( PersonenZaehler = 0; PersonenZaehler < DateiKopf->AnzPersonen; PersonenZaehler++ )
	{
	ReadPersonenInfo( PersonenInfo );
	WinSendMsg( PersonInfo, WM_SHOW, PERSON, 0 );

	if( PersonInAbtListe( ConfigData->AbtCheckListe[UEBERZEIT], PersonenInfo ) )
	    {
	    UeberzZaehler[PersonenZeiger].Zaehler = 0;
	    UeberzZaehler[PersonenZeiger].gekuerzterZaehler = 0;
	    UeberzZaehler[PersonenZeiger].Personalnummer = PersonenInfo->Personalnummer;

	    StdFarStrCpy( UeberzZaehler[PersonenZeiger].Abteilung, PersonenInfo->Felder[ConfigData->AbtFeldNr - 1].Feld );
	    StdFarStrCpy( UeberzZaehler[PersonenZeiger].Name, PersonenInfo->Name );
	    PersonenZeiger++;
	    }
	}

    ResetDataFile();

    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Daten werden ausgewertet...", (MPARAM)"" );
    WinCreateWindow( HWnd, &Progressbar, ProgressbarProc, 0, 0, 1, 17, 47, 19 );

    if( AnzMonate == 1 )
	{
	UeberzeitMonatsAuswertung( HWnd, AnzPersonen, UeberzZaehler,
				   ConfigData->Perioden[UEBERZEIT].AnfTag,
				   ConfigData->Perioden[UEBERZEIT].EndTag,
				   0, 100 );

	DeleteDataFile();
	}
    else
	for( MonatsZaehler = 0; MonatsZaehler < AnzMonate; MonatsZaehler++ )
	    {
	    if( MonatsZaehler > 0 )
		if( OpenDataFile( DateiKopf,
		    (WORD)(ConfigData->Perioden[UEBERZEIT].AnfJahr + (ConfigData->Perioden[UEBERZEIT].AnfMonat + MonatsZaehler - 1) / 12),
		    (BYTE)((ConfigData->Perioden[UEBERZEIT].AnfMonat + MonatsZaehler) % 12) ) != OK )
		    continue;

	    if( MonatsZaehler == 0 && ConfigData->Perioden[UEBERZEIT].AnfTag > 1 )
		{
		UeberzeitMonatsAuswertung( HWnd, AnzPersonen, UeberzZaehler,
				  (BYTE)ConfigData->Perioden[UEBERZEIT].AnfTag,
				  0,
				  (BYTE)StdDivide( (MonatsZaehler) * 100, AnzMonate ),
				  (BYTE)StdDivide( (MonatsZaehler + 1) * 100, AnzMonate ) );
		DeleteDataFile();
		continue;
		}

	    if( (MonatsZaehler == (BYTE)(AnzMonate - 1)) && (ConfigData->Perioden[UEBERZEIT].EndTag < StdMonthNumDays( ConfigData->Perioden[UEBERZEIT].EndMonat, ConfigData->Perioden[UEBERZEIT].EndJahr )) )
		{
		UeberzeitMonatsAuswertung( HWnd, AnzPersonen, UeberzZaehler,
				  0,
				  (BYTE)ConfigData->Perioden[UEBERZEIT].EndTag,
				  (BYTE)StdDivide( (MonatsZaehler) * 100, AnzMonate ),
				  (BYTE)StdDivide( (MonatsZaehler + 1) * 100, AnzMonate ) );
		DeleteDataFile();
		continue;
		}

	    UeberzeitMonatsAuswertung( HWnd, AnzPersonen, UeberzZaehler,
			      0, 0,
			      (BYTE)StdDivide( (MonatsZaehler) * 100, AnzMonate ),
			      (BYTE)StdDivide( (MonatsZaehler + 1) * 100, AnzMonate ) );
	    DeleteDataFile();
	    }

    WinSendMsg( Progressbar, WM_SHOW, 100, 0 );
    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Auswertung abgeschlossen.", (MPARAM)"<Enter> Drucken  -  <Esc> Abbrechen" );

    if( BiosGetKey() == KBENTER )
	UeberzeitDruck( AnzPersonen, UeberzZaehler );
    else
	WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Ausdruck wurde abgebrochen.", (MPARAM)"" );

    WinDestroyWindow( Progressbar );
    WinDestroyWindow( PersonInfo );

    DosFreeFarMem( UeberzZaehler );

    DosFreeFarMem( Tage );
    DosFreeFarMem( PersonenInfo );
    DosFreeFarMem( DateiKopf );
    return( TRUE );
    }


BYTE UeberzeitDruck( WORD AnzPersonen, struct UeberzeitZaehler FAR *UeberzZaehler )
    {
    CHAR Datum[9];
    WORD Counter;
    BYTE LinienZaehler;
    BYTE SpaltenZaehler;
    CHAR String[40];
    BYTE StringCounter;

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
    WritePrinter( DATA, "STATISTIK  -  Grenzwerte Åberschritten" );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( DATA, "======================================" );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    StdStrCpy( Datum, "  .  .  " );
    StdBinToAscii( ConfigData->Perioden[UEBERZEIT].AnfTag, 2, &Datum[0], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[UEBERZEIT].AnfMonat, 2, &Datum[3], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[UEBERZEIT].AnfJahr % 100, 2, &Datum[6], RIGHT, 1 );
    WritePrinter( DATA, Datum );
    WritePrinter( DATA, " - " );

    StdStrCpy( Datum, "  .  .  " );
    StdBinToAscii( ConfigData->Perioden[UEBERZEIT].EndTag, 2, &Datum[0], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[UEBERZEIT].EndMonat, 2, &Datum[3], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[UEBERZEIT].EndJahr % 100, 2, &Datum[6], RIGHT, 1 );
    WritePrinter( DATA, Datum );
    WritePrinter( DATA, " " );

    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( STARTUNDERLINE, NULL );
    WritePrinter( DATA, "Beruecksichtigte Abteilungen:" );
    WritePrinter( ENDUNDERLINE, NULL );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    for( Counter = 0; Counter < NumAbteilungen; Counter++ )
	if( ConfigData->AbtCheckListe[UEBERZEIT][Counter] )
	    {
	    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
	    WritePrinter( DATA, Abteilungen[Counter].Code );
	    WritePrinter( SETHPOS, (CHAR FAR *)(LEFTINDENT + 8) );
	    WritePrinter( DATA, Abteilungen[Counter].Description );
	    WritePrinter( NEWLINE, NULL );
	    }

    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( STARTUNDERLINE, NULL );
    WritePrinter( DATA, "Beruecksichtigte BegrÅndungen:" );
    WritePrinter( ENDUNDERLINE, NULL );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    for( Counter = 0; Counter < NumBegruendungen; Counter++ )
	if( ConfigData->BegrCheckListe[UEBERZEIT][Counter] )
	    {
	    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
	    WritePrinter( DATA, Begruendungen[Counter].Code );
	    WritePrinter( SETHPOS, (CHAR FAR *)(LEFTINDENT + 6) );
	    WritePrinter( DATA, Begruendungen[Counter].Description );
	    WritePrinter( NEWLINE, NULL );
	    }

    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    StringZeitAng( ConfigData->Grenzwert, String, TRUE );

    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( DATA, "Grenzwert: " );
    WritePrinter( DATA, String );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( DATA, "Abt.    Name                                    öberzeit    öberz. gekÅrzt" );
    WritePrinter( NEWLINE, NULL );

    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( DATA, "--------------------------------------------------------------------------" );
    WritePrinter( NEWLINE, NULL );

    for( Counter = 0; Counter < AnzPersonen; Counter++ )
	if( UeberzZaehler[Counter].Zaehler >= ConfigData->Grenzwert )
	    {
	    CHAR String[20];
	    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
	    WritePrinter( DATA, UeberzZaehler[Counter].Abteilung );

	    WritePrinter( SETHPOS, (CHAR FAR *)(LEFTINDENT + 8) );
	    WritePrinter( DATA, UeberzZaehler[Counter].Name );

	    WritePrinter( SETHPOS, (CHAR FAR *)(LEFTINDENT + 38) );

	    StringZeitAng( UeberzZaehler[Counter].Zaehler, String, TRUE );

	    WritePrinter( DATA, (CHAR FAR *)String );

	    WritePrinter( SETHPOS, (CHAR FAR *)(LEFTINDENT + 45) );

	    StringZeitAng( UeberzZaehler[Counter].gekuerzterZaehler, String, TRUE );

	    WritePrinter( DATA, (CHAR FAR *)String );

	    WritePrinter( NEWLINE, NULL );
	    }

    ClosePrinter();
    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Ausdruck abgeschlossen.", (MPARAM)"" );

    return( TRUE );
    }


BYTE UeberzeitMonatsAuswertung( HWND HWnd, WORD AnzPersonen, struct UeberzeitZaehler FAR *UeberzZaehler,
				BYTE Beginn, BYTE Ende, BYTE BeginnProzent, BYTE EndeProzent )
    {
    BYTE DataBegrZaehler;
    WORD BegrZaehler;
    BYTE TageZaehler;
    WORD PersonenZaehler;
    WORD AufnPersZaehler;

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

	for( AufnPersZaehler = 0; AufnPersZaehler < AnzPersonen; AufnPersZaehler++ )
	    if( PersonenInfo->Personalnummer == UeberzZaehler[AufnPersZaehler].Personalnummer )
		{
		Aufnehmen = TRUE;
		break;
		}

	if( !Aufnehmen )
	    continue;

	ReadTage( Tage );

	for( TageZaehler = (BYTE)(Beginn - 1); TageZaehler <= (BYTE)(Ende - 1); TageZaehler++ )
	    {
	    SWORD delta = 0;
	    for( DataBegrZaehler = 0; DataBegrZaehler < Tage[TageZaehler].AnzBegruendungen; DataBegrZaehler++ )
		for( BegrZaehler = 0; BegrZaehler < NumBegruendungen; BegrZaehler++ )
		    if( Tage[TageZaehler].Begruendungen[DataBegrZaehler].Code ==
			(WORD)StdAsciiToBin( Begruendungen[BegrZaehler].CodeLength, (CHAR FAR *)Begruendungen[BegrZaehler].Code ) )
			{
			switch( ConfigData->BegrCheckListe[UEBERZEIT][BegrZaehler] )
			    {
			    case PLUS:
				UeberzZaehler[AufnPersZaehler].Zaehler += Tage[TageZaehler].Begruendungen[DataBegrZaehler].Dauer;
				delta += Tage[TageZaehler].Begruendungen[DataBegrZaehler].Dauer;
				break;
			    case MINUS:
				UeberzZaehler[AufnPersZaehler].Zaehler -= Tage[TageZaehler].Begruendungen[DataBegrZaehler].Dauer;
				delta -= Tage[TageZaehler].Begruendungen[DataBegrZaehler].Dauer;
				break;
			    }
			break;
			}
	    if( delta >= ConfigData->Grenzwert )
		delta = ConfigData->Grenzwert;

	    UeberzZaehler[AufnPersZaehler].gekuerzterZaehler += delta;
	    }
	}

    if( !(BeginnProzent == 0 && EndeProzent == 0) )
	WinSendMsg( Progressbar, WM_SHOW,
	    (MPARAM)(BeginnProzent + StdDivide( (DWORD)PersonenZaehler * ((DWORD)EndeProzent - (DWORD)BeginnProzent), DateiKopf->AnzPersonen )), 0 );

    return( TRUE );
    }


MSG  UeberzeitPersonInfoProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
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



MSG  GrenzwertProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
	switch( Msg )
	{
	case WM_CREATE:
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    CHAR String[18];

	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    strcpy( String, "     Std.    Min." );
	    StdBinToAscii( ConfigData->Grenzwert / 60, 4,(CHAR FAR *)&String[0], RIGHT, 1 );
	    StdBinToAscii( ConfigData->Grenzwert % 60, 2, (CHAR FAR *)&String[10], RIGHT, 1 );

	    WinString( HWnd, String, LEFT, 1, 0 );

	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    switch( (WORD)MP1 )
		{
		case KBUP:
		case KBRIGHT:
		    ConfigData->Grenzwert++;
		    break;

		case KBDOWN:
		case KBLEFT:
		    if( ConfigData->Grenzwert >= 1 )
			ConfigData->Grenzwert--;
		    break;

		case KBPGUP:
		    ConfigData->Grenzwert += 60;
		    break;

		case KBPGDOWN:
		    if( ConfigData->Grenzwert >= 60 )
			ConfigData->Grenzwert -= 60;
		    break;

		case KBHOME:
		    ConfigData->Grenzwert = 0;
		    break;

		case KBEND:
		    break;

		default:
		    return( MP1 );
		}
	    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );
	    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
	    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );

	    return( WM_PROCESSED );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }
