// ****************************
// ***	  Einstellungen	    ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"

extern HWND Bottomline;

extern struct ConfigData FAR *ConfigData;


MSG  EinstellungenProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

MSG  TMSLaufWerkProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  ArbeitsTagProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  AbtFeldProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  ZeitAngProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

MSG  EinstellungenProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static HWND Selection;

    static HWND SubPanels[NUMEINSTELLSUBPANEL];

    static struct HelpKey HelpKeys[NUMEINSTELLHELPKEYS] =
	{ {  0,  0, "</>    Wert erh”hen/erniedrigen" },
	  {  0,	 1, "<Tab>    Schaltfeld wechseln" },
	  { 40,  1, "<Esc>    Schalttafel verlassen" } };


    switch( Msg )
	{
	case WM_CREATE:
	    {
	    Selection = 0;

	    WinCreateWindow( HWnd, &SubPanels[0], TMSLaufWerkProc, 0, 0, 1, 7, 4, 7 );
	    WinCreateWindow( HWnd, &SubPanels[1], ArbeitsTagProc, 0, 0, 22, 7, 38, 7 );
	    WinCreateWindow( HWnd, &SubPanels[2], AbtFeldProc, 0, 0, 1, 12, 8, 12 );
	    WinCreateWindow( HWnd, &SubPanels[3], ZeitAngProc, 0, 0, 22, 12, 37, 12 );

	    return( WM_PROCESSED );
	    }

	case WM_DESTROY:
	    {
	    BYTE SubPanelCounter;

	    for( SubPanelCounter = 0; SubPanelCounter < NUMEINSTELLSUBPANEL; SubPanelCounter++ )
		WinDestroyWindow( SubPanels[SubPanelCounter] );
	    }

	case WM_SHOW:
	    {
	    BYTE SubPanelCounter;

	    WinColor( HWnd, PANEL, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    WinColor( HWnd, PANEL, 0, 0, 8, 0 );
	    WinString( HWnd, "Einstellungen", LEFT, 1, 0 );
	    WinString( HWnd, "ÍÍÍÍÍÍÍÍÍÍÍÍÍ", LEFT, 1, 1 );

	    WinString( HWnd, "TMS Laufwerk:", LEFT, 1, 5 );
	    WinString( HWnd, "ÄÄÄÄÄÄÄÄÄÄÄÄÄ", LEFT, 1, 6 );
	    WinString( HWnd, "L„nge des Arbeitstages:", LEFT, 22, 5 );
	    WinString( HWnd, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ", LEFT, 22, 6 );
	    WinString( HWnd, "Feld fr Abt.codes:", LEFT, 1, 10 );
	    WinString( HWnd, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ", LEFT, 1, 11 );
	    WinString( HWnd, "Zeitangaben:", LEFT, 22, 10 );
	    WinString( HWnd, "ÄÄÄÄÄÄÄÄÄÄÄÄ", LEFT, 22, 11 );


	    for( SubPanelCounter = 0; SubPanelCounter < NUMEINSTELLSUBPANEL; SubPanelCounter++ )
		WinSendMsg( SubPanels[SubPanelCounter], WM_SHOW, 0, 0 );

	    WinString( HWnd, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 4) );
	    WinString( HWnd, "Auf dieser Schalttafel k”nnen Sie bestimmen,", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 3) );
	    WinString( HWnd, "auf welchem Laufwerk sich TMS befindet und", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 2) );
	    WinString( HWnd, "die L„nge eines Arbeitstages in Stunden und", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 1) );
	    WinString( HWnd, "Minuten einstellen.", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 0) );

	    return( WM_PROCESSED );
	    }
	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, 0, 14, 0 );

	    WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMPERIODEHELPKEYS );

	    WinSendMsg( SubPanels[Selection], WM_SETFOCUS, 0, 0 );
	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, PANEL, 0, 0, 14, 0 );

	    WinSendMsg( SubPanels[Selection], WM_CLEARFOCUS, 0, 0 );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    if( WinSendMsg( SubPanels[Selection], Msg, MP1, MP2 ) == WM_PROCESSED )
		return( WM_PROCESSED );

	    switch( (WORD)MP1 )
		{
		case KBTAB:
		    WinSendMsg( SubPanels[Selection], WM_CLEARFOCUS, 0, 0 );

		    if( Selection == NUMEINSTELLSUBPANEL - 1 )
			Selection = 0;
		    else
			Selection++;

		    WinSendMsg( SubPanels[Selection], WM_SETFOCUS, 0, 0 );
		    return( WM_PROCESSED );

		case KBSHTAB:
		    WinSendMsg( SubPanels[Selection], WM_CLEARFOCUS, 0, 0 );

		    if( Selection == 0 )
			Selection = NUMEINSTELLSUBPANEL - 1;
		    else
			Selection--;

		    WinSendMsg( SubPanels[Selection], WM_SETFOCUS, 0, 0 );
		    return( WM_PROCESSED );

		case KBUP:
		case KBLEFT:
		case KBDOWN:
		case KBRIGHT:
		    return( WM_PROCESSED );

		default:
		    return( MP1 );
		}

	}
    }


