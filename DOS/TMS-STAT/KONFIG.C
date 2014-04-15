// ****************************
// *** Statistik - Programm ***
// ***	    Konfigmenu	    ***
// ****************************
// ***			    ***
// ****************************

#include "constant.h"

void Begruendauswahl( void );
void Abteilauswahl( void );
void Tagbestimmung();
void KonfigInit( void );
bool WriteBegruend( struct begruendung _far *begruendung, word quantity );
bool WriteAbteil( char *key, struct abteilung _far *abteilung, word quantity );
bool ReadBegruend( struct begruendung _far **begruendung, word *quantity );
bool ReadAbteil( char *key, struct abteilung _far **abteilung, word *quantity );
void ErrorMessage( char *string );

box KonfigButton[5] =
    { { BUTTON, 20,  6, 59,  8, MENU, CHOICE, SINGLE, FALSE,  TRUE, "BegrÅndungen auswÑhlen..." },
      { BUTTON, 20,  8, 59, 10, MENU, CHOICE, SINGLE,  TRUE,  TRUE, "Abteilungen auswÑhlen..." },
      { BUTTON, 20, 10, 59, 12, MENU, CHOICE, SINGLE,  TRUE, FALSE, "Arbeitstag bestimmen..." },
      { BUTTON, 20, 14, 59, 16, MENU, CHOICE, SINGLE, FALSE,  TRUE, "Konfigurationsdatei initalisieren" },
      { BUTTON, 20, 16, 59, 18, MENU, CHOICE, SINGLE,  TRUE, FALSE, "ZurÅck zum HauptmenÅ..." } };

box BegruendList =
    { FRAME, 10, 6, 69, 21, MENU, CHOICE, DOUBLE, FALSE, FALSE, "" };

box WarningBox =
    { INFO, 22, 4, 57, 13, MENU, CHOICE, DOUBLE, FALSE, FALSE, "Achtung:" };

box WarningButton[2] =
    { { BUTTON, 28, 16, 51, 18, MENU, CHOICE, SINGLE, FALSE,  TRUE, "Fortsetzten..." },
      { BUTTON, 28, 18, 51, 20, MENU, CHOICE, SINGLE,  TRUE, FALSE, "Abbrechen" } };

void Konfigmenu( void )
    {
    byte choice;

    BoxDraw( &WarningBox );
    BoxWrite( &WarningBox, 1, 1, LEFT, "Falls Sie eine der Funktionen im" );
    BoxWrite( &WarningBox, 1, 2, LEFT, "Konfigurationsmenu ausfÅhren," );
    BoxWrite( &WarningBox, 1, 3, LEFT, "mÅssen alle kumulierten Dateien" );
    BoxWrite( &WarningBox, 1, 4, LEFT, "neugeneriert werden." );
    Statusline( "", "</> <Enter>" );
    if( ButtonMenu( 2, 2, WarningButton, NULL ) == 2 )
	{
	ScrClr( BACKGROUND );
	return;
	}

    ScrClr( BACKGROUND );

    do
	{
	Statusline( "Konfigurationsmenu", "</> <Enter>" );

	choice = ButtonMenu( 5, 1, KonfigButton, NULL );
	ScrClr( BACKGROUND );

	switch( choice )
	    {
	    case 1:
		Begruendauswahl();
		break;

	    case 2:
		Abteilauswahl();
		break;

	    case 3:
		Tagbestimmung();
		break;

	    case 4:
		KonfigInit();
		break;
	    }
	}
    while( choice != 5 );

    ScrClr( BACKGROUND );

    }

void Begruendauswahl( void )
    {
    box InstructionBox =
	{ FRAME, 4, 2, 75, 4, MENU, CHOICE, DOUBLE, FALSE, FALSE, "" };

    file begruend_cfg;
    struct begruendung _far *begruendung;
    word entries;

    if( ReadBegruend( &begruendung, &entries ) )
	return;

    Statusline( "BegrÅndungsauswahl", "</> <Leertaste> <Enter>" );

    BoxDraw( &InstructionBox );
    BoxWrite( &InstructionBox, 0, 0, CENTER, "BegrÅndungen mit Leertaste an-/abwÑhlen, mit Enter abschliessen." );

    CheckList( &BegruendList, (byte)entries, (struct checkline _far *)begruendung );

    if( WriteBegruend( (void _far *)begruendung, (byte)entries ) )
	return;

    ScrClr( BACKGROUND );
    }

