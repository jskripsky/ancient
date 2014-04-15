// ****************************
// ***	       Usego	    ***
// ****************************
// ***	File - Conversion   ***
// ****************************

#include "StdLib.H"
#include "Convert.H"

BOOL MemAllSameChar( BYTE FAR *Buffer, CHAR Character, WORD BufferLength );

CHAR ProgramTitle[] = "\n\rConvert 1.00  Copyright (c) 1992 J. Skripsky\n\r--------------------------------------------\n\r\n\r";
CHAR ProgramSyntax[] = "Syntax:  CONVERT.EXE  <Quelldatei>  <Zieldatei>\n\r\n\r";
CHAR CompleteText[] = "Konversion abgeschlossen.\n\r";

CHAR ErrorSourceFile[] = "Quelldatei kann nicht ge”ffnet werden!\n\r";
CHAR ErrorDestinationFile[] = "Zieldatei kann nicht erstellt werden!\n\r";

BYTE FAR *Source;
BYTE FAR *Destination;

HFILE SourceFile;
HFILE DestinationFile;

WORD  NumEntries;
DWORD FilePointer;


RET Main( WORD NumArgs, CHAR *Args[], CHAR *EnvStrings[] )
    {
    HFILE Screen;
    WORD  EntryCounter;

    DosCreate( "CON", &Screen, FILE_NORMAL );

    DosWrite( Screen, ProgramTitle, StdStrLen( ProgramTitle ), NULL );

    if( NumArgs == 3 )
	{
	if( DosOpen( Args[1], &SourceFile, OPEN_RDONLY ) != 0 )
	    {
	    DosWrite( Screen, ErrorSourceFile, StdStrLen( ErrorSourceFile ), NULL );
	    DosClose( Screen );
	    return( 1 );
	    }

	FilePointer = 0;
	DosSetFilePtr( SourceFile, &FilePointer, FILE_END, &FilePointer );
	NumEntries = FilePointer / SOURCEENTRYLENGTH;

	FilePointer = 0;
	DosSetFilePtr( SourceFile, &FilePointer, FILE_BEGIN, NULL );

	if( DosCreate( Args[2], &DestinationFile, FILE_NORMAL ) != 0 )
	    {
	    DosClose( SourceFile );
	    DosWrite( Screen, ErrorDestinationFile, StdStrLen( ErrorDestinationFile ), NULL );
	    DosClose( Screen );
	    return( 1 );
	    }


	Source = DosAllocFarMem( SOURCEENTRYLENGTH );
	Destination = DosAllocFarMem( SOURCEENTRYLENGTH );

	for( EntryCounter = 0; EntryCounter < NumEntries; EntryCounter++ )
	    {
	    WORD SOffset = 0;
	    WORD DOffset = 0;
	    BYTE EntryNumber = 0;
	    BYTE DataEntryNumber = 0;
	    BYTE NumDestinationEntries = 1;

	    CHAR Percent[5];

	    StdStrCpy( Percent, "   %" );
	    StdBinToAscii( StdDivide( (EntryCounter + 1) * 100, NumEntries ), 3, Percent, RIGHT, 1 );
	    DosWrite( Screen, Percent, StdStrLen( Percent ), NULL );

	    DosRead( SourceFile, Source, SOURCEENTRYLENGTH, NULL );
	    StdFarMemSet( Destination, '0', SOURCEENTRYLENGTH );

	    StdFarMemCpy( &Destination[DOffset], &Source[SOffset], STARTBLOCKLENGTH );
	    DOffset += STARTBLOCKLENGTH;
	    SOffset = ENDBLOCKOFFSET;

	    StdFarMemCpy( &Destination[DOffset], &Source[SOffset], ENDBLOCKLENGTH );
	    DOffset += ENDBLOCKLENGTH;
	    SOffset = DATAOFFSET;

	    do
		{
		if( (DataEntryNumber % 100 == 0) && (DataEntryNumber > 0) )
		    SOffset++;

		if( DOffset > (256 - 1 - DATAENTRYLENGTH) )
		    {
		    EntryNumber++;
		    DOffset = 0;
		    }

		StdFarMemCpy( &Destination[EntryNumber * DESTINATIONENTRYLENGTH + DOffset], &Source[SOffset], DATAENTRYLENGTH );
		DOffset += DATAENTRYLENGTH;
		SOffset += DATAENTRYLENGTH;

		DataEntryNumber++;
		}
	    while( SOffset <= (ENDBLOCKOFFSET - DATAENTRYLENGTH) );

	    for( EntryNumber = 1; EntryNumber <= 3; EntryNumber++ )
		{
		if( MemAllSameChar( &Destination[EntryNumber * DESTINATIONENTRYLENGTH], '0', DESTINATIONENTRYLENGTH ) )
		    break;

		Destination[(EntryNumber - 1) * DESTINATIONENTRYLENGTH + 255] = '1';
		NumDestinationEntries++;
		}

	    DosWrite( DestinationFile, Destination, DESTINATIONENTRYLENGTH * NumDestinationEntries, NULL );

	    StdStrCpy( Percent, "\b\b\b\b" );
	    DosWrite( Screen, Percent, StdStrLen( Percent ), NULL );
	    }

	DosClose( SourceFile );
	DosClose( DestinationFile );

	DosWrite( Screen, CompleteText, StdStrLen( CompleteText ), NULL );
	}
    else
	DosWrite( Screen, ProgramSyntax, StdStrLen( ProgramSyntax ), NULL );

    DosClose( Screen );

    return( 0 );
    }


BOOL MemAllSameChar( BYTE FAR *Buffer, CHAR Character, WORD BufferLength )
    {
    WORD Counter;

    for( Counter = 0; Counter < BufferLength; Counter++ )
	if( Buffer[Counter] != Character )
	    return( FALSE );

    return( TRUE );
    }
