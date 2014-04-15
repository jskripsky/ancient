// Copyright (c) 1995 Juraj Skripsky.
// Revision: 0.5
// Date: xx.11.1995

#ifndef ABOUTBOX
#define ABOUTBOX

#define Uses_TDialog
#include <TV.H>


/*
*/

class TAboutBox : public TDialog
{
public:
	TAboutBox();

protected:
	virtual void setState( ushort aState, Boolean enable );
};

#endif