void Abteilauswahl( void )
    {
    box InputBox =
	{ FRAME, 18, 7, 61, 14, MENU, CHOICE, DOUBLE, FALSE, FALSE, "" };

    file abteil_cfg;
    struct abteilung _far *abteilung;
    word entries;
    char abteilkey[KEYLENGTH];
    char string[KEYLENGTH+3];
    byte counter;
    byte subcounter;
    word input;

    if( ReadAbteil( abteilkey, &abteilung, &entries ) )
	return;

    string[0] = '<'; string[KEYLENGTH+1] = '>'; string[KEYLENGTH+2] = 0;
    for( counter = 0; counter < KEYLENGTH; counter++ )
	{
	string[counter + 1] = abteilkey[counter];
	if( string[counter + 1] == 0 )
	    string[counter + 1] = ' ';
	}

    Statusline( "Abteilungsauswahl", "<Del> <Enter>" );
    BoxDraw( &InputBox );
    BoxWrite( &InputBox, 0, 1, CENTER, "Neue Abteilungswahl eingeben," );
    BoxWrite( &InputBox, 0, 2, CENTER, "mit Enter abschliessen." );
    BoxWrite( &InputBox, 0, 4, CENTER, "<     >" );

    counter = 0;

    for( ; ; )
	{
	for( subcounter = 0; subcounter < KEYLENGTH; subcounter++ )
	    ScrCharacter( (byte)(37 + subcounter), InputBox.y1 + 5, abteilkey[subcounter] );

	ScrSetCursor( (byte)(37 + counter), InputBox.y1 + 5 );
	input = BiosGetKey();

	if( input == KBENTER )
	    break;

	if( input == KBDEL )
	    {
	    for( subcounter = 0; subcounter < KEYLENGTH; subcounter++ )
		abteilkey[subcounter] = 0;
	    counter = 0;
	    continue;
	    }

	if( counter == 0 )
	    for( subcounter = 0; subcounter < KEYLENGTH; subcounter++ )
		abteilkey[subcounter] = 0;

	if( ((byte)input > 0x20) && ((byte)input <= 0x7F) && (counter < KEYLENGTH) )
	    {
	    abteilkey[counter] = (byte)input;
	    counter++;
	    }

	if( (input == KBBACKSPACE) && (counter > 0) )
	    {
	    counter--;
	    abteilkey[counter] = 0;
	    }
	}

    if( WriteAbteil( abteilkey, (void _far *)abteilung, (byte)entries ) )
	return;

    ScrSetCursor( 0, 25 );
    ScrClr( BACKGROUND );
    }


