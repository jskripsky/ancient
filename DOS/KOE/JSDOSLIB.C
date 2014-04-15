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

#define BIOS_DATASEGMENT    0x0040
#define BIOS_TIMEROFFSET    0x006C

/*== typedef ===============================================================*/

typedef unsigned char	    byte;
typedef unsigned int	    word;
typedef unsigned long int   dword;

typedef signed long int     sdword;
typedef unsigned char	    bool;
typedef unsigned int	    fhandle;

/*== struct ================================================================*/

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

void _far _cdecl StdGetSpeed( void );
void _far _cdecl StdWait( word millisec );

void _far _cdecl StdInitRand( word initnum );
word _far _cdecl StdRandom( void );

/*== global variable =======================================================*/

struct dta _near	    dta;

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
