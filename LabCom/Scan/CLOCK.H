// Copyright (c) 1995 Juraj Skripsky.
// Revision: 0.5
// Date: xx.11.1995

#ifndef CLOCK
#define CLOCK


#define Uses_TView
#include <TV.H>


class TClockView : public TView
{
public:
	TClockView( TRect& r );
	virtual void draw();
	virtual void update();

private:
	char lastTime[9];
	char curTime[9];
};


#endif
