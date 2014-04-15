// ****************************
// ***	 Standardlibrary    ***
// ****************************
// ***			    ***
// ****************************

#include "constant.h"


#define SCRSEG 0xB800

byte scroldmode;
word errorcode;

word _cdecl BiosGetKey( void );
bool _cdecl BiosCheckKeybBuffer( void );

byte _cdecl DosDay( void );
byte _cdecl DosMonth( void );
word _cdecl DosYear( void );

file _cdecl DosCreateFile( word attribute, const char *filename );
file _cdecl DosOpenFile( byte mode, const char *filename );
void _cdecl DosDeleteFile( const char *filename );
void _cdecl DosCloseFile( file filehandle );
void _cdecl DosResetFile( file filehandle );
word _cdecl DosReadFile( file filehandle, word quantity, void _far *buffer );
word _cdecl DosWriteFile( file filehandle, word quantity, void _far *buffer );
word _cdecl DosGetErrorcode( void );

void _cdecl ScrSetMode( void );
void _cdecl ScrRestoreMode( void );
void _cdecl ScrSetCursor( byte x, byte y );
void _cdecl ScrClr( byte color );
void _cdecl ScrChgColor( byte x, byte y, byte width, byte destcolor );
void _cdecl ScrBoxChgColor( byte x1, byte y1, byte x2, byte y2, byte destcolor );
void _cdecl ScrCharacter( byte x, byte y, char character );
void _cdecl ScrCharFill( byte x, byte y, byte width, char character );
void _cdecl ScrWrite( byte x, byte y, const char *string );
void _cdecl ScrWriteCenter( byte x1, byte x2, byte y, const char *string );
void _cdecl ScrWriteRight( byte x, byte y, const char *string );


word _cdecl BiosGetKey( void )
    {
    _asm
	{
	xor	ah, ah
	int	0x16
	}
    }

bool _cdecl BiosCheckKeybBuffer( void )
    {
    _asm
	{
	mov	ah, 0x01
	int	0x16

	jnz	_setal

	xor	al, al
	jmp	_end

	_setal:
	mov	al, 0xFF

	_end:
	}
    }

byte _cdecl DosDay( void )
    {
    _asm
	{
	mov	ah, 0x2A
	int	0x21

	mov	al, dl
	}
    }

byte _cdecl DosMonth( void )
    {
    _asm
	{
	mov	ah, 0x2A
	int	0x21

	mov	al, dh
	}
    }

word _cdecl DosYear( void )
    {
    _asm
	{
	mov	ah, 0x2A
	int	0x21

	mov	ax, cx
	}
    }

file _cdecl DosCreateFile( word attribute, const char *filename )
    {
    _asm
	{
	mov	errorcode, NULL

	mov	ah, 0x3C
	mov	cx, attribute
	mov	dx, filename

	int	0x21

	jnc	_end
	mov	errorcode, ax

	_end:
	}
    }

file _cdecl DosOpenFile( byte mode, const char *filename )
    {
    _asm
	{
	mov	errorcode, NULL

	mov	ah, 0x3D
	mov	al, mode
	mov	dx, filename

	int	0x21

	jnc	_end
	mov	errorcode, ax

	_end:
	}
    }

void _cdecl DosDeleteFile( const char *filename )
    {
    _asm
	{
	mov	errorcode, NULL

	mov	ah, 0x41
	mov	dx, filename

	int	0x21

	jnc	_end
	mov	errorcode, ax

	_end:
	}
    }

void _cdecl DosCloseFile( file filehandle )
    {
    _asm
	{
	mov	errorcode, NULL

	mov	ah, 0x3E
	mov	bx, filehandle

	int	0x21

	jnc	_end
	mov	errorcode, ax

	_end:
	}
    }

void _cdecl DosResetFile( file filehandle )
    {
    _asm
	{
	mov	errorcode, NULL

	mov	ah, 0x42
	mov	al, 0x00
	mov	bx, filehandle

	mov	cx, 0x0000
	mov	dx, 0x0000

	int	0x21

	jnc	_end
	mov	errorcode, ax

	_end:
	}
    }

word _cdecl DosReadFile( file filehandle, word quantity, void _far *buffer )
    {
    _asm
	{
	mov	errorcode, NULL
	push	ds

	mov	ah, 0x3F
	mov	bx, filehandle
	mov	cx, quantity

	lds	dx, buffer

	int	0x21

	pop	ds
	jnc	_end
	mov	errorcode, ax

	_end:
	}
    }

word _cdecl DosWriteFile( file filehandle, word quantity, void _far *buffer )
    {
    _asm
	{
	mov	errorcode, NULL
	push	ds

	mov	ah, 0x40
	mov	bx, filehandle
	mov	cx, quantity

	lds	dx, buffer

	int	0x21

	pop	ds
	jnc	_end
	mov	errorcode, ax

	_end:
	}
    }

word _cdecl DosGetErrorcode( void )
{
    _asm
    {
    mov     ax, errorcode
    }
}

void _cdecl ScrSetMode( void )
    {
    _asm
	{
	mov	ah, 0x0F
	int	0x10
	mov	scroldmode, al

	mov	ax, 0x0003
	int	0x10
	}
    }

void _cdecl ScrRestoreMode( void )
    {
    _asm
	{
	mov	ah, 0x00
	mov	al, scroldmode
	int	0x10
	}
    }

void _cdecl ScrSetCursor( byte x, byte y )
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

void _cdecl ScrClr( byte color )
    {
    _asm
	{
	mov	ax, SCRSEG
	mov	es, ax
	mov	di, 0x0000
	mov	cx, 0x07D0

	mov	ah, color
	mov	al, 0x00

	rep	stosw
	}
    }

void _cdecl ScrChgColor( byte x, byte y, byte width, byte destcolor )
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
	mov	cl, width
	mov	al, destcolor

	_loop:
	mov	es:[di], al
	add	di, 2
	loop	_loop
	}
    }

void _cdecl ScrBoxChgColor( byte x1, byte y1, byte x2, byte y2, byte destcolor )
    {
    byte counter;

    for( counter = 0; counter < y2 - y1 + 1; counter++ )
	ScrChgColor( x1, (byte)(y1 + counter), (byte)(x2 - x1 + 1), destcolor );
    }

void _cdecl ScrCharacter( byte x, byte y, char character )
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
	mov	al, character
	mov	es:[di], al
	}
    }

void _cdecl ScrCharFill( byte x, byte y, byte width, char character )
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
	mov	cl, width
	mov	al, character

	_loop:
	mov	es:[di], al
	add	di, 0x02
	loop	_loop
	}
    }

void _cdecl ScrWrite( byte x, byte y, const char *string )
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
	mov	si, string

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

void _cdecl ScrWriteCenter( byte x1, byte x2, byte y, const char *string )
    {
    byte counter;

    counter = 0;
    while( string[counter] )
	counter++;

    ScrWrite( ( byte )((x1 + (x2 - x1 - counter + 1) / 2)), y, string );
    }

void _cdecl ScrWriteRight( byte x, byte y, const char *string )
    {
    byte counter;

    counter = 0;
    while( string[counter] )
	counter++;

    ScrWrite( ( byte )(x - counter + 1), y, string );
    }
