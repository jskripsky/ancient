/****************************************************************************/
/*									    */
/*			      JS Routine Library			    */
/*									    */
/****************************************************************************/
/*									    */
/*									    */
/*									    */
/*									    */
/*									    */
/*									    */
/*									    */
/*									    */
/****************************************************************************/

/*== define ================================================================*/

#define TRUE		    1
#define FALSE		    0

#define OK		    0
#define ERROR		    1

#define DOS_ATTRIB_NORMAL   0x00
#define DOS_ATTRIB_RDONLY   0x01
#define DOS_ATTRIB_HIDDEN   0x02
#define DOS_ATTRIB_SYSTEM   0x04
#define DOS_ATTRIB_VOLID    0x08
#define DOS_ATTRIB_SUBDIR   0x10
#define DOS_ATTRIB_ARCH	    0x20

#define DOS_ACCESS_RDONLY   0x00
#define DOS_ACCESS_WRONLY   0x01
#define DOS_ACCESS_RDWR	    0x02

#define DOS_ACCESS_SH_COMPAT	0x00
#define DOS_ACCESS_SH_DENYRDWR	0x10
#define DOS_ACCESS_SH_DENYWR	0x20
#define DOS_ACCESS_SH_DENYRD	0x30
#define DOS_ACCESS_SH_DENYNO	0x40

#define DOS_ACCESS_NOCHILD  0x80

#define DOS_DIR_ENTRYSIZE   14

#define MCGA_VRAMSEG	    0xA000
#define MCGA_TRANSCOLORBIT  0x80
#define MCGA_FONTCHARSET    0x60
#define MCGA_FONTASCIIDIF   0x20

#define BIOS_DATASEGMENT    0x0040
#define BIOS_TIMEROFFSET    0x006C

/*== typedef ===============================================================*/

typedef unsigned char	    byte;
typedef unsigned int	    word;
typedef unsigned long int   dword;

typedef signed long int     sdword;
typedef unsigned char	    bool;
typedef unsigned int	    fhandle;

typedef struct image_header image;
typedef struct iclib_header iconlib;
typedef struct font_header  font;

/*== struct ================================================================*/

struct image_header
{
    word		    xdelta;
    word		    ydelta;
};

struct iclib_header
{
    byte		    icon_quantity;
    byte		    xdelta;
    byte		    ydelta;
};

struct font_header
{
    byte		    xdelta;
    byte		    ydelta;
};

struct font_attrib
{
    byte		    darkcolor;
    byte		    color;
    byte		    lightcolor;
    byte		    shadowcolor;
    bool		    shadow;
};

struct dta
{
    byte		    reserved[21];
    byte		    attrib;
    word		    mod_time;
    word		    mod_date;
    dword		    size;
    char		    name[13];
};

struct dir_entry
{
    byte		    attrib;
    char		    name[13];
};

/*== prototype =============================================================*/

word _far _cdecl BiosGetKey( void );
bool _far _cdecl BiosCheckKeybBuffer( void );
byte _far _cdecl BiosGetKeybState( void );

byte _far _cdecl DosGetCurDir( char *path, byte drive );
byte _far _cdecl DosSetCurDir( const char *path );

void _far _cdecl DosInitDta( void );

byte _far _cdecl DosDirEntries( const char *filename, word attrib );
void _far _cdecl DosDir( struct dir_entry *dir, const char *filename, word attrib );

byte _far _cdecl DosCreateFile( fhandle *file, const char *filename, word attrib );
byte _far _cdecl DosOpenFile( fhandle *file, const char *filename, byte access );
byte _far _cdecl DosCloseFile( fhandle file );
byte _far _cdecl DosReadFile( fhandle file, void _far *buffer, word quantity );
byte _far _cdecl DosWriteFile( fhandle file, const void _far *buffer, word quantity );

void _far *_far _cdecl DosAllocFMem( word quantity );
void _far _cdecl DosFreeFMem( void _far *mem );

void _far _cdecl DosSetIntVector( byte intnumber, const void _far *routine );
void _far *_far _cdecl DosReadIntVector( byte intnumber );

void _far _cdecl DosKeepTsr( byte exitcode, word memsize );

void _far _cdecl McgaSetVideoMode( bool savescreen );
void _far _cdecl McgaRestoreVideoMode( bool savescreen );
void _far _cdecl McgaClearScreen( byte color );

