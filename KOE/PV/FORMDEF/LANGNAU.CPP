/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Langnau            						*/
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

	p->insert( new TNumericField( m, "Patientennr.", 8, "." ) );
	p->lastInserted->enableCard( 0, 1 );

	p->insert( new TNameField( m, "Name   ", 30, moHor ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 0, 0 );
	p->lastInserted->enableCardLabel( 0, 0, 29 );

	p->insert( new TNameField( m, "Vorname", 18, moNoSpace ) );
	p->lastInserted->enableCard( 30, 0 );
	p->lastInserted->enableCardLabel( 0, 1 );

	p->insert( new TTextField( m, "Strasse", 24 + 18 ) );
	p->lastInserted->enableCard( 48, 0, 24 );
	p->lastInserted->enableCardLabel( 0, 2, 24 );

	p->insert( new TTextField( m, "PLZ, Ort", 24 ) );
	p->lastInserted->enableCard( 72, 0 );
	p->lastInserted->enableCardLabel( 0, 3 );

	p->insert( new TNumericField( m, "Geburtsdatum  ", 8 ) );
	p->lastInserted->enableCard( 8, 1 );

	p->insert( new TTextField( m, 0, 1 ) );

	p->insert( new TDateField( m, "Eintrittsdatum", 8, "TT.MM.JJ" ) );
	p->lastInserted->enableCard( 17, 1 );

	p->insert( new TTextField( m, 0, 2 ) );

	p->insert( new TNumericField( m, "Austritt", 6 ) );
	p->insert( new TNumericField( m, "Austritt", 4 ) );

	p->insert( new TRadioField( m, "Geschlecht",
								1,
								new TSItem( "M„nnlich",
								new TSItem( "Weiblich", 0 )),
								new TSItem( "M",
								new TSItem( "W", 0 )),
								moDown ) );
	p->lastInserted->enableCard( 16, 1 );

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Personalien II" );
	m.reset();

	p->insert( new TNumericField( m, "Telefon-Nr.", 13, " -/" ) );
	p->lastInserted->enableCard( 25, 1 );

	p->insert( new TNumericField( m, "Telefon-Nr.", 29, " -/" ) );

	p->insert( new TRadioField( m, "Konfession",
								6 + 11,
								new TSItem( "keine",
								new TSItem( "r”misch-katholisch",
								new TSItem( "christlich-katholisch",
								new TSItem( "reformiert",
								new TSItem( "jdisch",
								new TSItem( "islamisch",
								new TSItem( "budhistisch",
								new TSItem( "griech./russ. orthodox",
								new TSItem( "andere", 0 ))))))))),
								new TSItem( "keine",
								new TSItem( "r”-kat",
								new TSItem( "ch-kat",
								new TSItem( "reform",
								new TSItem( "jd.",
								new TSItem( "islam",
								new TSItem( "budh.",
								new TSItem( "orthod",
								new TSItem( "andere", 0 ))))))))),
								moDown ) );
	p->lastInserted->enableCard( 45, 1, 6 );

	m.control.a.y += 8;
	m.control.b.y += 8;

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Personalien III" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TRadioField( m, "Zivilstand",
								3 + 12,
								new TSItem( "ledig",
								new TSItem( "verheiratet",
								new TSItem( "geschieden",
								new TSItem( "getrennt",
								new TSItem( "verwitwet", 0 ))))),
								new TSItem( "led",
								new TSItem( "vrh",
								new TSItem( "ges",
								new TSItem( "gtr",
								new TSItem( "vrw", 0 ))))),
								moDown ) );
	p->lastInserted->enableCard( 42, 1, 3 );

	m.control.a.y += 4;
	m.control.b.y += 4;

	p->insert( new TTextField( m, "Eintrittsgnde", 58 ) );

	p->insert( new TTextField( m, "Beruf", 20 + 2 ) );
	p->lastInserted->enableCard( 96, 0, 20 );

	p->insert( new TTextField( m, "Diagnose", 87 ) );

	p->insert( new TTextField( m, "Arbeitgeber", 98 ) );

	p->insert( new TTextField( m, "Klasse", 4 + 16 ) );
	p->lastInserted->enableCard( 38, 1, 4 );

	p->insert( new TTextField( m, "Zimmer", 19 ) );

	f->insert( p );

	/* Contructing Page 4... */
	p = new TPage( "Kosten/Angeh”rige" );
	m.reset();

	p->insert( new TTextField( m, "Kostenstelle", 5 + 12 ) );
	p->lastInserted->enableCard( 115, 1, 5 );

	p->insert( new TTextField( m, "Taxkategorie", 4 + 43 ) );
	p->lastInserted->enableCard( 111, 1, 4 );

	p->insert( new TTextField( m, "Heimatort", 61 ) );

	p->insert( new TTextField( m, "Angeh”rige 1", 48, moVert ) );
	p->insert( new TTextField( m, 0, 24, moNoSpace ) );
	p->insert( new TTextField( m, 0, 48, moNoSpace ) );

	p->insert( new TTextField( m, "Aufgenommen", 11, moHor ) );

	p->insert( new TTextField( m, "Angeh”rige 2", 48, moVert ) );
	p->insert( new TTextField( m, 0, 24, moNoSpace ) );
	p->insert( new TTextField( m, 0, 48, moNoSpace ) );

	f->insert( p );

	/* Contructing Page 5... */
	p = new TPage( "Garanten" );
	m.reset();

	p->insert( new TTextField( m, 0, 15, moVert ) );

	p->insert( new TTextField( m, "Garant 1", 18 + 6, moVert ) );
	p->lastInserted->enableCard( 0, 2, 18 );

	p->insert( new TTextField( m, 0, 18 + 6, moNoSpace ) );
	p->lastInserted->enableCard( 18, 2, 18 );

	p->insert( new TTextField( m, 0, 18 + 6, moNoSpace ) );

	p->insert( new TTextField( m, "PLZ Ort", 23 + 14, moNoSpace ) );
	p->lastInserted->enableCard( 36, 2, 23 );

	p->insert( new TTextField( m, "Mitgliedsnr.", 22, moNoSpace | moHor ) );


	p->insert( new TTextField( m, "Garant 2", 18 + 6, moVert ) );
	p->lastInserted->enableCard( 59, 2, 18 );

	p->insert( new TTextField( m, 0, 18 + 6, moNoSpace ) );
	p->lastInserted->enableCard( 77, 2, 18 );

	p->insert( new TTextField( m, 0, 18 + 6, moNoSpace ) );

	p->insert( new TTextField( m, "PLZ Ort", 23 + 14, moNoSpace ) );
	p->lastInserted->enableCard( 95, 2, 23 );

	p->insert( new TTextField( m, "Mitgliedsnr.", 17, moNoSpace | moHor ) );

	f->insert( p );

	/* Contructing Page 6... */
	p = new TPage( "Žrzte" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Garant 3", 114, moVert ) );

	p->insert( new TTextField( m, "Mitgliedsnr.", 17, moNoSpace | moHor ) );

	p->insert( new TTextField( m, "Beh. Arzt Nr.", 5 ) );

	p->insert( new TTextField( m, "Einweisender Arzt", 30, moVert ) );
	p->lastInserted->enableCard( 51, 1 );

	p->insert( new TTextField( m, 0, 32, moNoSpace ) );
	p->insert( new TTextField( m, 0, 15, moNoSpace ) );

	p->insert( new TTextField( m, "Hausarzt-Nr.", 54, moHor ) );

	p->insert( new TTextField( m, "Hausarzt", 30, moVert ) );
	p->lastInserted->enableCard( 81, 1 );

	p->insert( new TTextField( m, 0, 32, moNoSpace ) );
	p->insert( new TTextField( m, 0, 15, moNoSpace ) );

	f->insert( p );

	/* Contructing Page 7... */
	p = new TPage( "Diverses" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;


	p->insert( new TTextField( m, "BANR", 93, moVert ) );

	p->insert( new TTextField( m, "BA Gruppentext", 96 ) );

	p->insert( new TTextField( m, "Frherer Aufenthalt", 8, moHor ) );

	p->insert( new TTextField( m, "Reserve", 115, moVert ) );

	f->insert( p );


	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Langnau i.E." );
	sl->put( skPerson,				"Patient" );

	sl->put( skPersonList,			"~P~atienten" );
	sl->put( skNewPerson,			"Patienten ~e~infgen..." );
	sl->put( skDeletePerson,		"Patienten ~l~”schen" );
	sl->put( skEditPerson,			"Daten ~„~ndern..." );
	sl->put( skPrintPerson,			"~F~ormular drucken" );
	sl->put( skRawPrintPerson, 		"~D~aten drucken" );
	sl->put( skEncodeCard,			"~K~arte codieren" );
	return sl;
}
