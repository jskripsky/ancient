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
**  Gadget Classes                                                          **
**  --------------                                                          **
**                                                                          **
**  Defined classes:                                                        **
**    - Class THeapView                                                     **
**    - Class TClockView                                                    **
**                                                                          **
**                                                                          **
**  Module Name: GADGETS.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TDrawBuffer

#include "Gadgets.H"

#include <STRING.H>
#include <STDLIB.H>
#include <CTYPE.H>
#include <STRSTREA.H>
#include <IOMANIP.H>
#include <ALLOC.H>
#include <TIME.H>


THeapView::THeapView( TRect& r ) :
	TView( r )
{
	oldMem = 0;
	newMem = heapSize();
}


void THeapView::draw()
{
	TDrawBuffer buf;
	char c = getColor( 2 );

	buf.moveChar( 0, ' ', c, size.x );
	buf.moveStr( 0, heapStr, c );
	writeLine( 0, 0, size.x, 1, buf );
}


void THeapView::update()
{
	if( (newMem = heapSize()) != oldMem )
		{
		oldMem = newMem;
		drawView();
		}
}


long THeapView::heapSize()
{
	long total = farcoreleft();
	struct farheapinfo heap;
	ostrstream totalStr( heapStr, sizeof heapStr );

	switch( farheapcheck() )
		{
		case _HEAPEMPTY:
			strcpy( heapStr, "     No heap" );
			total = -1;
			break;

		case _HEAPCORRUPT:
			strcpy( heapStr, "Heap corrupt" );
			total = -2;
			break;

		case _HEAPOK:
			heap.ptr = NULL;
			while( farheapwalk( &heap ) != _HEAPEND )
				if( !heap.in_use )
					total += heap.size;
			totalStr << setw( 12 ) << total << ends;
			break;
		}
	return( total );
}


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
