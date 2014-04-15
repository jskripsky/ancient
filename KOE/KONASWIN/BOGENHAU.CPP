#include "FD_Macro.H"

// PAGE( TITLE )

// FIELD( RX, RY, RW, RH )
// LABEL( LRX, LRY, LRW, LABEL_TEXT )
// OBLIGATORY
// DISABLE_PRINT

// ENTRY( ID, MAXLEN, DEFAULT )
// (ENTRY_HEIGHT)

// SELECTION( ID, DISPLAY_TYPE, DEFAULT_SELECTION, NO_SELECTION )
// (DISPLAY_TYPE: LISTBOX / RADIOBUTTONS)
// ITEM( TEXT )


START_FORM_DEFINITION


PAGE( "Aufnahme" )

ENTRY( "Name", 30, "" )
	FIELD(  30,   0, 120, ENTRY_HEIGHT )
	LABEL(   0,   1,  30, "Name" )
	OBLIGATORY

ENTRY( "Vorname", 15, "" )
	FIELD(  30,  11, 120, ENTRY_HEIGHT )
	LABEL(   0,  12,  30, "Vorname" )
	OBLIGATORY

ENTRY( "GeburtsDatum", 10, "" )
	FIELD(  50,  27,  45, ENTRY_HEIGHT )
	LABEL(   0,  28,  50, "Geburtsdatum" )
	OBLIGATORY

SELECTION( "Geschlecht", LISTBOX, 0, -1 )
	ITEM( "Männlich" )
	ITEM( "Weiblich" )
	FIELD(  40,  44,  36, 20 )
	LABEL(   0,  43,  40, "Geschlecht" )
	PRINT_ITEM( "M" )
	PRINT_ITEM( "W" )

ENTRY( "AufnahmeNr.", 8, "95012355" )
	FIELD(   0,  75,  36, ENTRY_HEIGHT )
	LABEL(   0,  66,  50, "Aufnahmenr." )
	OBLIGATORY

ENTRY( "AufnahmeDatum", 8, "25.04.95" )
	FIELD(  50,  75,  36, ENTRY_HEIGHT )
	LABEL(  50,  66,  50, "Datum" )
	OBLIGATORY

ENTRY( "AufnahmeZeit", 5, "14:00" )
	FIELD(  94,  75,  24, ENTRY_HEIGHT )
	LABEL(  94,  66,  30, "Zeit" )
	OBLIGATORY

ENTRY( "Strasse", 30, "" )
	FIELD(  27,  92, 129, ENTRY_HEIGHT )
	LABEL(   0,  93,  27, "Strasse" )
	OBLIGATORY

ENTRY( "PLZ", 8, "" )
	FIELD(  27, 103,  36, ENTRY_HEIGHT )
	LABEL(   0, 104,  27, "PLZ" )
	OBLIGATORY

ENTRY( "Ort", 20, "" )
	FIELD(  86, 103,  70, ENTRY_HEIGHT )
	LABEL(  66, 104,  20, "Ort" )
	OBLIGATORY

ENTRY( "KassenNr.", 7, "" )
	FIELD(   0, 128,  34, ENTRY_HEIGHT )
	LABEL(   0, 119,  36, "Kassennr." )

ENTRY( "Krankenkassenname", 28, "" )
	FIELD(  45, 128, 108, ENTRY_HEIGHT )
	LABEL(  45, 119,  90, "Krankenkassenname" )

SELECTION( "Allgemein/Privat", LISTBOX, 0, 0 )
	ITEM( "(leer)" )
	ITEM( "Allgemein" )
	ITEM( "Privat" )
	FIELD(  60, 145,  50, 28 )
	LABEL(   0, 146,  60, "Allgemein/Privat" )
	OBLIGATORY
	PRINT_ITEM( "" )
	PRINT_ITEM( "Akut     2" )
	PRINT_ITEM( "Akut ML  1" )


PAGE( "Kostenträger" )

