// Copyright (c) 1995 Juraj Skripsky.
// Revision: 0.5
// Date: xx.11.1995

#ifndef BOARD
#define BOARD

#include "Module.H"

#define MAX_NUMBER_OF_MODULES	8


/* This class implements the protocol by which the PC communicates with the
   LabCom Interface.
   It doesn't know anything about the kind of modules plugged in except
   their data direction.
   At the request of an adopted Module object it hands off data to and from
   the physical modules. This class treats all module data as a simple
   byte.
*/

#include <Time.H>

class TBoard
{
public:
	TBoard( EBoolean dumpMode = kFalse );
	virtual ~TBoard();

	void AdoptModule( TModule * );

	int GetData( TModule& );
	void SetData( TModule&, int );

protected:
	EBoolean fDumpMode;

	int fModulesCount;

	clock_t fLastTime;

	TModule *fModules[MAX_NUMBER_OF_MODULES];

	void TransferData();

	byte fData[MAX_NUMBER_OF_MODULES];
	void GetData();
	void SetData();
};

#endif