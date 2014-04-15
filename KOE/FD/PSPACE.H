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
**  Declared classes:                                                       **
**    - Class PaperSpace                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: PSPACE.H                                                   **
**                                                                          **
*****************************************************************************/

#ifndef PSPACE
#define PSPACE

#include "Pos.H"
#include <TV.H>


class Printer;
class TNSCollection;


struct PrecPos {
	long x;		// PrinterUnits (1/360th inch)
	long y;		// PrinterUnits (1/360th inch)
};


class PaperSpace
{
public:
	PaperSpace( Printer * );
	virtual ~PaperSpace();

	virtual void moveTo( Pos ) = 0;
	virtual void move( Pos delta ) = 0;

	virtual void setFont( int aFont ) = 0;
	virtual void writeText( char * ) = 0;

	virtual void formFeed() = 0;

	virtual PrecPos getPrecTextMetrics( int font, int length ) = 0;

	// The following procedures belong to a abstract metaclass:
	//
	// static Pos getTextMetrics( int font, int length ) = 0;
	// static TNSCollection *getFontTitles() = 0;

	virtual Pos getPos();

	Printer *getPrinter();

protected:
	Printer *printer;

	PrecPos pos;
	PrecPos origin;

	int font;

	long leftStart;
	long topStart;

	static int convertToMMeters( long PUnits );
	static long convertToPUnits( int MMeters );

	static TNSCollection *fontTitles;
};


inline Printer *PaperSpace::getPrinter()
	{ return printer; }


#endif
