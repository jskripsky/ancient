#ifndef POINT
#define POINT


/*
*/

class TPlotterPoint
{
public:
	TPlotterPoint( double x, double y ) :
		fX( x ),
		fY( y )
		{}

	double fX, fY;
};

#endif