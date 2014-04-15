/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Butterfly Object Include File   	    */
/*												*/
/*----------------------------------------------*/

#ifndef BUTTERFL
#define BUTTERFL

#include "Figures\DynaMove.H"
#include "Figures\DiamExpl.H"


class Butterfly : public DynamicMoving, public DiamondExplosive
{
public:
	virtual FigureId id();
};


inline FigureId Butterfly::id()
	{ return idButterfly; }

#endif
