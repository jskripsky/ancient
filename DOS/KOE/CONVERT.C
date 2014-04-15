/*== include ===============================================================*/

#include <stdio.h>
#include <stdlib.h>

/*== prototype =============================================================*/

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

/*== global vars ===========================================================*/

struct in_element
{
    char		    zero_01[1];
    char		    address[2];
    char		    address_terminator[1];

    char		    data_01[5];
    char		    data_01_terminator[1];
    char		    data_02[2];
    char		    data_02_terminator[1];
    char		    data_03[2];
    char		    data_03_terminator[1];
    char		    data_04[2];
    char		    data_04_terminator[1];
    char		    data_05[2];
    char		    data_05_terminator[1];
    char		    data_06[2];
    char		    data_06_terminator[1];
    char		    data_07[2];
    char		    data_07_terminator[1];

    char		    zero_02[1];
    char		    code[2];

    char		    element_terminator[2];
}   inelement;

struct out_element
{
    char		    one[1];
    char		    address_01[2];
    char		    zero_01[3];
    char		    address_02[2];

    char		    data_01[5];
    char		    data_02[2];
    char		    data_03[2];
    char		    data_04[2];
    char		    data_05[2];
    char		    data_06[2];
    char		    data_07[2];

    char		    code[2];
    char		    zero_02[3];

    char		    element_terminator[2];
}   outelement;

fhandle 		    infile;
fhandle 		    outfile;
bool			    valid_eofarg = TRUE;
bool			    eofmark = FALSE;
const byte		    eofbyte = 0x1A;

const char		    const_01[1] = { '1' } ;
const char		    const_02[3] = { '0', '0', '0' };

/*== main ==================================================================*/
void main( word argcounter, char *argument[] )
{
    if( argcounter == 4 )
	if( memicmp( argument[3], "EOF", 4 ) )
	    valid_eofarg = FALSE;
	else
	    eofmark = TRUE;

    if( argcounter < 3 || argcounter > 4 || !valid_eofarg )
    {
	printf( "Syntax: CONVERT Quelldatei Zieldatei [EOF]\n" );
	exit( 1 );
    }

    if( DosOpenFile( &infile, argument[1], DOS_ACCESS_RDONLY ) )
    {
	printf( "Quelldatei kann nicht ge”ffnet werden.\n");
	exit( 1 );
    }

    if( DosCreateFile( &outfile, argument[2], DOS_ATTRIB_NORMAL ) )
    {
	printf( "Zieldatei kann nicht ge”ffnet werden.\n" );
	exit( 1 );
    }

    outelement.one[0] = '1';
    outelement.zero_01[0] = '0';
    outelement.zero_01[1] = '0';
    outelement.zero_01[2] = '0';
    outelement.zero_02[0] = '0';
    outelement.zero_02[1] = '0';
    outelement.zero_02[2] = '0';

    DosReadFile( infile, ( void _far * )&inelement, sizeof( inelement ) );

    while( inelement.zero_01[0] != eofbyte )
    {
	memcpy( &(outelement.address_01), &(inelement.address), 2 );
	memcpy( &(outelement.address_02), &(inelement.address), 2 );
	memcpy( &(outelement.data_01), &(inelement.data_01), 5 );
	memcpy( &(outelement.data_02), &(inelement.data_02), 2 );
	memcpy( &(outelement.data_03), &(inelement.data_03), 2 );
	memcpy( &(outelement.data_04), &(inelement.data_04), 2 );
	memcpy( &(outelement.data_05), &(inelement.data_05), 2 );
	memcpy( &(outelement.data_06), &(inelement.data_06), 2 );
	memcpy( &(outelement.data_07), &(inelement.data_07), 2 );
	memcpy( &(outelement.code), &(inelement.code), 2 );
	memcpy( &(outelement.element_terminator), &(inelement.element_terminator), 2 );

	DosWriteFile( outfile, ( void _far * )&outelement, sizeof( outelement ) );
	DosReadFile( infile, ( void _far * )&inelement, sizeof( inelement ) );
    }

    if( eofmark )
	DosWriteFile( outfile, ( void _far * )&eofbyte, 1 );
    DosCloseFile( outfile );
    DosCloseFile( infile );

}
