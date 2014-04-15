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
**  Defined classes:                                                        **
**    - Class FormPrinter 											        **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: FRMPRN.CPP                                                 **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TNSCollection
#include "FrmPrn.H"
#include "FrmSpace.H"
#include "FormObj.H"

#include <FStream.H>
#include <StdLib.H>
#include <String.H>


FormPrinter::FormPrinter( int port ) :
	StreamDevice( port )
{
}


FormPrinter::FormPrinter( char *fileName ) :
	StreamDevice( fileName )
{
}
