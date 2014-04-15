/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Figure Object Include File				*/
/*												*/
/*----------------------------------------------*/

#ifndef FIGURE
#define FIGURE

#include "Defs.H"
#include "ID.H"
#include "Directio.H"


class Square;

class Figure
{
public:
	virtual FigureId id() = 0;

	virtual void live() = 0;
	void moveTo( Square * );
	void moveTo( Direction );

	virtual Boolean collideWith( Figure * ) = 0;
	virtual void explode() = 0;

protected:
	Square *square;
	Square *squareAt( Direction );
};


inline void Figure::moveTo( Direction d )
	{ moveTo( squareAt( d ) ); }

#endif
