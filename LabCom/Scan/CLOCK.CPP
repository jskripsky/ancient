#include "Compiler.H"

#define Uses_TDrawBuffer

#include "Clock.H"

#include <STRING.H>
#include <TIME.H>


TClockView::TClockView( TRect& r ) :
	TView( r )
{
	strcpy( lastTime, "        " );
	strcpy( curTime, "        " );
}


void TClockView::draw()
{
	TDrawBuffer buf;
	char c = getColor( 2 );

	buf.moveChar( 0, ' ', c, size.x );
	buf.moveStr( 1, curTime, c );
	writeLine( 0, 0, size.x, 1, buf );
}


void TClockView::update()
{
	time_t t = time( 0 );
	char *date = ctime( &t );

	date[19] = '\0';
	strcpy( curTime, &date[11] );

	if( strcmp( lastTime, curTime ) )
		{
		drawView();
		strcpy( lastTime, curTime );
		}
}
