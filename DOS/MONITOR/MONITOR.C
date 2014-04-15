/********************
 **		   **
 **		   **
 **		   **
 ********************/


#include <string.h>
#include "stdlib.h"

#define  SCREENMEMSIZE		4000


#define  ADRESS_6845		0x03D4
#define  DATA_6845		0x03D5

#define  HSYNC_REG		0x02
#define  HSYNC_DUR_REG		0x03
#define  VSYNC_REG		0x07

#define  MODE_REG		0x03D8


VOID ActivateSignal( VOID );
VOID SetFrequency( BYTE HSync, BYTE HSyncDur, BYTE VSync );
VOID SetRegister6845( BYTE Register, BYTE Data );
VOID SaveVideo( VOID );
VOID RestoreVideo( VOID );

VOID InitSettings( VOID );
BOOL ChgSettings( VOID );

BYTE SavedVideoMode;
VOID FAR *SavedImage;




VOID Main( VOID )
    {
    BOOL  ExitProg = FALSE;

    SavedImage = DosAllocFarMem( 4000 );
    ScrSetMode();
    InitSettings();

    while( ChgSettings() )
	{
	SaveVideo();
	ActivateSignal();

	// for( Counter = 0; Counter <= 255; Counter++ )
	    // for( SubCounter = 0; SubCounter <= 255; SubCounter++ )
		// SetFrequency( 0, SubCounter, Counter );

	RestoreVideo();
	}

    ScrRestoreMode();
    DosFreeFarMem( SavedImage );
    }



VOID InitSettings( VOID )
    {
    }


BOOL ChgSettings( VOID )
    {
    }


VOID SetFrequency( BYTE HSync, BYTE HSyncDur, BYTE VSync )
    {
    SetRegister6845( HSYNC_REG, HSync );
    SetRegister6845( HSYNC_DUR_REG, HSyncDur );
    SetRegister6845( VSYNC_REG, VSync );
    }


VOID SetRegister6845( BYTE Register, BYTE Data )
    {
    _asm
	{
	mov	dx, ADRESS_6845

	mov	al, Register
	out	dx, al
	jmp	_Dump

	_Dump:
	mov	dx, DATA_6845

	mov	al, Data
	out	dx, al
	}
    }


VOID ActivateSignal( VOID )
    {
    _asm
	{
	mov	dx, MODE_REG
	mov	al, 0x2B

	// 101011: Blink, Signal,
	//	   Colorsignal, Graphicmode,
	//	   80x25 Mode

	out	dx, al
	}
    }


VOID SaveVideo( VOID )
    {
    _asm
	{
	mov	ah, 0x0F
	int	0x10
	mov	SavedVideoMode, al
	}

    StdFarMemCpy( SavedImage, (VOID FAR *)0xB8000000, SCREENMEMSIZE );
    }


VOID RestoreVideo( VOID )
    {
    _asm
	{
	mov	ah, 00
	mov	al, SavedVideoMode

	int	0x10
	}

    StdFarMemCpy( (VOID FAR *)0xB8000000, SavedImage, SCREENMEMSIZE );
    }
