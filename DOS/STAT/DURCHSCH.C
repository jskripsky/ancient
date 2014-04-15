// ****************************
// ***	   Durchschnitt     ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"


MSG  DurchschnittProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
BYTE Durchschnitt( HWND HWnd );
BYTE DurchschnittDruck( DWORD FAR *Total, DWORD FAR *Durchschnitt );
BYTE DurchschnittMonatsAuswertung( HWND HWnd, DWORD FAR *Zaehler, WORD *Personen, BYTE Beginn, BYTE Ende, BYTE BeginnProzent, BYTE EndeProzent );

MSG  DurchschnittPersonInfoProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

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



MSG  DurchschnittProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static struct HelpKey HelpKeys[NUMDURCHSCHHELPKEYS] =
	{ {  0,  0, "<Enter>  Statistik generieren" },
	  { 40,  0, "<Esc>    Schalttafel verlassen" } };

    switch( Msg )
	{
	case WM_SHOW:
	    {
	    WinColor( HWnd, PANEL, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    WinString( HWnd, "Durchschnittsstatistik", LEFT, 1, 0 );
	    WinString( HWnd, "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ", LEFT, 1, 1 );

	    WinString( HWnd, "ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿", LEFT, 1,  4 );
	    WinString( HWnd, "³                                        ³", LEFT, 1,  5 );
	    WinString( HWnd, "³  Code  Beschreibung      Tage/Mitarb.  ³", LEFT, 1,  6 );
	    WinString( HWnd, "³  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  ³", LEFT, 1,  7 );
	    WinString( HWnd, "³  001   Gesch„ftl. Abw.          7.54   ³", LEFT, 1,  8 );
	    WinString( HWnd, "³  010   Ferien                   0.30   ³", LEFT, 1,  9 );
	    WinString( HWnd, "³  011   Dienstjubil„um           2.19   ³", LEFT, 1, 10 );
	    WinString( HWnd, "³   .          .                   .     ³", LEFT, 1, 11 );
	    WinString( HWnd, "³   .          .                   .     ³", LEFT, 1, 12 );
	    WinString( HWnd, "³                                        ³", LEFT, 1, 13 );
	    WinString( HWnd, "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ", LEFT, 1, 14 );

	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, 0, 23, 0 );

	    WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMDURCHSCHHELPKEYS );
	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, PANEL, 0, 0, 23, 0 );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    switch( (WORD)MP1 )
		{
		    case KBENTER:
			WinFill( HWnd, SPACECHAR, 0, 2, WinGetx2( HWnd ), WinGety2( HWnd ) );
			Durchschnitt( HWnd );
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


BYTE Durchschnitt( HWND HWnd )
    {
    DWORD FAR *Zaehler;
    DWORD FAR *Durchschnitt;

    WORD Personen;
    WORD PersonenTotal;

    BYTE AnzMonate;
    BYTE EffMonate;
    BYTE MonatsZaehler;

    WORD Counter;

    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Daten werden ausgewertet...", (MPARAM)"" );

    DateiKopf = DosAllocFarMem( sizeof( *DateiKopf ) );
    PersonenInfo = DosAllocFarMem( sizeof( *PersonenInfo ) );
    Tage = DosAllocFarMem( sizeof( *Tage ) * 31 );

    Zaehler = DosAllocFarMem( sizeof( Zaehler ) * NumBegruendungen );
    Durchschnitt = DosAllocFarMem( sizeof( Durchschnitt ) * NumBegruendungen );
    StdFarMemSet( Zaehler, 0, sizeof( Zaehler ) * NumBegruendungen );

    PersonenTotal = 0;

    EffMonate = 0;
    AnzMonate = (BYTE)(( ConfigData->Perioden[DURCHSCHNITT].EndJahr
			 - ConfigData->Perioden[DURCHSCHNITT].AnfJahr
			 + 1 ) * 12
		     - ( ConfigData->Perioden[DURCHSCHNITT].AnfMonat - 1 )
		     - ( 12 - ConfigData->Perioden[DURCHSCHNITT].EndMonat ));


    WinCreateWindow( HWnd, &PersonInfo, DurchschnittPersonInfoProc, 0, 0, 0, 5, 47, 15 );
    WinCreateWindow( HWnd, &Progressbar, ProgressbarProc, 0, 0, 1, 17, 47, 19 );

    if( AnzMonate == 1 )
	{
	if( OpenDataFile( DateiKopf,
		(WORD)ConfigData->Perioden[DURCHSCHNITT].AnfJahr,
		(BYTE)ConfigData->Perioden[DURCHSCHNITT].AnfMonat ) == OK )
	    {
	    DurchschnittMonatsAuswertung( HWnd, Zaehler, &Personen,
			      ConfigData->Perioden[DURCHSCHNITT].AnfTag,
			      ConfigData->Perioden[DURCHSCHNITT].EndTag,
			      0, 100 );

	    PersonenTotal += Personen;
	    DeleteDataFile();
	    EffMonate++;
	    }
	}
    else
	for( MonatsZaehler = 0; MonatsZaehler < AnzMonate; MonatsZaehler++ )
	    {
	    WinSendMsg( PersonInfo, WM_SHOW, MONATE, (MPARAM)EffMonate );

	    if( EffMonate > 0 )
		WinSendMsg( PersonInfo, WM_SHOW, ANZPERSONEN, (MPARAM)StdDivide( PersonenTotal, EffMonate ) );

	    if( OpenDataFile( DateiKopf,
		(WORD)(ConfigData->Perioden[DURCHSCHNITT].AnfJahr + (ConfigData->Perioden[DURCHSCHNITT].AnfMonat + MonatsZaehler - 1) / 12),
		(BYTE)((ConfigData->Perioden[DURCHSCHNITT].AnfMonat + MonatsZaehler) % 12) ) != OK )
		continue;
	    else
		EffMonate++;

	    if( MonatsZaehler == 0 && ConfigData->Perioden[DURCHSCHNITT].AnfTag > 1 )
		{
		DurchschnittMonatsAuswertung( HWnd, Zaehler, &Personen,
				  (BYTE)ConfigData->Perioden[DURCHSCHNITT].AnfTag,
				  0,
				  (BYTE)StdDivide( (MonatsZaehler) * 100, AnzMonate ),
				  (BYTE)StdDivide( (MonatsZaehler + 1) * 100, AnzMonate ) );
		PersonenTotal += Personen;
		DeleteDataFile();
		continue;
		}

	    if( (MonatsZaehler == (BYTE)(AnzMonate - 1)) && (ConfigData->Perioden[DURCHSCHNITT].EndTag < StdMonthNumDays( ConfigData->Perioden[DURCHSCHNITT].EndMonat, ConfigData->Perioden[DURCHSCHNITT].EndJahr )) )
		{
		DurchschnittMonatsAuswertung( HWnd, Zaehler, &Personen,
				  0,
				  (BYTE)ConfigData->Perioden[DURCHSCHNITT].EndTag,
				  (BYTE)StdDivide( (MonatsZaehler) * 100, AnzMonate ),
				  (BYTE)StdDivide( (MonatsZaehler + 1) * 100, AnzMonate ) );
		PersonenTotal += Personen;
		DeleteDataFile();
		continue;
		}

	    DurchschnittMonatsAuswertung( HWnd, Zaehler, &Personen,
			      0, 0,
			      (BYTE)StdDivide( (MonatsZaehler) * 100, AnzMonate ),
			      (BYTE)StdDivide( (MonatsZaehler + 1) * 100, AnzMonate ) );
	    PersonenTotal += Personen;
	    DeleteDataFile();
	    }

    WinSendMsg( Progressbar, WM_SHOW, 100, 0 );

    if( (EffMonate > 0) && (PersonenTotal > 0) )
	{
	WinSendMsg( PersonInfo, WM_SHOW, MONATE, (MPARAM)EffMonate );

	PersonenTotal = StdDivide( PersonenTotal, EffMonate );
	WinSendMsg( PersonInfo, WM_SHOW, ANZPERSONEN, (MPARAM)PersonenTotal );

	if( PersonenTotal > 0 )
	    for( Counter = 0; Counter < NumBegruendungen; Counter++ )
		Durchschnitt[Counter] = StdDivide( Zaehler[Counter], PersonenTotal );
	else
	    for( Counter = 0; Counter < NumBegruendungen; Counter++ )
		Durchschnitt[Counter] = 0;

	WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Auswertung abgeschlossen.", (MPARAM)"<Enter> Drucken  -  <Esc> Abbrechen" );

	if( BiosGetKey() == KBENTER )
	    DurchschnittDruck( Zaehler, Durchschnitt );
	else
	    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Ausdruck wurde abgebrochen.", (MPARAM)"" );
	}
    else
	{
	if( EffMonate == 0 )
	    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Kein Monat der Periode ist vorhanden!", (MPARAM)"" );
	else
	    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Es wurden keine Personen gefunden!", (MPARAM)"" );
	}

    WinDestroyWindow( Progressbar );
    WinDestroyWindow( PersonInfo );

    DosFreeFarMem( Zaehler );
    DosFreeFarMem( Durchschnitt );

    DosFreeFarMem( Tage );
    DosFreeFarMem( PersonenInfo );
    DosFreeFarMem( DateiKopf );
    return( TRUE );
    }


BYTE DurchschnittDruck( DWORD FAR *Total, DWORD FAR *Durchschnitt )
    {
    CHAR String[40];
    BYTE StringCounter;
    CHAR Datum[9];
    WORD Counter;

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
    WritePrinter( DATA, "STATISTIK  -  Abwesenheiten nach Begrndung" );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( DATA, "===========================================" );
    WritePrinter( NEWLINE, NULL );
    WritePrinter( NEWLINE, NULL );

    StdStrCpy( Datum, "  .  .  " );
    StdBinToAscii( ConfigData->Perioden[DURCHSCHNITT].AnfTag, 2, &Datum[0], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[DURCHSCHNITT].AnfMonat, 2, &Datum[3], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[DURCHSCHNITT].AnfJahr % 100, 2, &Datum[6], RIGHT, 1 );
    WritePrinter( DATA, Datum );
    WritePrinter( DATA, " - " );

    StdStrCpy( Datum, "  .  .  " );
    StdBinToAscii( ConfigData->Perioden[DURCHSCHNITT].EndTag, 2, &Datum[0], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[DURCHSCHNITT].EndMonat, 2, &Datum[3], RIGHT, 1 );
    StdBinToAscii( ConfigData->Perioden[DURCHSCHNITT].EndJahr % 100, 2, &Datum[6], RIGHT, 1 );
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
	if( ConfigData->AbtCheckListe[DURCHSCHNITT][Counter] )
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
    WritePrinter( DATA, "Code  Beschreibung                               Tage Total        Tage/Mitarb." );
    WritePrinter( NEWLINE, NULL );

    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
    WritePrinter( DATA, "-------------------------------------------------------------------------------" );
    WritePrinter( NEWLINE, NULL );

    for( Counter = 0; Counter < NumBegruendungen; Counter++ )
	if( ConfigData->BegrCheckListe[DURCHSCHNITT][Counter] )
	    {
	    CHAR String[10];
	    WritePrinter( SETHPOS, (CHAR FAR *)LEFTINDENT );
	    WritePrinter( DATA, Begruendungen[Counter].Code );
	    WritePrinter( SETHPOS, (CHAR FAR *)(LEFTINDENT + 6) );
	    WritePrinter( DATA, Begruendungen[Counter].Description );

	    WritePrinter( SETHPOS, (CHAR FAR *)(LEFTINDENT + 50) );
	    StdStrCpy( String, "     0.00" );
	    StdBinToAscii( StdDivide( (DWORD)Total[Counter] * 100, ConfigData->ArbeitsTag ) / 100, 6, &String[0], RIGHT, 1 );
	    StdBinToAscii( StdDivide( (DWORD)Total[Counter] * 100, ConfigData->ArbeitsTag ) % 100, 2, &String[7], RIGHT, 2 );
	    WritePrinter( DATA, String );

	    WritePrinter( SETHPOS, (CHAR FAR *)(LEFTINDENT + 70) );
	    StdStrCpy( String, "     0.00" );
	    StdBinToAscii( StdDivide( (DWORD)Durchschnitt[Counter] * 100, ConfigData->ArbeitsTag ) / 100, 6, &String[0], RIGHT, 1 );
	    StdBinToAscii( StdDivide( (DWORD)Durchschnitt[Counter] * 100, ConfigData->ArbeitsTag ) % 100, 2, &String[7], RIGHT, 2 );
	    WritePrinter( DATA, String );

	    WritePrinter( NEWLINE, NULL );
	    }

    ClosePrinter();
    WinSendMsg( Bottomline, WM_MESSAGE, (MPARAM)"Ausdruck abgeschlossen.", (MPARAM)"" );

    return( TRUE );
    }


BYTE DurchschnittMonatsAuswertung( HWND HWnd, DWORD FAR *Zaehler, WORD *Personen, BYTE Beginn, BYTE Ende, BYTE BeginnProzent, BYTE EndeProzent )
    {
    WORD AbtZaehler;
    BYTE DataBegrZaehler;
    WORD BegrZaehler;
    BYTE TageZaehler;
    WORD PersonenZaehler;
    BOOL CheckedAbt;

    WinSendMsg( PersonInfo, WM_SHOW, MONATJAHR, 0 );

    (*Personen) = 0;

    if( Beginn == 0 )
	Beginn = 1;

    if( Ende == 0 )
	Ende = StdMonthNumDays( DateiKopf->Monat, DateiKopf->Jahr );

    for( PersonenZaehler = 0; PersonenZaehler < DateiKopf->AnzPersonen; PersonenZaehler++ )
	{
	if( !(BeginnProzent == 0 && EndeProzent == 0) )
	    WinSendMsg( Progressbar, WM_SHOW,
			(MPARAM)(BeginnProzent + StdDivide( (DWORD)PersonenZaehler * ((DWORD)EndeProzent - (DWORD)BeginnProzent), DateiKopf->AnzPersonen )), 0 );

	CheckedAbt = FALSE;
	ReadPersonenInfo( PersonenInfo );

	WinSendMsg( PersonInfo, WM_SHOW, PERSON, 0 );

	for( AbtZaehler = 0; AbtZaehler < NumAbteilungen; AbtZaehler++ )
	    if( ConfigData->AbtCheckListe[DURCHSCHNITT][AbtZaehler] )
		if( StdFarStrCmp( Abteilungen[AbtZaehler].Code, PersonenInfo->Felder[ConfigData->AbtFeldNr - 1].Feld ) == 0 )
		    {
		    CheckedAbt = TRUE;
		    break;
		    }

	if( !CheckedAbt )
	    continue;

	ReadTage( Tage );

	for( TageZaehler = (BYTE)(Beginn - 1); TageZaehler <= (BYTE)(Ende - 1); TageZaehler++ )
	    for( DataBegrZaehler = 0; DataBegrZaehler < Tage[TageZaehler].AnzBegruendungen; DataBegrZaehler++ )
		for( BegrZaehler = 0; BegrZaehler < NumBegruendungen; BegrZaehler++ )
		    if( Tage[TageZaehler].Begruendungen[DataBegrZaehler].Code ==
			(WORD)StdAsciiToBin( Begruendungen[BegrZaehler].CodeLength,
					     (CHAR FAR *)Begruendungen[BegrZaehler].Code ) )
			{
			Zaehler[BegrZaehler] += Tage[TageZaehler].Begruendungen[DataBegrZaehler].Dauer;
			break;
			}

	(*Personen)++;
	}

    if( !(BeginnProzent == 0 && EndeProzent == 0) )
	WinSendMsg( Progressbar, WM_SHOW,
	    (MPARAM)(BeginnProzent + StdDivide( (DWORD)PersonenZaehler * ((DWORD)EndeProzent - (DWORD)BeginnProzent), DateiKopf->AnzPersonen )), 0 );

    (*Personen) *= (Ende - Beginn + 1);
    (*Personen) = StdDivide( (*Personen), StdMonthNumDays( DateiKopf->Monat, DateiKopf->Jahr ) );

    return( TRUE );
    }


MSG  DurchschnittPersonInfoProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
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
		    WinFill( HWnd, 'Ä', 1, 1, (BYTE)StdStrLen( MonatJahr ), 1 );
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

		case ANZPERSONEN:
		    {
		    CHAR String[6];

		    WinFill( HWnd, SPACECHAR, 43, 8, 47, 8 );
		    StdStrCpy( String, "    0" );
		    StdBinToAscii( (WORD)MP2, 5, (CHAR FAR *)String, RIGHT, 1 );

		    WinString( HWnd, String, RIGHT, 47, 8 );

		    break;
		    }
		}
	    return( WM_PROCESSED );
	}
    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }
