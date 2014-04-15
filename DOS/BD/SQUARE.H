/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Square Object Include File				*/
/*												*/
/*----------------------------------------------*/

#ifndef SQUARE
#define SQUARE

#include "Defs.H"
#include "Directio.H"
#include "Figure.H"


class PlayingField;

class Square
{
public:
	Square();

	Boolean processed;

	Figure *figure();
	void placeFigure( Figure * );
	Boolean isEmpty();

	void empty();
	void explode();

	Square *squareAt( Direction );
	void squaresAt( ushort count, Direction *, Square * );

protected:
	Figure *fig;

	PlayingField *field;
};


inline Figure *Square::figure()
	{ return fig; }

inline void Square::placeFigure( Figure *f )
	{ fig = f; }

inline Boolean Square::isEmpty()
	{ return (fig->id() == idEmpty ? True : False); }

#endif