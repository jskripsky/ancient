#ifndef TSWINDOW
#define TSWINDOW

#define Uses_TWindow
#include <TV.H>


class TSpeedWindow : public TWindow
{
public:
	TSpeedWindow( const TRect& bounds, Boolean open, ushort duration );
	~TSpeedWindow();

protected:
	Boolean grow( TRect& endBounds );

	virtual void sizeLimits( TPoint& min, TPoint& max );
};


#endif
