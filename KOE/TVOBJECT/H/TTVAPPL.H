/*****************************************************************************
**                                                                          **
**                                                                          **
**  DOS Dialog Generator                                                    **
**  ====================                                                    **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  TtvApplication Class                                                    **
**  --------------------                                                    **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TtvApplication												**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TTVAPPL.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TTVAPPL
#define TTVAPPL

#define Uses_TApplication
#include <TV.H>


class tvMainFolder;
class THeapView;
class TClockView;
class TDeskTop;


class TtvApplication : public TApplication
{
public:
	TtvApplication( tvMainFolder *(*cMainFolder)(),
					char *aMainFolderFileName,
					char *aHelpFileName,
					Boolean (*enableHeapStatus)() =
						&TtvApplication::isHeapStatusToBeEnabled,
					void (*aboutDialog)() = 0 );
	~TtvApplication();

	tvMainFolder *getMainFolder();

protected:
	tvMainFolder *mainFld;

	char *mainFolderFileName;
	char *helpFileName;

	static Boolean isHeapStatusToBeEnabled();

	virtual void getEvent( TEvent& event );
	virtual void idle();

    static TDeskTop *initDeskTop( TRect );

	virtual TPalette& getPalette() const;

	THeapView *heapStatus;
	TClockView *clock;

};


inline tvMainFolder *TtvApplication::getMainFolder()
	{ return mainFld; }


#endif
