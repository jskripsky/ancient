/*== precompiler, global data ==============================================*/
/*== standard ==============================================================*/
/*== include ===============================================================*/

#include <stdlib.h>	/* memory allocation */
#include <dos.h>	/* interrupt vector manipulation */

/*== define ================================================================*/

#define DosMAlloc	    malloc
#define DosMFree	    free
#define DosGetIntVector	    _dos_getvect
#define DosSetIntVector	    _dos_setvect

#define TRUE		    1
#define FALSE		    0

#define OK		    0
#define ERROR		    1

#define BIOS_DATASEGMENT    0x0040
#define BIOS_TIMEROFFSET    0x006C
#define TIMERPOS	    0x0040006C

#define TIMER_INTERRUPT     0x1C

#define CGA_VRAMSEG	    0xB800

#define SINGLE		    1
#define DOUBLE		    2

/*== typedef ===============================================================*/

typedef unsigned char	    byte;
typedef unsigned int	    word;

typedef unsigned char	    bool;
typedef unsigned int	    fhandle;

/*== prototype =============================================================*/

word _cdecl BiosGetKey( void );
bool _cdecl BiosCheckKeybBuffer( void );
byte _cdecl BiosGetKeybState( void );

void _cdecl CgaSetMode( void );
void _cdecl CgaRestoreMode( void );
void _cdecl CgaClrScr( void );
void _cdecl CgaSetCursor( byte x, byte y );
void _cdecl CgaWrite( byte x, byte y, byte attrib, const char *text );
void _cdecl CgaWriteRight( byte x, byte y, byte attrib, const char *text );
void _cdecl CgaFill( byte x, byte y, byte fill, byte attrib, char character );
void _cdecl CgaCharacter( byte x, byte y, byte attrib, char character );
void _cdecl CgaFrame( byte x1, byte y1, byte x2, byte y2, byte attrib, byte type );

void _cdecl StdGetSpeed( void );
void _cdecl StdWait( word millisec );

void _cdecl StdInitRand( word initnum );
word _cdecl StdRandom( void );

/*== const =================================================================*/

char			    singleframe[6] = { 'Ú', '¿', 'À', 'Ù', 'Ä', '³' };
char			    doubleframe[6] = { 'É', '»', 'È', '¼', 'Í', 'º' };

/*== global variable =======================================================*/

byte			    old_video_mode;
word			    speed_index = 0;
word			    user_init_num = 0;
word			    random_var = 0;

/*== specific ==============================================================*/
/*== define ================================================================*/

#define Time		    0x6F
#define Topbar		    0x67
#define Bottombar	    0x67

#define Dice		    0x6F
#define Stattitle	    0x07

/*== prototype =============================================================*/

void ScreenMask( void );
void _interrupt _far CgaWriteTimer( void );

/*== const =================================================================*/

const char		    title[] = " JS - Dice 1.04 ";

/*== global variable =======================================================*/

struct
{
    word		    sixes;
    float		    average;
    word		    sum;
}			    stats[7];

word			    repetitions;
void (_interrupt _far *oldtimer)( void );
bool			    fastspeed = TRUE;
bool			    fastinit = FALSE;

/*== code ==================================================================*/
/*== main ==================================================================*/

