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
**  TFormObjDlg Class                                                       **
**  -----------------                                                       **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TFormObjDlg													**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFOBJDLG.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TFOBJDLG
#define TFOBJDLG

#include "TObjDlg.H"


class TRadioButtons;
class TInputLine;
class TCheckBoxes;
class TLabel;
class TListBox;


class TFormObjDlg : public TObjDlg
{
public:
	TFormObjDlg( const TRect& bounds, tvObject *anOwner );

	TLabel *posLabel;

	TInputLine *leftPos;	TLabel *leftPosLabel;
	TInputLine *rightPos;	TLabel *rightPosLabel;

	TInputLine *topPos;		TLabel *topPosLabel;
	TInputLine *bottomPos;	TLabel *bottomPosLabel;

// TFormFieldDlg::
	TListBox *fieldSel;

// TFormTextDlg:
	TListBox *fontSel;

// TFormStaticText:
	TInputLine *textLine;


protected:
	virtual void setupDialog();
};


#endif
