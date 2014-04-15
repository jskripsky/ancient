// ****************************
// ***	      Periode	    ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"

#define WM_CHECKDATA 2001

extern HWND Bottomline;

MSG  TagProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  MonatProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  JahrProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );


static BYTE Instance;


MSG  PeriodeProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static struct Periode FAR *Periode;
    static BYTE Selection;

    static HWND SubPanels[NUMPERIODESUBPANEL];

    static struct HelpKey HelpKeys[NUMPERIODEHELPKEYS] =
	{ {  0,  0, "</>    Wert erh”hen/erniedrigen" },
	  {  0,	 1, "<Tab>    Schaltfeld wechseln" },
	  { 40,  1, "<Esc>    Schalttafel verlassen" } };


    switch( Msg )
	{
	case WM_CREATE:
	    {
	    Periode = POINTER( MP1, MP2 );

	    Instance = 0;
	    WinCreateWindow( HWnd, &SubPanels[0], TagProc, SEG( &(Periode->AnfTag) ), OFS( &(Periode->AnfTag) ), 10, 5, 14, 5 );
	    WinCreateWindow( HWnd, &SubPanels[1], MonatProc, SEG( &(Periode->AnfMonat) ), OFS( &(Periode->AnfMonat) ), 16, 5, 26, 5 );
	    WinCreateWindow( HWnd, &SubPanels[2], JahrProc, SEG( &(Periode->AnfJahr) ), OFS( &(Periode->AnfJahr) ), 28, 5, 33, 5 );
	    Instance = 1;
	    WinCreateWindow( HWnd, &SubPanels[3], TagProc, SEG( &(Periode->EndTag) ), OFS( &(Periode->EndTag) ), 10, 7, 14, 7 );
	    WinCreateWindow( HWnd, &SubPanels[4], MonatProc, SEG( &(Periode->EndMonat) ), OFS( &(Periode->EndMonat) ), 16, 7, 26, 7 );
	    WinCreateWindow( HWnd, &SubPanels[5], JahrProc, SEG( &(Periode->EndJahr) ), OFS( &(Periode->EndJahr) ), 28, 7, 33, 7 );

	    Selection = 0;
	    Instance = 0;

	    return( WM_PROCESSED );
	    }

	case WM_DESTROY:
	    {
	    BYTE SubPanelCounter;

	    for( SubPanelCounter = 0; SubPanelCounter < NUMPERIODESUBPANEL; SubPanelCounter++ )
		{
		Instance = (BYTE)(SubPanelCounter / 3);
		WinDestroyWindow( SubPanels[SubPanelCounter] );
		}
	    }

	case WM_SHOW:
	    {
	    BYTE SubPanelCounter;
	    BYTE InstanceStack;

	    InstanceStack = Instance;

	    WinColor( HWnd, PANEL, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    WinString( HWnd, "Periode", LEFT, 1, 0 );
	    WinString( HWnd, "ÍÍÍÍÍÍÍ", LEFT, 1, 1 );

	    WinString( HWnd, "Anfang", LEFT, 1, 5 );
	    WinString( HWnd, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ", LEFT, 1, 6 );
	    WinString( HWnd, "Ende", LEFT, 1, 7 );

	    for( SubPanelCounter = 0; SubPanelCounter < NUMPERIODESUBPANEL; SubPanelCounter++ )
		{
		Instance = (BYTE)(SubPanelCounter / 3);
		WinSendMsg( SubPanels[SubPanelCounter], WM_SHOW, 0, 0 );
		}

	    Instance = InstanceStack;


	    WinString( HWnd, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 2) );
	    WinString( HWnd, "W„hlen Sie mit Hilfe dieser Schalttafel das", LEFT, 1, (BYTE)(WinGety2( HWnd ) - 1) );
	    WinString( HWnd, "Start- und Enddatum der jeweiligen Statistik." , LEFT, 1, (BYTE)(WinGety2( HWnd ) - 0) );

	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, 0, 8, 0 );

	    WinSendMsg( Bottomline, WM_HELP, (WORD)&HelpKeys, NUMPERIODEHELPKEYS );

	    WinSendMsg( SubPanels[Selection], WM_SETFOCUS, 0, 0 );
	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, PANEL, 0, 0, 8, 0 );

	    WinSendMsg( SubPanels[Selection], WM_CLEARFOCUS, 0, 0 );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    if( WinSendMsg( SubPanels[Selection], Msg, MP1, MP2 ) == WM_PROCESSED )
		{
		Instance = (BYTE)(Selection / 3);

		WinSendMsg( SubPanels[(Selection < 3 ? 0 : 3 )], WM_CHECKDATA, (MPARAM)(Selection < 3 ? Periode->AnfMonat : Periode->EndMonat), (MPARAM)(Selection < 3 ? Periode->AnfJahr : Periode->EndJahr) );
		WinSendMsg( SubPanels[Selection], WM_SETFOCUS, 0, 0 );
		return( WM_PROCESSED );
		}

	    switch( (WORD)MP1 )
		{
		case KBTAB:
		    WinSendMsg( SubPanels[Selection], WM_CLEARFOCUS, 0, 0 );

		    if( Selection == NUMPERIODESUBPANEL - 1 )
			Selection = 0;
		    else
			Selection++;

		    Instance = (BYTE)(Selection / 3);

		    WinSendMsg( SubPanels[Selection], WM_SETFOCUS, 0, 0 );
		    return( WM_PROCESSED );

		case KBSHTAB:
		    WinSendMsg( SubPanels[Selection], WM_CLEARFOCUS, 0, 0 );

		    if( Selection == 0 )
			Selection = NUMPERIODESUBPANEL - 1;
		    else
			Selection--;

		    Instance = (BYTE)(Selection / 3);

		    WinSendMsg( SubPanels[Selection], WM_SETFOCUS, 0, 0 );
		    return( WM_PROCESSED );

		case KBESC:
		case KBENTER:
		    if( Periode->AnfJahr < Periode->EndJahr )
			    return( MP1 );

		    if( Periode->AnfJahr > Periode->EndJahr )
			return( WM_PROCESSED );
		    else
			{
			if( Periode->AnfMonat < Periode->EndMonat )
			    return( MP1 );

			if( Periode->AnfMonat > Periode->EndMonat )
			    return( WM_PROCESSED );
			else
			    if( Periode->AnfTag <= Periode->EndTag )
				return( MP1 );
			    else
				return( WM_PROCESSED );
			}

		default:
		    return( MP1 );
		}
	    return( WM_PROCESSED );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


MSG  TagProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static BYTE FAR *Tag[2];

    switch( Msg )
	{
	case WM_CREATE:
	    Tag[Instance] = POINTER( MP1, MP2 );
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    CHAR String[4];

	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    strcpy( String, "  ." );
	    StdBinToAscii( (*Tag)[Instance], 2, (CHAR FAR *)String, RIGHT, 0 );
	    WinString( HWnd, String, LEFT, 1, 0 );

	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    return( WM_PROCESSED );

	case WM_CHECKDATA:
	    if( (*Tag)[Instance] > StdMonthNumDays( (BYTE)MP1, (WORD)MP2 ) )
		(*Tag)[Instance] = StdMonthNumDays( (BYTE)MP1, (WORD)MP2 );

	    WinSendMsg( HWnd, WM_SHOW, 0, 0 );

	    return( WM_PROCESSED );

	case WM_CHAR:
	    switch( (WORD)MP1 )
		{
		case KBUP:
		case KBRIGHT:
		    (*Tag)[Instance]++;
		    return( WM_PROCESSED );

		case KBDOWN:
		case KBLEFT:
		    if( (*Tag)[Instance] > 1 )
			(*Tag)[Instance]--;
		    return( WM_PROCESSED );

		case KBHOME:
		    (*Tag)[Instance] = 1;
		    return( WM_PROCESSED );

		case KBEND:
		    (*Tag)[Instance] = 31;
		    return( WM_PROCESSED );

		default:
		    return( MP1 );
		}
	    return( WM_PROCESSED );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }



MSG  MonatProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static BYTE FAR *(Monat[2]);

    switch( Msg )
	{
	case WM_CREATE:
	    Monat[Instance] = POINTER( MP1, MP2 );
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    CHAR String[10];

	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, ' ', 1, 0, 9, 0 );

	    strcpy( String, StdMonthName( (*Monat)[Instance] ) );
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
		    if( (*Monat)[Instance] < 12 )
			(*Monat)[Instance]++;

		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    return( WM_PROCESSED );

		case KBDOWN:
		case KBLEFT:
		    if( (*Monat)[Instance] > 1 )
			(*Monat)[Instance]--;
		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    return( WM_PROCESSED );

		case KBHOME:
		    (*Monat)[Instance] = 1;
		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    return( WM_PROCESSED );

		case KBEND:
		    (*Monat)[Instance] = 12;
		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    return( WM_PROCESSED );

		default:
		    return( MP1 );
		}
	    return( WM_PROCESSED );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


MSG  JahrProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static WORD FAR *(Jahr[2]);

    switch( Msg )
	{
	case WM_CREATE:
	    Jahr[Instance] = POINTER( MP1, MP2 );
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    static CHAR String[5];

	    WinColor( HWnd, MARK, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    strcpy( String, "    " );
	    StdBinToAscii( (*Jahr)[Instance], 4, (CHAR FAR *)String, RIGHT, 0 );
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
		    if( (*Jahr)[Instance] < 2049 )
			(*Jahr)[Instance]++;

		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    return( WM_PROCESSED );

		case KBDOWN:
		case KBLEFT:
		    if( (*Jahr)[Instance] > 1950 )
			(*Jahr)[Instance]--;
		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    return( WM_PROCESSED );

		case KBHOME:
		    (*Jahr)[Instance] = 1950;
		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    return( WM_PROCESSED );

		case KBEND:
		    (*Jahr)[Instance] = 2049;
		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    return( WM_PROCESSED );

		default:
		    return( MP1 );
		}
	    return( WM_PROCESSED );
	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }
