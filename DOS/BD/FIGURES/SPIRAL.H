/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Spiral Object Include File   			*/
/*												*/
/*----------------------------------------------*/

#ifndef SPIRAL
#define SPIRAL

#include "Figures\DynaMove.H"
#include "Figures\Explosiv.H"


class Spiral : public DynamicMoving, public Explosive
{
public:
	virtual FigureId id();
};


inline FigureId Spiral::id()
	{ return idSpiral; }

#endif
