#include "Compiler.H"

#include "GrphcWnd.H"
#include "Bitmap.H"

#include <Mem.H>

#define kMCGAVRAM	0xA0000000;
const int kMCGAPixelsPerLine = 320;

byte near	oldVideoMode;


TGraphicWindow::TGraphicWindow( TBitmap *bitmap ) :
	fBitmap( bitmap )
{
	SetVideoMode();

	byte grayScalePalette[256][3];
	for( int i = 0; i < 256; i++ )
		for( int c = 0; c < 3; c++ )
			grayScalePalette[i][c] = i / 4;

	SetPalette( grayScalePalette );

	Update();
}


TGraphicWindow::~TGraphicWindow()
{
	RestoreVideoMode();
}


void TGraphicWindow::Update()
{
	int cornerX, cornerY;

	cornerX = (320 - fBitmap->GetWidth()) / 2;
	cornerY = (200 - fBitmap->GetHeight()) / 2;

	if( cornerY < 0 )
		cornerY = 0;

	for( int y = 0; (y < fBitmap->GetHeight()) && (y < 200); y++ )
		{
		byte far *vram = (byte far *)kMCGAVRAM;
		memcpy( &vram[kMCGAPixelsPerLine * (cornerY + y) + cornerX],
			   fBitmap->GetLine( y ), fBitmap->GetWidth() );
		}
}


void TGraphicWindow::SetVideoMode()
{
	asm {
	mov	ah, 0x0F
	int	0x10

	mov	oldVideoMode, al

	mov	al, 0
	mov	cl, 7
	shl	al, cl

	or	al, 0x13

	xor	ah, ah
	int	0x10
	}
}


void TGraphicWindow::RestoreVideoMode()
{
	_asm {
	mov	al, 0
	mov	cl, 7
	shl	al, cl

	or	al, oldVideoMode

	xor	ah, ah
	int	0x10
	}
}


void TGraphicWindow::SetPalette( void far *palette )
{
	_asm {
	xor	bx, bx
	mov	cx, 256
	les	dx, palette

	mov	ax, 0x1012
	int	0x10
	}
}
