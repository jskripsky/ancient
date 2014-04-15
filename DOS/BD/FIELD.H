/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		PlayingField Object Include File		*/
/*												*/
/*----------------------------------------------*/

#ifndef FIELD
#define FIELD

#include "Defs.H"
#include "Directio.H"
#include "Square.H"


class PlayingField
{
public:
	PlayingField();

	Square *squareAt( Direction );
	void squaresAt( ushort number, Direction *, Square * );

protected:
	ushort width, length;
	Square **squares;
};

#endif