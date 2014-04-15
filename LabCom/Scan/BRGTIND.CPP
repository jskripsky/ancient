#include "Compiler.H"

#include "Types.H"
#include "BrgtInd.H"

#include <String.H>

#define cpBrightnessIndicator "\x06"
const char fillString[] = " °±²Û";
const char arrowChar = '';
const ushort numberOfShades = 5;


TBrightnessIndicator::TBrightnessIndicator( const TRect& b, ushort aRange ) :
	TView( b ),
	range( aRange ),
	position( 0 )
{
}


void TBrightnessIndicator::setData( void *rec )
{
	position = *(ushort *)rec;
	drawView();
}


void TBrightnessIndicator::getData( void *rec )
{
	*(ushort *)rec = position;
	drawView();
}


void TBrightnessIndicator::draw()
{
	ushort color = getColor(1);

	TDrawBuffer b;
	b.moveChar( 0, ' ', color, size.x );
	for( int i = 0; i < numberOfShades; i++ )
		b.moveChar( size.x * i / numberOfShades,
				  fillString[i], color,
				  size.x / numberOfShades );

	writeLine( 0, 0, size.x, 1, b );

	b.moveChar( 0, ' ', color, size.x );
	b.moveChar( size.x - 1 - Round(
		((double)position / (double)range) * (double)(size.x - 1) ),
		arrowChar, color, 1 );

	writeLine( 0, 1, size.x, 1, b );
}


TPalette& TBrightnessIndicator::getPalette() const
{
	static TPalette palette( cpBrightnessIndicator,
		sizeof( cpBrightnessIndicator ) - 1 );
	return palette;
}
