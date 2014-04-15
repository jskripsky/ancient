/*== include ===============================================================*/

#include <stdio.h>
#include <stdlib.h>

/*== prototype =============================================================*/

#define TRUE		    1
#define FALSE		    0

#define OK		    0
#define ERROR		    1

#define MAX_PARAMS	    1
#define MIN_PARAMS	    1

/*== typedef ===============================================================*/

typedef unsigned char	    byte;
typedef unsigned int	    word;
typedef unsigned long int   dword;

typedef signed long int     sdword;
typedef unsigned char	    bool;
typedef unsigned int	    fhandle;

/*== vars ==================================================================*/

byte			    errorlevel = 0;

byte			    counter;
byte			    pointpos;

byte			    date[3];
char			    filename[13];

char			    *temp;

/*== main ==================================================================*/
void main( word argcounter, char *argument[] )
{
    if( argcounter < ( MIN_PARAMS + 1 ) || argcounter > ( MAX_PARAMS + 1 ) )
    {
	printf( "Syntax: RENTODAT Dateiname\n" );
	exit( 1 );
    }

    _asm
    {
	mov	ah, 0x04
	int	0x1A

	mov	bx, offset date

	mov	[bx], dl
	mov	[bx+1], dh
	mov	[bx+2], cl
    }

    for( counter = 0; counter < 3; counter++ )
    {
	filename[counter*3] = date[counter] / 16;
	filename[counter*3+1] = date[counter] & 0x0F;
    }

    for( counter = 0; counter < 8; counter++ )
    {
	filename[counter] += 0x30;
    }

    filename[2] = 45;
    filename[5] = 45;

    pointpos = 0;

    while( !(argument[1][pointpos]==46) )
	pointpos++;

    memcpy( &(filename[8]), &(argument[1][pointpos]), 5 );

    temp = argument[1];

    _asm
    {
	mov	ax, ds
	mov	es, ax

	mov	dx, temp
	mov	di, offset filename

	mov	ah, 0x56
	int	0x21

	jnc	end

	mov	errorlevel, 0x01

	end:
    }





}
