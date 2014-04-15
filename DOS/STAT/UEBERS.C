// ****************************
// ***	    Uebersicht	    ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"


MSG  UebersichtProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
BYTE Uebersicht( HWND HWnd );
BYTE UebersichtDruck( BYTE AnzMonate, WORD (FAR *TagesSummen)[31], BYTE FAR *MonatsStatus );
BYTE UebersichtMonatsAuswertung( HWND HWnd, WORD FAR *TagesSummen, DWORD PersonalNr );

MSG  UebersichtPersonInfoProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

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



MSG  UebersichtProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
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

	    WinString( HWnd, "öbersichtstabelle", LEFT, 1, 0 );
	    WinString( HWnd, "ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕ", LEFT, 1, 1 );

	    WinString( HWnd, "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø", LEFT, 1,  4 );
	    WinString( HWnd, "≥                                         ≥", LEFT, 1,  5 );
	    WinString( HWnd, "≥  Franz Neumann                          ≥", LEFT, 1,	6 );
	    WinString( HWnd, "≥                                         ≥", LEFT, 1,  7 );
	    WinString( HWnd, "≥        Januar     Februar        MÑrz   ≥", LEFT, 1,  8 );
	    WinString( HWnd, "≥    ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ  ≥", LEFT, 1,  9 );
	    WinString( HWnd, "≥ 1.   0.50 Std.   0.00 Std.   0.00 Std.  ≥", LEFT, 1, 10 );
	    WinString( HWnd, "≥ 2.   0.00 Std.   0.00 Std.   0.00 Std.  ≥", LEFT, 1, 11 );
	    WinString( HWnd, "≥ 3.   1.40 Std.   1.00 Std.   0.00 Std.  ≥", LEFT, 1, 12 );
	    WinString( HWnd, "≥  .      .           .           .       ≥", LEFT, 1, 13 );
	    WinString( HWnd, "≥  .      .           .           .       ≥", LEFT, 1, 14 );
	    WinString( HWnd, "≥                                         ≥", LEFT, 1, 15 );
	    WinString( HWnd, "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ", LEFT, 1, 16 );

	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, 0, 18, 0 );

	    WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMDURCHSCHHELPKEYS );
	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, PANEL, 0, 0, 18, 0 );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    switch( (WORD)MP1 )
		{
		    case KBENTER:
			WinFill( HWnd, SPACECHAR, 0, 2, WinGetx2( HWnd ), WinGety2( HWnd ) );
			Uebersicht( HWnd );
			WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Statistik abgeschlossen.", (MPARAM)"" );
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


BYTE Uebersicht( HWND HWnd )
    {
    WORD (FAR *TagesSummen)[31];
    BYTE FAR *MonatsStatus;

    BYTE AnzMonate;
    BYTE MonatsZaehler;

    WORD PersonZeiger;
    WORD PersonZaehler;

    WORD Counter;

    DateiKopf = DosAllocFarMem( sizeof( *DateiKopf ) );
    PersonenInfo = DosAllocFarMem( sizeof( *PersonenInfo ) );
    Tage = DosAllocFarMem( sizeof( *Tage ) * 31 );

    AnzMonate = (BYTE)(( ConfigData->Perioden[UEBERSICHT].EndJahr
			 - ConfigData->Perioden[UEBERSICHT].AnfJahr
			 + 1 ) * 12
		     - ( ConfigData->Perioden[UEBERSICHT].AnfMonat - 1 )
		     - ( 12 - ConfigData->Perioden[UEBERSICHT].EndMonat ));

    *TagesSummen = DosAllocFarMem( AnzMonate * sizeof( *TagesSummen ) );
    MonatsStatus = DosAllocFarMem( AnzMonate * sizeof( *MonatsStatus ) );

    PersonZeiger = 0;

    for( ;; )
	{
	DWORD PersonalNr;
	BOOL PersonAufnehmen;

	WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Daten werden ausgewertet...", (MPARAM)"" );

	StdFarMemSet( TagesSummen, 0, AnzMonate * sizeof( *TagesSummen ) );
	StdFarMemSet( MonatsStatus, MONATINIT, AnzMonate * sizeof( *MonatsStatus ) );

	WinCreateWindow( HWnd, &PersonInfo, UebersichtPersonInfoProc, 0, 0, 0, 5, 47, 15 );
	WinCreateWindow( HWnd, &Progressbar, ProgressbarProc, 0, 0, 1, 17, 47, 19 );

	OpenDataFile( DateiKopf,
	    (WORD)(ConfigData->Perioden[UEBERSICHT].AnfJahr),
	    (BYTE)(ConfigData->Perioden[UEBERSICHT].AnfMonat) );

	PersonAufnehmen = FALSE;
	for( PersonZaehler = 0; PersonZaehler < PersonZeiger; PersonZaehler++ )
	    ReadPersonenInfo( PersonenInfo );

	for( ; PersonZeiger < DateiKopf->AnzPersonen; PersonZeiger++ )
	    {
	    WORD AbtZaehler;
	    ReadPersonenInfo( PersonenInfo );

	    WinSendMsg( PersonInfo, WM_SHOW, PERSON, 0 );


	    switch( ConfigData->Kriterium[UEBERSICHT] )
		{
		case 0:
		    if( StdFarStrCmp( ConfigData->Name[UEBERSICHT], PersonenInfo->Name ) == 0 )
			{
			PersonAufnehmen = TRUE;
			PersonZeiger++;
			};
		    break;

		case 1:
		    if( StdAsciiToBin( 9, ConfigData->PersonalNr[UEBERSICHT] ) == PersonenInfo->Personalnummer )
			{
			PersonAufnehmen = TRUE;
			PersonZeiger++;
			};
		    break;

		case 2:
		    for( AbtZaehler = 0; AbtZaehler < NumAbteilungen; AbtZaehler++ )
			{
			if( ConfigData->AbtCheckListe[UEBERSICHT][AbtZaehler] )
			    {
			    if( StdFarStrCmp( Abteilungen[AbtZaehler].Code, PersonenInfo->Felder[ConfigData->AbtFeldNr - 1].Feld ) == 0 )
				{
				PersonAufnehmen = TRUE;
				PersonZeiger++;
				break;
				};
			    };
			};
		    break;
		}

	    if( PersonAufnehmen )
		break;
	    }
	ResetDataFile();

	if( !PersonAufnehmen )
	    break;

	PersonalNr = PersonenInfo->Personalnummer;

	for( MonatsZaehler = 0; MonatsZaehler < AnzMonate; MonatsZaehler++ )
	    {
	    WinSendMsg( PersonInfo, WM_SHOW, MONATE, (MPARAM)MonatsZaehler + 1 );

	    if( MonatsZaehler > 0 )
		if( OpenDataFile( DateiKopf,
		    (WORD)(ConfigData->Perioden[UEBERSICHT].AnfJahr + (ConfigData->Perioden[UEBERSICHT].AnfMonat + MonatsZaehler - 1) / 12),
		    (BYTE)((ConfigData->Perioden[UEBERSICHT].AnfMonat + MonatsZaehler) % 12) ) != OK )
			{
			MonatsStatus[MonatsZaehler] = MONATNICHTVORH;
			continue;
			}

	    WinSendMsg( Progressbar, WM_SHOW,
		(BYTE)StdDivide( (MonatsZaehler) * 100, AnzMonate ), 0 );

	    UebersichtMonatsAuswertung( HWnd, TagesSummen[MonatsZaehler], PersonalNr );

	    MonatsStatus[MonatsZaehler] = MONATOK;
	    DeleteDataFile();
	    }

	WinSendMsg( Progressbar, WM_SHOW, 100, 0 );

	if( TRUE ) // Debug!!!!! --> if( Null Monate )
	    {
	    WinSendMsg( PersonInfo, WM_SHOW, MONATE, (MPARAM)MonatsZaehler );

	    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Auswertung abgeschlossen.", (MPARAM)"<Enter> Drucken  -  <Esc> Abbrechen" );

	    if( BiosGetKey() == KBENTER )
		UebersichtDruck( AnzMonate, TagesSummen, MonatsStatus );
	    else
		WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Ausdruck wurde abgebrochen.", (MPARAM)"" );
	    }
	else
	    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Kein Monat der Periode ist vorhanden!", (MPARAM)"" );

	WinDestroyWindow( Progressbar );
	WinDestroyWindow( PersonInfo );
	PersonZeiger++;
	}

    DosFreeFarMem( MonatsStatus );
    DosFreeFarMem( *TagesSummen );

    DosFreeFarMem( Tage );
    DosFreeFarMem( PersonenInfo );
    DosFreeFarMem( DateiKopf );
    return( TRUE );
    }


BYTE UebersichtDruck( BYTE AnzMonate, WORD (FAR *TagesSummen)[31], BYTE FAR *MonatsStatus )
    {
    CHAR String[60];
    CHAR Datum[9];
    WORD Counter;
    BYTE StringCounter;
    BYTE LinienZaehler;
    BYTE SpaltenZaehler;

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
    WritePrinter( DATA, "STATISTIK  -  AbwesenheitsÅbersicht" );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( DATA, "===================================" );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    StdStrCpy( Datum, "  .  .  " );
    StdBinToAscii( ConfigData->Perioden[UEBERSICHT].AnfTag, 2, &Datum[0], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[UEBERSICHT].AnfMonat, 2, &Datum[3], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[UEBERSICHT].AnfJahr % 100, 2, &Datum[6], RIGHT, 1 );
    WritePrinter( DATA, Datum );
    WritePrinter( DATA, " - " );

    StdStrCpy( Datum, "  .  .  " );
    StdBinToAscii( ConfigData->Perioden[UEBERSICHT].EndTag, 2, &Datum[0], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[UEBERSICHT].EndMonat, 2, &Datum[3], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[UEBERSICHT].EndJahr % 100, 2, &Datum[6], RIGHT, 1 );
    WritePrinter( DATA, Datum );
    WritePrinter( DATA, " " );

    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    WritePrinter( DATA, PersonenInfo->Name );

    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( STARTUNDERLINE, NULL );
    WritePrinter( DATA, "Beruecksichtigte BegrÅndungen:" );
    WritePrinter( ENDUNDERLINE, NULL );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    for( Counter = 0; Counter < NumBegruendungen; Counter++ )
	if( ConfigData->BegrCheckListe[UEBERSICHT][Counter] )
	    {
	    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
	    WritePrinter( DATA, Begruendungen[Counter].Code );
	    WritePrinter( SETHPOS, (CHAR FAR *)(LEFTINDENT + 8) );
	    WritePrinter( DATA, Begruendungen[Counter].Description );
	    WritePrinter( NEWLINE, NULL );
	    }

    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    for( Counter = 0; Counter < (AnzMonate + MONATEPROZEILE - 1) / MONATEPROZEILE; Counter++ )
	{
	for( LinienZaehler = 0; LinienZaehler - 3 < 31; LinienZaehler++ )
	    {
	    CHAR String[4];

	    if( LinienZaehler >= 3 )
		{
		WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
		StdStrCpy( String, "  ." );
		StdBinToAscii( LinienZaehler - 2, 2, String, RIGHT, 1 );
		WritePrinter( DATA, (CHAR FAR *)String );
		}

	    for( SpaltenZaehler = 0; SpaltenZaehler < MONATEPROZEILE; SpaltenZaehler++ )
		{
		WORD Spaltenoffset;

		if( SpaltenZaehler + (Counter * MONATEPROZEILE) + 1 > AnzMonate )
		    break;

		if( MonatsStatus[SpaltenZaehler + (Counter * MONATEPROZEILE)] != MONATOK )
		    continue;

		Spaltenoffset = LEFTINDENT + 6 + (SPALTENBREITE * SpaltenZaehler);
		WritePrinter( SETHPOS, (VOID FAR *)Spaltenoffset );

		switch( LinienZaehler )
		    {
		    case 0:
			WritePrinter( DATA, StdMonthName( (BYTE)((ConfigData->Perioden[UEBERSICHT].AnfMonat + (SpaltenZaehler + (Counter * MONATEPROZEILE)) % 12)) ) );
			break;

		    case 1:
			WritePrinter( DATA, "------------------" );
			break;

		    case 2:
			break;

		    default:
			{
			CHAR String[20];

			if( LinienZaehler - 2 > StdMonthNumDays( (BYTE)((ConfigData->Perioden[UEBERSICHT].AnfMonat + SpaltenZaehler + (Counter * MONATEPROZEILE)) % 12),
								 (WORD)((ConfigData->Perioden[UEBERSICHT].AnfJahr + ConfigData->Perioden[UEBERSICHT].AnfMonat + SpaltenZaehler + (Counter * MONATEPROZEILE)) / 12)) )
			    continue;

			StringZeitAng( TagesSummen[SpaltenZaehler + (Counter * MONATEPROZEILE)][LinienZaehler - 3], String, TRUE );

			WritePrinter( DATA, (CHAR FAR *)String );
			}
		    }
		}

	    WritePrinter( NEWLINE, NULL );
	    }

	WritePrinter( NEWLINE, NULL );
	}

    ClosePrinter();
    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Ausdruck abgeschlossen.", (MPARAM)"" );

    return( TRUE );
    }


BYTE UebersichtMonatsAuswertung( HWND HWnd, WORD FAR *TagesSummen, DWORD PersonalNr )
    {
    BYTE DataBegrZaehler;
    WORD BegrZaehler;
    BYTE TageZaehler;
    WORD PersonenZaehler;

    WinSendMsg( PersonInfo, WM_SHOW, MONATJAHR, 0 );

    for( PersonenZaehler = 0; PersonenZaehler < DateiKopf->AnzPersonen; PersonenZaehler++ )
	{
	ReadPersonenInfo( PersonenInfo );
	if( PersonenInfo->Personalnummer == PersonalNr )
	    {
	    ReadTage( Tage );

	    for( TageZaehler = 0; TageZaehler <= (BYTE)(StdMonthNumDays( DateiKopf->Monat, DateiKopf->Jahr ) - 1); TageZaehler++ )
		for( DataBegrZaehler = 0; DataBegrZaehler < Tage[TageZaehler].AnzBegruendungen; DataBegrZaehler++ )
		    for( BegrZaehler = 0; BegrZaehler < NumBegruendungen; BegrZaehler++ )
			if( (Tage[TageZaehler].Begruendungen[DataBegrZaehler].Code ==
			    (WORD)StdAsciiToBin( Begruendungen[BegrZaehler].CodeLength,
						 (CHAR FAR *)Begruendungen[BegrZaehler].Code )) &&
			    (ConfigData->BegrCheckListe[UEBERSICHT][BegrZaehler]) )
			    TagesSummen[TageZaehler] += Tage[TageZaehler].Begruendungen[DataBegrZaehler].Dauer;

	    break;
	    }
	}


    return( TRUE );
    }


MSG  UebersichtPersonInfoProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    switch( Msg )
	{
	case WM_CREATE:
	    {
	    WinString( HWnd, "Name:", LEFT, 1, 3 );
	    WinString( HWnd, "Personalnummer:", LEFT, 1, 4 );


	    WinString( HWnd, "Erfasste Monate:", LEFT, 1, 7 );
	    WinString( HWnd, "Durchsch. Personen:", LEFT, 1, 8 );
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

		case MONATE:
		    {
		    CHAR String[4];

		    WinFill( HWnd, SPACECHAR, 45, 7, 47, 7 );
		    StdStrCpy( String, "  0" );
		    StdBinToAscii( (WORD)MP2, 3, (CHAR FAR *)String, RIGHT, 1 );

		    WinString( HWnd, String, RIGHT, 47, 7 );

		    break;
		    }

		}
	    return( WM_PROCESSED );
	}
    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }
