// ****************************
// ***	     Personen	    ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"

extern HWND Bottomline;

extern struct ConfigData FAR *ConfigData;

MSG  PersonenProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  NameProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  PersonalNrProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

MSG  PersonenProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static struct HelpKey HelpKeys[NUMPERSONENHELPKEYS] =
	{ {  0,  0, "</>    Eintrag anw„hlen" },
	  {  0,	 1, "<Leer>   Eintrag ein-/ausschalten" },
	  { 40,  1, "<Esc>    Schalttafel verlassen" } };

    static WORD ConfigInstance;

    static BYTE Selection;

    static HWND SubPanel[NUMPERSONENSUBPANEL];

    switch( Msg )
	{
	case WM_CREATE:
	    ConfigInstance = MP2;
	    WinCreateWindow( HWnd, &SubPanel[0], NameProc, MP2, 0, 10, 3, 41, 3 );
	    WinCreateWindow( HWnd, &SubPanel[1], PersonalNrProc, MP2, 0, 31, 5, 41, 5 );
	    WinCreateWindow( HWnd, &SubPanel[2], CheckListeProc, (MPARAM)ABTEILUNGEN, MP2, 0, 7, 42, 15 );
	    Selection = 0;
	    return( WM_PROCESSED );

	case WM_DESTROY:
	    WinDestroyWindow( SubPanel[0] );
	    WinDestroyWindow( SubPanel[1] );
	    WinDestroyWindow( SubPanel[2] );
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    WinColor( HWnd, PANEL, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    WinColor( HWnd, PANEL, 0, 0, 8, 0 );
	    WinString( HWnd, "Person(en)", LEFT, 1, 0 );
	    WinString( HWnd, "ÍÍÍÍÍÍÍÍÍÍ", LEFT, 1, 1 );

	    WinString( HWnd, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 2) );
	    WinString( HWnd, "Schalttafel zur Auswahl Xxxxxxxxxxxxxxxx", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 1) );
	    WinString( HWnd, "xxxxxxxxxxxxxxxxxxxxxxxx." , LEFT, 1, (BYTE)(WinGety2( HWnd ) - 0) );

	    WinString( HWnd, "Name:", LEFT, 3, 3 );
	    WinString( HWnd, "Personalnummer:", LEFT, 3, 5 );

	    WinSendMsg( SubPanel[0], WM_SHOW, 0, 0 );
	    WinSendMsg( SubPanel[1], WM_SHOW, 0, 0 );
	    WinSendMsg( SubPanel[2], WM_SHOW, 0, 0 );

	    switch( ConfigData->Kriterium[ConfigInstance] )
		{
		case 0:
		    WinCharacter( HWnd, 'þ', 1, 3 );
		    break;

		case 1:
		    WinCharacter( HWnd, 'þ', 1, 5 );
		    break;

		}

	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, 0, 12, 0 );

	    WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMCHECKLSTHELPKEYS );
	    WinSendMsg( SubPanel[Selection], WM_SETFOCUS, 0, 0 );
	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, PANEL, 0, 0, 12, 0 );

	    WinSendMsg( SubPanel[Selection], WM_CLEARFOCUS, 0, 0 );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    if( WinSendMsg( SubPanel[Selection], Msg, MP1, MP2 ) == WM_PROCESSED )
		return( WM_PROCESSED );

	    switch( (WORD)MP1 )
		{
		case KBTAB:
		    WinSendMsg( SubPanel[Selection], WM_CLEARFOCUS, 0, 0 );

		    if( Selection == NUMPERSONENSUBPANEL - 1 )
			Selection = 0;
		    else
			Selection++;

		    WinSendMsg( SubPanel[Selection], WM_SETFOCUS, 0, 0 );
		    return( WM_PROCESSED );

		case KBSHTAB:
		    WinSendMsg( SubPanel[Selection], WM_CLEARFOCUS, 0, 0 );

		    if( Selection == 0 )
			Selection = NUMPERSONENSUBPANEL - 1;
		    else
			Selection--;

		    WinSendMsg( SubPanel[Selection], WM_SETFOCUS, 0, 0 );
		    return( WM_PROCESSED );

		case KBSPACE:
		    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );

		    if( ConfigData->Kriterium[ConfigInstance] == Selection )
			ConfigData->Kriterium[ConfigInstance] = 2;
		    else
			ConfigData->Kriterium[ConfigInstance] = Selection;

		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
		    return( WM_PROCESSED );

		default:
		    return( MP1 );
		}
	    return( WM_PROCESSED );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


MSG  NameProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static CHAR FAR *Name;

    switch( Msg )
	{
	case WM_CREATE:
	    Name = ConfigData->Name[MP1];
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    CHAR String[31];

	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    StdFarStrCpy( String, Name );
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
		case KBENTER:
		    {
		    CHAR String[31];
		    HWND Input;

		    StdFarStrCpy( String, Name );

		    WinCreateWindow( HWnd, &Input, InputProc, (MPARAM)String, 0, 1, 0, 30, 0 );
		    WinSendMsg( Input, WM_INPUT, 0, 0 );
		    WinDestroyWindow( Input );
		    WinHideCursor();

		    StdFarStrCpy( Name, String );
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
	    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );
	    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
	    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
	    return( WM_PROCESSED );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


MSG  PersonalNrProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static CHAR FAR *PersonalNr;

    switch( Msg )
	{
	case WM_CREATE:
	    PersonalNr = ConfigData->PersonalNr[MP1];
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    CHAR String[10];

	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    StdFarStrCpy( String, PersonalNr );
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
		case KBENTER:
		    {
		    CHAR String[10];
		    HWND Input;

		    StdFarStrCpy( String, PersonalNr );

		    WinCreateWindow( HWnd, &Input, InputProc, (MPARAM)String, 9, 1, 0, 9, 0 );
		    WinSendMsg( Input, WM_INPUT, 0, 0 );
		    WinDestroyWindow( Input );
		    WinHideCursor();

		    StdFarStrCpy( PersonalNr, String );
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
	    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );
	    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
	    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
	    return( WM_PROCESSED );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }
