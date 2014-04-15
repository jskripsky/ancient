// ****************************
// ***	       Main	    ***
// ****************************
// ***			    ***
// ****************************

#include "StdLib.H"
#include "WinLib.H"
#include <string.h>


#define     FIRMATITLE		"IWB"

/*
#define     FIRMATITLE		"Altersheim am Bachgraben Allschwil"
*/


MSG  PeriodeProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

#define     SEG(Pointer)	(WORD)((DWORD)##Pointer >> 16)
#define     OFS(Pointer)	(WORD)(##Pointer)
#define     POINTER( Seg, Ofs ) (VOID FAR *)( (DWORD)((DWORD)(##Seg) << 16) + (DWORD)##Ofs )

#define OK			0
#define ERROR			1

#define     PLUS		1
#define     MINUS		2

#define     TMSPATH		"\\TMS\\"
#define     TMSPATHFILENAME	"FILEPATH.DAT"

#define     TMSBEGRUENDNO	4
#define     TMSABTEILNO 	18
#define     TMSZEITKNO		7
#define     TMSEXPORTFILENO	60
#define     TMSPRINTERINFONO	82
#define     TMSPRINTERPORTNO	83


#define     MAXNUMWINDOWS	100

#define     CONFIGFILENAME	"Stat.Cfg"
#define     BEGRUENDFILENAME	"Begruend.Lst"
#define     ABTEILFILENAME	"Abteil.Lst"
#define     ZEITKFILENAME	"ZeitKont.Lst"

#define     FIRSTDRIVE		'C'
#define     LASTDRIVE		'Z'

#define     DURCHSCHNITT	0
#define     UEBERSICHT		1
#define     UEBERZEIT		2
#define     ZKONTI		3

#define     MONATJAHR		0
#define     PERSON		10
#define     ANZPERSONEN 	15
#define     MONATE		20

#define     BEGRUENDUNGEN	0
#define     ABTEILUNGEN 	1
#define     ZEITKONTI		2
#define     PMBEGRUENDUNGEN	3

#define     STDMIN		0
#define     STDCENTISTD 	1

#define     MONATINIT		0
#define     MONATOK		1
#define     MONATPERSNICHTVORH	10
#define     MONATNICHTVORH	20

#define     MONATEPROZEILE	4
#define     SPALTENBREITE	20

#define     BEGRUENDCODELENGTH	3
#define     ABTEILCODELENGTH	5
#define     ZEITKCODELENGTH	2

#define     JSCODELENGTH	5
#define     BESCHREIBUNGSLENGTH 30


#define     BACKGROUND		0x0F
#define     HIGHLIGHT		0x1F
#define     MARK		0x70

#define     MENU		0x07
#define     MENUARROWS		0x07
#define     KEYHELP		0x07
#define     PANEL		0x07
#define     NORMAL		0x07
#define     PROGRESSBAR 	0x70

#define     NUMCONTROLPANEL	4

#define     NUMPERIODEPANEL	4
#define     NUMABTEILPANEL	4
#define     NUMBEGRUENDPANEL	4
#define     NUMEXPCONVHELPKEYS	1
#define     NUMPERSONENPANEL	2

#define	    MAXABTEILUNGEN	1000
#define     MAXBEGRUENDUNGEN	1000
#define     MAXZEITKONTI	50

#define     NUMPERSONENSUBPANEL 3
#define     NUMPERSONENHELPKEYS 3

#define     NUMPERIODESUBPANEL	6
#define     NUMPERIODEHELPKEYS	4

#define     NUMLAUFWERKHELPKEYS 3

#define     NUMEINSTELLSUBPANEL 4
#define     NUMEINSTELLHELPKEYS 4

#define     NUMABTSUBPANEL	2
#define     NUMABTCHKLHELPKEYS	4
#define     NUMABTSCHLHELPKEYS	3

#define     NUMCHECKLSTHELPKEYS 3

#define     NUMDURCHSCHHELPKEYS 2

#define     NUMUEBERSHELPKEYS	3
#define     NUMUEBERZHELPKEYS	4

#define     BOTTOMLINEX1	0
#define     BOTTOMLINEY1	23
#define     BOTTOMLINEX2	79
#define     BOTTOMLINEY2	24

#define     PANELX1		28
#define     PANELY1		0
#define     PANELX2		77
#define     PANELY2		19

#define     DOT			1

#define     NUMMENUPOINTS	25
#define     NUMMENUHELPKEYS	3

#define     LEFTINDENT		0

#define DATA			0
#define INIT			1

#define TITLEFONT		10
#define NORMALFONT		11
#define COMPTITLEFONT		20
#define COMPNORMALFONT		21
#define STARTUNDERLINE		40
#define ENDUNDERLINE		41
#define STARTBOLD		60
#define ENDBOLD 		61

#define NEWLINE 		100
#define NEWPAGE 		150

#define SETHPOS 		200

#define LANDSCAPE		0
#define PORTRAIT		1



struct Periode
    {
    BYTE    AnfTag;
    BYTE    EndTag;
    BYTE    AnfMonat;
    BYTE    EndMonat;
    WORD    AnfJahr;
    WORD    EndJahr;
    };


