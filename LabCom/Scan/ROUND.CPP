#include "Compiler.H"

#include "Types.H"

#include <Math.H>


int Round( double d )
{
	int i = d;

	if( fabs( (double)i - d ) > 0.5 )
		{
		if( ((double)i - d) < 0 )
			i++;
		else
			i--;
		}

	return i;
}