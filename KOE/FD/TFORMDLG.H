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
**  TFormFldDlg Class                                                       **
**  -----------------                                                       **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TFormFldDlg                                                   **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFORMDLG.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TFORMDLG
#define TFORMDLG

#include "TFoldDlg.H"


class TRadioButtons;
class TInputLine;

class TFormFldDlg : public TFolderDlg
{
public:
	TFormFldDlg( const TRect& bounds, tvObject *anOwner );

	TRadioButtons *typeSwitch;
	TInputLine *formNumber;

protected:
	virtual void addTitleLine( int y );
};


#endif