void Tagbestimmung()
    {
    file tag_cfg;
    word daylength;
    byte hours;
    byte minutes;

    bool flag_hours = TRUE;
    bool flag_minutes = FALSE;

    word input;

    char status[] = "--.-- Stunden";
    box InputBox =
	{ FRAME, 18, 7, 61, 14, MENU, CHOICE, DOUBLE, FALSE, FALSE, "" };

    tag_cfg = DosOpenFile( DOS_ACCESS_RDONLY, TAG_CFG );
    if( DosGetErrorcode() )
	{
	ErrorMessage( "Konfigurationsdatei kann nicht geîffnet werden!" );
	return( TRUE );
	}

    DosReadFile( tag_cfg, sizeof(daylength), (void _far *)&daylength );
    DosCloseFile( tag_cfg );

    hours = daylength / 60;
    minutes = daylength % 60;

    Statusline( "Arbeitstagbestimmung", "</> <\x1B/\x1A> <Enter>" );
    BoxDraw( &InputBox );
    BoxWrite( &InputBox, 0, 1, CENTER, "Neuen Arbeitstag bestimmen," );
    BoxWrite( &InputBox, 0, 2, CENTER, "mit Enter abschliessen." );

    BoxMark( &InputBox, 14, 4, 15, 4 );

    do
	{
	status[0] = (hours / 10) + '0';
	status[1] = (hours % 10) + '0';
	status[3] = (minutes / 10) + '0';
	status[4] = (minutes % 10) + '0';
	BoxWrite( &InputBox, 0, 4, CENTER, status );

	input = BiosGetKey();

	switch( input )
	    {
	    case KBLEFT:
		BoxUnMark( &InputBox, 14, 4, 18, 4 );
		flag_hours = TRUE;
		flag_minutes = FALSE;
		BoxMark( &InputBox, 14, 4, 15, 4 );
		break;

	    case KBRIGHT:
		BoxUnMark( &InputBox, 14, 4, 18, 4 );
		flag_hours = FALSE;
		flag_minutes = TRUE;
		BoxMark( &InputBox, 17, 4, 18, 4 );
		break;

	    case KBUP:
		if( flag_minutes )
		    {
		    if( minutes != 59 )
			minutes++;
		    break;
		    }

		if( flag_hours )
		    {
		    if( hours != 23 )
			hours++;
		    break;
		    }
		break;

	    case KBDOWN:
		if( flag_minutes )
		    {
		    if( minutes != 0 )
			minutes--;
		    break;
		    }

		if( flag_hours )
		    {
		    if( hours != 0 )
			hours--;
		    break;
		    }
		break;
	    }
	}
    while( input != KBENTER );

    daylength = (hours * 60) + minutes;

    tag_cfg = DosCreateFile( DOS_ATTRIB_NORMAL, TAG_CFG );
    if( DosGetErrorcode() )
	{
	ErrorMessage( "TAG.CFG: Datei kann nicht erstellt werden!" );
	return( TRUE );
	}

    DosWriteFile( tag_cfg, sizeof(daylength), (void _far *)&daylength );
    DosCloseFile( tag_cfg );

    ScrClr( BACKGROUND );
    }


