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
**  TAboutDlg Class                                                         **
**  ---------------                                                         **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TAboutDlg                                                     **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TABOUT.H                                                   **
**                                                                          **
*****************************************************************************/

#ifndef TABOUT
#define TABOUT

#define Uses_TDialog
#include <TV.H>


class TAboutDlg : public TDialog
{
public:
	TAboutDlg();

	virtual void setState( ushort aState, Boolean enable );
	virtual void handleEvent( TEvent& );
};


#endif