void main( void )
{
    int 		    dec, sign;

    bool		    stop = FALSE;
    bool		    specialmsg = TRUE;
    byte		    randnumber;

    char		    *textpointer;
    char		    temptext[80];

    byte		    counter;
    byte		    subcounter;
    byte		    subsubcounter;

    for( counter = 0; counter < 7; counter++ )
    {
	stats[counter].sixes = 0;
	stats[counter].average = 0;
	stats[counter].sum = 0;
    }

    if( (BiosGetKeybState() & 0x03) )
	fastinit = TRUE;

    StdInitRand( *( word _far *)TIMERPOS );
    StdGetSpeed();
    CgaSetMode();

    ScreenMask();
    oldtimer = DosGetIntVector( TIMER_INTERRUPT );
    DosSetIntVector( TIMER_INTERRUPT, CgaWriteTimer );

    if( BiosGetKey() != 0x3920 )
	fastspeed = FALSE;

    for( repetitions = 0; repetitions < 999; repetitions++ )
    {
	itoa( ( int )(repetitions + 1), temptext, 10 );
	CgaWriteRight( 62, 19, Stattitle, temptext );
	for( counter = 0; counter < 6; counter++ )
	{
	    if( specialmsg )
	    {
		CgaFill( 0, 24, 80, Bottombar, ' ' );
		CgaWrite( 1, 24, Bottombar, "Press escape to stop dicing..." );
		specialmsg = FALSE;
	    }

	    CgaFrame( ( byte )(counter * 9 + 2), 18, ( byte )(counter * 9 + 6), 20, Dice, DOUBLE );
	    randnumber = ( byte )((StdRandom() % 6) + 1);
	    CgaCharacter( ( byte )(counter * 9 + 4), 19, Dice, ( char )(randnumber + 0x30) );

	    if( !fastspeed )
		for( subcounter = 0; subcounter < 100; subcounter++ )
		{
		    randnumber = ( byte )((StdRandom() % 6) + 1);
		    CgaCharacter( ( byte )(counter * 9 + 4), 19, Dice, ( char )(randnumber + 0x30) );
		    StdWait( 10 );
		}

	    if( randnumber == 6 )
		stats[counter].sixes++;
	    stats[counter].sum += ( word )randnumber;
	    stats[counter].average = (( float )(stats[counter].sum)) / (repetitions + 1);

	    itoa( ( int )(stats[counter].sixes), temptext, 10 );
	    CgaWriteRight( ( byte )(counter * 9 + 7), 5, Stattitle, temptext );

	    CgaWriteRight( ( byte )(counter * 9 + 7), 9, Stattitle, "    " );
	    textpointer = fcvt( ( double )stats[counter].average, 2, &dec, &sign );
	    textpointer[4] = textpointer[3];
	    textpointer[3] = textpointer[2];
	    textpointer[2] = textpointer[1];
	    textpointer[1] = '.';
	    CgaWriteRight( ( byte )(counter * 9 + 7), 9, Stattitle, textpointer );

	    itoa( ( int )(stats[counter].sum), temptext, 10 );
	    CgaWriteRight( ( byte )(counter * 9 + 7), 13, Stattitle, temptext );

	    CgaFrame( ( byte )(counter * 9 + 1), 17, ( byte )(counter * 9 + 7), 21, Dice, DOUBLE );
	    CgaCharacter( ( byte )(counter * 9 + 4), 19, Dice, ( char )(randnumber + 0x30) );

	    if( BiosCheckKeybBuffer() )
		if( BiosGetKey() == 0x011B )
		{
		    CgaFill( 0, 24, 80, Bottombar, ' ' );
		    CgaWrite( 1, 24, Bottombar, "Press space to continue or any other key to exit ..." );
		    specialmsg = TRUE;
		    if( BiosGetKey() != 0x3920 )
		    {
			stop = TRUE;
			break;
		    }
		}
	}

	if( stop )
	    break;

	stats[6].sixes = 0;
	stats[6].average = 0;
	stats[6].sum = 0;

	for( counter = 0; counter < 6; counter++ )
	{
	    stats[6].sixes += stats[counter].sixes;
	    stats[6].sum += stats[counter].sum;

	    CgaCharacter( ( byte )(counter * 9 + 4), 19, Dice, ' ' );
	}

	stats[6].average = (( float )(stats[6].sum)) / (6 * (repetitions + 1));

	itoa( ( int )(stats[6].sixes), temptext, 10 );
	CgaWriteRight( 64, 5, Stattitle, temptext );

	CgaWriteRight( 64, 9, Stattitle, "    " );
	textpointer = fcvt( ( double )stats[6].average, 2, &dec, &sign );
	textpointer[4] = textpointer[3];
	textpointer[3] = textpointer[2];
	textpointer[2] = textpointer[1];
	textpointer[1] = '.';
	CgaWriteRight( 64, 9, Stattitle, textpointer );

	itoa( ( int )(stats[6].sum), temptext, 10 );
	CgaWriteRight( 64, 13, Stattitle, temptext );
    }

    if( !stop )
    {
	CgaFill( 0, 24, 80, Bottombar, ' ' );
	CgaWrite( 1, 24, Bottombar, "Press any key to exit ..." );
	BiosGetKey();
    }

    DosSetIntVector( TIMER_INTERRUPT, oldtimer );

    for( subcounter = 0; subcounter < 14; subcounter++ )
    {
	CgaFill( 0, subcounter, 80, Dice, ' ' );
	CgaFill( 0, ( byte )(24 - subcounter), 80, Dice, ' ' );
	if( !fastinit )
	    StdWait( 30 );
    }

    for( subcounter = 0; subcounter < 14; subcounter++ )
    {
	CgaFill( 0, subcounter, 80, 0, ' ' );
	CgaFill( 0, ( byte )(24 - subcounter), 80, 0, ' ' );
	if( !fastinit )
	    StdWait( 30 );
    }

    CgaRestoreMode();

}


