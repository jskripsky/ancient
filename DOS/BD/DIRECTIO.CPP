/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Direction Object File   				*/
/*												*/
/*----------------------------------------------*/

#include "Directio.H"


void Direction::rotate( DirName d, Rotation r )
{
	if( dir == noDirection )
		return;
	switch( r )
		{
		case half:
			rotate( d, quarter );
			rotate( d, quarter );
			break;

		case quarter:
			rotate( d, eighth );
			rotate( d, eighth );
			break;

		case eighth:
			switch( d )
				{
				case clockwise:
					if( dir == upLeft )
						dir = up;
					else
						dir = (DirName)(dir + 1);
					break;

				case counterclockwise:
					if( dir == up )
						dir = upLeft;
					else
						dir = (DirName)(dir - 1);
					break;
				}
			break;
		}
}


short Direction::x()
{
	switch( dir )
		{
		case upRight:
		case right:
		case downRight:
			return 1;

		case up:
		case noDirection:
		case down:
			return 0;

		case upLeft:
		case left:
		case downLeft:
			return -1;

		default:
			return 0;
		}
}


short Direction::y()
{
	switch( dir )
		{
		case upLeft:
		case up:
		case upRight:
			return 1;

		case left:
		case noDirection:
		case right:
			return 0;

		case downLeft:
		case down:
		case downRight:
			return -1;

		default:
			return 0;
		}
}