void _far _cdecl McgaGetPalette( void _far *palette );
void _far _cdecl McgaSetPalette( const void _far *palette );

void _far _cdecl McgaDrawBox( byte color, word x1, word y1, word x2, word y2 );
void _far _cdecl McgaDrawXLine( byte color, word y, word x1, word x2 );
void _far _cdecl McgaDrawYLine( byte color, word x, word y1, word y2 );
void _far _cdecl McgaDrawLine( byte color, word x1, word y1, word x2, word y2 );
void _far _cdecl McgaChangeColor( byte color1, byte color2, word x1, word y1, word x2, word y2 );

word _far _cdecl McgaLoadImage( image _far **img, const char *filename, bool alloc );
word _far _cdecl McgaSaveImage( image _far *img, const char *filename, bool free );

void _far _cdecl McgaAllocImage( image _far **img, word x1, word y1, word x2, word y2 );
void _far _cdecl McgaGetImage( image _far *img, word x, word y );
void _far _cdecl McgaPutImage( const image _far *img, word x, word y );
void _far _cdecl McgaPrintImage( const image _far *img, word x, word y );
void _far _cdecl McgaPutCutout( const image _far *img, word x1, word y1, word x2, word y2, word x, word y );
void _far _cdecl McgaPrintCutout( const image _far *img, word x1, word y1, word x2, word y2, word x, word y );
void _far _cdecl McgaFreeImage( image _far *img );

word _far _cdecl McgaLoadIconLib( iconlib _far **iclib, const char *filename, bool alloc );
word _far _cdecl McgaSaveIconLib( iconlib _far *iclib, const char *filename, bool free );

void _far _cdecl McgaAllocIconLib( iconlib _far **iclib, byte quantity, byte xdelta, byte ydelta );
void _far _cdecl McgaGetIcon( iconlib _far *iclib, byte number, word x, word y );
void _far _cdecl McgaPutIcon( const iconlib _far *iclib, byte number, word x, word y );
void _far _cdecl McgaPrintIcon( const iconlib _far *iclib, byte number, word x, word y );
void _far _cdecl McgaFreeIconLib( iconlib _far *iclib );

word _far _cdecl McgaLoadFont( font _far **fnt, const char *filename );
void _far _cdecl McgaSetFont( struct font_attrib fnt_attr );
void _far _cdecl McgaOutText( font _far *fnt, word x, word y, const char *string );

void _far _cdecl StdGetSpeed( void );
void _far _cdecl StdWait( word millisec );

void _far _cdecl StdInitRand( word initnum );
word _far _cdecl StdRandom( void );

/*== global variable =======================================================*/

struct dta _near	    dta;

byte _near		    old_video_mode;

struct font_attrib _near    font_attribute = { 0, 0, 0, 0, FALSE };

word _near		    speed_index = 0;

word _near		    user_init_num = 0;
word _near		    random_var = 0;


/*== function ==============================================================*/

/*== BIOS - FUNCTIONS ======================================================*/
/*== function BiosGetKey ===================================================*/
word _far _cdecl BiosGetKey( void )
{
    _asm
    {
	xor	ah, ah
	int	0x16
    }
}

/*== function BiosCheckKeybBuffer ==========================================*/
bool _far _cdecl BiosCheckKeybBuffer( void )
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
byte _far _cdecl BiosGetKeybState( void )
{
    _asm
    {
	mov	ah, 0x02
	int	0x16
    }
}


/*== DOS - FUNCTIONS =======================================================*/
/*== function DosGetCurDir =================================================*/
byte _far _cdecl DosGetCurDir( char *path, byte drive )
{
    _asm
    {
	mov	dl, drive
	mov	si, path

	mov	ah, 0x47
	int	0x21

	mov	al, 0
	adc	al, 0
    }
}

/*== function DosSetCurDir =================================================*/
byte _far _cdecl DosSetCurDir( const char *path )
{
    _asm
    {
	mov	dx, path

	mov	ah, 0x3B
	int	0x21

	mov	al, 0
	adc	al, 0
    }
}

/*== function DosInitDta ===================================================*/
void _far _cdecl DosInitDta( void )
{
    _asm
    {
	mov	dx, OFFSET dta

	mov	ah, 0x1A
	int	0x21
    }
}