SELECTION( "Kostenträger", LISTBOX, 0, -1 )
	ITEM( "Noch unbekannt" )
	ITEM( "ADLER VERS:-10625 BERLIN" )
	ITEM( "ALL. PRIV. VERS.-65001 WIESBADEN" )
	ITEM( "ALLIANZ VERS. AG-13162 BERLIN" )
	ITEM( "AOK AACHEN" )
	ITEM( "AOK AALEN" )
	ITEM( "AOK ACHERN" )
	ITEM( "AOK AHRENSBURG" )
	ITEM( "AOK AHRWEILER-53456 BAD NEUENAHR-" )
	ITEM( "AOK AICHACH" )
	ITEM( "AOK ALBSTADT" )
	ITEM( "AOK ALFELD" )
	ITEM( "AOK ALSFELD" )
	ITEM( "AOK ALTDORF" )
	ITEM( "AOK ALTENKIRCHEN" )
	ITEM( "AOK ALTENSTEIG" )
	ITEM( "AOK ALTOETTING" )
	ITEM( "AOK ALTOETTING - MUEHLDORF" )
	ITEM( "AOK AMBERG" )
	ITEM( "AOK AMMERLAND-26641 WESTERSTEDE" )
	ITEM( "AOK ANSBACH" )
	ITEM( "AOK ARNSBERG" )
	ITEM( "AOK ARZBERG" )
	ITEM( "AOK ASCHAFFENBURG" )
	ITEM( "AOK AUGSBURG" )
	ITEM( "AOK AURICH" )
	ITEM( "AOK BABENHAUSEN" )
	FIELD(   0,  10,  150, 90 )
	LABEL(   0,   0,  50, "Kostenträger" )
	PRINT_ITEM( "UNBEKANNT                " )
	PRINT_ITEM( "ADLER-BER                " )
	PRINT_ITEM( "APK                      " )
	PRINT_ITEM( "ALL-BER                  " )
	PRINT_ITEM( "AOK-AAC                  " )
	PRINT_ITEM( "AOK-AAL                  " )
	PRINT_ITEM( "AOK-ACH                  " )
	PRINT_ITEM( "AOK-AHR                  " )
	PRINT_ITEM( "AOK-NEUE                 " )
	PRINT_ITEM( "AOK-AICH                 " )
	PRINT_ITEM( "AOK-ALB                  " )
	PRINT_ITEM( "AOK-ALF                  " )
	PRINT_ITEM( "AOK-ALS                  " )
	PRINT_ITEM( "AOK-ALTD                 " )
	PRINT_ITEM( "AOK-ALTEN                " )
	PRINT_ITEM( "AOK-ALTE                 " )
	PRINT_ITEM( "AOK-ALTOE                " )
	PRINT_ITEM( "AOK-ALT                  " )
	PRINT_ITEM( "AOK-AMB                  " )
	PRINT_ITEM( "AOK-WESTE                " )
	PRINT_ITEM( "AOK-ANS                  " )
	PRINT_ITEM( "AOK-ARN                  " )
	PRINT_ITEM( "AOK-ARZ                  " )
	PRINT_ITEM( "AOK-ASC                  " )
	PRINT_ITEM( "AOK-AUG                  " )
	PRINT_ITEM( "AOK-AUR                  " )
	PRINT_ITEM( "AOK-BAB                  " )

ENTRY( "Zusatzinfo I", 38, "" )
	FIELD(   0, 120, 150, ENTRY_HEIGHT )
	LABEL(   0, 110, 120, "Zusatzinfo (z.B. Kürzel, Adresse)" )

ENTRY( "Zusatzinfo II", 38, "" )
	FIELD(   0, 131, 150, ENTRY_HEIGHT )

ENTRY( "Zusatzinfo III", 38, "" )
	FIELD(   0, 142, 150, ENTRY_HEIGHT )


PAGE( "Station" )

SELECTION( "Station", LISTBOX, 0, 0 )
	ITEM( "(leer)" )
	ITEM( "Chirurgie 1" )
	ITEM( "Chirurgie 2" )
	ITEM( "Chirurgie 3" )
	ITEM( "Chirurgie 4" )
	ITEM( "Chirurgie 5" )
	ITEM( "Chirurgie 6" )
	ITEM( "Röntgen 1" )
	ITEM( "Röntgen 2" )
	FIELD(   0,  10, 150, 150 )
	LABEL(   0,   0, 120, "Befund an/Entlassen auf" )
	OBLIGATORY
	PRINT_ITEM( "                        " )
	PRINT_ITEM( "Chirurgie 1             " )
	PRINT_ITEM( "Chirurgie 2             " )
	PRINT_ITEM( "Chirurgie 3             " )
	PRINT_ITEM( "Chirurgie 4             " )
	PRINT_ITEM( "Chirurgie 5             " )
	PRINT_ITEM( "Chirurgie 6             " )
	PRINT_ITEM( "Röntgen 1               " )
	PRINT_ITEM( "Röntgen 2               " )


