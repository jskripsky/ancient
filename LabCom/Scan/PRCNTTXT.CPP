#include "Compiler.H"

#include "PrcntTxt.H"

#include "Types.H"

#include <String.H>
#include <StdLib.H>
#include <Math.H>

#define cpPercentageText "\x06"
const char percentageString[] = "%";
const char point = '.';


TPercentageText::TPercentageText( const TRect& b,
	ushort aPrecisionDigits ) :
	TView( b ),
	precisionDigits( aPrecisionDigits ),
	percentage( 0.0 )
{
}


void TPercentageText::setData( void *rec )
{
	percentage = *(double *)rec;
	drawView();
}


void TPercentageText::getData( void *rec )
{
	*(double *)rec = percentage;
	drawView();
}


void TPercentageText::draw()
{
	ushort color = getColor(1);

	char *string = new char[size.x + 1];
	itoa( Round( percentage * pow10( precisionDigits ) ), string, 10 );

	if( precisionDigits > 0 )
		{
		memmove( &string[strlen( string ) - precisionDigits + 1],
			    &string[strlen( string ) - precisionDigits],
			    precisionDigits + 1 );
		string[strlen( string ) - 1 - precisionDigits] = point;
		}
	strcat( string, percentageString );
	if( string[0] == point )
		{
		memmove( &string[1], string, strlen( string ) + 1 );
		string[0] = '0';
		}

	TDrawBuffer b;
	b.moveChar( 0, ' ', color, size.x );
	b.moveStr( size.x - 1 - strlen( string ), string, color );
	writeLine( 0, 0, size.x, 1, b );

	delete[] string;
}


TPalette& TPercentageText::getPalette() const
{
	static TPalette palette( cpPercentageText,
		sizeof( cpPercentageText ) - 1 );
	return palette;
}