/*== function DosDirEntries ================================================*/
byte _far _cdecl DosDirEntries( const char *filename, word attrib )
{
    _asm
    {
	mov	cx, attrib
	mov	dx, filename

	mov	ah, 0x4E
	int	0x21

	mov	cl, 0
	jc	_end

	_nextentry:
	inc	cl

	mov	ah, 0x4F
	int	0x21
	jnc	_nextentry

	_end:
	mov	al, cl
    }
}

/*== function DosDir =======================================================*/
void _far _cdecl DosDir( struct dir_entry *dir, const char *filename, word attrib )
{
    _asm
    {
	mov	di, dir
	mov	si, OFFSET dta

	mov	cx, attrib
	mov	dx, filename

	mov	ah, 0x4E
	int	0x21
	jc	_end

	_nextentry:
	mov	al, [si]dta.attrib
	mov	[di]dir.attrib, al

	xor	bx, bx
	_stringmove:
	mov	al, [si+bx]dta.name
	mov	[di+bx]dir.name, al

	inc	bx
	cmp	bx, 13
	jne	_stringmove

	mov	ah, 0x4F
	int	0x21
	jc	_end

	add	di, DOS_DIR_ENTRYSIZE
	jmp	_nextentry

	_end:
    }
}

/*== function DosCreateFile ================================================*/
byte _far _cdecl DosCreateFile( fhandle *file, const char *filename, word attrib )
{
    _asm
    {
	mov	cx, attrib
	mov	dx, filename

	mov	ah, 0x3C
	int	0x21

	mov	bx, file
	mov	[bx], ax

	mov	al, 0
	adc	al, 0
    }
}

/*== function DosOpenFile ==================================================*/
byte _far _cdecl DosOpenFile( fhandle *file, const char *filename, byte access )
{
    _asm
    {
	mov	dx, filename
	mov	al, access

	mov	ah, 0x3D
	int	0x21

	mov	bx, file
	mov	[bx], ax

	mov	al, 0
	adc	al, 0
    }
}

/*== function DosCloseFile =================================================*/
byte _far _cdecl DosCloseFile( fhandle file )
{
    _asm
    {
	mov	bx, file

	mov	ah, 0x3E
	int	0x21

	mov	al, 0
	adc	al, 0
    }
}

/*== function DosReadFile ==================================================*/
byte _far _cdecl DosReadFile( fhandle file, void _far *buffer, word quantity )
{
    _asm
    {
	push	ds

	mov	bx, file
	mov	cx, quantity
	lds	dx, buffer

	mov	ah, 0x3F
	int	0x21

	pop	ds

	mov	al, 0
	adc	al, 0
    }
}

/*== function DosWriteFile =================================================*/
byte _far _cdecl DosWriteFile( fhandle file, const void _far *buffer, word quantity )
{
    _asm
    {
	push	ds

	mov	bx, file
	mov	cx, quantity
	lds	dx, buffer

	mov	ah, 0x40
	int	0x21

	mov	al, 0
	adc	al, 0

	pop	ds
    }
}

/*== function DosAllocFMem =================================================*/
void _far *_far _cdecl DosAllocFMem( word quantity )
{
    _asm
    {
	mov	bx, quantity
	mov	cl, 0x04
	shr	bx, cl

	test	quantity, 0x0F
	jz	_noremainder

	inc	bx

	_noremainder:
	mov	ah, 0x48
	int	0x21

	mov	dx, ax
	xor	ax, ax
    }
}

/*== function DosFreeFMem ==================================================*/
void _far _cdecl DosFreeFMem( void _far *mem )
{
    _asm
    {
	les	dx, mem

	mov	ah, 0x49
	int	0x21
    }
}

/*== function DosReadIntVector =============================================*/
void _far *_far _cdecl DosReadIntVector( byte intnumber )
{
	_asm
	{
	    mov	    al, intnumber

	    mov	    ah, 0x35
	    int	    0x21

	    mov	    ax, bx
	    mov	    dx, es
	}
}

/*== function DosSetIntVector ==============================================*/
void _far _cdecl DosSetIntVector( byte intnumber, const void _far *routine )
{
	_asm
	{
	    push    ds

	    mov	    al, intnumber
	    lds	    dx, routine

	    mov	    ah, 0x25
	    int	    0x21

	    pop	    ds
	}
}

/*== function DosKeepTsr ===================================================*/
void _far _cdecl DosKeepTsr( byte exitcode, word memsize )
{
    _asm
    {
	mov	al, exitcode
	mov	dx, memsize

	mov	ah, 0x31
	int	0x21
    }
}