struct ConfigData
    {
    CHAR			TMSLaufWerk;
    WORD			ArbeitsTag;
    BYTE			AbtFeldNr;
    BYTE			ZeitAngModus;

    WORD			Grenzwert;

    DWORD			TMSAbteilungsDatum;
    DWORD			TMSBegruendungsDatum;
    DWORD			TMSZeitKontiDatum;

    struct Periode		Perioden[NUMCONTROLPANEL];

    CHAR			Name[NUMCONTROLPANEL][31];
    CHAR			PersonalNr[NUMCONTROLPANEL][10];
    BYTE			Kriterium[NUMCONTROLPANEL];

    CHAR			AbtSchluessel[NUMCONTROLPANEL][6];
    BOOL			AbtCheckListe[NUMCONTROLPANEL][MAXABTEILUNGEN];
    BOOL			BegrCheckListe[NUMCONTROLPANEL][MAXBEGRUENDUNGEN];
    BOOL			ZKontCheckListe[NUMCONTROLPANEL][MAXZEITKONTI];
    };


struct MenuPoint
    {
    BYTE    Style;
    BYTE    Indent;
    CHAR    Text[25];
    PROC    *Proc;
    VOID    FAR *Data;
    };


struct HelpKey
    {
    BYTE    x;
    BYTE    y;
    CHAR    Text[40];
    };


struct Eintrag
    {
    BYTE    CodeLength;
    CHAR    Code[JSCODELENGTH + 1];

    BYTE    DescriptionLength;
    CHAR    Description[BESCHREIBUNGSLENGTH + 1];
    };




MSG  BottomlineProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  ProgressbarProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  InputProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
BOOL PersonInAbtListe( BOOL FAR *AbtCheckListe, struct PersonenInfo FAR *PersonenInfo );
VOID StringZeitAng( SDWORD Zeit, CHAR FAR *String, BOOL Null );

MSG  PeriodeProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  EinstellungenProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  TMSLaufWerkProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

MSG  BegruendungenProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  PMBegruendungenProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  AbteilungenProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  PersonenProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  ZeitKontiProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

MSG  CheckListeProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

MSG  DurchschnittProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  UebersichtProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  UeberzeitProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );
MSG  ZeitKontiSumProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

BYTE ExportFileConversion( VOID );

BYTE OpenDataFile( struct DateiKopf FAR *DateiKopf, WORD Jahr, BYTE Monat );
BYTE ReadPersonenInfo( struct PersonenInfo FAR *PersonenInfo );
BYTE ReadTage( struct Tag FAR *Tage );
BYTE ResetDataFile( VOID );
BYTE DeleteDataFile( VOID );

BOOL OpenPathFile( VOID );
BOOL ReadPathFileEntry( BYTE Number, CHAR *Entry, BOOL NoPath );
BOOL ClosePathFile( VOID );

BOOL GetPrinterInfo( CHAR *PrinterInfoFileName, CHAR *PrinterPort );
BOOL FreePrinterInfo( VOID );
BOOL GetPrinterDescription( CHAR *PrinterDescription );
BOOL OpenPrinter( VOID );
BOOL ClosePrinter( VOID );
BOOL WritePrinter( BYTE Command, VOID FAR *Data );


MSG  DesktopWinProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

BOOL WinInitialize( WORD NumWindows );
BOOL WinTerminate( VOID );

BOOL WinCreateWindow( HWND HParentWnd, HWND *HWnd, PROC *WinProc, MPARAM MP1, MPARAM MP2, BYTE x1, BYTE y1, BYTE x2, BYTE y2 );
BOOL WinDestroyWindow( HWND HWnd );

MSG  WinSendMsg( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

MSG  WinDefWindowProc( HWND HWnd, MSG Msg, MPARAM MP1, MPARAM MP2 );

BYTE WinGetx2( HWND HWnd );
BYTE WinGety2( HWND HWnd );

BOOL WinSetCursorPos( HWND HWnd, BYTE x, BYTE y );
BOOL WinHideCursor( VOID );
BOOL WinColor( HWND HWnd, BYTE Color, BYTE x1, BYTE y1, BYTE x2, BYTE y2 );
BOOL WinString( HWND HWnd, CHAR *String, BYTE Direction, BYTE x, BYTE y );
BOOL WinCharacter( HWND HWnd, CHAR Character, BYTE x, BYTE y );
BOOL WinFill( HWND HWnd, CHAR Character, BYTE x1, BYTE y1, BYTE x2, BYTE y2 );



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
    CHAR	Name[31];

    WORD	JahrAnstellung;
    BYTE	MonatAnstellung;
    BYTE	TagAnstellung;

    WORD	JahrAustritt;
    BYTE	MonatAustritt;
    BYTE	TagAustritt;

    BYTE	Beschaeftigungsgrad;

    BYTE	LaengeFunktion;
    CHAR	Funktion[6];

    BYTE	AnzFelder;
    BYTE	BenutzteFelder;
    struct
	{
	BYTE	LaengeFeld;
	CHAR	Feld[6];
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
