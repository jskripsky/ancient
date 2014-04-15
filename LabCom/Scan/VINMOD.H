#ifndef VINMOD
#define VINMOD

#include "InOutMod.H"


/*
*/

class TVoltageInputModule : public TInputModule
{
public:
	TVoltageInputModule( TBoard *b ) :
		TInputModule( b ) {};

	double GetVoltage();

	double GetMaxVoltage();
	double GetResolution();
};


#endif