/*== specific function =====================================================*/
void ScreenMask( void )
{
    byte		    subcounter;
    byte		    counter;

    CgaSetCursor( 0, 25 );
    CgaClrScr();

    for( subcounter = 0; subcounter < 14; subcounter++ )
    {
	CgaFill( 0, subcounter, 80, Dice, ' ' );
	CgaFill( 0, ( byte )(24 - subcounter), 80, Dice, ' ' );
	if( !fastinit )
	    StdWait( 30 );
    }

    for( subcounter = 0; subcounter < 14; subcounter++ )
    {
	CgaFill( 0, subcounter, 80, 0, ' ' );
	CgaFill( 0, ( byte )(24 - subcounter), 80, 0, ' ' );
	if( !fastinit )
	    StdWait( 30 );
    }

    CgaFill( 0, 0, 80, Topbar, ' ' );

    counter = 0;
    while( title[counter] )
    {
	for( subcounter = (79 - counter); subcounter; subcounter-- )
	{
	    CgaCharacter( ( byte )(counter + subcounter - 1), 0, Topbar, title[counter] );
	    if( !fastinit )
		StdWait( 2 );
	}
	counter++;
    }

    for( subcounter = (79 - counter); subcounter; subcounter-- )
    {
	CgaCharacter( ( byte )(counter + subcounter - 1), 0, Topbar, ' ' );
	if( !fastinit )
	    StdWait( 3 );
    }

    for( counter = 0; counter < 6; counter++ )
    {
	for( subcounter = 0; subcounter < 8; subcounter++ )
	{
	    CgaFrame( ( byte )(counter * 9 + 1), ( byte )(24 - subcounter), ( byte )(counter * 9 + 7), ( byte )(28 - subcounter), Dice, DOUBLE );
	    if( !fastinit )
		StdWait( 30 );
	}
	for( subcounter = 0; subcounter < 8; subcounter++ )
	{
	    CgaFill( 0, ( byte )(29 - subcounter), 80, 0, ' ' );
	    if( !fastinit )
		StdWait( 50 );
	}
    }

    CgaFill( 0, 24, 80, Bottombar, ' ' );
    CgaWrite( 1, 24, Bottombar, "Press space for fast dicing or any other key for slow dicing..." );

    CgaWrite( 1, 3, Stattitle, "Number of sixes:" );
    CgaWrite( 1, 7, Stattitle, "Average Number:" );
    CgaWrite( 1, 11, Stattitle, "Sum of all the Numbers:" );

    CgaWrite( 56, 3, Stattitle, "Totals:" );

    for( counter = 0; counter < 3; counter++ )
    {
	CgaFill( 1, ( byte )(counter * 4 + 4), 52, Stattitle, singleframe[4] );
	CgaFill( 56, ( byte )(counter * 4 + 4), 9, Stattitle, singleframe[4] );
    }

    CgaFrame( 57, 18, 63, 20, Stattitle, SINGLE );

}

