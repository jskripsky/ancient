#include "MCGA.H"

#define MCGA_VRAMSEG	    0xA000
#define MCGA_PIXELPERLINE	320

byte _near		    old_video_mode;


void _far _cdecl McgaRestoreVideoMode( bool savescreen )
{
	_asm {
	mov	al, savescreen
	mov	cl, 7
	shl	al, cl

	or	al, old_video_mode

	xor	ah, ah
	int	0x10
	}
}


void _far _cdecl McgaSetVideoMode( bool savescreen )
{
	_asm {
	mov	ah, 0x0F
	int	0x10

	mov	old_video_mode, al

	mov	al, savescreen
	mov	cl, 7
	shl	al, cl

	or	al, 0x13

	xor	ah, ah
	int	0x10
	}
}


void _far _cdecl McgaClearScreen( byte color )
{
	_asm {
	mov	ax, MCGA_VRAMSEG
	mov	es, ax
	xor	di, di

	mov	al, color
	mov	ah, al

	mov	cx, 0xFFFF
	rep	stosw
	}
}


void _far _cdecl McgaGetPalette( void _far *palette )
{
	_asm {
	xor	bx, bx
	mov	cx, 256
	les	dx, palette

	mov	ax, 0x1017
	int	0x10
	}
}


void _far _cdecl McgaSetPalette( const void _far *palette )
{
	_asm {
	xor	bx, bx
	mov	cx, 256
	les	dx, palette

	mov	ax, 0x1012
	int	0x10
	}
}


void _far _cdecl McgaDrawBox( byte color, word x1, word y1, word x2, word y2 )
{
	_asm {
	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, MCGA_PIXELPERLINE
	mul	y1
	add	ax, x1
	mov	di, ax

	mov	dx, x2
	sub	dx, x1
	inc	dx

	mov	bx, MCGA_PIXELPERLINE
	sub	bx, dx

	mov	cx, y2
	sub	cx, y1
	inc	cx

	mov	al, color
	}

_loop:
	_asm {
	mov	si, cx
	mov	cx, dx

	rep	stosb

	mov	cx, si

	add	di, bx

	loop	_loop
	}
}


void _far _cdecl McgaDrawXLine( byte color, word y, word x1, word x2 )
{
	_asm {
	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, MCGA_PIXELPERLINE
	mul	y
	add	ax, x1
	mov	di, ax

	mov	cx, x2
	sub	cx, x1
	inc	cx

	mov	al, color

	rep	stosb
	}
}


void _far _cdecl McgaDrawYLine( byte color, word x, word y1, word y2 )
{
	_asm {
	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, MCGA_PIXELPERLINE
	mul	y1
	add	ax, x
	mov	di, ax

	mov	cx, y2
	sub	cx, y1
	inc	cx

	mov	al, color
	}

_loop:
	_asm {
	mov	es:[di], al

	add	di, MCGA_PIXELPERLINE

	loop	_loop
	}
}
