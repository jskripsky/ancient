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
**  FormDialog Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Defined classes:                                                        **
**    - Class FormDialog													**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: FORMDLG.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#include "FormDlg.H"
#include "FormObj.H"


FormDialog::FormDialog( int port ) :
	StreamDevice( port )
{
}


FormDialog::FormDialog( char *fileName ) :
	StreamDevice( fileName )
{
}
