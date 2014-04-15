/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Oberdies								*/
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

//	m.control.a.y -= 2;
//	m.control.b.y -= 2;

	p->insert( new TNumericField( m, "Patientennr.", 10, "." ) );
	p->lastInserted->enableCard( 0, 1 );

	p->insert( new TNameField( m, "Name   ", 25, moHor ) );
	p->lastInserted->enableCard( 0, 0 );

	p->insert( new TNameField( m, "Vorname", 15, moNoSpace ) );
	p->lastInserted->enableCard( 25, 0 );

	p->insert( new TTextField( m, "Strasse ", 25 ) );
	p->lastInserted->enableCard( 40, 0 );

	p->insert( new TTextField( m, "PLZ, Ort", 25, moNoSpace ) );
	p->lastInserted->enableCard( 0, 2 );

	p->insert( new TNumericField( m, "Telefon privat", 15, ". /" ) );
	p->lastInserted->enableCard( 25, 2 );

	p->insert( new TDateField( m, "Geburtsdatum  ", 8, "TT.MM.JJ" ) );
	p->lastInserted->enableCard( 10, 1 );
	p->lastInserted->setInfoLevel( ilNormal );

	p->insert( new TRadioField( m, "Geschlecht",
								1,
								new TSItem( "M„nnlich",
								new TSItem( "Weiblich",
								new TSItem( " ", 0 ))),
								new TSItem( "M",
								new TSItem( "W",
								new TSItem( " ", 0 ))),
								moDown ) );
	p->lastInserted->enableCard( 65, 0 );

	m.control.a.y += 2;
	m.control.b.y += 2;
	p->insert( new TTextField( m, "Nation ", 30 ) );

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Personalien II" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TRadioField( m, "Konfession",
								6 + 11,
								new TSItem( " ",
								new TSItem( "reformiert",
								new TSItem( "r”misch-katholisch",
								new TSItem( "andere",
								new TSItem( "keine",
								new TSItem( "christlich-katholisch",
								new TSItem( "jdisch",
								new TSItem( "islamisch",
								new TSItem( "budhistisch",
								new TSItem( "griech./russ. orthodox",
											0 )))))))))),

								new TSItem( " ",
								new TSItem( "R",
								new TSItem( "K",
								new TSItem( "A",
								new TSItem( "-",
								new TSItem( "C",
								new TSItem( "J",
								new TSItem( "I",
								new TSItem( "B",
								new TSItem( "O", 0 )))))))))),
								moDown ) );
	p->lastInserted->enableCard( 70, 0, 1 );

	m.control.a.y += 9;
	m.control.b.y += 9;

	p->insert( new TRadioField( m, "Zivilstand",
								3 + 12,
								new TSItem( "ledig",
								new TSItem( "verheiratet",
								new TSItem( "geschieden",
								new TSItem( "getrennt",
								new TSItem( "verwitwet",
								new TSItem( " ", 0 )))))),
								new TSItem( "led",
								new TSItem( "vrh",
								new TSItem( "ges",
								new TSItem( "gtr",
								new TSItem( "vrw",
								new TSItem( " ", 0 )))))),
								moDown ) );

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Personalien III" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Heimatort", 30 ) );

	p->insert( new TTextField( m, "Beruf      ", 20 + 2 ) );

	p->insert( new TTextField( m, "Steuer-Code", 3, moNoSpace ) );

	p->insert( new TTextField( m, "Arbeitgeber", 25, moVert ) );
	p->insert( new TTextField( m, 0, 25, moNoSpace ) );
	p->insert( new TTextField( m, 0, 25, moNoSpace ) );

	m.control.a.y --;
	m.control.b.y --;
	p->insert( new TTextField( m, "Zustelladresse", 25, moVert ) );
	p->insert( new TTextField( m, 0, 25, moNoSpace ) );
	p->insert( new TTextField( m, 0, 25, moNoSpace ) );

	m.control.a.y --;
	m.control.b.y --;
	p->insert( new TTextField( m, "Angeh”rige", 25, moVert ) );
	p->insert( new TTextField( m, 0, 25, moNoSpace ) );
	p->insert( new TTextField( m, 0, 25, moNoSpace ) );

	f->insert( p );


	/* Contructing Page 4... */
	p = new TPage( "Spital/Eintritt" );
	m.reset();

	p->insert( new TTextField( m, "Klinik-Abteilung", 10 ) );

	p->insert( new TTextField( m, "Station", 3 ) );

	p->insert( new TTextField( m, "Zimmer Nr.", 3 ) );
	p->insert( new TTextField( m, "Tel. intern", 3 ) );

	p->insert( new TDateField( m, "Eintrittsdatum", 8, "TT.MM.JJ" ) );
	p->lastInserted->enableCard( 18, 1 );

	p->insert( new TNumericField( m, "Eintrittszeit", 5, " .:" ) );

	p->insert( new TTextField( m, "Eintrittsgrund", 20 ) );

	p->insert( new TTextField( m, "Garant", 4 ) );
	p->lastInserted->enableCard( 66, 0 );

	p->insert( new TTextField( m, "Klasse", 1 ) );
	p->lastInserted->enableCard( 26, 1 );

	p->insert( new TNumericField( m, "Frherer Aufenthalt", 7, " .," ) );

	f->insert( p );

	/* Contructing Page 5... */
	p = new TPage( "Garanten" );
	m.reset();

	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TTextField( m, "Garant 1", 30, moVert ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );

	p->insert( new TTextField( m, "Garant 2", 30, moVert ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );

	p->insert( new TTextField( m, "Garant 3", 30, moVert ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );

	f->insert( p );

	/* Contructing Page 6... */
	p = new TPage( "Žrzte" );
	m.reset();

	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TTextField( m, "Einweisender Arzt", 25, moVert ) );
	p->lastInserted->enableCard( 40, 2 );

	p->insert( new TTextField( m, 0, 30, moNoSpace ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );

	p->insert( new TTextField( m, "Hausarzt", 30, moVert ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );

	p->insert( new TTextField( m, "Behandelnder Arzt", 30, moVert ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );


	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Bezirkspital Oberdiesbach" );
	sl->put( skPerson,				"Patient" );

	sl->put( skPersonList,			"~P~atienten" );
	sl->put( skNewPerson,			"Patienten ~e~infgen..." );
	sl->put( skDeletePerson,		"Patienten ~l~”schen" );
	sl->put( skEditPerson,			"Daten ~m~odifizieren..." );
	sl->put( skPrintPerson,			"~F~ormular drucken" );
	sl->put( skRawPrintPerson, 		"~S~tammblatt drucken" );
	sl->put( skEncodeCard,			"~K~arte codieren" );

	sl->put( skHeapView,			"" );

	sl->put( skOldDevice,			"OldDevice" );
	sl->put( skFormatedRawPrint,	"FormatedRawPrint" );
	sl->put( skNumRPCopiesDlg,		"NumRPCopiesDlg" );

	sl->put( skAutoSave,			"AutoSave" );

	sl->put( skFormDlgOK,			"~O~K" );
	sl->put( skFormDlgCancel,		"A~b~brechen" );

	sl->put( skPrintLog,			"" );

	sl->put( skConfirmNewPerson,	"" );
	sl->put( skDisableOptions,		"" );

	sl->put( skListWindowTitle,		"Patientendaten-Verwaltung" );

	sl->put( skExportData,			"" );

	return sl;
}