/*== MCGA - FUNCTIONS ======================================================*/
/*== function McgaGetVideoMode =============================================*/
void _far _cdecl McgaRestoreVideoMode( bool savescreen )
{
    _asm
    {
	mov	al, savescreen
	mov	cl, 7
	shl	al, cl

	or	al, old_video_mode

	xor	ah, ah
	int	0x10
    }
}

/*== function McgaSetVideoMode =============================================*/
void _far _cdecl McgaSetVideoMode( bool savescreen )
{
    _asm
    {
	mov	ah, 0x0F
	int	0x10

	mov	old_video_mode, al

	mov	al, savescreen
	mov	cl, 7
	shl	al, cl

	or	al, 0x13

	xor	ah, ah
	int	0x10
    }
}

/*== function McgaClearScreen ==============================================*/
void _far _cdecl McgaClearScreen( byte color )
{
    _asm
    {
	mov	ax, MCGA_VRAMSEG
	mov	es, ax
	xor	di, di

	mov	al, color
	mov	ah, al

	mov	cx, 0xFFFF
	rep	stosw
    }
}

/*== function McgaGetPalette ===============================================*/
void _far _cdecl McgaGetPalette( void _far *palette )
{
    _asm
    {
	xor	bx, bx
	mov	cx, 256
	les	dx, palette

	mov	ax, 0x1017
	int	0x10
    }
}

/*== function McgaSetpalette ===============================================*/
void _far _cdecl McgaSetPalette( const void _far *palette )
{
    _asm
    {
	xor	bx, bx
	mov	cx, 256
	les	dx, palette

	mov	ax, 0x1012
	int	0x10
    }
}

/*== function McgaDrawbox ==================================================*/
void _far _cdecl McgaDrawBox( byte color, word x1, word y1, word x2, word y2 )
{
    _asm
    {
	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, 320
	mul	y1
	add	ax, x1
	mov	di, ax

	mov	dx, x2
	sub	dx, x1
	inc	dx

	mov	bx, 320
	sub	bx, dx

	mov	cx, y2
	sub	cx, y1
	inc	cx

	mov	al, color

	_loop:
	mov	si, cx
	mov	cx, dx

	rep	stosb

	mov	cx, si

	add	di, bx

	loop	_loop
    }
}

/*== function McgaDrawXLine ================================================*/
void _far _cdecl McgaDrawXLine( byte color, word y, word x1, word x2 )
{
    _asm
    {
	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, 320
	mul	y
	add	ax, x1
	mov	di, ax

	mov	cx, x2
	sub	cx, x1
	inc	cx

	mov	al, color

	rep	stosb
    }
}

/*== function McgaDrawYLine ================================================*/
void _far _cdecl McgaDrawYLine( byte color, word x, word y1, word y2 )
{
    _asm
    {
	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, 320
	mul	y1
	add	ax, x
	mov	di, ax

	mov	cx, y2
	sub	cx, y1
	inc	cx

	mov	al, color

	_loop:
	mov	es:[di], al

	add	di, 320

	loop	_loop
    }
}

/*== function McgaDrawLine =================================================*/
void _far _cdecl McgaDrawLine( byte color, word x1, word y1, word x2, word y2 )
{
    word xdelta;
    word ydelta;
    word vramoffset;

    _asm
    {
	push	bp

	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, y2
	cmp	ax, y1
	jae	_nolineswap

	xchg	ax, y1
	mov	y2, ax

	mov	ax, x2
	xchg	ax, x1
	mov	x2, ax

	_nolineswap:
	mov	ax, 320
	mul	y1
	add	ax, x1
	mov	vramoffset, ax

	mov	ax, y2
	sub	ax, y1
	mov	ydelta, ax

	mov	ax, x2
	cmp	ax, x1
	jae	_noxdabsolute

	mov	ax, x1
	sub	ax, x2
	mov	xdelta, ax
	mov	si, -1
	jmp	_octantselection

	_noxdabsolute:
	sub	ax, x1
	mov	xdelta, ax
	mov	si, +1

	_octantselection:
	mov	bl, color

	cmp	ax, ydelta
	ja	_octant0

	mov	dx, xdelta
	shl	dx, 1

	mov	cx, ydelta

	mov	di, cx
	shl	di, 1
	sub	di, dx

	mov	ax, dx
	sub	ax, cx

	mov	bp, vramoffset

	inc	cx

	_loop1:

	mov	es:[bp], bl

	cmp	ax, 0
	jl	_advy

	add	bp, si
	sub	ax, di
	add	bp, 320
	loop	_loop1

	jmp	_end

	_advy:
	add	ax, dx
	add	bp, 320
	loop	_loop1

	jmp	_end

	_octant0:
	mov	dx, ydelta
	shl	dx, 1

	mov	cx, xdelta

	mov	di, cx
	shl	di, 1
	sub	di, dx

	mov	ax, dx
	sub	ax, cx

	mov	bp, vramoffset

	inc	cx

	_loop0:
	mov	es:[bp], bl

	cmp	ax, 0
	jl	_advx

	add	bp, 320
	sub	ax, di
	add	bp, si
	loop	_loop0

	jmp	_end

	_advx:
	add	ax, dx
	add	bp, si
	loop	_loop0

	_end:

	pop	bp
    }
}

