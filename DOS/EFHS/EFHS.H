// ****************************
// ***	      EFHS.H	    ***
// ****************************
// ***			    ***
// ****************************

#include "stdlib.h"


// *** Prototype **************
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


DWORD StdDivide( DWORD Dividend, WORD Divisor );
BYTE StdBinToAscii( DWORD Number, BYTE Length, CHAR FAR *String, BYTE Direction, BYTE Zeros );
DWORD StdAsciiToBin( BYTE Length, CHAR FAR *Number );


// *** Constants **************


#define EXPORTFILENAME	"F60-SCAR.DAT"

#define JSFILEIDMARKE		"TMS Exportfile, JS Format"
#define JSFILEGRVERSION 	1
#define JSFILEKLVERSION 	0


#define  OK			0
#define  TMSFILE_INV_LENGTH	1
#define  TMSFILE_OLD_VERSION	2

#define  TMSFILE_DOS_ERROR	11
#define  JSFILE_DOS_ERROR	12

#define  COMPRESS_SWITCH	4



// *** Vartypes	***************
struct SatzAnfang
    {
    CHAR		    Flag;
    CHAR		    Personalnummer[9];
    CHAR		    Name[30];
    CHAR		    Anstellung[6];
    CHAR		    Austritt[6];
    CHAR		    Beschaeftigungsgrad[3];
    CHAR		    Jahresplan[3];
    CHAR		    Funktion[5];
    CHAR		    Beschreibung[30];
    CHAR		    Felder[7][5];
    CHAR		    Zeitkonti[20][7];
    CHAR		    Frei[154];
    CHAR		    Schlusszeichen;
    CHAR		    ASCIISchlusszeichen[2];
    };

struct SatzMitte
    {
    CHAR		    Flag;
    CHAR		    Stempelung[2];
    CHAR		    Monat_Vormonat[1];
    CHAR		    Stempelungen[20][5];

    struct
	{
	CHAR		    Code[3];
	CHAR		    Typ;
	CHAR		    Herkunft[1];
	CHAR		    Dauer[4];
	}		    Begruendungen[21];

    CHAR		    Zeitkonti[20][5];
    CHAR		    Monat[2];
    CHAR		    Jahr[2];
    CHAR		    Kontrolle[3];
    CHAR		    Tagesplan[3];
    CHAR		    Frei[19];
    CHAR		    Schlusszeichen;
    CHAR		    ASCIISchlusszeichen[2];
    };

struct SatzEnde
    {
    CHAR		    Flag;

    CHAR		    PseudoFrei[147];

    CHAR		    Frei[274];
    CHAR		    Schlusszeichen;
    CHAR		    ASCIISchlusszeichen[2];
    };





#pragma pack( 1 )

struct DateiKopf
    {
    CHAR	IdMarke[30];
    BYTE	GrVersion;
    BYTE	KlVersion;

    WORD	Jahr;
    BYTE	Monat;
    BYTE	AnzTage;

    WORD	AnzPersonen;
    BOOL	Kontrolliert;
    };

struct PersonenInfo
    {
    DWORD	Personalnummer;

    BYTE	LaengeName;
    CHAR	Name[30];

    WORD	JahrAnstellung;
    BYTE	MonatAnstellung;
    BYTE	TagAnstellung;

    WORD	JahrAustritt;
    BYTE	MonatAustritt;
    BYTE	TagAustritt;

    BYTE	Beschaeftigungsgrad;

    BYTE	LaengeFunktion;
    CHAR	Funktion[5];

    BYTE	AnzFelder;
    BYTE	BenutzteFelder;
    struct
	{
	BYTE	LaengeFeld;
	CHAR	Feld[5];
	}	Felder[7];
    };

struct Tag
    {
    BYTE	AnzStempelungen;
    struct
	{
	UNSIGNED Zeit	    : 14;
	UNSIGNED EinAusgang :  1;
	}	Stempelungen[20];

    BYTE	AnzBegruendungen;
    struct
	{
	UNSIGNED Dauer	    : 14;
	UNSIGNED Code	    : 10;
	UNSIGNED Typ	    :  2;
	UNSIGNED Herkunft   :  3;
	}	Begruendungen[21];

    BYTE	AnzZeitkonti;
    DWORD	BenutzteZeitkonti;
    SWORD	Zeitkonti[20];
    };

#pragma pack()
