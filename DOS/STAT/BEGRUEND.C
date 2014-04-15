// ****************************
// ***	   Begr］dungen     ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"

extern HWND Bottomline;

MSG  BegruendungenProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );


MSG  BegruendungenProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static struct HelpKey HelpKeys[NUMCHECKLSTHELPKEYS] =
	{ {  0,  0, "</>    Eintrag anw�hlen" },
	  {  0,	 1, "<Leer>   Eintrag ein-/ausschalten" },
	  { 40,  1, "<Esc>    Schalttafel verlassen" } };

    static HWND SubPanel;

    switch( Msg )
	{
	case WM_CREATE:
	    WinCreateWindow( HWnd, &SubPanel, CheckListeProc, (MPARAM)BEGRUENDUNGEN, MP2, 0, 3, 42, 15 );

	    return( WM_PROCESSED );

	case WM_DESTROY:
	    WinDestroyWindow( SubPanel );
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    WinColor( HWnd, PANEL, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    WinColor( HWnd, PANEL, 0, 0, 8, 0 );
	    WinString( HWnd, "Begr］dungen", LEFT, 1, 0 );
	    WinString( HWnd, "ﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍ", LEFT, 1, 1 );

	    WinString( HWnd, "ﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄ", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 2) );
	    WinString( HWnd, "Schalttafel zur Auswahl aller zu ber…k-", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 1) );
	    WinString( HWnd, "sichtigender Begr］dungen." , LEFT, 1, (BYTE)(WinGety2( HWnd ) - 0) );

	    WinSendMsg( SubPanel, WM_SHOW, 0, 0 );

	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, 0, 13, 0 );

	    WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMCHECKLSTHELPKEYS );
	    WinSendMsg( SubPanel, WM_SETFOCUS, 0, 0 );
	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, PANEL, 0, 0, 13, 0 );

	    WinSendMsg( SubPanel, WM_CLEARFOCUS, 0, 0 );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    if( WinSendMsg( SubPanel, Msg, MP1, MP2 ) == WM_PROCESSED )
		return( WM_PROCESSED );

	    switch( (WORD)MP1 )
		{
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
