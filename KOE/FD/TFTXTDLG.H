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
**  TFormTextDlg Class                                                      **
**  ------------------                                                      **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TFormTextDlg												    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFTXTDLG.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TFTXTDLG
#define TFTXTDLG

#include "TFObjDlg.H"


class TListBox;

class TFormTextDlg : public virtual TFormObjDlg
{
public:
	TFormTextDlg( const TRect& bounds, tvObject *anOwner );

protected:
	virtual void setupDialog();

	void addFontSelection( int y );
};


#endif
