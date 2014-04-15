// ****************************
// ***	 Standardlibrary    ***
// ****************************
// ***			    ***
// ****************************

#include "JSLib.H"
#include <Malloc.H>

#define SCRSEG 0xB800

BYTE ScrPrevVideoMode;
WORD LastErrorcode;

CHAR MonthNames[12][10] = { "Januar", "Februar", "M„rz", "April", "Mai", "Juni", "Juli",
			    "August", "September", "Oktober", "November", "Dezember" };

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
RET  _cdecl DosLastModTime( HFILE FileHandle, DWORD *Time );
RET  _cdecl DosCurrentDrive(  BYTE *Drive );
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

#define StdMemCpy	 memcpy
#define StdMemCmp	 memcmp
#define StdMemSet	 memset
#define StdFarMemCpy	 _fmemcpy
#define StdFarMemCmp	 _fmemcmp
#define StdFarMemSet	 _fmemset

#define StdStrCpy	 strcpy
#define StdStrCmp	 strcmp
#define StdStrSet	 strset
#define StdStrCat	 strcat
#define StdStrLwr	 strlwr
#define StdStrChr	 strchr
#define StdStrLen	 strlen
#define StdFarStrCpy	 _fstrcpy
#define StdFarStrCmp	 _fstrcmp
#define StdFarStrSet	 _fstrset

DWORD StdDivide( DWORD Dividend, WORD Divisor );
BYTE  StdBinToAscii( DWORD Number, BYTE Length, CHAR FAR *String, BYTE Direction, BYTE Zeros );
DWORD StdAsciiToBin( BYTE Length, CHAR FAR *Number );

BYTE  StdMonthNumDays( BYTE Month, WORD Year );
CHAR *StdMonthName( BYTE Month );

#pragma warn -rvl

WORD _cdecl BiosGetKey( VOID )
{
	asm {
	xor	ah, ah
	int	0x16
	}
}

BOOL _cdecl BiosIsKeyInBuffer( VOID )
{
	asm {
	mov	ah, 0x01
	int	0x16

	mov	al, FALSE
	jz	_end

	mov	al, TRUE

	}

	_end:
}

BYTE _cdecl DosQueryDay( VOID )
{
	asm {
	mov	ah, 0x2A
	int	0x21

	mov	al, dl
	}
}

BYTE _cdecl DosQueryMonth( VOID )
{
	asm {
	mov	ah, 0x2A
	int	0x21

	mov	al, dh
	}
}

WORD _cdecl DosQueryYear( VOID )
{
	asm {
	mov	ah, 0x2A
	int	0x21

	mov	ax, cx
	}
}

RET  _cdecl DosCreate( const CHAR *FileName, HFILE *FileHandle, WORD FileAttribute )
{
	asm {
	mov	ah, 0x3C
	mov	cx, FileAttribute
	mov	dx, FileName

	int	0x21

	jc	_end
	mov	si, FileHandle
	mov	[si], ax
	mov	ax, FALSE
	}

	_end:
	asm {
	mov	LastErrorcode, ax
	}
}



RET  _cdecl DosOpen( const CHAR *FileName, HFILE *FileHandle, BYTE OpenMode )
{
	asm {
	mov	ah, 0x3D
	mov	al, OpenMode
	mov	dx, FileName

	int	0x21

	jc	_end
	mov	si, FileHandle
	mov	[si], ax
	mov	ax, FALSE
	}

	_end:
	asm {
	mov	LastErrorcode, ax
	}
}

RET  _cdecl DosDelete( const CHAR *FileName )
{
	asm {
	mov	ah, 0x41
	mov	dx, FileName

	int	0x21

	jc	_end
	mov	ax, FALSE
	}

	_end:
	asm {
	mov	LastErrorcode, ax
	}
}

RET  _cdecl DosRename( const CHAR *OldFileName, const CHAR *NewFileName )
{
	asm {
	mov	dx, OldFileName
	mov	ax, ds
	mov	es, ax
	mov	di, NewFileName

	mov	ah, 0x56
	int	0x21

	jc	_end
	mov	ax, FALSE
	}

	_end:
	asm {
	mov	LastErrorcode, ax
	}
}

RET  _cdecl DosClose( HFILE FileHandle )
{
	asm {
	mov	ah, 0x3E
	mov	bx, FileHandle

	int	0x21

	jc	_end
	mov	ax, FALSE
	}

	_end:
	asm {
	mov	LastErrorcode, ax
	}
}


RET  _cdecl DosSetFilePtr( HFILE FileHandle, SDWORD *Distance, BYTE MoveType, SDWORD *NewPointer )
{
	asm {
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
	mov	ax, FALSE
	}

	_end:
	asm {
	mov	LastErrorcode, ax
	}
}


RET  _cdecl DosRead( HFILE FileHandle, VOID FAR *BufferArea, WORD BufferLength, WORD *BytesRead )
{
	asm {
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
	mov	ax, FALSE
	}

	_end:
	asm {
	mov	LastErrorcode, ax
	}
}

RET  _cdecl DosWrite( HFILE FileHandle, VOID FAR *BufferArea, WORD BufferLength, WORD *BytesWritten )
{
	asm {
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
	mov	ax, FALSE
	}
	_end:

	asm {
	mov	LastErrorcode, ax
	}
}

