// Copyright (c) 1995 Juraj Skripsky.
// Revision: 0.5
// Date: xx.11.1995

#ifndef SCANAPP
#define SCANAPP

#define Uses_TApplication
#include <TV.H>


/*
*/

class TScanControlPanel;
class TClockView;

class TScanApplication : public TApplication
{
public:
	TScanApplication( Boolean aDumpMode = False );
	virtual ~TScanApplication();

	Boolean isDumpModeOn()
		{ return dumpMode; }

protected:
	static TDeskTop *initDeskTop( TRect r );
	static TStatusLine *initStatusLine( TRect r );

	virtual void idle();

protected:
	TClockView *clock;

	TScanControlPanel *scanControlPanel;

	Boolean dumpMode;
};

#endif