/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Herzogenbuchsee    						*/
/*		Form Definition Source File 			*/
/*												*/
/*----------------------------------------------*/

#include "FormDef\SpecDef.Use"


#include <TV.H>
#include "FormDef\SpecDef.H"


TSpecDefinition::TSpecDefinition( TForm *(*)(), TStrListMaker *(*)() ) :
	TFormDefinition( TSpecDefinition::initForm,
					 TSpecDefinition::initStringList )
	{ }


TForm *TSpecDefinition::initForm()
{
	TForm *f = new TForm();
	TPage *p;

	TMeasurements m = TMeasurements();

	/* Contructing Page 1... */
	p = new TPage( "Personalien I" );
	m.reset();

	p->insert( new TNumericField( m, "Patientennr.", 10, "." ) );
	p->lastInserted->makeNecessary();
//	p->lastInserted->enableCard( 0, 1 );
	p->lastInserted->enableCard( 29, 1 );
	p->lastInserted->enableCardLabel( 18, 4 );

	p->insert( new TNameField( m, "Name   ", 26 ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 0, 0 );
	p->lastInserted->enableCardLabel( 1, 0 );

	p->insert( new TNameField( m, "Vorname", 12, moNoSpace ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 26, 0 );
	p->lastInserted->enableCardLabel( 1, 1 );

	p->insert( new TTextField( m, "Strasse, Nr.", 26 ) );
	p->lastInserted->enableCard( 64, 0 );

	p->insert( new TTextField( m, "PLZ, Ort    ", 26, moNoSpace ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 38, 0 );
	p->lastInserted->enableCardLabel( 1, 2 );

	p->insert( new TNumericField( m, "Steuer-Code", 3, " ", moVert ) );

	p->insert( new TTextField( m, "Heimatort/Nat.", 18, moVert | moRight ) );

	p->insert( new TDateField( m, "Geburtsdatum", 10, "TT.MM.JJJJ", moHor ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 9, 1 );
	p->lastInserted->enableCardLabel( 1, 3 );
	p->lastInserted->setInfoLevel( ilNormal );

	p->insert( new TRadioField( m, "Geschlecht",
								2,
								new TSItem( "M„nnlich",
								new TSItem( "Weiblich",
								new TSItem( "S„ugling m„nnlich",
								new TSItem( "S„ugling weiblich",
								0 )))),
								new TSItem( "M",
								new TSItem( "W",
								new TSItem( "SM",
								new TSItem( "SW",
								0 )))),
								moDown ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 19, 1 );
	p->lastInserted->enableCardLabel( 13, 3 );

	m.control.a.y += 3;
	m.control.b.y += 3;

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Personalien II" );
	m.reset();
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TRadioField( m, "Zivilstand",
								5,
								new TSItem( "ledig",
								new TSItem( "verheiratet",
								new TSItem( "geschieden",
								new TSItem( "getrennt",
								new TSItem( "verwitwet", 0 ))))),
								new TSItem( "LEDIG",
								new TSItem( "VERH.",
								new TSItem( "GESCH",
								new TSItem( "GETR.",
								new TSItem( "VERW.", 0 ))))),
								moDown ) );

	m.control.a.y += 4;
	m.control.b.y += 4;

	p->insert( new TRadioField( m, "Konfession",
								5,
								new TSItem( "reformiert",
								new TSItem( "r”misch-katholisch",
								new TSItem( "christlich-katholisch",
								new TSItem( "neuapostolisch",
								new TSItem( "freikirchlich",
								new TSItem( "jdisch",
								new TSItem( "islamisch",
								new TSItem( "budhistisch",
								new TSItem( "andere",
								new TSItem( "keine", 0 )))))))))),
								new TSItem( "REF",
								new TSItem( "RK",
								new TSItem( "CHK",
								new TSItem( "NAP",
								new TSItem( "FK",
								new TSItem( "JšD",
								new TSItem( "ISLAM",
								new TSItem( "BUDHA",
								new TSItem( "AND",
								new TSItem( "KEINE", 0 )))))))))),
								moDown ) );

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Personalien III" );
	m.reset();

	p->insert( new TNumericField( m, "Telefon Privat", 13, " -/" ) );
	p->insert( new TTextField( m, "Ehepartner", 26 ) );

	p->insert( new TTextField( m, "Beruf", 18 ) );
	p->insert( new TTextField( m, "Arbeitgeber ", 34 ) );
	p->insert( new TNumericField( m, "Telefon Arb.", 13, " -/", moNoSpace ) );

	p->insert( new TTextField( m, "Angeh”rige 1", 34 ) );
	p->insert( new TNumericField( m, "Telefon Ang.", 13, " -/", moNoSpace ) );

	p->insert( new TTextField( m, "Angeh”rige 2", 34 ) );
	p->insert( new TNumericField( m, "Telefon Ang.", 13, " -/", moNoSpace ) );

	p->insert( new TTextField( m, "Angeh”rige 3", 34 ) );
	p->insert( new TNumericField( m, "Telefon Ang.", 13, " -/", moNoSpace ) );


	f->insert( p );

	/* Contructing Page 4... */
	p = new TPage( "Eintritt" );
	m.reset();

	p->insert( new TTextField( m, "Klasse ", 1 ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 94, 0 );
	p->lastInserted->enableCardLabel( 13, 4 );

	p->insert( new TTextField( m, "Abteilung ", 4 ) );
	p->lastInserted->enableCard( 90, 0 );
	p->lastInserted->enableCardLabel( 1, 4 );

	p->insert( new TTextField( m, "Station", 1 ) );
	p->insert( new TTextField( m, "Zimmer-Nr.", 3 ) );

	p->insert( new TTextField( m, "Eintritts-Code", 1 ) );

	p->insert( new TDateField( m, "Eintr.Datum", 8, "TT.MM.JJ" ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 21, 1 );
	p->lastInserted->enableCardLabel( 20, 3 );

	p->insert( new TNumericField( m, "Zeit", 5, ".", moRight ) );
	p->insert( new TTextField( m, "Eintr.Grund", 15 ) );

	p->insert( new TNumericField( m, "Frh.Aufenthalt", 7, " ,/-" ) );

	p->insert( new TTextField( m, "Taxkat.", 2 ) );

	p->insert( new TTextField( m,    "Garant 1", 34 ) );
	p->insert( new TTextField( m, "Mitglied-Nr.", 15, moNoSpace ) );

	p->insert( new TTextField( m,    "Garant 2", 34 ) );
	p->insert( new TTextField( m, "Mitglied-Nr.", 15, moNoSpace ) );

	f->insert( p );

	/* Contructing Page 5... */
	p = new TPage( "Žrzte" );
	m.reset();

	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TTextField( m, "Zustelladresse", 34, moVert ) );
	p->insert( new TTextField( m, 0, 34, moNoSpace ) );
	p->insert( new TTextField( m, 0, 34, moNoSpace ) );

	p->insert( new TTextField( m, "Einweisender Arzt", 34, moVert ) );
	p->insert( new TTextField( m, "Hausarzt ", 34, moVert ) );
	p->insert( new TTextField( m, "Behandelnder Arzt", 15 ) );

	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TTextField( m, "Aufgenommen durch", 5, moHor ) );
	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Herzogenbuchsee" );
	sl->put( skPerson,				"Patient" );

	sl->put( skPersonList,			"~P~atienten" );
	sl->put( skNewPerson,			"Patienten ~e~infgen..." );
	sl->put( skDeletePerson,		"Patienten ~l~”schen" );
	sl->put( skEditPerson,			"Daten ~„~ndern..." );
	sl->put( skPrintPerson,			"~F~ormular drucken" );
	sl->put( skRawPrintPerson, 		"~D~aten drucken" );
	sl->put( skEncodeCard,			"~K~arte codieren" );

	sl->put( skHeapView,			"HeapView" );

	sl->put( skOldDevice,			"" );
	sl->put( skFormatedRawPrint,	"" );
	sl->put( skNumRPCopiesDlg,		"" );

	sl->put( skAutoSave,			"" );

	sl->put( skFormDlgOK,			"" );
	sl->put( skFormDlgCancel,		"" );

	sl->put( skPrintLog,			"" );

	sl->put( skConfirmNewPerson,	"" );
	sl->put( skDisableOptions,		"" );

	sl->put( skListWindowTitle,		"Patientendaten-Verwaltung" );

	sl->put( skExportData,			"" );

	return sl;
}
