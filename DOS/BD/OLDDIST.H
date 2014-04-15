/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Distance Object Include File   			*/
/*												*/
/*----------------------------------------------*/

#ifndef DISTANCE
#define DISTANCE

#include "Defs.H"


enum Direction
{
	upLeft, up, upRight,
	left, noDirection, right,
	downLeft, down, downRight
};


enum Rotation
{
	half, quarter,
	eighth
};


class Distance
{
public:
	short x, y;

	Distance( short aX = 0, short aY = 0 ) :
		x( aX > 0 ? 1 : 0 ),
		y( aY > 0 ? 1 : 0 )
		{ }

	Distance( Direction dir );

	Direction direction();
	void rotate( Direction, Rotation r = quarter );
};

#endif
