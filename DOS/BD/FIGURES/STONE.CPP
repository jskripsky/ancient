/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Stone Object File   					*/
/*												*/
/*----------------------------------------------*/

#include "Figures\Stone.H"
#include "Square.H"


void Stone::live()
{
	Square *s = squareAt( Direction( down ) );

	if( isFalling )
		{
		if( isFreeForFall( s ) )
			moveTo( s );
		else
			isFalling = False;
		}
	else
		if( s->isEmpty() )
			{
			moveTo( s );
			isFalling = True;
			}

	// Yet to be implemented: Stone on single Stone (rolls down).
}


Boolean Stone::collideWith( Figure *f )
{
	switch( f->id() )
		{
		case idSpiral:
		case idButterfly:
			square->placeFigure( f );
			f->explode();
			delete this;
			return True;

		case idPlayer:
			// Yet to be implemented!!!!!!
			return True;

		default:
			return False;
		}
}


Boolean Stone::isFreeForFall( Square *s )
{
	if( s->isEmpty() ||
		s->figure()->id() == idPlayer ||
		s->figure()->id() == idSpiral ||
		s->figure()->id() == idButterfly )
		return True;
	else
		return False;
}
