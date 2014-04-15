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
**  Defined classes:                                                        **
**    - Class EpsonPaperSpace                                               **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: EPSPACE.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#include "EPSpace.H"
#include "Printer.H"


#define moveToFont	2


EpsonPaperSpace::EpsonPaperSpace( Printer *aPrinter ) :
	PaperSpace( aPrinter ),
	bold( False ),
	compressed( False )
{
	font = -1;
}


void EpsonPaperSpace::moveTo( Pos newPos )
{
	if( convertToPUnits( newPos.x ) < pos.x )
		carriageReturn();

	int oldFont = font;
	setFont( moveToFont );

	PrecPos character = getCharMetrics( font );
	int lines = (convertToPUnits( newPos.y ) - pos.y) / character.y;

	while( lines )
		{
		lineFeed();
		lines--;
		}

	lineFeed180th( (convertToPUnits( newPos.y ) - pos.y) / 2 );

	int tabPos = (convertToPUnits( newPos.x ) - pos.x) / character.x;
	setHTabulator( tabPos );
	hTabulator();

	setFont( oldFont );
}


void EpsonPaperSpace::move( Pos delta )
{
	delta;
}


void EpsonPaperSpace::setFont( int aFont )
{
	if( aFont == font )
		return;

	escape();
	switch( aFont )
		{
		case 0:
		case 3:
		case 5:
			printer->writeByte( 0x50 );
			break;

		case 1:
		case 4:
		case 6:
			printer->writeByte( 0x4D );
			break;

		case 2:
			printer->writeByte( 0x67 );
			break;
		}

	switch( aFont )
		{
		case 0:
		case 1:
		case 2:
			enableCompressed( False );
			enableBold( False );
			break;

		case 3:
		case 4:
			enableCompressed();
			enableBold( False );
			break;

		case 5:
		case 6:
			enableCompressed( False );
			enableBold();
			break;
		}

	font = aFont;
}


void EpsonPaperSpace::writeText( char *text )
{
	for( int i = 0; text[i]; i++ )
		printer->writeByte( text[i] );
}


PrecPos EpsonPaperSpace::getPrecTextMetrics( int font, int length )
{
	PrecPos aPrecPos = getCharMetrics( font );

	aPrecPos.x *= length;

	return aPrecPos;
}


void EpsonPaperSpace::escape()
{
	printer->writeByte( 0x1B );
}


void EpsonPaperSpace::nul()
{
	printer->writeByte( 0x00 );
}


void EpsonPaperSpace::setHTabulator( unsigned char aPos )
{
	escape();
	printer->writeByte( 0x44 );
	printer->writeByte( aPos );
	nul();

	hTabPos = aPos;
}


void EpsonPaperSpace::hTabulator()
{
	printer->writeByte( 0x09 );

	PrecPos character = getCharMetrics( font );
	pos.x = origin.x + (hTabPos * character.x);
}


void EpsonPaperSpace::lineFeed()
{
	printer->writeByte( 0x0A );
	pos.y += 60;
}


void EpsonPaperSpace::carriageReturn()
{
	printer->writeByte( 0x0D );
	pos.x = origin.x;
}


void EpsonPaperSpace::formFeed()
{
	printer->writeByte( 0x0C );
	pos = origin;
}


void EpsonPaperSpace::lineFeed180th( unsigned char num )
{
	if( num == 0 )
		return;

	escape();
	printer->writeByte( 0x33 );
	printer->writeByte( num );
	pos.x += num * 2;
}


void EpsonPaperSpace::enableBold( Boolean enable )
{
	if( bold == enable )
		return;

	escape();
	if( enable )
		printer->writeByte( 0x45 );
	else
		printer->writeByte( 0x46 );
}


void EpsonPaperSpace::enableCompressed( Boolean enable )
{
	if( compressed == enable )
		return;

	escape();
	if( enable )
		printer->writeByte( 0x0F );
	else
		printer->writeByte( 0x12 );
}


PrecPos EpsonPaperSpace::getCharMetrics( int font )
{
	PrecPos aPos;

	switch( font )
		{
		case 0:
			aPos.x = 36;
			break;

		case 1:
			aPos.x = 30;
			break;

		case 2:
			aPos.x = 24;
			break;

		case 3:
			aPos.x = 21;
			break;

		case 4:
			aPos.x = 18;
			break;

		case 5:
			aPos.x = 36;
			break;

		case 6:
			aPos.x = 30;
			break;
		}
	aPos.y = 60;

	return aPos;
}


Pos EpsonPaperSpace::getTextMetrics( int font, int length )
{
	PrecPos aPrecPos = getCharMetrics( font );

	aPrecPos.x *= length;

	Pos aPos;
	aPos.x = convertToMMeters( aPrecPos.x );
	aPos.y = convertToMMeters( aPrecPos.y );

	return aPos;
}


TNSCollection *EpsonPaperSpace::getFontTitles()
{
	fontTitles->removeAll();

	fontTitles->insert( "10 CPI Normal" );
	fontTitles->insert( "12 CPI Normal" );
	fontTitles->insert( "15 CPI Normal" );
	fontTitles->insert( "17 CPI Kompr." );
	fontTitles->insert( "20 CPI Kompr." );
	fontTitles->insert( "10 CPI Fett" );
	fontTitles->insert( "12 CPI Fett" );

	return fontTitles;
}
