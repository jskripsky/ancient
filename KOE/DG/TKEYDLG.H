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
**  TKeyDlg Class                                                           **
**  -------------                                                           **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TKeyDlg                                                       **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TKEYDLG.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TKEYDLG
#define TKEYDLG

#include "TObjDlg.H"


class TRadioButtons;
class TListBox;
class TInputLine;
class TLabel;


class TKeyDlg : public TObjDlg
{
public:
	TKeyDlg( const TRect& bounds, tvObject *anOwner );

	TRadioButtons *typeSwitch;

	TListBox *characterBox;
	TInputLine *scanCodeLine; TLabel *scanCodeLineLabel;

	void disableCharacterBox( Boolean disable );
	void disableScanCodeLine( Boolean disable );

protected:
	virtual void setupDialog();
};


#endif
