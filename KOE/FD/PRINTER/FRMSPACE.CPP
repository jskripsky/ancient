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
**  Defined classes:                                                        **
**    - Class FormSpace                                                     **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: FRMSPACE.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#include "FrmSpace.H"
#include "FrmPrn.H"


FormSpace::FormSpace( Printer *aPrinter ) :
	EpsonPaperSpace( aPrinter )
	{}


void FormSpace::printTextField( int index )
{
	printer->writeByte( 0xFE );
	printer->writeByte( index );
}
