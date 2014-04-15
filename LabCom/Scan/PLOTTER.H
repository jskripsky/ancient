#ifndef PLOTTER
#define PLOTTER

#include "Types.H"
#include "Point.H"


/*
*/

class TPlotterArm;

class TPlotter
{
public:
	TPlotter( TPlotterArm *xArm, TPlotterArm *yArm );
	virtual ~TPlotter();

	void MovePenTo( TPlotterPoint, EBoolean asynchronously = kFalse );
	EBoolean IsPenInPosition();
	TPlotterPoint GetPenPosition();

	TPlotterPoint GetResolution();

protected:
	TPlotterArm *fXArm, *fYArm;

	TPlotterPoint fPenPosition;
};

#endif