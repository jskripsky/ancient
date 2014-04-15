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
**  TFormTextFieldDlg Class                                                 **
**  -----------------------                                                 **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TFormTextFieldDlg												**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFTFDLG.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TFTFDLG
#define TFTFDLG

#include "TFFldDlg.H"
#include "TFTxtDlg.H"


class TFormTextFieldDlg : public TFormFieldDlg, public TFormTextDlg
{
public:
	TFormTextFieldDlg( const TRect& bounds, tvObject *anOwner );

protected:
	virtual void setupDialog();
};


#endif
