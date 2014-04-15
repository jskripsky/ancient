/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Bamberg            						*/
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
	p = new TPage( "Aufnahme" );
	m.reset();

	p->insert( new TTextField( m, "Behandl. Art ", 4 ) );

	p->insert( new TNumericField( m, "Aufnahme Nr. ", 5, ".", moDown ) );
	p->lastInserted->enableCard( 0, 0 );

	p->insert( new TDateField( m, "Aufnahme Tag ", 8, "TT.MM.JJ", moDown ) );
	p->lastInserted->enableCard( 5, 0 );

	p->insert( new TNumericField( m, "Aufnahme Zeit", 5, ":", moDown ) );
	p->lastInserted->enableCard( 13, 0 );

	p->insert( new TTextField( m, "J.-Zahl      ", 6, moDown ) );
	p->lastInserted->enableCard( 18, 0 );

	p->insert( new TTextField( m, "Station      ", 4, moDown ) );
	p->lastInserted->enableCard( 24, 0 );

	p->insert( new TTextField( m, "Wiederkehr   ", 1, moDown ) );
	p->lastInserted->enableCard( 28, 0 );

	p->insert( new TTextField( m, "Aufnahme Art ", 1, moDown ) );

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Patientendaten I" );
	m.reset();

	p->insert( new TNameField( m, "Name       ", 25 ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 29, 0 );
	p->lastInserted->enableCardLabel( 0, 0 );

	p->insert( new TNameField( m, "Vorname    ", 15, moNoSpace ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 54, 0 );
	p->lastInserted->enableCardLabel( 0, 1 );

	p->insert( new TTextField( m, "Geb. Name  ", 25 ) );

	p->insert( new TTextField( m, "Strasse    ", 25 ) );
	p->lastInserted->enableCard( 69, 0 );
	p->lastInserted->enableCardLabel( 0, 2 );

	p->insert( new TTextField( m, "PLZ Ort    ", 25 ) );
	p->lastInserted->enableCard( 94, 0 );
	p->lastInserted->enableCardLabel( 0, 3 );

	p->insert( new TDateField( m, "Geb. Datum ", 10, "TT.MM.JJJJ", moVert ) );
	p->lastInserted->enableCard( 0, 1 );

	p->insert( new TTextField( m, "Geb. Ort", 15, moRight ) );

	p->insert( new TTextField( m, "Staatsangeh", 5, moHor ) );
	p->lastInserted->enableCard( 10, 1 );

	p->insert( new TTextField( m, "Beruf      ", 25 ) );
	p->insert( new TTextField( m, "Arbeitgeber", 25 ) );

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Patientendaten II" );
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
								new TSItem( "ledig",
								new TSItem( "verh.",
								new TSItem( "gesch",
								new TSItem( "getr.",
								new TSItem( "verw.", 0 ))))),
								moDown ) );
	p->lastInserted->enableCard( 15, 1 );

	m.control.a.y += 4;
	m.control.b.y += 4;

	p->insert( new TRadioField( m, "Religion  ",
								5,
								new TSItem( "keine",
								new TSItem( "r”misch-katholisch",
								new TSItem( "christlich-katholisch",
								new TSItem( "reformiert",
								new TSItem( "jdisch",
								new TSItem( "islamisch",
								new TSItem( "budhistisch",
								new TSItem( "andere", 0 )))))))),
								new TSItem( "keine",
								new TSItem( "r”m-k",
								new TSItem( "chr-k",
								new TSItem( "refor",
								new TSItem( "jd.",
								new TSItem( "islam",
								new TSItem( "budh.",
								new TSItem( "ander", 0 )))))))),
								moDown ) );
	p->lastInserted->enableCard( 20, 1 );

	m.control.a.y += 7;
	m.control.b.y += 7;

	p->insert( new TRadioField( m, "Geschlecht",
								1,
								new TSItem( "M„nnlich",
								new TSItem( "Weiblich", 0 )),
								new TSItem( "M",
								new TSItem( "W", 0 )),
								moDown ) );
	p->lastInserted->enableCard( 25, 1 );

	m.control.a.y += 1;
	m.control.b.y += 1;

	f->insert( p );

	/* Contructing Page 4... */
	p = new TPage( "Versicherter" );
	m.reset();

	p->insert( new TTextField( m, "Name       ", 25 ) );
	p->lastInserted->enableCard( 26, 1 );
	p->insert( new TTextField( m, "Vorname    ", 15, moNoSpace ) );
	p->lastInserted->enableCard( 51, 1 );

	p->insert( new TTextField( m, "Strasse    ", 25 ) );
	p->lastInserted->enableCard( 66, 1 );

	p->insert( new TTextField( m, "PLZ Ort    ", 25 ) );
	p->lastInserted->enableCard( 91, 1 );

	p->insert( new TDateField( m, "Geb. Datum ", 10, "TT.MM.JJJJ" ) );

	p->insert( new TTextField( m, "Staatsangeh", 5 ) );

	p->insert( new TTextField( m, "Beruf      ", 25 ) );
	p->insert( new TTextField( m, "Arbeitgeber", 25 ) );

	f->insert( p );

	/* Contructing Page 5... */
	p = new TPage( "Kostentr„ger" );
	m.reset();

	p->insert( new TTextField( m, "Kostentr.-Nr", 8 ) );
	p->lastInserted->enableCard( 0, 2 );

	p->insert( new TTextField( m, "Name        ", 25 ) );
	p->lastInserted->enableCard( 8, 2 );

	p->insert( new TTextField( m, "Strasse     ", 25 ) );
	p->insert( new TTextField( m, "PLZ Ort     ", 25 ) );

	p->insert( new TTextField( m, "Aktenzeichen", 25 ) );

	p->insert( new TTextField( m, "Versich. Art", 5 ) );
	p->insert( new TTextField( m, "ABKZ        ", 5 ) );

	f->insert( p );

	/* Contructing Page 6... */
	p = new TPage( "Einweisender Arzt" );
	m.reset();

	p->insert( new TTextField( m, "Arzt. Nr.  ", 8 ) );

	p->insert( new TTextField( m, "Name Teil 1", 25 ) );
	p->lastInserted->enableCard( 33, 2 );
	p->lastInserted->enableCardLabel( 0, 4 );
	p->insert( new TTextField( m, "Name Teil 2", 25 ) );

	p->insert( new TTextField( m, "Strasse    ", 25 ) );
	p->insert( new TTextField( m, "PLZ Ort    ", 25 ) );

	f->insert( p );

	/* Contructing Page 7... */
	p = new TPage( "Hausarzt" );
	m.reset();

	p->insert( new TTextField( m, "Arzt. Nr.  ", 8 ) );

	p->insert( new TTextField( m, "Name Teil 1", 25 ) );
	p->lastInserted->enableCard( 58, 2 );
	p->lastInserted->enableCardLabel( 0, 5 );
	p->insert( new TTextField( m, "Name Teil 2", 25 ) );

	p->insert( new TTextField( m, "Strasse    ", 25 ) );
	p->insert( new TTextField( m, "PLZ Ort    ", 25 ) );

	f->insert( p );

	/* Contructing Page 8... */
	p = new TPage( "Diverses" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Name Angeh”rig.", 25 ) );
	p->insert( new TTextField( m, "Vorname Angeh. ", 15 ) );
	p->insert( new TDateField( m, "Geb. Datum Ang.", 10, "TT.MM.JJJJ" ) );

	p->insert( new TTextField( m, "Einw. Diagnose ", 25 ) );

	p->insert( new TTextField( m, "BG/Priv/Kasse  ", 1 ) );
	p->lastInserted->enableCard( 83, 2 );

	p->insert( new TTextField( m, "Mitglieds Nr.  ", 10 ) );
	p->lastInserted->enableCard( 84, 2 );

	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TTextField( m, "Aufgenommen durch", 10 ) );

	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Bamberg" );
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
