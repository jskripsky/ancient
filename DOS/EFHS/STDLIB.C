// ****************************
// ***	 Standardlibrary    ***
// ****************************
// ***			    ***
// ****************************

#include "stdlib.h"
#include <malloc.h>

#define SCRSEG 0xB800

BYTE ScrPrevVideoMode;
WORD LastErrorcode;

WORD _cdecl BiosGetKey( VOID );
BOOL _cdecl BiosIsKeyInBuffer( VOID );

BYTE _cdecl DosQueryDay( VOID );
BYTE _cdecl DosQueryMonth( VOID );
WORD _cdecl DosQueryYear( VOID );

RET  _cdecl DosCreate( const CHAR *FileName, HFILE *FileHandle, WORD FileAttribute );
RET  _cdecl DosOpen( const CHAR *FileName, HFILE *FileHandle, BYTE OpenMode );
RET  _cdecl DosDelete( const CHAR *FileName );
RET  _cdecl DosRename( const CHAR *OldFileName, const CHAR *NewFileName );
RET  _cdecl DosClose( HFILE FileHandle );
RET  _cdecl DosSetFilePtr( HFILE FileHandle, SDWORD *Distance, BYTE MoveType, SDWORD *NewPointer );
RET  _cdecl DosRead( HFILE FileHandle, VOID FAR *BufferArea, WORD BufferLength, WORD *BytesRead );
RET  _cdecl DosWrite( HFILE FileHandle, VOID FAR *BufferArea, WORD BufferLength, WORD *BytesWritten );
WORD _cdecl DosGetLastErrorcode( VOID );

#define DosAllocMem	 _nmalloc  // VOID NEAR *DosAllocMem( WORD BufferLength );
#define DosAllocFarMem	 _fmalloc  // VOID FAR *DosAllocFarMem( WORD BufferLength );
#define DosFreeMem	 _nfree    // VOID DosFreeMem( VOID NEAR *MemBlock );
#define DosFreeFarMem	 _ffree    // VOID DosFreeFarMem( VOID FAR *MemBlock );

VOID _cdecl ScrSetMode( VOID );
VOID _cdecl ScrRestoreMode( VOID );
VOID _cdecl ScrSetCursor( BYTE x, BYTE y );
VOID _cdecl ScrClr( BYTE Color );
VOID _cdecl ScrChgColor( BYTE x, BYTE y, BYTE Width, BYTE DestColor );
VOID _cdecl ScrBoxChgColor( BYTE x1, BYTE y1, BYTE x2, BYTE y2, BYTE DestColor );
VOID _cdecl ScrCharacter( BYTE x, BYTE y, CHAR Character );
VOID _cdecl ScrCharFill( BYTE x, BYTE y, BYTE Width, CHAR Character );
VOID _cdecl ScrWrite( BYTE x, BYTE y, const CHAR *String );
VOID _cdecl ScrWriteCenter( BYTE x1, BYTE x2, BYTE y, const CHAR *String );
VOID _cdecl ScrWriteRight( BYTE x, BYTE y, const CHAR *String );


DWORD StdDivide( DWORD Dividend, WORD Divisor );
BYTE StdBinToAscii( DWORD Number, BYTE Length, CHAR FAR *String, BYTE Direction, BYTE Zeros );
DWORD StdAsciiToBin( BYTE Length, CHAR FAR *Number );


WORD _cdecl BiosGetKey( VOID )
    {
    _asm
	{
	xor	ah, ah
	int	0x16
	}
    }

BOOL _cdecl BiosIsKeyInBuffer( VOID )
    {
    _asm
	{
	mov	ah, 0x01
	int	0x16

	mov	al, FALSE
	jz	_end

	mov	al, TRUE

	_end:
	}
    }

BYTE _cdecl DosQueryDay( VOID )
    {
    _asm
	{
	mov	ah, 0x2A
	int	0x21

	mov	al, dl
	}
    }

BYTE _cdecl DosQueryMonth( VOID )
    {
    _asm
	{
	mov	ah, 0x2A
	int	0x21

	mov	al, dh
	}
    }

WORD _cdecl DosQueryYear( VOID )
    {
    _asm
	{
	mov	ah, 0x2A
	int	0x21

	mov	ax, cx
	}
    }

RET  _cdecl DosCreate( const CHAR *FileName, HFILE *FileHandle, WORD FileAttribute )
    {
    _asm
	{
	mov	ah, 0x3C
	mov	cx, FileAttribute
	mov	dx, FileName

	int	0x21

	jc	_end
	mov	si, FileHandle
	mov	[si], ax
	mov	ax, FALSE

	_end:
	mov	LastErrorcode, ax
	}
    }



