// ****************************
// ***	      Printer	    ***
// ****************************
// ***			    ***
// ****************************

#include "Main.H"
#include "Printer.H"

BOOL GetPrinterInfo( CHAR *PrinterInfoFileName, CHAR *PrinterPort );
BOOL FreePrinterInfo( VOID );
BOOL GetPrinterDescription( CHAR *PrinterDescription );
BOOL OpenPrinter( VOID );
BOOL ClosePrinter( VOID );
BOOL WritePrinter( BYTE Command, VOID FAR *Data );

VOID ReadLine( HFILE File, CHAR *Line );

struct PrinterInfo FAR *PrinterInfo;
HFILE Printer;

BYTE  HPos;
BYTE  VPos;
BYTE  Page;
BOOL  DataInPrinterBuffer;

extern struct ConfigData FAR *ConfigData;



BOOL GetPrinterInfo( CHAR *PrinterInfoFileName, CHAR *PrinterPort )
    {
    HFILE PrnInfoFile;
    CHAR  Line[102];
    BYTE  CodeCounter;

    PrinterInfo = DosAllocFarMem( sizeof( *PrinterInfo ) );
    StdFarMemSet( PrinterInfo, 0, sizeof( *PrinterInfo ) );

    StdFarStrCpy( PrinterInfo->PrinterPort, (CHAR FAR *)PrinterPort );
    if( DosOpen( PrinterInfoFileName, &PrnInfoFile, OPEN_RDONLY ) )
	return( FALSE ); // Debug!!!!!

    ReadLine( PrnInfoFile, Line );
    StdFarStrCpy( PrinterInfo->PrinterDescription, (CHAR FAR *)&Line[4] );

    for( CodeCounter = 0; CodeCounter < 10; CodeCounter++ )
	{
	BYTE CharCounter;
	ReadLine( PrnInfoFile, Line );

	CharCounter = 0;

	while( Line[4 + CharCounter * 3] )
	    {
	    BYTE DigitCounter;

	    PrinterInfo->ControlCodes[CodeCounter][CharCounter] = 0;

	    for( DigitCounter = 0; DigitCounter < 2; DigitCounter++ )
		{
		PrinterInfo->ControlCodes[CodeCounter][CharCounter] *= 16;
		if( Line[4 + CharCounter * 3 + DigitCounter] >= 'A' )
		    PrinterInfo->ControlCodes[CodeCounter][CharCounter]
		     += (BYTE)(Line[4 + CharCounter * 3 + DigitCounter] - (BYTE)'A' + 10);
		else
		    PrinterInfo->ControlCodes[CodeCounter][CharCounter]
		     += (BYTE)(Line[4 + CharCounter * 3 + DigitCounter] - (BYTE)'0');
		}

	    CharCounter++;
	    }

	}

    ReadLine( PrnInfoFile, Line );
    PrinterInfo->Orientation = (BYTE)(Line[4] - ZEROCHAR);
    PrinterInfo->LinesPerPage = StdAsciiToBin( 3, (CHAR FAR *)&Line[6] ) - 6;

    DosClose( PrnInfoFile );
    return( TRUE );
    }


BOOL FreePrinterInfo( VOID )
    {
    DosFreeFarMem( PrinterInfo );
    return( TRUE );
    }


BOOL GetPrinterDescription( CHAR *PrinterDescription )
    {
    return( TRUE );
    }


BOOL OpenPrinter( VOID )
    {
    CHAR String[65];

    StdFarStrCpy( String, PrinterInfo->PrinterPort );
    DosCreate( String, &Printer, FILE_NORMAL );
    // Debug!!!!! DosCreate( "PRINTER.$$$", &Printer, FILE_NORMAL );

    WritePrinter( INIT, NULL );
    return( TRUE );
    }


BOOL ClosePrinter( VOID )
    {
    if( DataInPrinterBuffer )
	WritePrinter( NEWPAGE, NULL );

    DosClose( Printer );
    return( TRUE );
    }