PAGE( "Personalien" )

SELECTION( "Einlieferung", LISTBOX, 0, -1 )
	ITEM( "Selbst" )
	ITEM( "Rettungswagen" )
	ITEM( "Notarztwagen" )
	ITEM( "Hubschrauber" )
	FIELD(   0,  10,  100, 35 )
	LABEL(   0,   0,  80, "Eingeliefert durch" )
	PRINT_ITEM( "Selbst              " )
	PRINT_ITEM( "Rettungswagen       " )
	PRINT_ITEM( "Notarztwagen        " )
	PRINT_ITEM( "Hubschrauber        " )

ENTRY( "Arbeitgeber Name", 30, "" )
	FIELD(   0,  65, 112, ENTRY_HEIGHT )
	LABEL(   0,  55, 100, "Arbeitgeber Name, Str., PLZ, Ort" )

ENTRY( "Strasse", 30, "" )
	FIELD(   0,  76, 112, ENTRY_HEIGHT )

ENTRY( "PLZ, Ort", 28, "" )
	FIELD(   0,  87, 112, ENTRY_HEIGHT )


PAGE( "Anamnese" )

ENTRY( "Hauptversicherter", 30, "" )
	FIELD(  60,   0,  90, ENTRY_HEIGHT )
	LABEL(   0,   1,  60, "Hauptversicherter" )

ENTRY( "GebDatumHauptvers.", 10, "" )
	FIELD(  60,  13,  60, ENTRY_HEIGHT )
	LABEL(   0,  14,  60, "Geburtsdatum" )

SELECTION( "Status", LISTBOX, 0, -1 )
	ITEM( "HV" )
	ITEM( "FAM" )
	ITEM( "REN" )
	FIELD(  30,  28,  30, 28 )
	LABEL(   0,  29,  30, "Status" )
	PRINT_ITEM( "HV " )
	PRINT_ITEM( "FAM" )
	PRINT_ITEM( "REN" )

ENTRY( "Arztnummer", 8, "" )
	FIELD( 115,  32,  38, ENTRY_HEIGHT )
	LABEL(  70,  33,  45, "Arztnummer" )

ENTRY( "Anamnese", 38, "" )
	FIELD(   0,  67, 150, ENTRY_HEIGHT )
	LABEL(   0,  57, 100, "Anamnese" )

ENTRY( "A2", 38, "" )
	FIELD(   0,  78, 150, ENTRY_HEIGHT )
ENTRY( "A3", 38, "" )
	FIELD(   0,  89, 150, ENTRY_HEIGHT )
ENTRY( "A4", 38, "" )
	FIELD(   0, 100, 150, ENTRY_HEIGHT )
ENTRY( "A5", 38, "" )
	FIELD(   0, 111, 150, ENTRY_HEIGHT )
ENTRY( "A6", 38, "" )
	FIELD(   0, 122, 150, ENTRY_HEIGHT )
ENTRY( "A7", 38, "" )
	FIELD(   0, 133, 150, ENTRY_HEIGHT )
ENTRY( "A8", 38, "" )
	FIELD(   0, 144, 150, ENTRY_HEIGHT )
ENTRY( "A9", 38, "" )
	FIELD(   0, 155, 150, ENTRY_HEIGHT )

PAGE( "Aufnahmebefund" )

ENTRY( "Aufnahmebefund", 38, "" )
	FIELD(   0,  10, 150, ENTRY_HEIGHT )
	LABEL(   0,   0, 100, "Aufnahmebefund" )
	DISABLE_PRINT

