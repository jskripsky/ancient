/*****************************************************************************
**                                                                          **
**                                                                          **
**  DOS Form Designer                                                       **
**  =================                                                       **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  TProjectDlg Class                                                       **
**  -----------------                                                       **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TProjectDlg                                                   **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TPROJDLG.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TPROJDLG
#define TPROJDLG

#include "TFoldDlg.H"


class TProjectDlg : public TFolderDlg
{
public:
	TProjectDlg( const TRect& bounds, tvObject *anOwner );

protected:
	virtual void handleEvent( TEvent& event );

	virtual void setupButtons();
	virtual void addGenerateFileButton();
};


#endif
