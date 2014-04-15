/*----------------------------------------------*/
/*                                              */
/*              PV 1.0                          */
/*              Demo-Programm MCP4000           */
/*              Form Definition Source File     */
/*                                              */
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

//      m.control.a.y -= 2;
//      m.control.b.y -= 2;

	p->insert( new TNumericField( m, "Patientennr.", 9, "." ) );
	p->lastInserted->enableCard( 0, 2 );
	p->lastInserted->enableCardLabel( 20, 1 );

	p->insert( new TNameField( m, "Vorname", 28, moHor ) );
	p->lastInserted->enableCard( 0, 0 );
		p->lastInserted->enableCardLabel( 0, 1, 18 );

	p->insert( new TNameField( m, "Name   ", 28, moNoSpace ) );
		p->lastInserted->enableCard( 28, 0 );
		p->lastInserted->enableCardLabel( 0, 0 );

		p->insert( new TDateField( m, "Geburtsdatum  ", 8, "TT.MM.JJ" ) );
		p->lastInserted->enableCard( 56, 0 );
		p->lastInserted->enableCardLabel( 0, 2 );

		p->insert( new TTextField( m, "Strasse", 28 ) );
		p->lastInserted->enableCard( 64, 0 );

		p->insert( new TTextField( m, "Wohnsitz", 3 ) );

		p->insert( new TNumericField( m, "PLZ", 7, " -", moHor ) );
		p->lastInserted->enableCard( 92, 0 );

		p->insert( new TTextField( m, "Ort     ", 23, moHor ) );
		p->lastInserted->enableCard( 0, 1 );

	p->insert( new TRadioField( m, "Geschlecht",
								1,
								new TSItem( "M„nnlich",
								new TSItem( "Weiblich", 0 )),
								new TSItem( "M",
								new TSItem( "W", 0 )),
								moDown ) );
		p->lastInserted->enableCard( 99, 0 );
		p->lastInserted->enableCardLabel( 11, 2 );
	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Personalien II" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;
		p->insert( new TRadioField( m, "Zivilstand",
																10,
																new TSItem( "ledig",
																new TSItem( "verheiratet",
																new TSItem( "geschieden",
																new TSItem( "getrennt",
																new TSItem( "verwitwet", 0 ))))),
																new TSItem( "ledig     ",
																new TSItem( "verheirat.",
																new TSItem( "geschied. ",
																new TSItem( "getrennt  ",
																new TSItem( "verwittw. ", 0 ))))),
																moDown ) );
		p->lastInserted->enableCard( 100, 0 );

	m.control.a.y += 4;
	m.control.b.y += 4;
		p->insert( new TRadioField( m, "Konfession",
								12,
								new TSItem( "keine",
								new TSItem( "r”misch-katholisch",
								new TSItem( "christlich-katholisch",
								new TSItem( "reformiert",
								new TSItem( "jdisch",
								new TSItem( "islamisch",
								new TSItem( "budhistisch",
								new TSItem( "griech./russ. orthodox",
								new TSItem( "andere", 0 ))))))))),
																new TSItem( "keine       ",
																new TSItem( "r”misch-kat.",
																new TSItem( "christl-kat.",
																new TSItem( "reformiert  ",
																new TSItem( "jdisch     ",
																new TSItem( "islam       ",
																new TSItem( "budhistisch ",
																new TSItem( "orthodox    ",
																new TSItem( "andere      ", 0 ))))))))),
								moDown ) );
		p->lastInserted->enableCard( 9, 2 );

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Personalien III" );
	m.reset();

		p->insert( new TDateField( m, "Eintrittsdatum", 10, "TT.MM.JJJJ" ) );
		p->lastInserted->enableCard( 110, 0 );

		p->insert( new TTextField( m, "Klasse", 10 ) );
		p->lastInserted->enableCard( 23, 1 );
		p->lastInserted->enableCardLabel( 19, 2 );

		p->insert( new TTextField( m, "Klinik", 4 ) );
		p->lastInserted->enableCard( 33, 1 );
		p->lastInserted->enableCardLabel( 0, 3 );

		p->insert( new TTextField( m, "Station", 3 ) );
		p->lastInserted->enableCard( 21, 2 );
		p->lastInserted->enableCardLabel( 26, 3 );

		p->insert( new TNumericField( m, "Telefon-Nr.", 15, " -/" ) );

		p->insert( new TTextField( m, "Beruf", 25 ) );
		p->lastInserted->enableCard( 37, 1 );


	f->insert( p );

	/* Contructing Page 4... */
		p = new TPage( "Angeh”rige/Žrzte" );
	m.reset();
	m.control.a.y -= 2;
	m.control.b.y -= 2;

		p->insert( new TTextField( m, "Angeh”r. Name", 26 ) );
		p->lastInserted->enableCard( 24, 2 );

		p->insert( new TTextField( m, "Angeh”r. Tel.", 15 ) );
		p->lastInserted->enableCard( 50, 2 );

		p->insert( new TTextField( m, "Einw. Arzt", 30 ) );
		p->lastInserted->enableCard( 62, 1 );

		p->insert( new TTextField( m, "Ort Einw. Arzt", 30 ) );
		p->lastInserted->enableCard( 65, 2 );

		p->insert( new TTextField( m, "Hausarzt", 23 ) );
		p->lastInserted->enableCard( 95, 2 );

		p->insert( new TTextField( m, "Tel. Hausarzt", 15 ) );

		f->insert( p );

	/* Contructing Page 5... */
		p = new TPage( "Versicherung" );
	m.reset();
	m.control.a.y -= 2;
	m.control.b.y -= 2;

		p->insert( new TTextField( m, "Garant Name", 28 ) );
		p->lastInserted->enableCard( 92, 1 );
		p->lastInserted->enableCardLabel( 0, 4 );

		p->insert( new TTextField( m, "Garant Nummer", 7 ) );

		p->insert( new TTextField( m, "Versicherungs-Nummer", 12 ) );

		p->insert( new TTextField( m, "VKNR", 5 ) );

		p->insert( new TTextField( m, "Versich.Status", 4 ) );

		p->insert( new TTextField( m, "Status Erg„nzung", 3 ) );

		p->insert( new TNumericField( m, "Gltigkeit", 4, " .-/" ) );


	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Koelliker AG" );
	sl->put( skPerson,				"Patient" );

	sl->put( skPersonList,			"~P~atienten" );
	sl->put( skNewPerson,			"Patienten ~e~infgen..." );
	sl->put( skDeletePerson,		"Patienten ~l~”schen" );
	sl->put( skEditPerson,			"Daten ~„~ndern..." );
	sl->put( skPrintPerson,			"~F~ormular drucken" );
	sl->put( skRawPrintPerson,		"~D~aten drucken" );
	sl->put( skEncodeCard,			"~K~arte codieren" );

	sl->put( skHeapView,			"" );

	sl->put( skOldDevice,			"" );
	sl->put( skFormatedRawPrint,	"" );
	sl->put( skNumRPCopiesDlg,		"" );

	sl->put( skAutoSave,			"" );

	sl->put( skFormDlgOK,			"" );
	sl->put( skFormDlgCancel,		"" );

	return sl;
}
