// *************************************
// ***	Koelliker Broautomation AG	 ***
// *************************************
// ***		   Presentation	         ***
// *************************************

#include "JSLib.H"


#define SCRBACKGROUND		0x07
#define LIGHTTEXT		    0x0F
#define MARKTEXT		    0x1F


#define ANZANZGERICHTE		   8

#define BEENDEN			    0xFF

#define PATIENTENOFFSET 	0xA0
#define ANZPATIENTEN		   8

#define GERICHTEOFFSET		0xE0
#define ANZGERICHTE		      28

#define YPATIENT		      10
#define XPATIENTENTITEL 	   4
#define XPATIENT		      30

#define YGERICHT		      13
#define XGERICHTETITEL		   4
#define XGERICHT		      30


CHAR Firma[] = "Koelliker Broautomation AG";

#ifdef ITALIENISCH
CHAR Titel[][20] = { "Gestione pasti",
					 "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" };

CHAR Patiententitel[][20] = { "Paziente:",
							  "ÄÄÄÄÄÄÄÄÄ" };

CHAR Gerichtetitel[][20] = { "Menu:",
							 "ÄÄÄÄÄ" };

CHAR EingabeUngueltig[] = { "Invalid input!" };

CHAR Patienten[][30] = { "Fawer Ursula",
						 "Guhl Iris",
						 "Kunkel Simone",
						 "Manser Armin",
						 "Dupont Jean-Pierre",
						 "Dotta Emilio",
						 "Skripsky Juraj",
						 "Allemann Bea" };

CHAR Gerichte[][30] = { "Menu del giorno",
						"Menu leggero",
						"Vegetario",
						"Diabetes",
						"Piccata milanese",
						"Spaghetti Bolo.",
						"Piatto fitness",
						"Menu con pesce",
						"Zuppa del giorno",
						"Crema di verdura",
						"Minestrone",
						"Bouillon",
						"Piatto ticinese",
						"Piatto formaggi",
						"Piatto d'insalata",
						"Spec. della settimana",
						"Tirami su",
						"Birche",
						"Pudino di semola",
						"Ricotta docle",
						"Dolce del giorno",
						"Torta di frutta",
						"Insalata di frutta",
						"Succo di mele",
						"Succo d'arancia",
						"Caffe",
						"Latte freddo",
						"Sandwich" };
#endif

#ifdef DEUTSCH
CHAR Titel[][20] = { "Wahlmenusystem",
					 "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" };

CHAR Patiententitel[][20] = { "Patientenname:",
							  "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" };

CHAR Gerichtetitel[][20] = { "Essenswnsche:",
							 "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" };

CHAR EingabeUngueltig[] = { "Ungltige Eingabe!" };

CHAR Patienten[][30] = { "Fawer Ursula",
						 "Guhl Iris",
						 "Kunkel Simone",
						 "Manser Armin",
						 "Muster Peter",
						 "Tobler Willy",
						 "Skripsky Juraj",
						 "Allemann Bea" };

CHAR Gerichte[][30] = { "Menu del giorno",
						"Menu leggero",
						"Vegetario",
						"Diabetes",
						"Piccata milanese",
						"Spaghetti Bolo.",
						"Piatto fitness",
						"Menu con pesce",
						"Zuppa del giorno",
						"Crema di verdura",
						"Minestrone",
						"Bouillon",
						"Piatto ticinese",
						"Piatto formaggi",
						"Piatto d'insalata",
						"Spec. della settimana",
						"Tirami su",
						"Birche",
						"Pudino di semola",
						"Ricotta docle",
						"Dolce del giorno",
						"Torta di frutta",
						"Insalata di frutta",
						"Succo di mele",
						"Succo d'arancia",
						"Caffe",
						"Latte freddo",
						"Sandwich" };
#endif

#ifdef FRANZOESISCH
CHAR Titel[][20] = { "Gestion repas",
					 "ÄÄÄÄÄÄÄÄÄÄÄÄÄ" };

CHAR Patiententitel[][20] = { "Patient:",
							  "ÄÄÄÄÄÄÄÄ" };

CHAR Gerichtetitel[][20] = { "Menu:",
							 "ÄÄÄÄÄ" };

CHAR EingabeUngueltig[] = { "Erreur!" };

CHAR Patienten[][30] = { "Fawer Ursula",
						 "Guhl Iris",
						 "Kunkel Simone",
						 "Manser Armin",
						 "Dupont Jean-Pierre",
						 "Dotta Emilio",
						 "Skripsky Juraj",
						 "Allemann Bea" };

CHAR Gerichte[][30] = { "Menu du jour",
						"Menu l‚ger",
						"Menu v‚g‚",
						"Menu s/sel",
						"Potage du jour",
						"Bouillon l‚gumes",
						"Jus d'oranges",
						"Jus de tomates",
						"Ass. du jour",
						"Ass. viande froide",
						"Ass. crudit‚s",
						"Assiette No 4",
						"Ass. salade gr.",
						"Ass. salade pt.",
						"Ass. fromages",
						"Sp‚cialit‚ semaine",
						"Tirami su",
						"Bircher",
						"Dessert du jour",
						"Glac‚",
						"Pain complet",
						"Pain blanc",
						"Croissant",
						"Flan",
						"Caf‚",
						"Caf‚ s/caf‚ine",
						"Lait chaud",
						"" };
