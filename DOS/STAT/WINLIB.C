// ****************************
// ***	  Windowlibrary     ***
// ****************************
// ***			    ***
// ****************************

#include "StdLib.H"
#include "WinLib.H"
#include <string.h>

HWND		    LastWindow;
struct Window FAR   *Windows;

BOOL		    ProgScreenStored;
VOID FAR	    *ProgScreen;

MSG  DesktopWinProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

BOOL WinInitialize( WORD NumWindows );
BOOL WinTerminate( VOID );

BOOL WinCreateWindow( HWND HParentWnd, HWND *HWnd, PROC *WinProc, MPARAM MP1, MPARAM MP2, BYTE x1, BYTE y1, BYTE x2, BYTE y2 );
BOOL WinDestroyWindow( HWND HWnd );

MSG  WinSendMsg( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

MSG  WinDefWindowProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

BYTE WinGetx2( HWND HWnd );
BYTE WinGety2( HWND HWnd );

BOOL WinSetCursorPos( HWND HWnd, BYTE x, BYTE y );
BOOL WinHideCursor( VOID );
BOOL WinColor( HWND HWnd, BYTE Color, BYTE x1, BYTE y1, BYTE x2, BYTE y2 );
BOOL WinString( HWND HWnd, CHAR *String, BYTE Direction, BYTE x, BYTE y );
BOOL WinCharacter( HWND HWnd, CHAR Character, BYTE x, BYTE y );
BOOL WinFill( HWND HWnd, CHAR Character, BYTE x1, BYTE y1, BYTE x2, BYTE y2 );


/* VOID WinCriticalErrorMsg( CHAR *Message ); */





BOOL WinInitialize( WORD NumWindows )
    {
    ProgScreenStored = FALSE;
    ProgScreen = DosAllocFarMem( SCREENMEMSIZE );

    Windows = DosAllocFarMem( sizeof( *Windows ) * NumWindows );

    if( Windows == NULL )
	return( FALSE );

    LastWindow = HWND_NULL;

    return( TRUE );
    }


BOOL WinTerminate( VOID )
    {
    if( Windows[HWND_DESKTOP].Exists )
	WinSendMsg( HWND_DESKTOP, WM_DESTROY, 0, 0 );

    DosFreeFarMem( Windows );
    DosFreeFarMem( ProgScreen );

    return( TRUE );
    }


BOOL WinCreateWindow( HWND HParentWnd, HWND *HWnd, PROC *WinProc, MPARAM MP1, MPARAM MP2, BYTE x1, BYTE y1, BYTE x2, BYTE y2 )
    {
    HWND	WinCounter;

    if( LastWindow == HWND_NULL )
	{
	LastWindow = HWND_DESKTOP;
	*HWnd = HWND_DESKTOP;
	Windows[*HWnd].x1 = 0;
	Windows[*HWnd].y1 = 0;
	Windows[*HWnd].x2 = 79;
	Windows[*HWnd].y2 = 24;

	Windows[*HWnd].Proc = DesktopWinProc;
	}
    else
	{
	WinCounter = HWND_DESKTOP + 1;
	while( Windows[WinCounter].Exists && WinCounter <= LastWindow )
	    WinCounter++;

	if( WinCounter > LastWindow )
	    LastWindow++;

	*HWnd = WinCounter;

	Windows[*HWnd].x1 = Windows[HParentWnd].x1 + x1;
	Windows[*HWnd].y1 = Windows[HParentWnd].y1 + y1;
	Windows[*HWnd].x2 = Windows[HParentWnd].x1 + x2;
	Windows[*HWnd].y2 = Windows[HParentWnd].y1 + y2;

	Windows[*HWnd].Proc = WinProc;
	}

    Windows[*HWnd].Exists = TRUE;
    Windows[*HWnd].Visible = FALSE;

    WinSendMsg( *HWnd, WM_CREATE, MP1, MP2 );

    return( TRUE );
    }


BOOL WinDestroyWindow( HWND HWnd )
    {
    WinSendMsg( HWnd, WM_DESTROY, 0, 0 );

    Windows[HWnd].Exists = FALSE;

    if( HWnd == HWND_DESKTOP )
	{
	LastWindow = HWND_NULL;
	return( TRUE );
	}

    if( HWnd == LastWindow )
	while( !Windows[LastWindow].Exists )
	    LastWindow--;

    return( TRUE );
    }



MSG  WinSendMsg( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    Windows[HWnd].Proc( HWnd, Msg, MP1, MP2 );
    }


MSG  WinDefWindowProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {

    switch( Msg )
	{
	case WM_SHOW:
	    return( WM_PROCESSED );

	case WM_HIDE:
	    return( WM_PROCESSED );
	}

    return( WM_PROCESSED );

    }


BYTE WinGetx2( HWND HWnd )
    {
    return( Windows[HWnd].x2 - Windows[HWnd].x1 );
    }


BYTE WinGety2( HWND HWnd )
    {
    return( Windows[HWnd].y2 - Windows[HWnd].y1 );
    }


BOOL WinSetCursorPos( HWND HWnd, BYTE x, BYTE y )
    {
    ScrSetCursor( (BYTE)(Windows[HWnd].x1 + x), (BYTE)(Windows[HWnd].y1 + y) );
    }


BOOL WinHideCursor( VOID )
    {
    ScrSetCursor( 0, 25 );
    }


BOOL WinColor( HWND HWnd, BYTE Color, BYTE x1, BYTE y1, BYTE x2, BYTE y2 )
    {
    ScrBoxChgColor( (BYTE)(Windows[HWnd].x1 + x1), (BYTE)(Windows[HWnd].y1 + y1), (BYTE)(Windows[HWnd].x1 + x2), (BYTE)(Windows[HWnd].y1 + y2), Color );
    }


BOOL WinString( HWND HWnd, CHAR *String, BYTE Direction, BYTE x, BYTE y )
    {
    switch( Direction )
	{
	case LEFT:
	    ScrWrite( (BYTE)(Windows[HWnd].x1 + x), (BYTE)(Windows[HWnd].y1 + y), String );
	    break;
	case RIGHT:
	    ScrWriteRight( (BYTE)(Windows[HWnd].x1 + x), (BYTE)(Windows[HWnd].y1 + y), String );
	    break;
	case CENTER:
	    ScrWriteCenter( (BYTE)Windows[HWnd].x1, (BYTE)Windows[HWnd].x2, (BYTE)(Windows[HWnd].y1 + y), String );
	    break;
	}
    }


BOOL WinCharacter( HWND HWnd, CHAR Character, BYTE x, BYTE y )
    {
    ScrCharacter( (BYTE)(Windows[HWnd].x1 + x), (BYTE)(Windows[HWnd].y1 + y), Character );
    }


BOOL WinFill( HWND HWnd, CHAR Character, BYTE x1, BYTE y1, BYTE x2, BYTE y2 )
    {
    BYTE LineCounter;

    for( LineCounter = 0; LineCounter < (BYTE)(y2 - y1 + 1); LineCounter++ )
	ScrCharFill( (BYTE)(Windows[HWnd].x1 + x1), (BYTE)(Windows[HWnd].y1 + y1 + LineCounter), (BYTE)(x2 - x1 + 1), Character );
    }


MSG  DesktopWinProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 )
    {
    switch( Msg )
	{
	case WM_CREATE:
	case WM_SETVIDEOMODE:
	    ScrSetMode();
	    WinHideCursor();
	    if( ProgScreenStored )
		StdFarMemCpy( (VOID FAR *)0xB8000000, ProgScreen, SCREENMEMSIZE );
	    return( WM_PROCESSED );

	case WM_DESTROY:
	    ScrRestoreMode();
	    return( WM_PROCESSED );

	case WM_RESTOREVIDEOMODE:
	    ProgScreenStored = TRUE;
	    StdFarMemCpy( ProgScreen, (VOID FAR *)0xB8000000, SCREENMEMSIZE );
	    ScrRestoreMode();
	    return( WM_PROCESSED );

	}

    return( WM_PROCESSED );
    }
