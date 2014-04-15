// ****************************
// *** Statistik - Programm ***
// ***	    Boxlibrary	    ***
// ****************************
// ***			    ***
// ****************************

#include "constant.h"


const char lines[2][2] = { { 'Ä', '³' }, { 'Í', 'º' } };
const char corner[2][4] = { { 'Ú', '¿', 'Ù', 'À' }, { 'É', '»', '¼', 'È' } };
const char titlebar[2][3] = { { 'Ã', 'Ä', '´' }, { 'Ç', 'Ä', '¶' } };
const char joiner[2][2] = { { 'Ã', '´' }, { 'Ì', '¹' } };


void _cdecl BoxDraw( struct box *box );
void _cdecl BoxWrite( struct box *box, byte x, byte y, byte direction, char *string );
void _cdecl BoxClear( struct box *box );
void _cdecl BoxMark( struct box *box, byte x1, byte y1, byte x2, byte y2 );
void _cdecl BoxUnMark( struct box *box, byte x1, byte y1, byte x2, byte y2 );
void _cdecl ButtonMark( struct box *box );
void _cdecl ButtonUnmark( struct box *box );
byte _cdecl ButtonMenu( byte quantity, byte start, struct box *button, void (*standard)( byte choice ) );
void _cdecl CheckList( struct box *box, byte quantity, struct checkline _far *checkline );

void _cdecl BoxDraw( struct box *box )
    {
    byte counter;

    for( counter = 0; counter < box->y2 - box->y1 + 1; counter++ )
	ScrCharFill( (byte)(box->x1), (byte)(box->y1 + counter), (byte)(box->x2 - box->x1 + 1), 0 );

    ScrBoxChgColor( box->x1, box->y1, box->x2, box->y2, box->color );
    ScrCharFill( (byte)(box->x1 + 1), box->y1, (byte)(box->x2 - box->x1 - 1), lines[box->lines][0] );
    ScrCharFill( (byte)(box->x1 + 1), box->y2, (byte)(box->x2 - box->x1 - 1), lines[box->lines][0] );
    for( counter = 0; counter < box->y2 - box->y1 - 1; counter++ )
	{
	ScrCharacter( box->x1, (byte)(box->y1 + counter + 1), lines[box->lines][1] );
	ScrCharacter( box->x2, (byte)(box->y1 + counter + 1), lines[box->lines][1] );
	}

    if( box->joinup )
	{
	ScrCharacter( box->x1, box->y1, joiner[box->lines][0] );
	ScrCharacter( box->x2, box->y1, joiner[box->lines][1] );
	}
    else
	{
	ScrCharacter( box->x1, box->y1, corner[box->lines][0] );
	ScrCharacter( box->x2, box->y1, corner[box->lines][1] );
	}

    if( box->joindown )
	{
	ScrCharacter( box->x1, box->y2, joiner[box->lines][0] );
	ScrCharacter( box->x2, box->y2, joiner[box->lines][1] );
	}
    else
	{
	ScrCharacter( box->x1, box->y2, corner[box->lines][3] );
	ScrCharacter( box->x2, box->y2, corner[box->lines][2] );
	}

    switch( box->type )
	{
	case INFO:
	    ScrCharacter( box->x1, (byte)(box->y1 + 2), titlebar[box->lines][0] );
	    ScrCharFill( (byte)(box->x1 + 1), (byte)(box->y1 + 2), (byte)(box->x2 - box->x1 - 1), titlebar[box->lines][1] );
	    ScrCharacter( box->x2, (byte)(box->y1 + 2), titlebar[box->lines][2] );
	    ScrWriteCenter( box->x1, box->x2, (byte)(box->y1 + 1), box->title );
	    break;
	case BUTTON:
	    ScrWrite( (byte)(box->x1 + 3), (byte)(box->y1 + 1), box->title );
	    break;
	case FRAME:
	    break;
	}
    }

void _cdecl BoxWrite( struct box *box, byte x, byte y, byte direction, char *string )
    {
    if( box->type == INFO )
	y += 2;
    switch( direction )
	{
	case LEFT:
	    ScrWrite( (byte)(box->x1 + 1 + x), (byte)(box->y1 + 1 + y), string );
	    break;
	case RIGHT:
	    ScrWriteRight( (byte)(box->x1 + 1 + x), (byte)(box->y1 + 1 + y), string );
	    break;
	case CENTER:
	    ScrWriteCenter( box->x1, box->x2, (byte)(box->y1 + 1 + y), string );
	}
    }

