#include "Compiler.H"

#define Uses_TProgram
#define Uses_TDeskTop
#define Uses_TRect
#include "SpeedWnd.H"

#include <DOS.H>


TSpeedWindow::TSpeedWindow( const TRect& bounds, Boolean open,
							ushort duration ) :
	TWindowInit( &TSpeedWindow::initFrame ),
	TWindow( bounds, "", 0 )
{
	palette = wpGrayWindow;
	flags &= ~(wfMove | wfGrow | wfClose | wfZoom);
	setState( sfShadow, False );

	TRect bigBounds = getBounds();
	TRect midBounds = bigBounds;
	TRect smallBounds = midBounds;

	TPoint delta;
	delta.x = (size.x - 3) / 2;
	delta.y = (size.y - 3) / 2;
	smallBounds.grow( -delta.x, -delta.y );
	ushort smallDelta = (size.x < size.y ? delta.x : delta.y);
	midBounds.grow( -smallDelta, -smallDelta );

	ushort bigDelta = (size.x > size.y ? delta.x : delta.y);
	ushort rate = duration / bigDelta;

	if( open )
		locate( smallBounds );

	TProgram::deskTop->insert( this );
	TProgram::deskTop->unlock();

	if( open )
		{
		while( grow( midBounds ) )
			rate; //delay( rate );

		while( grow( bigBounds ) )
			rate; //delay( rate );
		}
	else
		{
		while( grow( midBounds ) )
			rate; //delay( rate );

		while( grow( smallBounds ) )
			rate; //delay( rate );
		}
}


TSpeedWindow::~TSpeedWindow()
{
	hide();
	TProgram::deskTop->remove( this );
}


Boolean TSpeedWindow::grow( TRect& endBounds )
{
	TRect bounds = getBounds();
	if( bounds == endBounds )
		return False;

	int x, y;
	if( endBounds.a.x == bounds.a.x )
		x = 0;
	else
		x = (endBounds.a.x < bounds.a.x ? 1 : -1 );

	if( endBounds.a.y == bounds.a.y )
		y = 0;
	else
		y = (endBounds.a.y < bounds.a.y ? 1 : -1 );

	bounds.grow( x, y );
	locate( bounds );
	return True;
}


void TSpeedWindow::sizeLimits( TPoint& min, TPoint& max )
{
	TWindow::sizeLimits( min, max );
	min.x = min.y = 2;
}
