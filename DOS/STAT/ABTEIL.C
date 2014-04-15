// ****************************
// ***	   Abteilungen	    ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"

extern HWND Bottomline;

extern struct ConfigData FAR *ConfigData;

extern WORD NumAbteilungen;
extern struct Eintrag FAR *Abteilungen;

MSG  AbteilungenProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  AbtSchluesselProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

VOID AbtFilter( CHAR FAR *Schluessel, WORD PanelNum );


MSG  AbteilungenProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static struct HelpKey HelpKeys[NUMABTCHKLHELPKEYS] =
	{ {  0,  0, "</>    Eintrag anwÑhlen" },
	  {  0,	 1, "<Tab>    Schalttafel wechseln" },
	  { 40,	 0, "<Leer>   Eintrag ein-/ausschalten" },
	  { 40,  1, "<Esc>    Schalttafel verlassen" } };

    static HWND SubPanels[NUMABTSUBPANEL];
    static HWND Selection;

    static WORD PanelNum;

    switch( Msg )
	{
	case WM_CREATE:
	    Selection = 0;

	    PanelNum = MP2;

	    WinCreateWindow( HWnd, &SubPanels[0], CheckListeProc, (MPARAM)ABTEILUNGEN, MP2, 0, 5, 42, 12 );
	    WinCreateWindow( HWnd, &SubPanels[1], AbtSchluesselProc, MP2, SubPanels[0], 13, 3, 19, 3 );
	    return( WM_PROCESSED );

	case WM_DESTROY:
	    WinDestroyWindow( SubPanels[0] );
	    WinDestroyWindow( SubPanels[1] );
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    WinColor( HWnd, PANEL, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    WinColor( HWnd, PANEL, 0, 0, 8, 0 );
	    WinString( HWnd, "Abteilungen", LEFT, 1, 0 );
	    WinString( HWnd, "ÕÕÕÕÕÕÕÕÕÕÕ", LEFT, 1, 1 );

	    WinString( HWnd, "SchlÅssel:", LEFT, 1, 3 );

	    WinString( HWnd, "ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 5) );
	    WinString( HWnd, "Schalttafel zur Auswahl aller zu berÅck-", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 4) );
	    WinString( HWnd, "sichtigender Abteilungen." , LEFT, 1, (BYTE)(WinGety2( HWnd ) - 3) );
	    WinString( HWnd, "Ein Stern '*' im SchlÅssel steht fÅr" , LEFT, 1, (BYTE)(WinGety2( HWnd ) - 1) );
	    WinString( HWnd, "ein beliebiges Zeichen." , LEFT, 1, (BYTE)(WinGety2( HWnd ) - 0) );

	    WinSendMsg( SubPanels[0], WM_SHOW, 0, 0 );
	    WinSendMsg( SubPanels[1], WM_SHOW, 0, 0 );

	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, 0, 12, 0 );

	    WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMCHECKLSTHELPKEYS );

	    WinSendMsg( SubPanels[Selection], WM_SETFOCUS, 0, 0 );
	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, PANEL, 0, 0, 12, 0 );

	    WinSendMsg( SubPanels[Selection], WM_CLEARFOCUS, 0, 0 );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    if( (Selection == 0) && ((WORD)MP1 == KBSPACE) )
		{
		StdFarStrCpy( ConfigData->AbtSchluessel[PanelNum], "-----" );
		WinSendMsg( SubPanels[1], WM_SHOW, 0, 0 );
		}

	    if( WinSendMsg( SubPanels[Selection], Msg, MP1, MP2 ) == WM_PROCESSED )
		return( WM_PROCESSED );

	    switch( (WORD)MP1 )
		{
		case KBTAB:
		    WinSendMsg( SubPanels[Selection], WM_CLEARFOCUS, 0, 0 );

		    if( Selection == NUMABTSUBPANEL - 1 )
			Selection = 0;
		    else
			Selection++;

		    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
		    return( WM_PROCESSED );

		case KBSHTAB:
		    WinSendMsg( SubPanels[Selection], WM_CLEARFOCUS, 0, 0 );

		    if( Selection == 0 )
			Selection = NUMABTSUBPANEL - 1;
		    else
			Selection--;

		    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
		    return( WM_PROCESSED );

		default:
		    return( MP1 );
		}
	    return( WM_PROCESSED );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


MSG  AbtSchluesselProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static struct HelpKey HelpKeys[NUMABTSCHLHELPKEYS] =
	{ {  0,  0, "<Enter>  SchlÅssel Ñndern" },
	  {  0,	 1, "<Tab>    Schalttafel wechseln" },
	  { 40,  1, "<Esc>    Schalttafel verlassen" } };

    static CHAR FAR *Schluessel;
    static WORD PanelNum;
    static HWND CheckListe;

    switch( Msg )
	{
	case WM_CREATE:
	    Schluessel = ConfigData->AbtSchluessel[MP1];
	    PanelNum = MP1;
	    CheckListe = MP2;
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    CHAR String[6];

	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    StdFarStrCpy( String, Schluessel );
	    WinString( HWnd, String, LEFT, 1, 0 );

	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMABTSCHLHELPKEYS );

	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    switch( (WORD)MP1 )
		{
		case KBENTER:
		    {
		    CHAR String[6];
		    HWND Input;

		    StdFarStrCpy( String, Schluessel );

		    WinCreateWindow( HWnd, &Input, InputProc, (MPARAM)String, 0, 1, 0, 5, 0 );
		    WinSendMsg( Input, WM_INPUT, 0, 0 );
		    WinDestroyWindow( Input );
		    WinHideCursor();

		    StdFarStrCpy( Schluessel, String );
		    break;
		    }

		case KBLEFT:
		case KBRIGHT:
		case KBUP:
		case KBDOWN:
		case KBEND:
		case KBHOME:
		    return( WM_PROCESSED );

		default:
		    return( MP1 );
		}

	    AbtFilter( Schluessel, PanelNum );

	    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );
	    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
	    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );

	    WinSendMsg( CheckListe, WM_SHOW, 0, 0 );

	    return( WM_PROCESSED );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


VOID AbtFilter( CHAR FAR *Schluessel, WORD PanelNum )
    {
    WORD Index = 0;
    WORD Counter;
    BYTE StrCounter;
    BOOL Check;

    while( Schluessel[Index] != 0 )
	Index++;

    do
	{
	Schluessel[Index] = 0;
	Index--;
	}
    while( Schluessel[Index] == SPACECHAR );

    StdFarMemSet( ConfigData->AbtCheckListe[PanelNum], FALSE, sizeof( ConfigData->AbtCheckListe[PanelNum] ) );

    for( Counter = 0; Counter < NumAbteilungen; Counter++ )
	{
	Check = TRUE;

	Index = 0;
	while( Schluessel[Index] != 0 )
	    {
	    if( (Schluessel[Index] != '*') &&
		(Schluessel[Index] != Abteilungen[Counter].Code[Index] ) )
		{
		Check = FALSE;
		break;
		}

	    Index++;
	    }

	if( Abteilungen[Counter].Code[Index] != 0 )
	    Check = FALSE;

	if( Check )
	    ConfigData->AbtCheckListe[PanelNum][Counter] = TRUE;
	}
    }
