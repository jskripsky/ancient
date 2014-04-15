// ****************************
// ***	    CheckListe	    ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"

extern HWND Bottomline;

extern struct ConfigData FAR *ConfigData;

extern WORD NumBegruendungen;
extern WORD NumAbteilungen;
extern WORD NumZeitKonti;
extern struct Eintrag FAR *Begruendungen;
extern struct Eintrag FAR *Abteilungen;
extern struct Eintrag FAR *ZeitKonti;


MSG  CheckListeProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  CheckLstArrowsProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );



MSG  CheckListeProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static struct HelpKey HelpKeys[NUMCHECKLSTHELPKEYS] =
	{ {  0,  0, "</>    Wert erh”hen/erniedrigen" },
	  {  0,	 1, "<Tab>    Schaltfeld wechseln" },
	  { 40,  1, "<Esc>    Schalttafel verlassen" } };

    static HWND CheckLstArrows;

    static struct Eintrag FAR *Liste;
    static WORD NumEintraege;

    static BOOL FAR *CheckListe;

    static WORD Selection;
    static WORD TopLine;

    static BYTE Type;


    switch( Msg )
	{
	case WM_CREATE:
	    {
	    WinCreateWindow( HWnd, &CheckLstArrows, CheckLstArrowsProc, 0, 0, -3, -4, -3, 20 );

	    Type = (BYTE)MP1;

	    switch( Type )
		{
		case BEGRUENDUNGEN:
		case PMBEGRUENDUNGEN:
		    Liste = Begruendungen;
		    NumEintraege = NumBegruendungen;

		    CheckListe = ConfigData->BegrCheckListe[MP2];
		    break;

		case ABTEILUNGEN:
		    Liste = Abteilungen;
		    NumEintraege = NumAbteilungen;
		    CheckListe = ConfigData->AbtCheckListe[MP2];
		    break;

		case ZEITKONTI:
		    Liste = ZeitKonti;
		    NumEintraege = NumZeitKonti;
		    CheckListe = ConfigData->ZKontCheckListe[MP2];
		    break;
		}

	    Selection = 0;
	    TopLine = 0;

	    return( WM_PROCESSED );
	    }

	case WM_DESTROY:
	    WinDestroyWindow( CheckLstArrows );
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    CHAR String[31];
	    BYTE LineCounter;

	    WinColor( HWnd, PANEL, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );

	    WinString( HWnd, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ", LEFT, 1, 0 );
	    WinString( HWnd, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ", LEFT, 1, WinGety2( HWnd ) );


	    for( LineCounter = 0; LineCounter <= (BYTE)(WinGety2( HWnd ) - 2); LineCounter++ )
		{
		if( LineCounter + TopLine == NumEintraege )
		    break;

		switch( Type )
		    {
		    case PMBEGRUENDUNGEN:
			switch( CheckListe[LineCounter + TopLine] )
			    {
			    case PLUS:
				WinString( HWnd, "+", LEFT, 1, (BYTE)(LineCounter + 1) );
				break;

			    case MINUS:
				WinString( HWnd, "-", LEFT, 1, (BYTE)(LineCounter + 1) );
				break;
			    }
			break;

		    default:
			if( CheckListe[LineCounter + TopLine] )
			    WinString( HWnd, "ş", LEFT, 1, (BYTE)(LineCounter + 1) );
		    }

		StdFarMemCpy( String, Liste[LineCounter + TopLine].Code, sizeof( Liste[LineCounter + TopLine].Code ) );
		WinString( HWnd, String, LEFT, 3, (BYTE)(LineCounter + 1) );
		StdFarMemCpy( String, Liste[LineCounter + TopLine].Description, sizeof( Liste[LineCounter + TopLine].Description ) );
		WinString( HWnd, String, LEFT, 10, (BYTE)(LineCounter + 1) );
		}

	    return( WM_PROCESSED );
	    }

	case WM_SETFOCUS:
	    WinColor( HWnd, HIGHLIGHT, 0, (BYTE)(Selection - TopLine + 1), WinGetx2( HWnd ), (BYTE)(Selection - TopLine + 1) );
	    return( WM_PROCESSED );

	case WM_CLEARFOCUS:
	    WinColor( HWnd, PANEL, 0, (BYTE)(Selection - TopLine + 1), WinGetx2( HWnd ), (BYTE)(Selection - TopLine + 1) );
	    return( WM_PROCESSED );

	case WM_CHAR:
	    switch( (WORD)MP1 )
		{
		case KBDOWN:
		case KBRIGHT:
		    if( Selection == NumEintraege - 1 )
			break;

		    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );
		    Selection++;

		    if( Selection - TopLine + 1 > (WORD)(WinGety2( HWnd ) - 1) )
			{
			TopLine++;
			WinSendMsg( HWnd, WM_SHOW, 0, 0 );
			}

		    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
		    break;

		case KBUP:
		case KBLEFT:
		    if( Selection == 0)
			break;

		    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );
		    Selection--;

		    if( Selection < TopLine )
			{
			TopLine--;
			WinSendMsg( HWnd, WM_SHOW, 0, 0 );
			}

		    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
		    break;

		case KBHOME:
		    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );

		    TopLine = 0;
		    Selection = 0;

		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
		    break;

		case KBEND:
		    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );

		    Selection = NumEintraege - 1;
		    if( NumEintraege - 1 < (WORD)(WinGety2( HWnd ) - 1) )
			TopLine = 0;
		    else
			TopLine = NumEintraege - (WinGety2( HWnd ) - 1);

		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
		    break;

		case KBSPACE:
		    WinSendMsg( HWnd, WM_CLEARFOCUS, 0, 0 );

		    switch( Type )
			{
			case PMBEGRUENDUNGEN:
			    switch( CheckListe[Selection] )
				{
				case FALSE:
				    CheckListe[Selection] = PLUS;
				    break;
				case PLUS:
				    CheckListe[Selection] = MINUS;
				    break;
				case MINUS:
				    CheckListe[Selection] = FALSE;
				    break;
				}
			    break;

			default:
			    CheckListe[Selection] = (BOOL)(!CheckListe[Selection]);
			}
		    WinSendMsg( HWnd, WM_SHOW, 0, 0 );
		    WinSendMsg( HWnd, WM_SETFOCUS, 0, 0 );
		    break;

		default:
		    return( MP1 );
		}

	    return( WM_PROCESSED );
	}
    }



MSG  CheckLstArrowsProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    return( MP1 );
    }
