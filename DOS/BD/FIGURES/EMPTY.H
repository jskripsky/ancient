/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Empty Object Include File   			*/
/*												*/
/*----------------------------------------------*/

#ifndef EMPTY
#define EMPTY

#include "Figure.H"


class Empty : virtual public Figure
{
public:
	virtual FigureId id();

	virtual void live();

	virtual Boolean collideWith( Figure * );
	virtual void explode();
};


inline FigureId Empty::id()
	{ return idEmpty; }

inline void Empty::live()
	{ }

inline void Empty::explode()
	{ }

#endif