/*== function McgaChangeColor ==============================================*/
void _far _cdecl McgaChangeColor( byte color1, byte color2, word x1, word y1, word x2, word y2 )
{
    _asm
    {
	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, 320
	mul	y1
	add	ax, x1
	mov	di, ax

	mov	dx, x2
	sub	dx, x1
	inc	dx

	mov	bx, 320
	sub	bx, dx

	mov	cx, y2
	sub	cx, y1
	inc	cx

	mov	al, color1

	_loop:
	mov	si, cx
	mov	cx, dx

	_rep:
	repne	scasb

	test	cx, cx
	jz	_doloop

	mov	al, color2
	dec	di
	mov	es:[di], al
	inc	di

	mov	al, color1

	jmp	_rep

	_doloop:
	mov	cx, si

	add	di, bx

	loop	_loop
    }
}

/*== function McgaLoadImage ================================================*/
word _far _cdecl McgaLoadImage( image _far **img, const char *filename, bool alloc )
{
    fhandle		    file;
    struct image_header	    header;

    if( DosOpenFile( &file, filename, DOS_ACCESS_RDONLY ) )
	return( ERROR );

    if( DosReadFile( file, ( void _far * )&header, sizeof( header ) ) )
	return( ERROR );

    if( alloc )
	McgaAllocImage( img, 0, 0, header.xdelta - 1, header.ydelta - 1 );

    ( *img )->xdelta = header.xdelta;
    ( *img )->ydelta = header.ydelta;

    if( DosReadFile( file, *img + 1, header.xdelta * header.ydelta ) )
	return( ERROR );

    if( DosCloseFile( file ) )
	return( ERROR );

    return( OK );
}

/*== function McgaSaveImage ================================================*/
word _far _cdecl McgaSaveimage( image _far *img, const char *filename, bool free )
{
    fhandle		    file;

    if( DosCreateFile( &file, filename, DOS_ATTRIB_NORMAL ) )
	return( ERROR );

    if( DosWriteFile( file, img, img->xdelta * img->ydelta + sizeof( *img ) ) )
	return( ERROR );

    if( DosCloseFile( file ) )
	return( ERROR );

    if( free )
	McgaFreeImage( img );

    return( OK );
}

/*== function McgaAllocImage ===============================================*/
void _far _cdecl McgaAllocImage( image _far **img, word x1, word y1, word x2, word y2 )
{
    *img = DosAllocFMem( ( x2 - x1 + 1 ) * ( y2 - y1 + 1 ) + sizeof( img ) );

    ( *img )->xdelta = x2 - x1 + 1;
    ( *img )->ydelta = y2 - y1 + 1;
}

/*== function McgaGetImage =================================================*/
void _far _cdecl McgaGetImage( image _far *img, word x, word y )
{
    _asm
    {
	push	ds

	les	di, img

	mov	ax, MCGA_VRAMSEG
	mov	ds, ax

	mov	ax, 320
	mul	y
	add	ax, x
	mov	si, ax

	mov	dx, es:[di]img.xdelta
	mov	cx, es:[di]img.ydelta
	mov	bx, 320
	sub	bx, dx

	add	di, SIZE img

	_loop:
	mov	ax, cx
	mov	cx, dx

	rep	movsb

	mov	cx, ax
	add	si, bx

	loop	_loop

	pop	ds
    }
}

