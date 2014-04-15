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
**  FormSpace Class                                                         **
**  ---------------                                                         **
**                                                                          **
**  Declared classes:                                                       **
**    - Class FormSpace                                                     **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: FRMSPACE.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef FRMSPACE
#define FRMSPACE

#include "EPSpace.H"


class Printer;

class FormSpace : public EpsonPaperSpace
{
public:
	FormSpace( Printer * );

	virtual void printTextField( int index );

	//virtual void moveTo( Pos );     // class OptFormPrinter
	//virtual void move( Pos delta ); // class OptFormPrinter
};


#endif