#endif


BYTE GetBarCode( VOID );


VOID Main( VOID )
	{
	BYTE AnzGerichte;
	BYTE Counter;
	WORD Code;

	ScrSetMode();
	ScrClr( SCRBACKGROUND );
	ScrSetCursor( 0, 25 );

	ScrWriteCenter( 0, 79, 2, Firma );
	ScrBoxChgColor( (BYTE)((78 - StdStrLen( Titel[0] )) / 2), 4,
			(BYTE)(79 - (78 - StdStrLen( Titel[0] )) / 2), 4,
			MARKTEXT );
    ScrWriteCenter( 0, 79, 4, Titel[0] );
    ScrWriteCenter( 0, 79, 5, Titel[1] );


    ScrWrite( XPATIENTENTITEL, YPATIENT, Patiententitel[0] );
	ScrWrite( XPATIENTENTITEL, (BYTE)(YPATIENT + 1), Patiententitel[1] );

    ScrWrite( 4, YGERICHT, Gerichtetitel[0] );
	ScrWrite( 4, (BYTE)(YGERICHT + 1), Gerichtetitel[1] );

	ScrBoxChgColor( (BYTE)(XPATIENTENTITEL - 1), YPATIENT, (BYTE)(XPATIENTENTITEL + StdStrLen( Patiententitel[0] )), YPATIENT, MARKTEXT );
    ScrSetCursor( XPATIENT, YPATIENT );
    Code = GetBarCode();

    while( Code != BEENDEN )
	{
	Code -= PATIENTENOFFSET;
	if( Code < ANZPATIENTEN )
	    {
	    ScrWrite( XPATIENT, YPATIENT, Patienten[Code] );
		ScrBoxChgColor( (BYTE)(XPATIENTENTITEL - 1), YPATIENT, (BYTE)(XPATIENTENTITEL + StdStrLen( Patiententitel[0] )), YPATIENT, SCRBACKGROUND );

	    AnzGerichte = 0;
		ScrBoxChgColor( (BYTE)(XGERICHTETITEL - 1), YGERICHT, (BYTE)(XGERICHTETITEL + StdStrLen( Gerichtetitel[0] )), YGERICHT, MARKTEXT );
	    ScrSetCursor( XGERICHT, YGERICHT );
	    Code = GetBarCode();

	    while( Code != BEENDEN )
		{
		Code -= GERICHTEOFFSET;
		if( Code < ANZGERICHTE )
		    if( AnzGerichte < ANZANZGERICHTE )
			{
			ScrWrite( XGERICHT, (BYTE)(YGERICHT + AnzGerichte), Gerichte[Code] );
			AnzGerichte++;
			ScrSetCursor( XGERICHT, (BYTE)(YGERICHT + AnzGerichte) );
			}

		Code = GetBarCode();
		}

		ScrBoxChgColor( (BYTE)(XGERICHTETITEL - 1), YGERICHT, (BYTE)(XGERICHTETITEL + StdStrLen( Gerichtetitel[0] )), YGERICHT, SCRBACKGROUND );

	    for( Counter = 0; Counter < ANZANZGERICHTE; Counter++ )
		ScrCharFill( XGERICHT, (BYTE)(YGERICHT + Counter), 40, SPACECHAR );

		ScrCharFill( XPATIENT, YPATIENT, 40, SPACECHAR );
		ScrBoxChgColor( (BYTE)(XPATIENTENTITEL - 1), YPATIENT, (BYTE)(XPATIENTENTITEL + StdStrLen( Patiententitel[0] )), YPATIENT, MARKTEXT );
	    ScrSetCursor( XPATIENT, YPATIENT );
	    }

	Code = GetBarCode();
	}

    ScrRestoreMode();
    }


BYTE GetBarCode( VOID )
    {
    WORD Key;
    WORD Buffer[2] = { 0, 0 };
	BYTE Counter;
	BYTE Code;

    Counter = 0;

    Key = BiosGetKey();
    while( Key != KBENTER )
	{
	if( Counter == 2 )
	    {
	    Buffer[0] = Buffer[1];
	    Counter--;
	    }

	Buffer[Counter] = Key;
	Counter++;
	Key = BiosGetKey();
	}

    for( Counter = 0; Counter < 2; Counter++ )
	if( (BYTE)Buffer[Counter] >= 'A' )
	    {
	    Buffer[Counter] = Buffer[Counter] & 0xDF;
	    Buffer[Counter] -= 'A' - '9' - 1;
	    }

	Code = ((BYTE)Buffer[0] - '0') << 4;
	Code += (BYTE)Buffer[1] - '0';

    return( Code );
    }