RET  _cdecl DosOpen( const CHAR *FileName, HFILE *FileHandle, BYTE OpenMode )
    {
    _asm
	{
	mov	ah, 0x3D
	mov	al, OpenMode
	mov	dx, FileName

	int	0x21

	jc	_end
	mov	si, FileHandle
	mov	[si], ax
	mov	ax, FALSE

	_end:
	mov	LastErrorcode, ax
	}
    }

RET  _cdecl DosDelete( const CHAR *FileName )
    {
    _asm
	{
	mov	ah, 0x41
	mov	dx, FileName

	int	0x21

	jc	_end
	mov	ax, FALSE

	_end:
	mov	LastErrorcode, ax
	}
    }

RET  _cdecl DosRename( const CHAR *OldFileName, const CHAR *NewFileName )
    {
    _asm
	{
	mov	dx, OldFileName
	mov	ax, ds
	mov	es, ax
	mov	di, NewFileName

	mov	ah, 0x56
	int	0x21

	jc	_end
	mov	ax, FALSE

	_end:
	mov	LastErrorcode, ax
	}
    }

RET  _cdecl DosClose( HFILE FileHandle )
    {
    _asm
	{
	mov	ah, 0x3E
	mov	bx, FileHandle

	int	0x21

	jc	_end
	mov	ax, FALSE

	_end:
	mov	LastErrorcode, ax
	}
    }


RET  _cdecl DosSetFilePtr( HFILE FileHandle, SDWORD *Distance, BYTE MoveType, SDWORD *NewPointer )
    {
    _asm
	{
	mov	ah, 0x42

	mov	al, MoveType
	mov	bx, FileHandle

	mov	si, Distance
	mov	dx, ds:[si+0x00]
	mov	cx, ds:[si+0x02]

	int	0x21

	jc	_end
	cmp	NewPointer, 0x0000
	je	_end

	mov	si, NewPointer
	mov	ds:[si+0x00], ax
	mov	ds:[si+0x02], dx

	_end:
	mov	LastErrorcode, ax
	}
    }


RET  _cdecl DosRead( HFILE FileHandle, VOID FAR *BufferArea, WORD BufferLength, WORD *BytesRead )
    {
    _asm
	{
	push	ds

	mov	ah, 0x3F
	mov	bx, FileHandle
	mov	cx, BufferLength

	lds	dx, BufferArea

	int	0x21

	pop	ds
	jc	_end

	cmp	BytesRead, 0x0000
	je	_end
	mov	si, BytesRead
	mov	[si], ax

	_end:
	mov	LastErrorcode, ax
	}
    }

RET  _cdecl DosWrite( HFILE FileHandle, VOID FAR *BufferArea, WORD BufferLength, WORD *BytesWritten )
    {
    _asm
	{
	push	ds

	mov	ah, 0x40
	mov	bx, FileHandle
	mov	cx, BufferLength

	lds	dx, BufferArea

	int	0x21

	pop	ds
	jc	_end

	cmp	BytesWritten, 0x0000
	je	_end
	mov	si, BytesWritten
	mov	[si], ax

	_end:
	mov	LastErrorcode, ax
	}
    }

WORD _cdecl DosGetLastErrorcode( VOID )
    {
    _asm
	{
	mov	ax, LastErrorcode
	}
    }

VOID _cdecl ScrSetMode( VOID )
    {
    _asm
	{
	mov	ah, 0x0F
	int	0x10
	mov	ScrPrevVideoMode, al

	mov	ax, 0x0003
	int	0x10
	}
    }

VOID _cdecl ScrRestoreMode( VOID )
    {
    _asm
	{
	mov	ah, 0x00
	mov	al, ScrPrevVideoMode
	int	0x10
	}
    }

VOID _cdecl ScrSetCursor( BYTE x, BYTE y )
    {
    _asm
	{
	mov	ah, 0x02
	mov	bh, 0x00
	mov	dl, x
	mov	dh, y
	int	0x10
	}
    }

VOID _cdecl ScrClr( BYTE Color )
    {
    _asm
	{
	mov	ax, SCRSEG
	mov	es, ax
	mov	di, 0x0000
	mov	cx, 0x07D0

	mov	ah, Color
	mov	al, 0x00

	rep	stosw
	}
    }

VOID _cdecl ScrChgColor( BYTE x, BYTE y, BYTE Width, BYTE DestColor )
    {
    _asm
	{
	mov	ax, SCRSEG
	mov	es, ax

	mov	al, 0xA0
	mul	y
	shl	x, 1
	mov	dh, 0x00
	mov	dl, x
	add	ax, dx
	inc	ax

	mov	di, ax

	mov	ch, 0x00
	mov	cl, Width
	mov	al, DestColor

	_loop:
	mov	es:[di], al
	add	di, 2
	loop	_loop
	}
    }

