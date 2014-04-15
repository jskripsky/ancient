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
**  TDialogDlg Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TDialogDlg                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TDLGDLG.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TDLGDLG
#define TDLGDLG

#include "TFoldDlg.H"


class TRadioButtons;
class TInputLine;

class TDialogDlg : public TFolderDlg
{
public:
	TDialogDlg( const TRect& bounds, tvObject *anOwner );

	TInputLine *numberLine;
	TRadioButtons *keySwitch;

protected:
	virtual TListBox *createListBox( TScrollBar * );
	virtual TScrollBar *createScrollBar();

	virtual void addTitleLine( int y );
};


#endif
