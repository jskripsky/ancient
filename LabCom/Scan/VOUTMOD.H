#ifndef VOUTMOD
#define VOUTMOD

#include "InOutMod.H"


/*
*/

class TVoltageOutputModule : public TOutputModule
{
public:
	TVoltageOutputModule( TBoard *b );

	void SetVoltage( double );

	double GetVoltage();
	double GetMaxVoltage();
	double GetResolution();
};


#endif