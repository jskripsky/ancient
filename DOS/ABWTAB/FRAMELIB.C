// ****************************
// ***	   Framelibrary	    ***
// ****************************
// ***			    ***
// ****************************

#include "constant.h"


const char line[2][2] = { { 'ƒ', '≥' }, { 'Õ', '∫' } };
const char corner[2][4] = { { '⁄', 'ø', 'Ÿ', '¿' }, { '…', 'ª', 'º', '»' } };

void ScrFrameInput( struct frame *frame, byte x, byte y, char *string, byte minlength, byte maxlength, byte options );

void ScrDrawFrame( struct frame *frame, byte linetype );
void ScrFrameWrite( struct frame *frame, byte x, byte y, const char *string );
void ScrFrameWriteRight( struct frame *frame, byte x, byte y, const char *string );
void ScrFrameWriteCenter( struct frame *frame, byte y, const char *string );
void ScrFrameCharacter( struct frame *frame, byte x, byte y, char character );
void ScrFrameChgColor( struct frame *frame, byte x1, byte y1, byte x2, byte y2, byte destcolor );


void ScrDrawFrame( struct frame *frame, byte linetype )
    {
    byte counter;

    ScrCharacter( frame->x1, frame->y1, corner[linetype][0] );
    ScrCharacter( frame->x2, frame->y1, corner[linetype][1] );
    ScrCharacter( frame->x1, frame->y2, corner[linetype][3] );
    ScrCharacter( frame->x2, frame->y2, corner[linetype][2] );

    for( counter = 0; counter < frame->x2 - frame->x1 - 1; counter++ )
	{
	ScrCharacter( (byte)(frame->x1 + counter + 1), frame->y1, line[linetype][0] );
	ScrCharacter( (byte)(frame->x1 + counter + 1), frame->y2, line[linetype][0] );
	}

    for( counter = 0; counter < frame->y2 - frame->y1 - 1; counter++ )
	{
	ScrCharacter( frame->x1, (byte)(frame->y1 + counter + 1), line[linetype][1] );
	ScrCharacter( frame->x2, (byte)(frame->y1 + counter + 1), line[linetype][1] );
	}

    if( frame->title[0] )
	ScrWriteCenter( frame->x1, frame->x2, frame->y1, frame->title );

    ScrBoxChgColor( frame->x1, frame->y1, frame->x2, frame->y1, frame->color );
    ScrBoxChgColor( frame->x1, frame->y2, frame->x2, frame->y2, frame->color );
    ScrBoxChgColor( frame->x1, frame->y1, frame->x1, frame->y2, frame->color );
    ScrBoxChgColor( frame->x2, frame->y1, frame->x2, frame->y2, frame->color );
    }


void ScrFrameWrite( struct frame *frame, byte x, byte y, const char *string )
    {
    ScrWrite( (byte)(frame->x1 + x + 1), (byte)(frame->y1 + y + 1), string );
    }


void ScrFrameWriteRight( struct frame *frame, byte x, byte y, const char *string )
    {
    ScrWriteRight( (byte)(frame->x1 + x + 1), (byte)(frame->y1 + y + 1), string );
    }


void ScrFrameWriteCenter( struct frame *frame, byte y, const char *string )
    {
    ScrWriteCenter( frame->x1, frame->x2, (byte)(frame->y1 + y + 1), string );
    }


void ScrFrameCharacter( struct frame *frame, byte x, byte y, char character )
    {
    ScrCharacter( (byte)(frame->x1 + x + 1), (byte)(frame->y1 + y + 1), character );
    }


void ScrFrameChgColor( struct frame *frame, byte x1, byte y1, byte x2, byte y2, byte destcolor )
    {
    ScrBoxChgColor( (byte)(frame->x1 + x1 + 1), (byte)(frame->y1 + y1 + 1), (byte)(frame->x1 + x2 + 1), (byte)(frame->y1 + y2 + 1), destcolor );
    }


void ScrFrameInput( struct frame *frame, byte x, byte y, char *string, byte minlength, byte maxlength, byte options )
    {
    byte pos = 0;
    word key;
    byte asciikey;
    byte counter;


    for( ; ; )
	{
	ScrCharFill( (byte)(frame->x1 + x + 1), (byte)(frame->y1 + y + 1), maxlength, 0 );
	ScrWrite( (byte)(frame->x1 + x + 1), (byte)(frame->y1 + y + 1), string );
	ScrSetCursor( (byte)(frame->x1 + x + 1 + pos), (byte)(frame->y1 + y + 1)	);
	key = BiosGetKey();

	switch( key )
	    {
	    case KBENTER:
		if( pos < minlength )
		    break;
		ScrSetCursor( 0, 25 );
		return;

	    case KBBACKSPACE:
		if( pos == 0 )
		    break;

		string[pos - 1] = 0;
		pos--;
		break;

	    default:
		if( pos == maxlength )
		    break;

		asciikey = (byte)key;

		if( options == NUM )
		    if( asciikey > '9' || asciikey < '0')
			break;

		if( pos == 0 )
		    for( counter = 0; counter < maxlength; counter++ )
			string[counter] = 0;
		if( asciikey > 'Z' )
		    switch( asciikey )
			{
			case (byte)'Ñ':
			    asciikey = 'é';
			    break;

			case (byte)'î':
			    asciikey = 'ô';
			    break;

			case (byte)'Å':
			    asciikey = 'ö';
			    break;

			default:
			    asciikey = asciikey & 0xDF;
			}

		string[pos] = asciikey;
		string[pos + 1] = 0;
		pos++;
	    }
	}
    }
