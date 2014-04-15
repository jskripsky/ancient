/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Explosive Object Include File   		*/
/*												*/
/*----------------------------------------------*/

#ifndef EXPLOSIVE
#define EXPLOSIVE

#include "Figure.H"


class Explosive : virtual public Figure
{
public:
	virtual Boolean collideWith( Figure * );
	virtual void explode();
};

#endif
