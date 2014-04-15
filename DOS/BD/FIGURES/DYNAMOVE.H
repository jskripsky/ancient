/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		DynamicMoving Object Include File   	*/
/*												*/
/*----------------------------------------------*/

#ifndef DYNAMOVE
#define DYNAMOVE

#include "Figures\Movable.H"


class DynamicMoving : virtual public Movable
{
public:
	virtual void live();

protected:
	Direction direction;

	virtual Boolean isFreeForMove( Square * );
};

#endif
