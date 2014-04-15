// ****************************
// ***	       EFHS	    ***
// ****************************
// ***			    ***
// ****************************

#include <process.h>
#include <string.h>
#include "efhs.h"

typedef  BYTE			APPERRORCODE;

APPERRORCODE WriteJSFormat( HFILE JSFile, HFILE TMSFile, CHAR *JSFileName );


VOID Main( VOID )
    {
    APPERRORCODE    AppErrorcode;
    RET 	    DosErrorcode;

    HFILE TMSFile;
    HFILE JSFile;
    CHAR JSFileName[13] = "JSFile.Tmp";



    if( DosOpen( EXPORTFILENAME, &TMSFile, OPEN_RDONLY ) )
	; // Debug!!

    if( DosCreate( JSFileName, &JSFile, FILE_NORMAL ) )
	; // Debug!!

    AppErrorcode = WriteJSFormat( TMSFile, JSFile, JSFileName );

    DosClose( TMSFile );
    DosClose( JSFile );

    execl( "pkarc.com", "pkarc.com", "a", "jsfile.arc", "jsfile.tmp", NULL );

    }


APPERRORCODE WriteJSFormat( HFILE TMSFile, HFILE JSFile, CHAR *JSFileName )
    {
    SDWORD FilePtrDistance;
    SDWORD TMSDateiLaenge;
    BYTE   AnzTage[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    CHAR   TmpFlag;
    BOOL   AlleTageVorhanden;
    BYTE   TageZaehler;

    WORD   PersZaehler;
    BYTE   FeldZaehler;
    BYTE   ZKontiZaehler;
    BYTE   BegruendungenZaehler;
    BYTE   StempelungenZaehler;


    struct SatzAnfang FAR *TMSSatzAnfang;
    struct SatzMitte  FAR *TMSSatzMitte;
    struct SatzEnde   FAR *TMSSatzEnde;

    struct DateiKopf FAR *JSDateiKopf;
    struct PersonenInfo FAR *JSPersonenInfo;
    struct Tag FAR *JSTag;

    FilePtrDistance = 0;
    DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_END, &TMSDateiLaenge );
    if( TMSDateiLaenge == 0 )
	; // Debug!!

    TMSSatzAnfang = DosAllocFarMem( sizeof( *TMSSatzAnfang ) );
    TMSSatzMitte = DosAllocFarMem( sizeof( *TMSSatzMitte ) );
    TMSSatzEnde = DosAllocFarMem( sizeof( *TMSSatzEnde ) );

    JSDateiKopf = DosAllocFarMem( sizeof( *JSDateiKopf ) );
    JSPersonenInfo = DosAllocFarMem( sizeof( *JSPersonenInfo ) );
    JSTag = DosAllocFarMem( sizeof( *JSTag ) );

    _fmemset( JSDateiKopf, 0, sizeof( *JSDateiKopf ) );
    _fstrcpy( JSDateiKopf->IdMarke, (CHAR FAR *)JSFILEIDMARKE );
    JSDateiKopf->GrVersion = JSFILEGRVERSION;
    JSDateiKopf->KlVersion = JSFILEKLVERSION;

    FilePtrDistance = (SDWORD)sizeof( *TMSSatzAnfang );
    DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_BEGIN, NULL );
    DosRead( TMSFile, TMSSatzMitte, sizeof( *TMSSatzMitte ), NULL );

    JSDateiKopf->Jahr = (WORD)StdAsciiToBin( (BYTE)sizeof( TMSSatzMitte->Jahr ), TMSSatzMitte->Jahr );
    if( JSDateiKopf->Jahr >= 50 )
	JSDateiKopf->Jahr += 1900;
    else
	JSDateiKopf->Jahr += 2000;
    JSDateiKopf->Monat = (BYTE)StdAsciiToBin( (BYTE)sizeof( TMSSatzMitte->Monat ), TMSSatzMitte->Monat );

    if( (JSDateiKopf->Jahr % 4 == 0) && (JSDateiKopf->Monat == 2) )
	AnzTage[2 - 1]++;

    JSDateiKopf->AnzTage = AnzTage[JSDateiKopf->Monat - 1];

    AlleTageVorhanden = TRUE;
    FilePtrDistance = (SDWORD)((SDWORD)sizeof( *TMSSatzMitte ) - (SDWORD)sizeof( TMSSatzMitte->Flag ));
    for( TageZaehler = 2; TageZaehler <= JSDateiKopf->AnzTage; TageZaehler++ )
	{
	DosRead( TMSFile, (VOID FAR *)&TmpFlag, sizeof( TMSSatzMitte->Flag ), NULL );
	if( TmpFlag != 'D' )
	    {
	    AlleTageVorhanden = FALSE;
	    break;
	    }

	DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_CURRENT, NULL );
	}

    FilePtrDistance = 0;
    DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_BEGIN, NULL );

    if( !AlleTageVorhanden )
	; // Debug!!

    if( TMSDateiLaenge % (sizeof( *TMSSatzAnfang ) + (JSDateiKopf->AnzTage * sizeof( *TMSSatzMitte )) + sizeof( *TMSSatzEnde )) != 0 )
	; // Debug!!

    JSDateiKopf->AnzPersonen = (WORD)(TMSDateiLaenge / (sizeof( *TMSSatzAnfang ) + (JSDateiKopf->AnzTage * sizeof( *TMSSatzMitte )) + sizeof( *TMSSatzEnde )));
    JSDateiKopf->Kontrolliert = TRUE;

    DosWrite( JSFile, JSDateiKopf, sizeof( *JSDateiKopf ), NULL );


    for( PersZaehler = 0; PersZaehler < JSDateiKopf->AnzPersonen; PersZaehler++ )
	{
	DosRead( TMSFile, TMSSatzAnfang, sizeof( *TMSSatzAnfang ), NULL );

	_fmemset( JSPersonenInfo, 0, sizeof( *JSPersonenInfo ) );
	JSPersonenInfo->Personalnummer = StdAsciiToBin( 9, TMSSatzAnfang->Personalnummer );

	JSPersonenInfo->LaengeName = sizeof( TMSSatzAnfang->Name );
	while( TMSSatzAnfang->Name[JSPersonenInfo->LaengeName - 1] == SPACECHAR && JSPersonenInfo->LaengeName > 0 )
	    JSPersonenInfo->LaengeName--;

	_fmemcpy( JSPersonenInfo->Name, TMSSatzAnfang->Name, JSPersonenInfo->LaengeName );

	JSPersonenInfo->JahrAnstellung = (WORD)StdAsciiToBin( 2, &(TMSSatzAnfang->Anstellung[0]) );
	if( JSPersonenInfo->JahrAnstellung >= 50 )
	    JSPersonenInfo->JahrAnstellung += 1900;
	else
	    JSPersonenInfo->JahrAnstellung += 2000;
	JSPersonenInfo->MonatAnstellung = (BYTE)StdAsciiToBin( 2, &(TMSSatzAnfang->Anstellung[2]) );
	JSPersonenInfo->TagAnstellung =   (BYTE)StdAsciiToBin( 2, &(TMSSatzAnfang->Anstellung[4]) );
	if( JSPersonenInfo->MonatAnstellung == 0 || JSPersonenInfo->TagAnstellung == 0 )
	    {
	    JSPersonenInfo->JahrAnstellung = 0;
	    JSPersonenInfo->MonatAnstellung = 0;
	    JSPersonenInfo->TagAnstellung = 0;
	    }

	JSPersonenInfo->JahrAustritt = (WORD)StdAsciiToBin( 2, &(TMSSatzAnfang->Austritt[0]) );
	if( JSPersonenInfo->JahrAustritt >= 50 )
	    JSPersonenInfo->JahrAustritt += 1900;
	else
	    JSPersonenInfo->JahrAustritt += 2000;
	JSPersonenInfo->MonatAustritt = (BYTE)StdAsciiToBin( 2, &(TMSSatzAnfang->Austritt[2]) );
	JSPersonenInfo->TagAustritt =	(BYTE)StdAsciiToBin( 2, &(TMSSatzAnfang->Austritt[4]) );
	if( JSPersonenInfo->MonatAustritt == 0 || JSPersonenInfo->TagAustritt == 0 )
	    {
	    JSPersonenInfo->JahrAustritt = 0;
	    JSPersonenInfo->MonatAustritt = 0;
	    JSPersonenInfo->TagAustritt = 0;
	    }

	JSPersonenInfo->Beschaeftigungsgrad = (BYTE)StdAsciiToBin( (BYTE)sizeof( TMSSatzAnfang->Beschaeftigungsgrad ), TMSSatzAnfang->Beschaeftigungsgrad );

	JSPersonenInfo->LaengeFunktion = sizeof( TMSSatzAnfang->Funktion );
	while( TMSSatzAnfang->Funktion[JSPersonenInfo->LaengeFunktion - 1] == SPACECHAR && JSPersonenInfo->LaengeFunktion > 0 )
	    JSPersonenInfo->LaengeFunktion--;

	_fmemcpy( JSPersonenInfo->Funktion, TMSSatzAnfang->Funktion, JSPersonenInfo->LaengeFunktion );

	for( FeldZaehler = 0; FeldZaehler < 7; FeldZaehler++ )
	    {
	    JSPersonenInfo->Felder[FeldZaehler].LaengeFeld = sizeof( TMSSatzAnfang->Felder[FeldZaehler] );
	    while( TMSSatzAnfang->Felder[FeldZaehler][JSPersonenInfo->Felder[FeldZaehler].LaengeFeld - 1] == SPACECHAR && JSPersonenInfo->Felder[FeldZaehler].LaengeFeld > 0 )
		JSPersonenInfo->Felder[FeldZaehler].LaengeFeld--;

	    _fmemcpy( JSPersonenInfo->Felder[FeldZaehler].Feld, TMSSatzAnfang->Felder[FeldZaehler], JSPersonenInfo->Felder[FeldZaehler].LaengeFeld );

	    if( JSPersonenInfo->Felder[FeldZaehler].LaengeFeld > 0 )
		{
		JSPersonenInfo->BenutzteFelder |= 1 << FeldZaehler;
		JSPersonenInfo->AnzFelder++;
		}
	    }

	DosWrite( JSFile, JSPersonenInfo, sizeof( *JSPersonenInfo ), NULL );

	for( TageZaehler = 0; TageZaehler < JSDateiKopf->AnzTage; TageZaehler++ )
	    {
	    DosRead( TMSFile, TMSSatzMitte, sizeof( *TMSSatzMitte ), NULL );
	    _fmemset( JSTag, 0, sizeof( *JSTag ) );

	    for( StempelungenZaehler = 0; StempelungenZaehler < 20; StempelungenZaehler++ )
		if( _fmemcmp( TMSSatzMitte->Stempelungen[StempelungenZaehler], (CHAR FAR *)"00000", 5 ) == 0 )
		    continue;
		else
		    {
		    JSTag->Stempelungen[StempelungenZaehler].EinAusgang = StdAsciiToBin( 1, &(TMSSatzMitte->Stempelungen[StempelungenZaehler][0]) ) - 1;
		    JSTag->Stempelungen[StempelungenZaehler].Zeit = StdAsciiToBin( 4, &(TMSSatzMitte->Stempelungen[StempelungenZaehler][1]) );
		    JSTag->AnzStempelungen++;
		    }

	    for( BegruendungenZaehler = 0; BegruendungenZaehler < 21; BegruendungenZaehler++ )
		if( _fmemcmp( TMSSatzMitte->Begruendungen[BegruendungenZaehler].Code, (CHAR FAR *)"000", 3 ) == 0 )
		    continue;
		else
		    {
		    JSTag->Begruendungen[BegruendungenZaehler].Code = StdAsciiToBin( 3, TMSSatzMitte->Begruendungen[BegruendungenZaehler].Code );
		    JSTag->Begruendungen[BegruendungenZaehler].Typ = StdAsciiToBin( 1, &TMSSatzMitte->Begruendungen[BegruendungenZaehler].Typ ) - 1;
		    JSTag->Begruendungen[BegruendungenZaehler].Herkunft = StdAsciiToBin( 1, &(TMSSatzMitte->Begruendungen[BegruendungenZaehler].Herkunft[0]) ) - 1;
		    JSTag->Begruendungen[BegruendungenZaehler].Dauer = StdAsciiToBin( 4, TMSSatzMitte->Begruendungen[BegruendungenZaehler].Dauer );
		    JSTag->AnzBegruendungen++;
		    }

	    for( ZKontiZaehler = 0; ZKontiZaehler < 20; ZKontiZaehler++ )
		if( _fmemcmp( TMSSatzMitte->Zeitkonti[ZKontiZaehler], (CHAR FAR *)"0000", 4 ) == 0 )
		    continue;
		else
		    {
		    JSTag->Zeitkonti[ZKontiZaehler] = StdAsciiToBin( 4, &(TMSSatzMitte->Zeitkonti[ZKontiZaehler][0]) );
		    if( TMSSatzMitte->Zeitkonti[ZKontiZaehler][4] == '-' )
			JSTag->Zeitkonti[ZKontiZaehler] = -(JSTag->Zeitkonti[ZKontiZaehler]);

		    JSTag->BenutzteZeitkonti |= 1 << ZKontiZaehler;
		    JSTag->AnzZeitkonti++;
		    }

	    DosWrite( JSFile, JSTag, sizeof( *JSTag ), NULL );
	    }

	FilePtrDistance = (SDWORD)sizeof( *TMSSatzEnde );
	DosSetFilePtr( TMSFile, &FilePtrDistance, FILE_CURRENT, NULL );
	}
    }