VOID _cdecl ScrBoxChgColor( BYTE x1, BYTE y1, BYTE x2, BYTE y2, BYTE DestColor )
    {
    BYTE Counter;

    for( Counter = 0; Counter < y2 - y1 + 1; Counter++ )
	ScrChgColor( x1, (BYTE)(y1 + Counter), (BYTE)(x2 - x1 + 1), DestColor );
    }

VOID _cdecl ScrCharacter( BYTE x, BYTE y, CHAR Character )
    {
    _asm
	{
	mov	ax, SCRSEG
	mov	es, ax

	mov	al, 0xA0
	mul	y
	shl	x, 1
	mov	dh, 0x00
	mov	dl, x
	add	ax, dx

	mov	di, ax
	mov	al, Character
	mov	es:[di], al
	}
    }

VOID _cdecl ScrCharFill( BYTE x, BYTE y, BYTE Width, CHAR Character )
    {
    _asm
	{
	mov	ax, SCRSEG
	mov	es, ax

	mov	al, 0xA0
	mul	y
	shl	x, 1
	mov	dh, 0x00
	mov	dl, x
	add	ax, dx

	mov	di, ax
	mov	ch, 0x00
	mov	cl, Width
	mov	al, Character

	_loop:
	mov	es:[di], al
	add	di, 0x02
	loop	_loop
	}
    }

VOID _cdecl ScrWrite( BYTE x, BYTE y, const CHAR *String )
    {
    _asm
	{
	mov	ax, SCRSEG
	mov	es, ax

	mov	al, 0xA0
	mul	y
	shl	x, 1
	mov	dh, 0x00
	mov	dl, x
	add	ax, dx

	mov	di, ax
	mov	si, String

	test	[si], 0xFF
	jz	_end

	_loop:

	movsb
	inc	di
	test	[si], 0xFF

	jnz	_loop
	_end:
	}
    }

VOID _cdecl ScrWriteCenter( BYTE x1, BYTE x2, BYTE y, const CHAR *String )
    {
    BYTE Counter;

    Counter = 0;
    while( String[Counter] )
	Counter++;

    ScrWrite( ( BYTE )((x1 + (x2 - x1 - Counter + 1) / 2)), y, String );
    }

VOID _cdecl ScrWriteRight( BYTE x, BYTE y, const CHAR *String )
    {
    BYTE Counter;

    Counter = 0;
    while( String[Counter] )
	Counter++;

    ScrWrite( ( BYTE )(x - Counter + 1), y, String );
    }

DWORD StdAsciiToBin( BYTE Length, CHAR FAR *Number )
    {
    DWORD EndNumber = 0;
    DWORD TempNumber;
    BYTE Counter;
    BYTE SubCounter;

    for( Counter = 0; Counter < Length; Counter++ )
	{
	if( Number[Counter] > '9' || Number[Counter] < '0' )
	    continue;

	TempNumber = Number[Counter] - ZEROCHAR;
	for( SubCounter = Length - Counter - 1; SubCounter; SubCounter-- )
	    TempNumber *= 10;
	EndNumber += TempNumber;
	}

    return( EndNumber );
    }


BYTE StdBinToAscii( DWORD Number, BYTE Length, CHAR FAR *String, BYTE Direction, BYTE Zeros )
    {
    BYTE Counter;
    BYTE Remainder;
    BYTE EffLength = 0;

    for( Counter = 0; Counter < Length; Counter++ )
	{
	if( (Number == 0) && (Counter >= Zeros) )
	    String[Length - Counter - 1] = SPACECHAR;
	else
	    {
	    Remainder = Number % 10;
	    String[Length - Counter - 1] = Remainder + ZEROCHAR;
	    EffLength++;
	    }
	Number /= 10;
	}

    switch( Direction )
	{
	case LEFT:
	    for( Counter = 0; Counter < EffLength; Counter++ )
		String[Counter] = String[Length - EffLength + Counter];
	    for( Counter = 0; Counter < Length - EffLength; Counter++ )
		String[Length - 1 - Counter] = SPACECHAR;
	    break;
	case RIGHT:
	    break;
	}

    return( EffLength );
    }


DWORD StdDivide( DWORD Dividend, WORD Divisor )
    {
    DWORD Quotient;
    WORD DivisorHalf;

    Quotient = Dividend / Divisor;
    DivisorHalf = Divisor / 2;
    if( Divisor % 2 == 1 )
	DivisorHalf++;

    if( Dividend % Divisor >= DivisorHalf )
	Quotient++;

    return( Quotient );
    }
