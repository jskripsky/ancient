/*== include ===============================================================*/

#include <malloc.h>
#include <stdio.h>

/*== pragma ================================================================*/

/*== define ================================================================*/

#define TRUE		    1
#define FALSE		    0

#define OK		    0
#define ERROR		    1

#define _ATTRIB_NORMAL	    0x00
#define _ATTRIB_RDONLY	    0x01
#define _ATTRIB_HIDDEN	    0x02
#define _ATTRIB_SYSTEM	    0x04
#define _ATTRIB_VOLID	    0x08
#define _ATTRIB_SUBDIR	    0x10
#define _ATTRIB_ARCH	    0x20

#define _ACCESS_RDONLY	    0x00
#define _ACCESS_WRONLY	    0x01
#define _ACCESS_RDWR	    0x02

#define _ACCESS_SH_COMPAT   0x00
#define _ACCESS_SH_DENYRDWR 0x10
#define _ACCESS_SH_DENYWR   0x20
#define _ACCESS_SH_DENYRD   0x30
#define _ACCESS_SH_DENYNO   0x40

#define _ACCESS_NOCHILD     0x80

#define VRAMSEG 	    0xA000

#define TRANSCOLORBIT	    128

#define BIOS_DATA_SEGMENT   0x0040
#define BIOS_TIMER_OFFSET   0x006C

#define DIR_ENTRY_SIZE	    14

#define DosFreeFMem	    _ffree
#define DosAllocFMem	    _fmalloc


/*== typedef ===============================================================*/

typedef unsigned char	    byte;
typedef unsigned int	    word;
typedef unsigned long int   dword;

typedef signed long int     sdword;
typedef unsigned char	    bool;
typedef unsigned int	    fhandle;

typedef struct image_header image;
typedef struct iclib_header iconlib;

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

void _far _cdecl McgaOutText( byte fontnumber, const char *text );

void _far _cdecl StdGetSpeed( void );
void _far _cdecl StdWait( word millisec );

void _far _cdecl StdInitRand( word initnum );
word _far _cdecl StdRandom( void );

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

/*== main ==================================================================*/
void main( void )
{
    word		    Key;

    do
    {
	Key = BiosGetKey();
	printf( "0x%x\n", Key );
    } while( Key != 32 );

}