void _interrupt _far CgaWriteTimer( void )
{
    _asm
    {
	mov	ax, CGA_VRAMSEG
	mov	es, ax
	mov	di, 0x9C

	mov	bh, Time

	mov	ah, 0x2C
	int	0x21

	mov	dl, 10
	xor	ah, ah
	mov	al, dh
	div	dl

	add	ah, 0x30
	mov	bl, ah

	cmp	es:[di], bx
	je	_timerend

	mov	es:[di], bx
	sub	di, 0x02
	xor	ah, ah
	div	dl
	add	ah, 0x30
	mov	bl, ah
	mov	es:[di], bx
	sub	di, 0x02
	mov	bl, ':'
	mov	es:[di], bx
	sub	di, 0x02

	xor	ah, ah
	mov	al, cl
	div	dl

	add	ah, 0x30
	mov	bl, ah

	cmp	es:[di], bx
	je	_timerend

	mov	es:[di], bx
	sub	di, 0x02
	xor	ah, ah
	div	dl
	add	ah, 0x30
	mov	bl, ah
	mov	es:[di], bx
	sub	di, 0x02
	mov	bl, ':'
	mov	es:[di], bx
	sub	di, 0x02

	xor	ah, ah
	mov	al, ch
	div	dl

	add	ah, 0x30
	mov	bl, ah

	cmp	es:[di], bx
	je	_timerend

	mov	es:[di], bx
	sub	di, 0x02
	xor	ah, ah
	div	dl
	add	ah, 0x30
	mov	bl, ah
	mov	es:[di], bx

	_timerend:
    }
}

/*== standard function =====================================================*/

/*== BIOS - FUNCTIONS ======================================================*/
/*== function BiosGetKey ===================================================*/
word _cdecl BiosGetKey( void )
{
    _asm
    {
	xor	ah, ah
	int	0x16
    }
}

/*== function BiosCheckKeybBuffer ==========================================*/
bool _cdecl BiosCheckKeybBuffer( void )
{
    _asm
    {
	mov	ah, 0x01
	int	0x16

	jnz	_setal

	xor	al, al
	jmp	_end

	_setal:
	mov	al, 0xFF

	_end:
    }
}


/*== function BiosGetKeybState =============================================*/
byte _cdecl BiosGetKeybState( void )
{
    _asm
    {
	mov	ah, 0x02
	int	0x16
    }
}


/*== CGA - FUNCTIONS =======================================================*/
/*== function CgaSetMode ===================================================*/
void _cdecl CgaSetMode( void )
{
    _asm
    {
	mov	ah, 0x0F
	int	0x10

	mov	old_video_mode, al

	xor	ah, al
	mov	al, 0x03

	int	0x10
    }
}

/*== function CgaRestoreMode ===============================================*/
void _cdecl CgaRestoreMode( void )
{
    _asm
    {
	mov	al, old_video_mode

	xor	ah, ah
	int	0x10
    }
}

/*== function CgaClrScr ====================================================*/
void _cdecl CgaClrScr( void )
{
    _asm
    {
	mov	ax, CGA_VRAMSEG
	mov	es, ax
	xor	di, di

	xor	ax, ax

	mov	cx, 0x07D0
	rep	stosw
    }
}

/*== function CgaSetCursor =================================================*/
void _cdecl CgaSetCursor( byte x, byte y )
{
    _asm
    {
	xor	bh, bh
	mov	dl, x
	mov	dh, y

	mov	ah, 0x02
	int	0x10
    }
}

/*== function CgaWrite =====================================================*/
void _cdecl CgaWrite( byte x, byte y, byte attrib, const char *text )
{
    _asm
    {
	mov	ax, CGA_VRAMSEG
	mov	es, ax

	mov	al, 0xA0
	mul	y

	shl	x, 1
	xor	dh, dh
	mov	dl, x
	add	ax, dx

	mov	di, ax

	mov	si, text
	mov	ah, attrib

	mov	al, [si]

	_loop:
	stosw

	inc	si
	mov	al, [si]
	or	al, al

	jnz	_loop
    }
}

/*== function CgaWriteRight ================================================*/
void _cdecl CgaWriteRight( byte x, byte y, byte attrib, const char *text )
{
    byte		    counter;

    counter = 0;
    while( text[counter] )
	counter++;

    CgaWrite( ( byte )(x - counter), y, attrib, text );
}

