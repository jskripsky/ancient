// ****************************
// *** Statistik - Programm ***
// ***	     Constant	    ***
// ****************************
// ***			    ***
// ****************************

#include <malloc.h>


#define DEBUG
#define Main main

#define NULL   0

#define TRUE  1
#define FALSE 0


typedef unsigned char	    byte;
typedef unsigned int	    word;
typedef unsigned long	    dword;

typedef unsigned char	    bool;
typedef unsigned int	    fhandle;

typedef word		    file;


// *** Prototype **************
word _cdecl BiosGetKey( void );
bool _cdecl BiosCheckKeybBuffer( void );

byte _cdecl DosDay( void );
byte _cdecl DosMonth( void );
word _cdecl DosYear( void );

file _cdecl DosCreateFile( word attribute, const char *filename );
file _cdecl DosOpenFile( byte mode, const char *filename );
void _cdecl DosCloseFile( file filehandle );
void _cdecl DosResetFile( file filehandle );
word _cdecl DosReadFile( file filehandle, word quantity, void _far *buffer );
word _cdecl DosWriteFile( file filehandle, word quantity, void _far *buffer );
word _cdecl DosGetErrorcode( void );

#define DosAllocMem	 _nmalloc  // void _near *DosAllocMem( word quantity );
#define DosAllocFarMem	 _fmalloc  // void _far *DosAllocFarMem( word quantity );
#define DosFreeMem	 _nfree    // void DosFreeMem( void _near *memblock );
#define DosFreeFarMem	 _ffree    // void DosFreeFarMem( void _far *memblock );

void _cdecl ScrSetMode( void );
void _cdecl ScrRestoreMode( void );
void _cdecl ScrSetCursor( byte x, byte y );
void _cdecl ScrClr( byte color );
void _cdecl ScrChgColor( byte x, byte y, byte width, byte destcolor );
void _cdecl ScrBoxChgColor( byte x1, byte y1, byte x2, byte y2, byte destcolor );
void _cdecl ScrCharacter( byte x, byte y, char character );
void _cdecl ScrCharFill( byte x, byte y, byte width, char character );
void _cdecl ScrWrite( byte x, byte y, const char *string );
void _cdecl ScrWriteCenter( byte x1, byte x2, byte y, const char *string );
void _cdecl ScrWriteRight( byte x, byte y, const char *string );

void _cdecl BoxDraw( struct box *box );
void _cdecl BoxWrite( struct box *box, byte x, byte y, byte direction, char *string );
void _cdecl BoxClear( struct box *box );
void _cdecl BoxMark( struct box *box, byte x1, byte y1, byte x2, byte y2 );
void _cdecl BoxUnMark( struct box *box, byte x1, byte y1, byte x2, byte y2 );
void _cdecl ButtonMark( struct box *box );
void _cdecl ButtonUnmark( struct box *box );
byte _cdecl ButtonMenu( byte quantity, byte start, struct box *button, void (*standard)( byte choice ) );
void _cdecl CheckList( struct box *box, byte quantity, struct checkline _far *checkline );


// *** Constants **************
#define KBUP		0x4800
#define KBDOWN		0x5000
#define KBLEFT		0x4B00
#define KBRIGHT		0x4D00
#define KBENTER 	0x1C0D
#define KBSPACE 	0x3920
#define KBESC		0x011B
#define KBBACKSPACE	0x0E08
#define KBDEL		0x5300

#define BACKGROUND	0x17
#define STATUSLINE	0x70

#define BEGRUEND_COD	"BEGRUEND.COD"
#define ABTEIL_COD	"ABTEIL.COD"
#define BEGRUEND_CFG	"BEGRUEND.CFG"
#define ABTEIL_CFG	"ABTEIL.CFG"
#define TAG_CFG 	"TAG.CFG"
#define EXPORTFILE	"F60-SCAR.DAT"

#define MONTH		0
#define PART		1
#define YEAR		2

#define GESCHLECHT	3
#define ABTEILUNG	0

#define CHOICE		0x17
#define MENU		0x70

#define INFO   0
#define FRAME  1
#define BUTTON 2

#define SINGLE 0
#define DOUBLE 1

#define LEFT   0
#define RIGHT  1
#define CENTER 2

#define SPACE  ' '
#define ZERO   '0'

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

#define KEYLENGTH	    5


// *** Vartypes	***************
struct box
    {
    byte		    type;
    byte		    x1;
    byte		    y1;
    byte		    x2;
    byte		    y2;
    byte		    color;
    byte		    markcolor;
    byte		    lines;
    bool		    joinup;
    bool		    joindown;

    char *		    title;
    };

typedef struct box	    box;

struct checkline
    {
    bool		    checkmark;
    char		    string[80];
    };

struct begruendung
    {
    bool		    checkmark;
    char		    number[3];
    char		    genus;
    char		    space;
    char		    description[75];
    };

struct abteilung
    {
    char		    code[KEYLENGTH];
    char		    space;
    char		    description[75];
    };

struct Satz_Anfang
    {
    char		    Flag;
    char		    Personalnummer[9];
    char		    Name[30];
    char		    Anstellung[6];
    char		    Austritt[6];
    char		    Beschaeftigungsgrad[3];
    char		    Jahresplan[3];
    char		    Funktion[5];
    char		    Beschreibung[30];
    char		    Felder[7][5];
    char		    Zeitkonti[20][7];
    char		    Frei[154];
    char		    Schlusszeichen;
    char		    ASCIISchlusszeichen[2];
    };

struct Satz_Mitte
    {
    char		    Flag;
    char		    Stempelung[2];
    char		    Monat_Vormonat[1];
    char		    Stempelungen[20][5];

    struct
	{
	char		    Code[3];
	char		    Typ;
	char		    Herkunft[1];
	char		    Dauer[4];
	}		    Begruendungen[21];

    char		    Zeitkonti[20][5];
    char		    Monat[2];
    char		    Jahr[2];
    char		    Kontrolle[3];
    char		    Tagesplan[3];
    char		    Frei[19];
    char		    Schlusszeichen;
    char		    ASCIISchlusszeichen[2];
    };

struct Satz_Ende
    {
    char		    Flag;

    char		    PseudoFrei[147];

    char		    Frei[274];
    char		    Schlusszeichen;
    char		    ASCIISchlusszeichen[2];
    };
