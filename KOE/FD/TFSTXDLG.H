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
**  TFormStaticTextDlg Class                                                **
**  ------------------------                                                **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TFormStaticTextDlg											**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFSTXDLG.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TFSTXDLG
#define TFSTXDLG

#include "TFTxtDlg.H"


class TInputLine;

class TFormStaticTextDlg : public TFormTextDlg
{
public:
	TFormStaticTextDlg( const TRect& bounds, tvObject *anOwner );

protected:
	virtual void setupDialog();

	virtual void addTextLine( int y );
};


#endif