MSG  TMSLaufWerkProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
	switch( Msg )
	{
	case WM_CREATE:
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    CHAR String[3];

	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    strcpy( String, " :" );
	    String[0] = ConfigData->TMSLaufWerk;
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
		    if( ConfigData->TMSLaufWerk < LASTDRIVE )
			ConfigData->TMSLaufWerk++;
		    break;

		case KBDOWN:
		case KBLEFT:
		    if( ConfigData->TMSLaufWerk > FIRSTDRIVE )
			ConfigData->TMSLaufWerk--;

		    break;

		case KBEND:
		    ConfigData->TMSLaufWerk = LASTDRIVE;
		    break;

		case KBHOME:
		    ConfigData->TMSLaufWerk = FIRSTDRIVE;
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


MSG  ArbeitsTagProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
	switch( Msg )
	{
	case WM_CREATE:
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    CHAR String[16];

	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    strcpy( String, "   Std.    Min." );
	    StdBinToAscii( ConfigData->ArbeitsTag / 60, 2, (CHAR FAR *)&String[0], RIGHT, 1 );
	    StdBinToAscii( ConfigData->ArbeitsTag % 60, 2, (CHAR FAR *)&String[8], RIGHT, 1 );

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
		    if( ConfigData->ArbeitsTag < 12 * 60 )
			ConfigData->ArbeitsTag++;

		    break;

		case KBDOWN:
		case KBLEFT:

		    if( ConfigData->ArbeitsTag > 1 )
			ConfigData->ArbeitsTag--;

		    break;

		case KBPGUP:
		    if( ConfigData->ArbeitsTag <= 11 * 60 )
			ConfigData->ArbeitsTag += 60;

		    break;

		case KBPGDOWN:
		    if( ConfigData->ArbeitsTag >= 61 )
			ConfigData->ArbeitsTag -= 60;

		    break;

		case KBEND:
		    ConfigData->ArbeitsTag = 12 * 60;
		    break;

		case KBHOME:
		    ConfigData->ArbeitsTag = 1;
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


MSG  AbtFeldProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
	switch( Msg )
	{
	case WM_CREATE:
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    CHAR String[2];

	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinString( HWnd, "Feld", LEFT, 1, 0 );
	    strcpy( String, " " );
	    String[0] = (CHAR)(ConfigData->AbtFeldNr + '0');
	    WinString( HWnd, String, LEFT, 6, 0 );

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
		    if( ConfigData->AbtFeldNr < 7 )
			ConfigData->AbtFeldNr++;
		    break;

		case KBDOWN:
		case KBLEFT:
		    if( ConfigData->AbtFeldNr > 1 )
			ConfigData->AbtFeldNr--;

		    break;

		case KBEND:
		    ConfigData->AbtFeldNr = 7;
		    break;

		case KBHOME:
		    ConfigData->AbtFeldNr = 1;
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


MSG  ZeitAngProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
	switch( Msg )
	{
	case WM_CREATE:
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    CHAR String[2];

	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    switch( ConfigData->ZeitAngModus )
		{
		case STDMIN:
		    WinString( HWnd, "xx Std. xx Min", LEFT, 1, 0 );
		    break;

		case STDCENTISTD:
		    WinString( HWnd, "xxxx.xx Std.", LEFT, 1, 0 );
		    break;
		}

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
		case KBDOWN:
		case KBLEFT:
		case KBSPACE:
		    switch( ConfigData->ZeitAngModus )
			{
			case STDMIN:
			    ConfigData->ZeitAngModus = STDCENTISTD;
			    break;

			case STDCENTISTD:
			    ConfigData->ZeitAngModus = STDMIN;
			    break;
			}
		    break;

		case KBHOME:
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
