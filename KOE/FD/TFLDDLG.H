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
**  TFieldDlg Class                                                         **
**  ---------------                                                         **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TFieldDlg                                                     **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFLDDLG.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TFLDDLG
#define TFLDDLG

#include "TObjDlg.H"


class TRadioButtons;
class TInputLine;
class TCheckBoxes;
class TLabel;

class TFieldDlg : public TObjDlg
{
public:
	TFieldDlg( const TRect& bounds, tvObject *anOwner );

	TInputLine *length;		TLabel *lengthLabel;
	TInputLine *offset;     TLabel *offsetLabel;

	TCheckBoxes *dumpable;

	TRadioButtons *posSel;	TLabel *posSelLabel;

	TInputLine *track;		TLabel *trackLabel;
	TInputLine *pos;		TLabel *posLabel;

	TRadioButtons *restr;	TLabel *restrLabel;

	void disablePosSel( Boolean disable );
	void disableTrackPos( Boolean disable );
	void disableRestr( Boolean disable );

protected:
	virtual void setupDialog();
};


#endif
