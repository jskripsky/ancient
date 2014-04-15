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
**  Printer Class                                                           **
**  -------------                                                           **
**                                                                          **
**  Declared classes:                                                       **
**    - Class Printer    												    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: PRINTER.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef PRINTER
#define PRINTER

#include "StrDev.H"

class PaperSpace;

class Printer : public virtual StreamDevice
{
public:
	Printer();

    PaperSpace *getPaperSpace();
	void connectTo( PaperSpace * );


protected:
	PaperSpace *paperSpace;
};


inline void Printer::connectTo( PaperSpace *aPaperSpace )
	{ paperSpace = aPaperSpace; }

inline PaperSpace *Printer::getPaperSpace()
	{ return paperSpace; }


#endif