/*== function McgaPutImage =================================================*/
void _far _cdecl McgaPutImage( const image _far *img, word x, word y )
{
    _asm
    {
	push	ds

	lds	si, img

	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, 320
	mul	y
	add	ax, x
	mov	di, ax

	mov	dx, ds:[si]img.xdelta
	mov	cx, ds:[si]img.ydelta
	mov	bx, 320
	sub	bx, dx

	add	si, SIZE img

	_loop:
	mov	ax, cx
	mov	cx, dx

	rep	movsb

	mov	cx, ax
	add	di, bx

	loop	_loop

	pop	ds
    }
}

/*== function McgaPrintImage ===============================================*/
void _far _cdecl McgaPrintImage( const image _far *img, word x, word y )
{
    word		    temp;

    _asm
    {
	push	ds

	lds	si, img

	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, 320
	mul	y
	add	ax, x
	mov	di, ax

	mov	dx, ds:[si]img.xdelta
	mov	cx, ds:[si]img.ydelta
	mov	bx, 320
	sub	bx, dx

	add	si, SIZE img

	_loop1:
	mov	temp, cx
	mov	cx, dx

	_loop2:
	lodsb
	test	al, MCGA_TRANSCOLORBIT
	jnz	_doloop

	mov	es:[di], al

	_doloop:
	inc	di

	loop	_loop2

	mov	cx, temp
	add	di, bx

	loop	_loop1

	pop	ds
    }
}

/*== function McgaPutCutout ================================================*/
void _far _cdecl McgaPutCutout( const image _far *img, word x1, word y1, word x2, word y2, word x, word y )
{
    word		    temp;

    _asm
    {
	push	ds

	lds	si, img

	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, y1
	add	y, ax

	mov	ax, 320
	mul	y
	add	ax, x
	add	ax, x1
	mov	di, ax

	mov	dx, x2
	sub	dx, x1
	inc	dx

	mov	cx, y2
	sub	cx, y1
	inc	cx

	mov	bx, 320
	sub	bx, dx

	mov	ax, ds:[si]img.xdelta
	sub	ax, dx
	mov	temp, ax

	push	dx
	mov	ax, ds:[si]img.xdelta
	mul	y1
	add	ax, x1
	pop	dx

	add	si, ax
	add	si, SIZE img

	_loop:
	mov	ax, cx
	mov	cx, dx

	rep	movsb

	mov	cx, ax
	add	di, bx
	add	si, temp

	loop	_loop

	pop	ds
    }
}

/*== function McgaPrintCutout ==============================================*/
void _far _cdecl McgaPrintCutout( const image _far *img, word x1, word y1, word x2, word y2, word x, word y )
{
    word		    temp1;
    word		    temp2;

    _asm
    {
	push	ds

	lds	si, img

	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, y1
	add	y, ax

	mov	ax, 320
	mul	y
	add	ax, x
	add	ax, x1
	mov	di, ax

	mov	dx, x2
	sub	dx, x1
	inc	dx

	mov	cx, y2
	sub	cx, y1
	inc	cx

	mov	bx, 320
	sub	bx, dx

	mov	ax, ds:[si]img.xdelta
	sub	ax, dx
	mov	temp1, ax

	push	dx
	mov	ax, ds:[si]img.xdelta
	mul	y1
	add	ax, x1
	pop	dx

	add	si, ax
	add	si, SIZE img

	_loop1:
	mov	temp2, cx
	mov	cx, dx

	_loop2:
	lodsb
	test	al, MCGA_TRANSCOLORBIT
	jnz	_doloop

	mov	es:[di], al

	_doloop:
	inc	di

	loop	_loop2

	mov	cx, temp2
	add	di, bx
	add	si, temp1

	loop	_loop1

	pop	ds
    }
}

/*== function McgaFreeImage ================================================*/
void _far _cdecl McgaFreeImage( image _far *img )
{
    DosFreeFMem( img );
}

/*== function McgaLoadIconLib ==============================================*/
word _far _cdecl McgaLoadIconLib( iconlib _far **iclib, const char *filename, bool alloc )
{
    fhandle		    file;
    struct iclib_header	    header;


    if( DosOpenFile( &file, filename, DOS_ACCESS_RDONLY ) )
	return( ERROR );

    if( DosReadFile( file, &header, sizeof( header ) ) )
	return( ERROR );

    if( alloc )
	McgaAllocIconLib( iclib, header.icon_quantity, header.xdelta, header.ydelta );

    ( *iclib )->icon_quantity = header.icon_quantity;
    ( *iclib )->xdelta = header.xdelta;
    ( *iclib )->ydelta = header.ydelta;

    if( DosReadFile( file, *iclib + 1, header.icon_quantity * header.xdelta * header.ydelta ) )
	return( ERROR );

    if( DosCloseFile( file ) )
	return( ERROR );

    return( OK );
}