RET  _cdecl DosLastModTime( HFILE FileHandle, DWORD *Time )
{
	asm {
	mov	ah, 0x57
	mov	al, 0x00

	mov	bx, FileHandle

	int	0x21

	jc	_end

	mov	si, Time
	mov	ds:[si+0x00], cx
	mov	ds:[si+0x02], dx
	mov	ax, FALSE
	}

	_end:
    asm {
	mov	LastErrorcode, ax
	}
}

RET  _cdecl DosCurrentDrive(  BYTE *Drive )
{
	asm {
	mov	ah, 0x19

	int	0x21

	mov	si, Drive
	mov	[si], al

	mov	ax, FALSE
	}
}

WORD _cdecl DosGetLastErrorcode( VOID )
{
	asm {
	mov	ax, LastErrorcode
	}
}

VOID _cdecl ScrSetMode( VOID )
{
	asm {
	mov	ah, 0x0F
	int	0x10
	mov	ScrPrevVideoMode, al

	mov	ax, 0x0003
	int	0x10
	}
}

VOID _cdecl ScrRestoreMode( VOID )
{
	asm {
	mov	ah, 0x00
	mov	al, ScrPrevVideoMode
	int	0x10
	}
}

VOID _cdecl ScrSetCursor( BYTE x, BYTE y )
{
	asm {
	mov	ah, 0x02
	mov	bh, 0x00
	mov	dl, x
	mov	dh, y
	int	0x10
	}
}

VOID _cdecl ScrClr( BYTE Color )
{
	asm {
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
	asm {
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
	}

	_loop:
	asm {
	mov	es:[di], al
	add	di, 2
	loop	_loop
	}
}

VOID _cdecl ScrBoxChgColor( BYTE x1, BYTE y1, BYTE x2, BYTE y2, BYTE DestColor )
{
	BYTE Counter;

	for( Counter = 0; Counter < (BYTE)(y2 - y1 + 1); Counter++ )
	ScrChgColor( x1, (BYTE)(y1 + Counter), (BYTE)(x2 - x1 + 1), DestColor );
}

VOID _cdecl ScrCharacter( BYTE x, BYTE y, CHAR Character )
{
	asm {
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
	asm {
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
	}

	_loop:
	asm {
	mov	es:[di], al
	add	di, 0x02
	loop	_loop
	}
}

VOID _cdecl ScrWrite( BYTE x, BYTE y, const CHAR *String )
{
	asm {
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

	test BYTE PTR [si], 0xFF
	jz	_end
	}

	_loop:
	asm {
	movsb
	inc	di
	test	BYTE PTR [si], 0xFF

	jnz	_loop
	}
	_end:
}

#pragma warn +rvl


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


/*
SBYTE _cdecl StdMemCmp( VOID FAR *Buffer1, VOID FAR *Buffer2, WORD Size )
	{
	WORD Counter;
	BOOL Id = TRUE;

	for( Counter = 0; Counter < Size; Counter++ )
	if( ((BYTE FAR *)Buffer1)[Counter] != ((BYTE FAR *)Buffer2)[Counter] )
		{
		Id = FALSE;
		break;
		}

	if( Id )
	return( 0 );
	else
	if( ((BYTE FAR *)Buffer1)[Counter] < ((BYTE FAR *)Buffer2)[Counter] )
		return( -1 );
	else
		return(  1 );
	}


WORD  _cdecl StdMemCpy( VOID FAR *Destination, VOID FAR *Source, WORD Size )
	{
	WORD Counter;

	if( (WORD)OFS( Destination ) < (WORD)OFS( Source ) )
	for( Counter = 1; Counter <= Size; Counter++ )
		((BYTE FAR *)Destination)[Counter - 1] = ((BYTE FAR *)Source)[Counter - 1];
	else
	for( Counter = Size; Counter >= 1; Counter-- )
		((BYTE FAR *)Destination)[Counter - 1] = ((BYTE FAR *)Source)[Counter - 1];
	}


WORD  _cdecl StdMemSet( VOID FAR *Buffer, BYTE Value, WORD Size )
	{
	WORD Counter;

	for( Counter = 0; Counter < Size; Counter++ )
	((BYTE FAR *)Buffer)[Counter] = Value;
	}


BYTE  _cdecl StdStrCmp( CHAR FAR *String1, CHAR FAR *String2 )
	{
	BYTE Counter;
	BOOL Id = TRUE;

	for( Counter = 0; String1[Counter]; Counter++ )
	if( ((BYTE FAR *)String1)[Counter] != ((BYTE FAR *)String2)[Counter] )
		{
		Id = FALSE;
		break;
		}

	if( Id )
	return( 0 );
	else
	return(	1 );
	}
*/



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
	for( SubCounter = (BYTE)(Length - Counter - 1); SubCounter; SubCounter-- )
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
	    Remainder = (BYTE)(Number % 10);
	    String[Length - Counter - 1] = (CHAR)(Remainder + ZEROCHAR);
	    EffLength++;
	    }
	Number /= 10;
	}

    switch( Direction )
	{
	case LEFT:
	    StdFarMemCpy( String, &String[Length - EffLength], EffLength );
	    StdFarMemSet( &String[EffLength], SPACECHAR, Length - EffLength );
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


BYTE  StdMonthNumDays( BYTE Month, WORD Year )
    {
    BYTE Months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if( Year % 4 == 0 )
	Months[1]++;

    return( Months[Month - 1] );
    }


CHAR *StdMonthName( BYTE Month )
    {
    return( MonthNames[Month - 1] );
    }
