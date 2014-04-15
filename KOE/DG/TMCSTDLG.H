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
**  TMCRSettingsDlg Class                                                   **
**  ---------------------                                                   **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TMCRSettingsDlg											 	**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TMCSTDLG.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TMCSTDLG
#define TMCSTDLG

#include "TSTObDlg.H"
#include "tvMCRSet.H"


class TInputLine;
class TCheckBoxes;
class TRadioButtons;


class TMCRSettingsDlg : public TStaticTitleObjDlg
{
public:
	TMCRSettingsDlg( const TRect& bounds, tvObject *anOwner );

	TRadioButtons *typeSwitch;

	TCheckBoxes *trackSwitches;

protected:
	virtual void setupDialog();
};


#endif
