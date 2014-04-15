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
**  TMCReaderFieldDlg Class                                                 **
**  -----------------------                                                 **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TMCReaderFieldDlg                                             **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TMCRFDLG.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TMCRFDLG
#define TMCRFDLG

#include "TFldDlg.H"

class TInputLine;
class TRadioButtons;
class TCheckBoxes;


class TMCReaderFieldDlg : public TFieldDlg
{
public:
	TMCReaderFieldDlg( const TRect& bounds, tvObject *anOwner );

	TRadioButtons *trackSel;

	TInputLine *startLine;
	TInputLine *endLine;

	TCheckBoxes *numericBox;

protected:
	virtual void addFieldControls();
};


#endif
