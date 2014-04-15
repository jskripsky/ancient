// ****************************
// ***	 Standardlibrary    ***
// ****************************
// ***			    ***
// ****************************

#include <malloc.h>
#include <string.h>

#define Main main

#define     SEG(Pointer)	(WORD)((DWORD)##Pointer >> 16)
#define     OFS(Pointer)	(WORD)(##Pointer)
#define     POINTER( Seg, Ofs ) (VOID FAR *)( (DWORD)((DWORD)(##Seg) << 16) + (DWORD)##Ofs )

#define NULL	(VOID *)0x0000

#define FAR	_far
#define NEAR	_near

#define TRUE	1
#define FALSE	0


#define FILE_NORMAL	    0x00
#define FILE_RDONLY	    0x01
#define FILE_HIDDEN	    0x02
#define FILE_SYSTEM	    0x04
#define FILE_VOLID	    0x08
#define FILE_SUBDIR	    0x10
#define FILE_ARCH	    0x20


#define OPEN_RDONLY	    0x00
#define OPEN_WRONLY	    0x01
#define OPEN_RDWR	    0x02

#define OPEN_SH_COMPAT	    0x00
#define OPEN_SH_DANYRDWR    0x10
#define OPEN_SH_DENYWR	    0x20
#define OPEN_SH_DENYRD	    0x30
#define OPEN_SH_DENYNO	    0x40

#define OPEN_NOCHILD	    0x80


#define FILE_BEGIN	    0x00
#define FILE_CURRENT	    0x01
#define FILE_END	    0x02


#define KBUP		0x4800
#define KBDOWN		0x5000
#define KBLEFT		0x4B00
#define KBRIGHT		0x4D00
#define KBHOME		0x4700
#define KBEND		0x4F00
#define KBPGUP		0x4900
#define KBPGDOWN	0x5100
#define KBENTER 	0x1C0D
#define KBSPACE 	0x3920
#define KBESC		0x011B
#define KBBACKSPACE	0x0E08
#define KBDEL		0x5300
#define KBINS		0x5200
#define KBTAB		0x0F09
#define KBSHTAB 	0x0F00


#define SPACECHAR	' '
#define ZEROCHAR	'0'

#define LEFT		0
#define RIGHT		1
#define CENTER		2


#define UNSIGNED	unsigned


typedef unsigned char	    BYTE;
typedef unsigned int	    WORD;
typedef unsigned long	    DWORD;

typedef signed short	    SBYTE;
typedef signed int	    SWORD;
typedef signed long	    SDWORD;

typedef unsigned char	    CHAR;
typedef void		    VOID;

typedef unsigned char	    BOOL;

typedef unsigned int	    RET;
typedef unsigned int	    HFILE;


WORD _cdecl BiosGetKey( VOID );
BOOL _cdecl BiosIsKeyInBuffer( VOID );

BYTE _cdecl DosQueryDay( VOID );
BYTE _cdecl DosQueryMonth( VOID );
WORD _cdecl DosQueryYear( VOID );

RET  _cdecl DosCreate( const CHAR *FileName, HFILE *FileHandle, WORD FileAttribute );
RET  _cdecl DosOpen( const CHAR *FileName, HFILE *FileHandle, BYTE OpenMode );
RET  _cdecl DosDelete( const CHAR *FileName );
RET  _cdecl DosRename( const CHAR *OldFileName, const CHAR *NewFileName );
RET  _cdecl DosClose( HFILE FileHandle );
RET  _cdecl DosSetFilePtr( HFILE FileHandle, SDWORD *Distance, BYTE MoveType, SDWORD *NewPointer );
RET  _cdecl DosRead( HFILE FileHandle, VOID FAR *BufferArea, WORD BufferLength, WORD *BytesRead );
RET  _cdecl DosWrite( HFILE FileHandle, VOID FAR *BufferArea, WORD BufferLength, WORD *BytesWritten );
RET  _cdecl DosLastModTime( HFILE FileHandle, DWORD *Time );
RET  _cdecl DosCurrentDrive(  BYTE *Drive );
WORD _cdecl DosGetLastErrorcode( VOID );

#define DosAllocMem	 _nmalloc  // VOID NEAR *DosAllocMem( WORD BufferLength );
#define DosAllocFarMem	 _fmalloc  // VOID FAR *DosAllocFarMem( WORD BufferLength );
#define DosFreeMem	 _nfree    // VOID DosFreeMem( VOID NEAR *MemBlock );
#define DosFreeFarMem	 _ffree    // VOID DosFreeFarMem( VOID FAR *MemBlock );

VOID _cdecl ScrSetMode( VOID );
VOID _cdecl ScrRestoreMode( VOID );
VOID _cdecl ScrSetCursor( BYTE x, BYTE y );
VOID _cdecl ScrClr( BYTE Color );
VOID _cdecl ScrChgColor( BYTE x, BYTE y, BYTE Width, BYTE DestColor );
VOID _cdecl ScrBoxChgColor( BYTE x1, BYTE y1, BYTE x2, BYTE y2, BYTE DestColor );
VOID _cdecl ScrCharacter( BYTE x, BYTE y, CHAR Character );
VOID _cdecl ScrCharFill( BYTE x, BYTE y, BYTE Width, CHAR Character );
VOID _cdecl ScrWrite( BYTE x, BYTE y, const CHAR *String );
VOID _cdecl ScrWriteCenter( BYTE x1, BYTE x2, BYTE y, const CHAR *String );
VOID _cdecl ScrWriteRight( BYTE x, BYTE y, const CHAR *String );

#define StdMemCpy	 memcpy
#define StdMemCmp	 memcmp
#define StdMemSet	 memset
#define StdFarMemCpy	 _fmemcpy
#define StdFarMemCmp	 _fmemcmp
#define StdFarMemSet	 _fmemset

#define StdStrCpy	 strcpy
#define StdStrCmp	 strcmp
#define StdStrSet	 strset
#define StdStrCat	 strcat
#define StdStrLwr	 strlwr
#define StdStrChr	 strchr
#define StdStrLen	 strlen
#define StdFarStrCpy	 _fstrcpy
#define StdFarStrCmp	 _fstrcmp
#define StdFarStrSet	 _fstrset
#define StdFarStrLen	 _fstrlen


DWORD StdDivide( DWORD Dividend, WORD Divisor );
BYTE  StdBinToAscii( DWORD Number, BYTE Length, CHAR FAR *String, BYTE Direction, BYTE Zeros );
DWORD StdAsciiToBin( BYTE Length, CHAR FAR *Number );

BYTE  StdMonthNumDays( BYTE Month, WORD Year );
CHAR *StdMonthName( BYTE Month );