void KonfigInit( void )
    {
    file begruend_cod;
    file abteil_cod;
    file tag_cfg;

    box StatusBox = { FRAME, 10, 8, 69, 14, MENU, CHOICE, DOUBLE, FALSE, FALSE, "" };
    box OKButton = { BUTTON, 36, 16, 43, 18, MENU, CHOICE, DOUBLE, FALSE, FALSE, "OK" };
    char abteilkey[KEYLENGTH];

    struct begruendung _far *begruendung;
    struct abteilung _far *abteilung;

    word entries;
    word daylength = 480;
    word counter;
    word subcounter;
    word tempword;
    char tempchar;
    byte bytecounter;
    bool string = FALSE;

    for( bytecounter = 0; bytecounter < KEYLENGTH; bytecounter++ )
	abteilkey[bytecounter] = 0;

    begruend_cod = DosOpenFile( DOS_ACCESS_RDONLY, BEGRUEND_COD );
    if( DosGetErrorcode() )
	{
	ErrorMessage( "BEGRUEND.COD: Datei kann nicht geîffnet werden!" );
	return;
	}

    BoxDraw( &StatusBox );
    BoxWrite( &StatusBox, 0, 0, CENTER, "BegrÅndungsverzeichnis wird generiert..." );

    entries = 0;
    do
	{
	tempword = DosReadFile( begruend_cod, sizeof(tempchar), (void _far *)&tempchar );
	if( tempchar == '"' )
	    string = !string;

	if( (!string) && (tempchar == '-') )
	    entries++;
	}
    while( tempword == sizeof(tempchar)	);
    DosResetFile( begruend_cod );

    begruendung = DosAllocFarMem( sizeof(struct begruendung) * entries );

    for( counter = 0; counter < entries; counter++ )
	{
	do
	    DosReadFile( begruend_cod, sizeof(tempchar), (void _far *)&tempchar );
	while( tempchar != '-' );
	begruendung[counter].checkmark = TRUE;
	DosReadFile( begruend_cod, sizeof(begruendung->number), begruendung[counter].number );
	DosReadFile( begruend_cod, sizeof(begruendung->genus), &begruendung[counter].genus );
	begruendung[counter].genus &= 0xDF;
	begruendung[counter].space = ' ';

	do
	    tempword = DosReadFile( begruend_cod, sizeof(tempchar), (void _far *)&tempchar );
	while( tempchar != '"' && tempword == 1 );

	for( subcounter = 0; subcounter < 75; subcounter++ )
	    {
	    tempword = DosReadFile( begruend_cod, sizeof(char), &begruendung[counter].description[subcounter] );

	    if( (begruendung[counter].description[subcounter] == '"') || (tempword != 1) )
		break;
	    }

	for( ; subcounter < 74; subcounter++ )
	    begruendung[counter].description[subcounter] = 0;

	begruendung[counter].description[74] = 0x00;

	DosReadFile( begruend_cod, 0x0001, (void _far *)&tempchar );
	if( tempchar != '.' )
	    {
		ErrorMessage( "BEGRUEND.COD: Dateiformat fehlerhaft!" );
		return;
	    }
	}

    if( WriteBegruend( begruendung, entries ) )
	return;

    DosCloseFile( begruend_cod );


    abteil_cod = DosOpenFile( DOS_ACCESS_RDONLY, ABTEIL_COD );
    if( DosGetErrorcode() )
	{
	ErrorMessage( "ABTEIL.COD: Datei kann nicht geîffnet werden!" );
	return;
	}

    BoxWrite( &StatusBox, 0, 2, CENTER, "Abteilungsverzeichnis wird generiert..." );

    entries = 0;
    do
	{
	tempword = DosReadFile( abteil_cod, sizeof(tempchar), (void _far *)&tempchar );
	if( tempchar == '"' )
	    string = !string;

	if( (!string) && (tempchar == '-') )
	    entries++;
	}
    while( tempword == sizeof(tempchar)	);
    DosResetFile( abteil_cod );

    abteilung = DosAllocFarMem( sizeof(struct abteilung) * entries );

    for( counter = 0; counter < entries; counter++ )
	{
	do
	    DosReadFile( begruend_cod, sizeof(tempchar), (void _far *)&tempchar );
	while( tempchar != '-' );
	DosReadFile( abteil_cod, KEYLENGTH, abteilung[counter].code );
	abteilung[counter].space = ' ';

	do
	    tempword = DosReadFile( abteil_cod, sizeof(tempchar), (void _far *)&tempchar );
	while( tempchar != '"' && tempword == 1 );

	for( subcounter = 0; subcounter < 75; subcounter++ )
	    {
	    tempword = DosReadFile( abteil_cod, sizeof(char), &abteilung[counter].description[subcounter] );

	    if( (abteilung[counter].description[subcounter] == '"') || (tempword != 1) )
		break;
	    }

	for( ; subcounter < 74; subcounter++ )
	    abteilung[counter].description[subcounter] = 0x00;

	abteilung[counter].description[74] = 0x00;

	DosReadFile( abteil_cod, sizeof(tempchar), (void _far *)&tempchar );
	if( tempchar != '.' )
	    {
		ErrorMessage( "ABTEIL.COD: Dateiformat fehlerhaft!" );
		return;
	    }
	}

    if( WriteAbteil( abteilkey, abteilung, entries ) )
	return;

    DosCloseFile( abteil_cod );

    tag_cfg = DosCreateFile( DOS_ATTRIB_NORMAL, TAG_CFG );
    if( DosGetErrorcode() )
	{
	ErrorMessage( "TAG.CFG: Datei kann nicht erstellt werden!" );
	return( TRUE );
	}

    DosWriteFile( tag_cfg, sizeof(daylength), (void _far *)&daylength );
    DosCloseFile( tag_cfg );

    BoxWrite( &StatusBox, 0, 4, CENTER, "Initialisierung abgeschlossen." );
    Statusline( "", "<Enter>" );
    ButtonMenu( 1, 1, &OKButton, NULL );

    ScrClr( BACKGROUND );
    }

