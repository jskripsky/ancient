/*****************************************************************************
**                                                                          **
**                                                                          **
**  Form Designer                                                           **
**  =============                                                           **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  FormPrinter Class                                                       **
**  -----------------                                                       **
**                                                                          **
**  Declared classes:                                                       **
**    - Class FormPrinter 											        **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: FRMPRN.H                                                   **
**                                                                          **
*****************************************************************************/

#ifndef FRMPRN
#define FRMPRN

#include "FormDev.H"
#include "Printer.H"

#define normalBlock	0
#define fieldBlock	1


class FormPrinter : public FormDevice, public Printer
{
public:
	FormPrinter( char *fileName );
	FormPrinter( int port );

};


#endif