ENTRY( "A2", 38, "" )
	FIELD(   0,  21, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A3", 38, "" )
	FIELD(   0,  32, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A4", 38, "" )
	FIELD(   0,  43, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A5", 38, "" )
	FIELD(   0,  54, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A6", 38, "" )
	FIELD(   0,  65, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A7", 38, "" )
	FIELD(   0,  76, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A8", 38, "" )
	FIELD(   0,  87, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A9", 38, "" )
	FIELD(   0,  98, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A7", 38, "" )
	FIELD(   0, 109, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A8", 38, "" )
	FIELD(   0, 120, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A9", 38, "" )
	FIELD(   0, 131, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A9", 38, "" )
	FIELD(   0, 142, 150, ENTRY_HEIGHT )
	DISABLE_PRINT


PAGE( "Diagnose/Behandlung" )

ENTRY( "Aufnahmediagnose", 38, "" )
	FIELD(   0,  10, 150, ENTRY_HEIGHT )
	LABEL(   0,   0, 100, "Aufnahmediagnose" )
	DISABLE_PRINT

ENTRY( "A2", 38, "" )
	FIELD(   0,  21, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A3", 38, "" )
	FIELD(   0,  32, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A4", 38, "" )
	FIELD(   0,  43, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A5", 38, "" )
	FIELD(   0,  54, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A6", 38, "" )
	FIELD(   0,  65, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A7", 38, "" )
	FIELD(   0,  76, 150, ENTRY_HEIGHT )
	DISABLE_PRINT

ENTRY( "Behandlung", 38, "" )
	FIELD(   0, 106, 150, ENTRY_HEIGHT )
	LABEL(   0,  96, 100, "Behandlung" )
	DISABLE_PRINT
ENTRY( "A9", 38, "" )
	FIELD(   0, 116, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A7", 38, "" )
	FIELD(   0, 126, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A8", 38, "" )
	FIELD(   0, 136, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A9", 38, "" )
	FIELD(   0, 146, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A9", 38, "" )
	FIELD(   0, 156, 150, ENTRY_HEIGHT )
	DISABLE_PRINT

PAGE( "Sonstiges" )

ENTRY( "Medikamente + Leistungen", 38, "" )
	FIELD(   0,  10, 150, ENTRY_HEIGHT )
	LABEL(   0,   0, 100, "Medikamente + Leistungen" )
	DISABLE_PRINT

ENTRY( "A2", 38, "" )
	FIELD(   0,  21, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A3", 38, "" )
	FIELD(   0,  32, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A4", 38, "" )
	FIELD(   0,  43, 150, ENTRY_HEIGHT )
	DISABLE_PRINT
ENTRY( "A5", 38, "" )
	FIELD(   0,  54, 150, ENTRY_HEIGHT )
	DISABLE_PRINT

ENTRY( "Nachschau Datum", 8, "" )
	FIELD(  50,  70,  40, ENTRY_HEIGHT )
	LABEL(   0,  71,  50, "Nachschau am" )
	DISABLE_PRINT

ENTRY( "Nachschau Zeit", 5, "" )
	FIELD( 110,  70,  30, ENTRY_HEIGHT )
	LABEL(  95,  71,  15, "Uhr" )
	DISABLE_PRINT

SELECTION( "Ambulant/Stationär", LISTBOX, 0, -1 )
	ITEM( "in Behandlung" )
	ITEM( "entlassen/verlegt" )
	ITEM( "stationär aufgenommen" )
	ITEM( "D13-Eigenunfall" )
	ITEM( "D13 entlassen/verlegt" )
	ITEM( "D13 stationär aufgenommen" )
	FIELD(   0, 100, 100, 54 )
	LABEL(   0,  90,  90, "Ambulant/Stationär" )
	DISABLE_PRINT


PAGE( "Konsilärzte" )

ENTRY( "Arzt Name", 30, "" )
	FIELD(   0,   9,  100, ENTRY_HEIGHT )
	LABEL(   0,   0,  50, "Arzt Name" )
	DISABLE_PRINT

ENTRY( "Arzt Name", 30, "" )
	FIELD(   0,  34,  100, ENTRY_HEIGHT )
	LABEL(   0,  25,  50, "Konsilarzt 1" )
	DISABLE_PRINT

ENTRY( "Arzt Name", 30, "" )
	FIELD(   0,  59,  100, ENTRY_HEIGHT )
	LABEL(   0,  50,  50, "Konsilarzt 2" )
	DISABLE_PRINT

ENTRY( "Arzt Name", 30, "" )
	FIELD(   0,  84,  100, ENTRY_HEIGHT )
	LABEL(   0,  75,  50, "Konsilarzt 3" )
	DISABLE_PRINT

ENTRY( "Arzt Name", 30, "" )
	FIELD(   0, 109,  100, ENTRY_HEIGHT )
	LABEL(   0, 100,  50, "Konsilarzt 4" )
	DISABLE_PRINT

//ENTRY( "Arzt Name", 30, "" )
//	FIELD(   0, 134,  100, ENTRY_HEIGHT )
//	LABEL(   0, 125,  50, "Konsilarzt 4" )
//	DISABLE_PRINT


END_FORM_DEFINITION
