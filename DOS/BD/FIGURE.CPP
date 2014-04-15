/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Figure Object File   					*/
/*												*/
/*----------------------------------------------*/

#include "Figure.H"
#include "Square.H"


void Figure::moveTo( Square *s )
{
	square->empty();
	square = s;

	if( !collideWith( s->figure() ) )
		s->figure()->collideWith( this );
}


Square *Figure::squareAt( Direction d )
	{ return square->squareAt( d ); }
