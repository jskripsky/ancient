/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Stone Object Include File   			*/
/*												*/
/*----------------------------------------------*/

#ifndef STONE
#define STONE

#include "Figures\Static.H"
#include "Figures\Movable.H"


class Stone : public Static, public Movable
{
public:
	virtual FigureId id();

	virtual void live();
	virtual Boolean collideWith( Figure * );

protected:
	Boolean isFalling;

	virtual Boolean isFreeForFall( Square * );
};


inline FigureId Stone::id()
	{ return idStone; }

#endif