/*== function McgaSaveIconLib =============================================*/
word _far _cdecl McgaSaveIconLib( iconlib _far *iclib, const char *filename, bool free )
{
    fhandle		    file;

    if( DosCreateFile( &file, filename, DOS_ATTRIB_NORMAL ) )
	return( ERROR );

    if( DosWriteFile( file, iclib, iclib->icon_quantity * iclib->xdelta * iclib->ydelta + sizeof( *iclib ) ) )
	return( ERROR );

    if( DosCloseFile( file ) )
	return( ERROR );

    if( free )
	McgaFreeIconLib( iclib );

    return( OK );
}

/*== function McgaAllocIconLib =============================================*/
void _far _cdecl McgaAllocIconLib( iconlib _far **iclib, byte quantity, byte xdelta, byte ydelta )
{
    *iclib = DosAllocFMem( quantity * xdelta * ydelta + sizeof( iclib ) );

    ( *iclib )->xdelta = xdelta;
    ( *iclib )->ydelta = xdelta;
}

/*== function McgaGetIcon ==================================================*/
void _far _cdecl McgaGetIcon( iconlib _far *iclib, byte number, word x, word y )
{
    _asm
    {
	push	ds

	les	di, iclib

	mov	ax, MCGA_VRAMSEG
	mov	ds, ax

	mov	ax, 320
	mul	y
	add	ax, x
	mov	si, ax

	mov	ch, es:[di]iclib.xdelta
	mov	cl, es:[di]iclib.ydelta
	mov	bx, 320
	sub	bl, ch

	mov	al, number
	xor	ah, ah
	mul	es:[di]iclib.xdelta
	mul	es:[di]iclib.ydelta
	add	di, ax
	add	di, SIZE iclib

	mov	ah, ch
	xor	ch, ch

	_loop:
	mov	al, cl
	mov	cl, ah

	rep	movsb

	mov	cl, al
	add	si, bx

	loop	_loop

	pop	ds
    }
}

/*== function McgaPutIcon =================================================*/
void _far _cdecl McgaPutIcon( const iconlib _far *iclib, byte number, word x, word y )
{
    _asm
    {
	push	ds

	lds	si, iclib

	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, 320
	mul	y
	add	ax, x
	mov	di, ax

	mov	ch, ds:[si]iclib.xdelta
	mov	cl, ds:[si]iclib.ydelta
	mov	bx, 320
	sub	bl, ch

	mov	al, number
	xor	ah, ah
	mul	[si]iclib.xdelta
	mul	[si]iclib.ydelta
	add	si, ax
	add	si, SIZE iclib

	mov	ah, ch
	xor	ch, ch

	_loop:
	mov	al, cl
	mov	cl, ah

	rep	movsb

	mov	cl, al
	add	di, bx

	loop	_loop

	pop	ds
    }
}

/*== function McgaPrintIcon ================================================*/
void _far _cdecl McgaPrintIcon( const iconlib _far *iclib, byte number, word x, word y )
{
    _asm
    {
	push	ds

	lds	si, iclib

	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	mov	ax, 320
	mul	y
	add	ax, x
	mov	di, ax

	mov	ch, ds:[si]iclib.xdelta
	mov	cl, ds:[si]iclib.ydelta
	mov	bx, 320
	sub	bl, ch

	mov	al, number
	xor	ah, ah
	mul	[si]iclib.xdelta
	mul	[si]iclib.ydelta
	add	si, ax
	add	si, SIZE iclib

	mov	dl, ch
	xor	ch, ch

	_loop1:
	mov	ah, cl
	mov	cl, dl

	_loop2:
	lodsb
	test	al, MCGA_TRANSCOLORBIT
	jnz	_doloop

	mov	es:[di], al

	_doloop:
	inc	di

	loop	_loop2

	mov	cl, ah
	add	di, bx

	loop	_loop1

	pop	ds
    }
}

/*== function McgaFreeIconLib ==============================================*/
void _far _cdecl McgaFreeIconLib( iconlib _far *iclib )
{
    DosFreeFMem( iclib );
}

