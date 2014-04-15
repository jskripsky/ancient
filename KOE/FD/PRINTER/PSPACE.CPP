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
**  PaperSpace Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Defined classes:                                                        **
**    - Class PaperSpace                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: PSPACE.CPP                                                 **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TNSCollection
#include "PSpace.H"
#include "Printer.H"


PaperSpace::PaperSpace( Printer *aPrinter ) :
	printer( aPrinter )
{
	printer->connectTo( this );
	origin.x = origin.y = 0;
	pos = origin;
}


PaperSpace::~PaperSpace()
{
}


Pos PaperSpace::getPos()
{
	Pos aPos;

	aPos.x = convertToMMeters( pos.x );
	aPos.y = convertToMMeters( pos.y );
	return aPos;
}


int PaperSpace::convertToMMeters( long PUnits )
{
	int MMeters = (PUnits * 254 / 360);

	if( ((PUnits * 254 / 36) - (10 * MMeters)) >= 5 )
		MMeters++;

	return MMeters;
}


long PaperSpace::convertToPUnits( int MMeters )
{
	long PUnits = (MMeters * 360 / 254);

	if( ((MMeters * 3600 / 254) - (10 * PUnits)) >= 5 )
		PUnits++;

	return PUnits;
}


TNSCollection *PaperSpace::fontTitles = new TNSCollection( 10, 2 );
