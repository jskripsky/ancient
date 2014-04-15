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
**  TSingle-, TDoubleFieldDlg Classes                                       **
**  ---------------------------------                                       **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TSingleFieldDlg                                               **
**    - Class TDoubleFieldDlg                                               **
**                                                                          **
**                                                                          **
**  Module Name: TSFLDDLG.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TSFLDDLG
#define TSFLDDLG

#include "TFldDlg.H"

class TInputLine;
class TListBox;
class TCheckBoxes;


class TSingleFieldDlg : public TFieldDlg
{
public:
	TSingleFieldDlg( const TRect& bounds, tvObject *anOwner );

	TListBox *dataFieldSel;

	TInputLine *startLine;
	TInputLine *endLine;

	TCheckBoxes *numericBox;

protected:
	virtual void addFieldControls();
};


class TDoubleFieldDlg : public TFieldDlg
{
public:
	TDoubleFieldDlg( const TRect& bounds, tvObject *anOwner );

	TListBox *dataFieldSel[2];
	TInputLine *lengthLine;

protected:
	virtual void addFieldControls();
};


#endif
