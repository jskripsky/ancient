/*----------------------------------------------*/
/*                                  			*/
/*		Boulder Dash 1.0   				    	*/
/*												*/
/*		Distance Object File   					*/
/*												*/
/*----------------------------------------------*/

#include "Distance.H"


Distance::Distance( Direction d )
{
	switch( d )
		{
		case upLeft:
		case up:
		case upRight:
			y = 1;
			break;

		case left:
		case noDirection:
		case right:
			y = 0;
			break;

		case downLeft:
		case down:
		case downRight:
			y = -1;
			break;
		}

	switch( d )
		{
		case upLeft:
		case left:
		case downLeft:
			x = -1;
			break;

		case up:
		case noDirection:
		case down:
			x = 0;
			break;

		case upRight:
		case right:
		case downRight:
			y = 1;
			break;
		}
}


Direction Distance::direction()
{
	Direction d;

	switch( y )
		{
		case -1:
			d = down;

		case 0:
			d = noDirection;

		case 1:
			d = up;
		}

	d = (Direction)(d + x);
	return d;
}


void Distance::rotate( Direction d, Rotation r )
{
	switch( r )
		{
		case half:
			x = -x;
			y = -y;
			break;

		case quarter:
			rotate( d, eighth );
			rotate( d, eighth );
			break;

		case eighth:
			switch( d )
				{
					case left:
						switch( y )
							{
								case -1:
									switch( x )
										{
											case -1:
												x = 0;
												break;
											case 0:
												x = 1;
												break;
											case 1:
												y = 0;
												break;
										}
									break;

								case 0:
									switch( x )
										{
											case -1:
												y = -1;
												break;
											case 1:
												y = 1;
												break;
										}
									break;

								case 1:
									switch( x )
										{
											case -1:
												y = 0;
												break;
											case 0:
												x = -1;
												break;
											case 1:
												x = 0;
												break;
										}
									break;
							}
						break;

					case right:
						switch( y )
							{
								case -1:
									switch( x )
										{
											case -1:
												y = 0;
												break;
											case 0:
												x = -1;
												break;
											case 1:
												x = 0;
												break;
										}
									break;

								case 0:
									switch( x )
										{
											case -1:
												y = 1;
												break;
											case 1:
												y = -1;
												break;
										}
									break;

								case 1:
									switch( x )
										{
											case -1:
												x = 0;
												break;
											case 0:
												x = 1;
												break;
											case 1:
												y = 0;
												break;
										}
									break;
							}
						break;
				}
			break;
		}

}