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
**  Defined classes:                                                        **
**    - Class TFormTextFieldDlg												**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFTFDLG.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#include "TFTFDlg.H"


TFormTextFieldDlg::TFormTextFieldDlg( const TRect& bounds,
									  tvObject *anOwner ) :
	TWindowInit( &TFormObjDlg::initFrame ),
	TFormObjDlg( bounds, anOwner ),
	TFormFieldDlg( bounds, anOwner ),
	TFormTextDlg( bounds, anOwner )
	{}


void TFormTextFieldDlg::setupDialog()
{
	TFormObjDlg::setupDialog();
	TFormFieldDlg::setupDialog();
	TFormTextDlg::setupDialog();
}
