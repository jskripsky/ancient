/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Explosive Object File   				*/
/*												*/
/*----------------------------------------------*/

#include "Figures\Explosiv.H"


Boolean Explosive::collideWith( Figure *f )
{
	switch( f->id() )
		{
		case idStone:
		case idPlayer:
			delete f;
			explode();
			return True;

		default:
			return False;
		}
}


void Explosive::explode()
{
	// Yet to be implemented!!!!!
}
