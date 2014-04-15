#ifndef GRPHCWND
#define GRPHCWND

#include "Types.H"

/* Lifetime = Time during which GraphicWindow is "visible".
*/

class TBitmap;

class TGraphicWindow
{
public:
	TGraphicWindow( TBitmap *bitmap );
	virtual ~TGraphicWindow();

	virtual void Update();

protected:
	void SetVideoMode();
	void RestoreVideoMode();

	void SetPalette( void far *palette );

	TBitmap *fBitmap;
};

#endif