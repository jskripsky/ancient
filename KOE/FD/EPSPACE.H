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
**  EpsonPaperSpace Class                                                   **
**  ---------------------                                                   **
**                                                                          **
**  Declared classes:                                                       **
**    - Class EpsonPaperSpace                                               **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: EPSPACE.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef EPSPACE
#define EPSPACE

#include "PSpace.H"


class Printer;

class EpsonPaperSpace : public PaperSpace
{
public:
	EpsonPaperSpace( Printer * );

	virtual void moveTo( Pos );     // class OptFormPrinter: opt. override
	virtual void move( Pos delta ); // class OptFormPrinter: opt. override

	virtual void setFont( int aFont );
	virtual void writeText( char *text );

	virtual void formFeed();

	virtual PrecPos getPrecTextMetrics( int font, int length );

protected:
	virtual void escape();
	virtual void nul();

	virtual void setHTabulator( unsigned char );
	virtual void hTabulator();

	unsigned char hTabPos;

	virtual void lineFeed();
	virtual void carriageReturn();

	virtual void lineFeed180th( unsigned char );

	virtual void enableBold( Boolean enable = True );
	virtual void enableCompressed( Boolean enable = True );

	Boolean bold;
	Boolean compressed;


public:
	static Pos getTextMetrics( int font, int length );
	static PrecPos getCharMetrics( int font );
	static TNSCollection *getFontTitles();
};


#endif
