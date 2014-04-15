/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Direction Object Include File   		*/
/*												*/
/*----------------------------------------------*/

#ifndef DISTANCE
#define DISTANCE

#include "Defs.H"


enum DirName
{
	noDirection,

	up, upRight, right, downRight,
	down, downLeft, left, upLeft,

	clockwise,
	counterclockwise
};


enum Rotation
{
	half, quarter,
	eighth
};


class Direction
{
public:
	Direction( DirName );

	DirName direction();
	void rotate( DirName, Rotation r = quarter );

	short x();
	short y();

private:
	DirName dir;
};


inline Direction::Direction( DirName d ) :
	dir( d )
	{ }


inline DirName Direction::direction()
	{ return dir; }

#endif
