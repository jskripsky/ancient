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
#include "tvField.H"


class TInputLine;
class TListBox;


class TFieldDlg : public TObjDlg
{
public:
	TFieldDlg( const TRect& bounds, tvObject *anOwner );

	TInputLine *start;
	TInputLine *end;

	struct KeyLine
		{
		TListBox *keySel;
		TInputLine *timesLine;
		} keyLines[2][numDistinctKeys];

protected:
	virtual void setupDialog();

	virtual void addFieldControls() = 0;

	virtual void addDataFieldSelection( TListBox **sel, char *label, int y );
	virtual void addKeyLine( KeyLine *keyLine, TPoint p );
};


#endif
