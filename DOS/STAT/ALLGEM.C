// ****************************
// ***	   Allgemeines	    ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"


MSG  ProgressbarProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  InputProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

BOOL PersonInAbtListe( BOOL FAR *AbtCheckListe, struct PersonenInfo FAR *PersonenInfo );
VOID StringZeitAng( SDWORD Zeit, CHAR FAR *String, BOOL Null );

extern struct ConfigData FAR *ConfigData;

extern WORD NumAbteilungen;
extern struct Eintrag FAR *Abteilungen;



MSG  ProgressbarProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    switch( Msg )
	{
	case WM_CREATE:
	    WinFill( HWnd, 'Ä', 0, 0, WinGetx2( HWnd ), 0 );
	    WinFill( HWnd, 'Ä', 0, 2, WinGetx2( HWnd ), 2 );
	    return( WM_PROCESSED );

	case WM_SHOW:
	    {
	    CHAR String[5];

	    StdStrCpy( String, "  0%" );
	    StdBinToAscii( (BYTE)MP1, 3, (CHAR FAR *)String, RIGHT, 1 );
	    WinString( HWnd, String, CENTER, 0, 1 );

	    if( (BYTE)StdDivide( (BYTE)MP1 * (WinGetx2( HWnd ) + 1), 100 ) > 0 )
		WinColor( HWnd, PROGRESSBAR, 0, 1, (BYTE)(StdDivide( (BYTE)MP1 * (WinGetx2( HWnd ) + 1), 100 ) - 1), 1 );

	    return( WM_PROCESSED );
	    }

	case WM_DESTROY:
	    WinColor( HWnd, NORMAL, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
	    return( WM_PROCESSED );

	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


MSG  InputProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    static CHAR *String;
    static BYTE MaxLength;
    static BYTE MinLength;

    switch( Msg )
	{
	case WM_CREATE:
	    WinSetCursorPos( HWnd, 0, 0 );
	    String = (CHAR *)MP1;
	    MaxLength = WinGetx2( HWnd ) + 1;
	    MinLength = (BYTE)MP2;

	    return( WM_PROCESSED );

	case WM_INPUT:
	    {
	    BYTE Pos = 0;
	    WORD Key;
	    BYTE AsciiKey;
	    BYTE Counter;


	    for( ; ; )
		{
		WinFill( HWnd, SPACECHAR, 0, 0, WinGetx2( HWnd ), WinGety2( HWnd ) );
		WinString( HWnd, String, LEFT, 0, 0 );
		WinSetCursorPos( HWnd, Pos, 0 );
		Key = BiosGetKey();

		switch( Key )
		    {
		    case KBENTER:
		    case KBESC:
			if( Pos < MinLength )
			    break;

			return( WM_PROCESSED );

		    case KBBACKSPACE:
			if( Pos == 0 )
			    break;

			String[Pos - 1] = 0;
			Pos--;
			break;

		   default:
			if( Pos == MaxLength )
			    break;

			AsciiKey = (BYTE)Key;

			if( Pos == 0 )
			    for( Counter = 0; Counter < MaxLength; Counter++ )
				String[Counter] = 0;

			String[Pos] = AsciiKey;
			String[Pos + 1] = 0;
			Pos++;
		    }
		}
	    return( WM_PROCESSED );
	    }

	case WM_DESTROY:
	    return( WM_PROCESSED );

	}

    return( WinDefWindowProc( HWnd, Msg, MP1, MP2 ) );
    }


BOOL PersonInAbtListe( BOOL FAR *AbtCheckListe, struct PersonenInfo FAR *PersonenInfo )
    {
    WORD AbtZaehler;

    for( AbtZaehler = 0; AbtZaehler < NumAbteilungen; AbtZaehler++ )
	{
	if( AbtCheckListe[AbtZaehler] )
	    if( StdFarStrCmp( Abteilungen[AbtZaehler].Code, PersonenInfo->Felder[ConfigData->AbtFeldNr - 1].Feld ) == 0 )
		return( TRUE );
	}

    return( FALSE );
    }


VOID StringZeitAng( SDWORD Zeit, CHAR FAR *String, BOOL Null )
    {
    BOOL Negativ = FALSE;

    if( Zeit < 0 )
	{
	Negativ = TRUE;
	Zeit = 0 - Zeit;
	}

    switch( ConfigData->ZeitAngModus )
	{
	case STDMIN:
	    StdFarStrCpy( String, "      Std.    Min." );
	    if( Negativ )
		String[0] = '-';

	    if( Null )
		{
		StdBinToAscii( Zeit / 60, 4, (CHAR FAR *)&String[1], RIGHT, 1 );
		StdBinToAscii( Zeit % 60, 2, (CHAR FAR *)&String[11], RIGHT, 1 );
		}
	    else
		{
		StdBinToAscii( Zeit / 60, 4, (CHAR FAR *)&String[1], RIGHT, 0 );
		StdBinToAscii( Zeit % 60, 2, (CHAR FAR *)&String[11], RIGHT, 0 );
		}

	    break;

	case STDCENTISTD:
	    StdFarStrCpy( String, "      xxxx.xx Std." );
	    if( Negativ )
		String[0] = '-';

	    StdBinToAscii( StdDivide( Zeit * 100, 60 ) / 100, 4, (CHAR FAR *)&String[6], RIGHT, 1 );
	    StdBinToAscii( StdDivide( Zeit * 100, 60 ) % 100, 2, (CHAR FAR *)&String[11], RIGHT, 2 );
	    break;
	}
    }