/*== function CgaCharacter =================================================*/
void _cdecl CgaCharacter( byte x, byte y, byte attrib, char character )
{
    _asm
    {
	mov	ax, CGA_VRAMSEG
	mov	es, ax

	mov	al, 0xA0
	mul	y

	shl	x, 1
	xor	dh, dh
	mov	dl, x
	add	ax, dx

	mov	di, ax

	mov	al, character
	mov	ah, attrib

	mov	es:[di], ax
    }
}

/*== function CgaFill ======================================================*/
void _cdecl CgaFill( byte x, byte y, byte fill, byte attrib, char character )
{
    _asm
    {
	mov	ax, CGA_VRAMSEG
	mov	es, ax

	mov	al, 0xA0
	mul	y

	shl	x, 1
	xor	dh, dh
	mov	dl, x
	add	ax, dx

	mov	di, ax

	mov	al, character
	mov	ah, attrib

	xor	ch, ch
	mov	cl, fill

	rep	stosw
    }
}

/*== function CgaFrame =====================================================*/
void _cdecl CgaFrame( byte x1, byte y1, byte x2, byte y2, byte attrib, byte type )
{
    char		    *frame;
    byte		    counter;

    for( counter = 0; counter < (y2 - y1 + 1); counter++ )
	CgaFill( x1, ( byte )(y1 + counter), ( byte )(x2 - x1 + 1), attrib, ' ' );

    if (type == SINGLE)
	frame = singleframe;
    else
	frame = doubleframe;

    CgaCharacter( x1, y1, attrib, frame[0] );
    CgaCharacter( x2, y1, attrib, frame[1] );
    CgaCharacter( x1, y2, attrib, frame[2] );
    CgaCharacter( x2, y2, attrib, frame[3] );

    CgaFill( ( byte )(x1 + 1), y1, ( byte )(x2 - x1 - 1), attrib, frame[4] );
    CgaFill( ( byte )(x1 + 1), y2, ( byte )(x2 - x1 - 1), attrib, frame[4] );

    for( counter = (y2 - y1 - 1); counter; counter-- )
    {
	CgaCharacter( x1, ( byte )(y1 + counter), attrib, frame[5] );
	CgaCharacter( x2, ( byte )(y1 + counter), attrib, frame[5] );
    }
}


/*== STD - FUNCTIONS =======================================================*/
/*== function StdGetSpeed ==================================================*/
void _cdecl StdGetSpeed( void )
{
    _asm
    {
	mov	ax, BIOS_DATASEGMENT
	mov	es, ax
	mov	di, BIOS_TIMEROFFSET

	_waittick:
	mov	dx, es:[di]

	mov	cx, 0x0040
	_tickloop:
	loop	_tickloop

	cmp	dx, es:[di]
	je	_waittick

	mov	dx, es:[di]
	xor	ax, ax

	_loop:
	mov	cx, 0x0040
	_subloop:
	loop	_subloop

	inc	ax
	cmp	dx, es:[di]
	je	_loop

	mov	dx, 18
	mul	dx

	mov	speed_index, ax
    }
}

/*== function StdWait ======================================================*/
void _cdecl StdWait( word millisec )
{
    _asm
    {
	mov	ax, millisec
	mul	speed_index
	mov	cx, 1000
	div	cx

	mov	millisec, ax

	mov	ax, ds
	mov	es, ax

	lea	di, millisec

	xor	ax, ax

	_loop:
	mov	cx, 0x0040
	_subloop:
	loop	_subloop

	inc	ax
	cmp	ax, es:[di]
	jne	_loop
    }
}

/*== function StdInitRand ==================================================*/
void _cdecl StdInitRand( word initnum )
{
    user_init_num = initnum;
    random_var = 0;
}

/*== function StdRandom ====================================================*/
word _cdecl StdRandom( void )
{
    _asm
    {
	mov	ax, random_var
	mov	cx, 0x43FD
	mul	cx
	mov	bx, ax

	mov	ax, user_init_num
	mov	cx, 0x0003
	mul	cx
	add	bx, ax

	mov	ax, user_init_num
	mov	cx, 0x43FD
	mul	cx
	add	dx, bx

	add	ax, 0x9EC3
	adc	dx, 0x0026

	mov	user_init_num, ax
	mov	random_var, dx

	mov	ax, dx
	and	ah, 0x7F
    }
}
