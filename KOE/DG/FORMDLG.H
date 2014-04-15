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
**  Declared classes:                                                       **
**    - Class FormDialog													**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: FORMDLG.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef FORMDLG
#define FORMDLG

#include "FormDev.H"
#include "Dialog.H"


class FormDialog : public FormDevice, public Dialog
{
public:
	FormDialog( char *fileName );
	FormDialog( int port );

};


#endif
