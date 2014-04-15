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
**  TSystemDlg Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TSystemDlg                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TSYSDLG.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TSYSDLG
#define TSYSDLG

#include "TObjDlg.H"


class TListBox;
class TInputLine;
class TLabel;
class TCheckBoxes;


class TSystemDlg : public TObjDlg
{
public:
	TSystemDlg( const TRect& bounds, tvObject *anOwner );

	TInputLine *IDLine;

	TListBox *characterBox;

	TInputLine *byteLines[4];
	TCheckBoxes *shiftSwitch;
	TInputLine *commentLine;

protected:
	virtual void handleEvent( TEvent& event );

	virtual void setupDialog();
};


#endif
