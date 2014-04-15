#ifndef PLOTARM
#define PLOTARM

#include "Types.H"

/*
   This Object doesn't adopt the TVoltageOutputModule object.
*/

#include <Time.H>

class TVoltageOutputModule;

class TPlotterArm
{
public:
	enum EDirection { kPositive, kNegative };

public:
	TPlotterArm( TVoltageOutputModule *, EDirection d = kPositive );

	void MoveTo( double, EBoolean asynchronously = kFalse );
	EBoolean IsInPosition();
	double GetPosition();

	double GetResolution();

protected:
	double CalculateMoveDuration( double distance );

	TVoltageOutputModule *fModule;

	EDirection fDirection;

	EBoolean fInPosition;
	clock_t fMoveStartTime;
	double fMoveDuration;
};

#endif