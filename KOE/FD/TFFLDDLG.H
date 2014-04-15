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
**  TFormFieldDlg Class                                                     **
**  -------------------                                                     **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TFormFieldDlg												    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFFLDDLG.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TFFLDDLG
#define TFFLDDLG

#include "TFObjDlg.H"


class TListBox;

class TFormFieldDlg : public virtual TFormObjDlg
{
public:
	TFormFieldDlg( const TRect& bounds, tvObject *anOwner );

protected:
	virtual void setupDialog();

	void addFieldSelection( int y );
};


#endif