BOOL WritePrinter( BYTE Command, VOID FAR *Data )
    {
    switch( Command )
	{
	case INIT:
	    DosWrite( Printer, PrinterInfo->ControlCodes[0], (WORD)StdFarStrLen( PrinterInfo->ControlCodes[0] ), NULL );
	    DosWrite( Printer, PrinterInfo->ControlCodes[1], (WORD)StdFarStrLen( PrinterInfo->ControlCodes[1] ), NULL );
	    DataInPrinterBuffer = TRUE;
	    HPos = 0;
	    VPos = 0;
	    Page = 1;
	    break;

	case TITLEFONT:
	    DosWrite( Printer, PrinterInfo->ControlCodes[2], (WORD)StdFarStrLen( PrinterInfo->ControlCodes[2] ), NULL );
	    break;

	case NORMALFONT:
	    DosWrite( Printer, PrinterInfo->ControlCodes[3], (WORD)StdFarStrLen( PrinterInfo->ControlCodes[3] ), NULL );
	    break;

	case COMPTITLEFONT:
	    DosWrite( Printer, PrinterInfo->ControlCodes[4], (WORD)StdFarStrLen( PrinterInfo->ControlCodes[4] ), NULL );
	    break;

	case COMPNORMALFONT:
	    DosWrite( Printer, PrinterInfo->ControlCodes[5], (WORD)StdFarStrLen( PrinterInfo->ControlCodes[5] ), NULL );
	    break;

	case STARTUNDERLINE:
	    DosWrite( Printer, PrinterInfo->ControlCodes[6], (WORD)StdFarStrLen( PrinterInfo->ControlCodes[6] ), NULL );
	    break;

	case ENDUNDERLINE:
	    DosWrite( Printer, PrinterInfo->ControlCodes[7], (WORD)StdFarStrLen( PrinterInfo->ControlCodes[7] ), NULL );
	    break;

	case STARTBOLD:
	    DosWrite( Printer, PrinterInfo->ControlCodes[8], (WORD)StdFarStrLen( PrinterInfo->ControlCodes[8] ), NULL );
	    break;

	case ENDBOLD:
	    DosWrite( Printer, PrinterInfo->ControlCodes[9], (WORD)StdFarStrLen( PrinterInfo->ControlCodes[9] ), NULL );
	    break;

	case DATA:
	    DosWrite( Printer, Data, (WORD)StdFarStrLen( Data ), NULL );
	    HPos += (BYTE)StdFarStrLen( Data );
	    DataInPrinterBuffer = TRUE;
	    break;

	case SETHPOS:
	    {
	    BYTE Counter;

	    for( Counter = HPos; Counter < (BYTE)Data; Counter++ )
		{
		DosWrite( Printer, (CHAR FAR *)" ", 1, NULL );
		HPos++;
		}

	    DataInPrinterBuffer = TRUE;
	    break;
	    }

	case NEWLINE:
	    if( VPos == PrinterInfo->LinesPerPage - 3 )
		{
		CHAR String[4];

		DosWrite( Printer, "\r\n\n", 3, NULL );
		HPos = 0;
		WritePrinter( SETHPOS, (CHAR FAR *)78 );

		StdStrCpy( String, "   " );
		StdBinToAscii( Page, 3, String, RIGHT, 1 );
		WritePrinter( DATA, String );
		DosWrite( Printer, "\r\f", 2, NULL );
		HPos = 0;
		VPos = 0;
		Page++;
		DataInPrinterBuffer = FALSE;
		return( FALSE );
		}
	    else
		{
		DosWrite( Printer, "\r\n", 2, NULL );
		VPos++;
		HPos = 0;
		return( TRUE );
		}
	    break;

	case NEWPAGE:
	    while( WritePrinter( NEWLINE, (CHAR FAR *)NULL ) );
	    break;
	}
    return( TRUE );
    }


VOID ReadLine( HFILE File, CHAR *Line )
    {
    SDWORD Distance;
    CHAR *LineEnd;
    DosRead( File, (VOID FAR *)Line, 102, NULL );

    LineEnd = StdStrChr( Line, '\r' );

    LineEnd[0] = 0;
    LineEnd[1] = 0;

    Distance = (SDWORD)((SDWORD)(WORD)LineEnd - (SDWORD)(WORD)Line - 102 + 2);

    DosSetFilePtr( File, &Distance, FILE_CURRENT, NULL );
    }
