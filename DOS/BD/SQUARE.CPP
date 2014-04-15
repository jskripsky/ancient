/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Square Object File   				 	*/
/*												*/
/*----------------------------------------------*/

#include "Square.H"
#include "Field.H"
#include "Figures\Empty.H"


void Square::explode()
{
	fig->explode();
}


void Square::empty()
{
	fig = new Empty();
}


Square *Square::squareAt( Direction d )
{
	// Use field-Object;
	d;
	return 0;
}


void Square::squaresAt( ushort c, Direction *d, Square *s )
{
	// Use field-Object;
	c;
	d;
	s;
}
