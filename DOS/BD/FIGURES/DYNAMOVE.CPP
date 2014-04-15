/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		DynamicMoving Object File   			*/
/*												*/
/*----------------------------------------------*/

#include "Figures\DynaMove.H"
#include "Square.H"


void DynamicMoving::live()
{
	Square *s = squareAt( direction );

	int c = 0;
	while( !isFreeForMove( s ) )
		{
		Direction d = direction;
		d.rotate( clockwise );

		if( isFreeForMove( squareAt( d ) ) )
			direction.rotate( clockwise );
		else
			direction.rotate( counterclockwise );
		s = squareAt( direction );

		c++;
		if( c == 4 )
			return;
		}

	moveTo( s );
}


Boolean DynamicMoving::isFreeForMove( Square *s )
{
	if( s->isEmpty() ||
		s->figure()->id() == idPlayer )
		return True;
	else
		return False;
}