void _cdecl BoxClear( struct box *box )
    {
    byte counter = 0;

    if( box->type == INFO )
	counter += 2;

    for( ; counter < box->y2 - box->y1 - 1; counter++ )
	ScrCharFill( (byte)(box->x1 + 1), (byte)(box->y1 + counter + 1), (byte)(box->x2 - box->x1 - 1), 0 );

    ScrBoxChgColor( box->x1, box->y1, box->x2, box->y2, box->color );
    }

void _cdecl BoxMark( struct box *box, byte x1, byte y1, byte x2, byte y2 )
    {
    ScrBoxChgColor( (byte)(box->x1 + 1 + x1), (byte)(box->y1 + 1 + y1), (byte)(box->x1 + 1 + x2), (byte)(box->y1 + 1 + y2), box->markcolor );
    }

void _cdecl BoxUnMark( struct box *box, byte x1, byte y1, byte x2, byte y2 )
    {
    ScrBoxChgColor( (byte)(box->x1 + 1 + x1), (byte)(box->y1 + 1 + y1), (byte)(box->x1 + 1 + x2), (byte)(box->y1 + 1 + y2), box->color );
    }

void _cdecl ButtonMark( struct box *box )
    {
    BoxMark( box, 0, 0, (byte)(box->x2 - box->x1 - 2), (byte)(box->y2 - box->y1 - 2) );
    }

void _cdecl ButtonUnMark( struct box *box )
    {
    BoxUnMark( box, 0, 0, (byte)(box->x2 - box->x1 - 2), (byte)(box->y2 - box->y1 - 2) );
    }

byte _cdecl ButtonMenu( byte quantity, byte start, struct box *button, void (*standard)( byte choice ) )
    {
    byte counter;
    word input;
    byte choice = start - 1;

    for( counter = 0; counter < quantity; counter++ )
	BoxDraw( &(button[counter]) );

    do
	{
	ButtonMark( &(button[choice]) );

	if( (void *)(*standard) != NULL )
	    (*standard)( choice );

	input = BiosGetKey();
	ButtonUnMark( &(button[choice]) );

	switch( input )
	    {
	    case KBUP:
		if( choice == 0)
		    choice = quantity - 1;
		else
		    choice--;
		break;
	    case KBDOWN:
		if( choice == quantity - 1)
		    choice = 0;
		else
		    choice++;
		break;
	    }
	}
    while( input != KBENTER );

    return( choice + 1 );
    }

void _cdecl CheckList( struct box *box, byte quantity, struct checkline _far *checkline )
    {
    char string[80];
    byte counter;
    byte subcounter;
    word input;
    byte choice = 0;
    byte topentry = 0;
    byte bottomentry = (box->y2 - box->y1 - 2);
    byte offset = 0;
    bool update = TRUE;

    BoxDraw( box );
    if( box->type == INFO )
	offset = 2;

    do
	{
	if( update )
	    {
	    BoxClear( box );
	    for( counter = 0; counter < (box->y2 - box->y1 - 1 - offset); counter++ )
		{
		if( (counter + topentry) > (quantity - 1) )
		    break;

		BoxWrite( box, 2, (byte)(counter + offset), LEFT, "[ ]" );
		if( checkline[counter + topentry].checkmark )
		    BoxWrite( box, 3, (byte)(counter + offset), LEFT, "X" );

		for( subcounter = 0; subcounter < 80; subcounter++ )
		    string[subcounter] = checkline[counter + topentry].string[subcounter];

		BoxWrite( box, 6, (byte)(counter + offset), LEFT, string );
		}
	    }
	update = FALSE;

	BoxMark( box, 0, (byte)( choice - topentry + offset ), (byte)( box->x2 - box->x1 - 2), (byte)( choice - topentry + offset ) );
	input = BiosGetKey();
	BoxUnMark( box, 0, (byte)( choice - topentry + offset ), (byte)( box->x2 - box->x1 - 2), (byte)( choice - topentry + offset ) );

	switch( input )
	    {
	    case KBUP:
		if( choice != 0)
		    {
		    if( topentry == choice )
			{
			topentry--;
			bottomentry--;
			update = TRUE;
			}
		    choice--;
		    }
		break;
	    case KBDOWN:
		if( choice != (quantity - 1))
		    {
		    if( bottomentry == choice )
			{
			topentry++;
			bottomentry++;
			update = TRUE;
			}
		    choice++;
		    }
		break;
	    case KBSPACE:
		checkline[choice].checkmark = !checkline[choice].checkmark;
		update = TRUE;
		break;
	    }
	}
    while( input != KBENTER );
    }