/*== function McgaLoadFont =================================================*/
word _far _cdecl McgaLoadFont( font _far **fnt, const char *filename )
{
    fhandle		    file;
    struct font_header	    header;

    if( DosOpenFile( &file, filename, DOS_ACCESS_RDONLY ) )
	return( ERROR );

    if( DosReadFile( file, ( void _far * )&header, sizeof( header ) ) )
	return( ERROR );

    *fnt = DosAllocFMem( ( ( ( header.xdelta * header.ydelta ) + 1 ) * MCGA_FONTCHARSET ) + sizeof( header ) );

    ( *fnt )->xdelta = header.xdelta;
    ( *fnt )->ydelta = header.ydelta;

    if( DosReadFile( file, *fnt + 1, ( ( header.xdelta * header.ydelta ) + 1 ) * MCGA_FONTCHARSET ) )
	return( ERROR );

    if( DosCloseFile( file ) )
	return( ERROR );

    return( OK );
}

/*== function McgaSetFont ==================================================*/
void _far _cdecl McgaSetFont( struct font_attrib fnt_attr )
{
    font_attribute.darkcolor = fnt_attr.darkcolor;
    font_attribute.color = fnt_attr.color;
    font_attribute.lightcolor = fnt_attr.lightcolor;
    font_attribute.shadowcolor = fnt_attr.shadowcolor;
    font_attribute.shadow = fnt_attr.shadow;
}

/*== function McgaOutText ==================================================*/
void _far _cdecl McgaOutText( font _far *fnt, word x, word y, const char *string )
{
    bool		    shadow;
    byte		    color[3];
    word		    origin;

    char		    *stringcopy;

    byte		    xdelta;
    byte		    ydelta;
    byte		    charsize;
    byte		    charwidth;

    _asm
    {
	mov	bx, OFFSET font_attribute
	mov	al, [bx]font_attribute.shadow
	mov	shadow, al

	push	ds

	lds	si, fnt
	mov	al, ds:[si]font.xdelta
	mov	xdelta, al
	mov	al, ds:[si]font.ydelta
	mov	ydelta, al

	pop	ds

	mul	xdelta
	inc	al
	mov	charsize, al

	mov	ax, MCGA_VRAMSEG
	mov	es, ax

	_init:
	mov	ax, 320
	mul	y
	add	ax, x
	mov	origin, ax

	mov	ax, string
	mov	stringcopy, ax

	mov	bx, OFFSET font_attribute

	test	shadow, 0xFF
	jz	_noshadow

	add	origin, 0x0141
	mov	al, [bx]font_attribute.shadowcolor
	mov	color[0], al
	mov	color[1], al
	mov	color[2], al

	jmp	_aftercolor

	_noshadow:
	mov	al, [bx]font_attribute.darkcolor
	mov	color[0], al
	mov	al, [bx]font_attribute.color
	mov	color[1], al
	mov	al, [bx]font_attribute.lightcolor
	mov	color[2], al

	_aftercolor:

	_loop:
	mov	bx, stringcopy

	mov	al, [bx]
	sub	al, MCGA_FONTASCIIDIF

	mul	charsize
	mov	bx, ax

	push	ds
	lds	si, fnt
	add	si, SIZE fnt

	mov	al, [bx+si]
	mov	charwidth, al
	inc	bx

	pop	ds



	test	shadow, 0xFF
	jz	_end

	mov	shadow, 0
	jmp	_init

	_end:
    }
}

/*== STD - FUNCTIONS =======================================================*/
/*== function StdGetSpeed ==================================================*/
void _far _cdecl StdGetSpeed( void )
{
    _asm
    {
	mov	ax, BIOS_DATASEGMENT
	mov	es, ax
	mov	di, BIOS_TIMEROFFSET

	_waittick:
	mov	dx, es:[di]

	mov	cx, 0x0100
	_tickloop:
	loop	_tickloop

	cmp	dx, es:[di]
	je	_waittick

	mov	dx, es:[di]
	xor	ax, ax

	_loop:
	mov	cx, 0x0100
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
void _far _cdecl StdWait( word millisec )
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
	mov	cx, 0x0100
	_subloop:
	loop	_subloop

	inc	ax
	cmp	ax, es:[di]
	jne	_loop
    }
}

/*== function StdInitRand ==================================================*/
void _far _cdecl StdInitRand( word initnum )
{
    user_init_num = initnum;
    random_var = 0;
}

/*== function StdRandom ====================================================*/
word _far _cdecl StdRandom( void )
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

/*== END_OF_FILE ===========================================================*/