bool WriteBegruend( struct begruendung _far *begruendung, word quantity	)
    {
    file begruend_cfg;

    begruend_cfg = DosCreateFile( DOS_ATTRIB_NORMAL, BEGRUEND_CFG );
    if( DosGetErrorcode() )
	{
	ErrorMessage( "BEGRUEND.CFG: Datei kann nicht erstellt werden!" );
	return( TRUE );
	}

    DosWriteFile( begruend_cfg, sizeof(quantity), (void _far *)&quantity );
    DosWriteFile( begruend_cfg, quantity * sizeof( struct begruendung ), begruendung );

    DosCloseFile( begruend_cfg );
    DosFreeFarMem( begruendung );

    return( FALSE );
    }

bool WriteAbteil( char *key, struct abteilung _far *abteilung, word quantity )
    {
    file abteil_cfg;

    abteil_cfg = DosCreateFile( DOS_ATTRIB_NORMAL, ABTEIL_CFG );
    if( DosGetErrorcode() )
	{
	ErrorMessage( "ABTEIL.CFG: Datei kann nicht erstellt werden!" );
	return( TRUE );
	}

    DosWriteFile( abteil_cfg, KEYLENGTH, (void _far *)key );
    DosWriteFile( abteil_cfg, sizeof(quantity), (void _far *)&quantity );
    DosWriteFile( abteil_cfg, quantity * sizeof( struct abteilung ), abteilung );

    DosCloseFile( abteil_cfg );
    DosFreeFarMem( abteilung );

    return( FALSE );
    }

bool ReadBegruend( struct begruendung _far **begruendung, word *quantity )
    {
    file begruend_cfg;

    begruend_cfg = DosOpenFile( DOS_ACCESS_RDONLY, BEGRUEND_CFG );
    if( DosGetErrorcode() )
	{
	ErrorMessage( "Konfigurationsdatei kann nicht geîffnet werden!" );
	return( TRUE );
	}

    DosReadFile( begruend_cfg, sizeof(*quantity), (void _far *)quantity );

    *begruendung = DosAllocFarMem( sizeof(struct begruendung) * (*quantity) );
    DosReadFile( begruend_cfg, sizeof(struct begruendung) * (*quantity), (void _far *)*begruendung );
    DosCloseFile( begruend_cfg );

    return( FALSE );
    }

bool ReadAbteil( char *key, struct abteilung _far **abteilung, word *quantity )
    {
    file abteil_cfg;

    abteil_cfg = DosOpenFile( DOS_ACCESS_RDONLY, ABTEIL_CFG );
    if( DosGetErrorcode() )
	{
	ErrorMessage( "Konfigurationsdatei kann nicht geîffnet werden!" );
	return( TRUE );
	}

    DosReadFile( abteil_cfg, KEYLENGTH, (void _far *)key );
    DosReadFile( abteil_cfg, sizeof(*quantity), (void _far *)quantity );

    *abteilung = DosAllocFarMem( sizeof(struct abteilung) * (*quantity) );
    DosReadFile( abteil_cfg, sizeof(struct abteilung) * (*quantity), (void _far *)*abteilung );
    DosCloseFile( abteil_cfg );

    return( FALSE );
    }

void ErrorMessage( char *string )
    {
    box ErrorBox = { FRAME, 10,	11, 69, 13, MENU, CHOICE, DOUBLE, FALSE, FALSE, "" };
    box OKButton = { BUTTON, 36, 15, 43, 17, MENU, CHOICE, DOUBLE, FALSE, FALSE, "OK" };

    ScrClr( BACKGROUND );
    BoxDraw( &ErrorBox );
    BoxWrite( &ErrorBox, 0, 0, CENTER, string );
    Statusline( "", "<Enter>" );
    ButtonMenu( 1, 1, &OKButton, NULL );
    ScrClr( BACKGROUND );
    }
