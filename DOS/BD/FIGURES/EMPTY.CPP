/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Empty Object File   					*/
/*												*/
/*----------------------------------------------*/

#include "Figures\Empty.H"
#include "Square.H"


Boolean Empty::collideWith( Figure *f )
{
	square->placeFigure( f );
	delete this;
	return True;
}