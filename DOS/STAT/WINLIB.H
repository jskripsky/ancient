// ****************************
// ***	  Windowlibrary     ***
// ****************************
// ***			    ***
// ****************************

#include "StdLib.H"


#define     WM_PROCESSED	    0

#define     WM_CREATE		    10
#define     WM_DESTROY		    11

#define     WM_SHOW		    20
#define     WM_HIDE		    21

#define     WM_SETFOCUS 	    30
#define     WM_CLEARFOCUS	    31

#define     WM_CHAR		    50

#define     WM_HELP		    101
#define     WM_MESSAGE		    102

#define     WM_RESTOREVIDEOMODE     201
#define     WM_SETVIDEOMODE	    202

#define     WM_SET		    1011

#define     WM_INPUT		    1500

#define     MP_CLEARBACKGROUND	    1


#define     HWND_DESKTOP	    0
#define     HWND_NULL		    10000

#define     SCREENMEMSIZE	    4000

typedef     WORD		    MSG;
typedef     WORD		    HWND;
typedef	    WORD		    MPARAM;

typedef     MSG (PROC)(HWND, MSG, MPARAM, MPARAM);


struct Window
    {
    BOOL	    Exists;
    BYTE	    x1, y1;
    BYTE	    x2, y2;

    PROC	    *Proc;

    BOOL	    Visible;
    };
