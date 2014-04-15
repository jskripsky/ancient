/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Klinikum Hof							*/
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

	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TTextField( m, "Aufn. Nr.", 6, moVert ) );
	p->lastInserted->enableCard( 0, 0 );
	p->lastInserted->enableCardLabel( 14, 1 );

	p->insert( new TTextField( m, "Datum", 6, moVert ) );
	p->lastInserted->enableCard( 6, 0 );
	p->lastInserted->enableCardLabel( 5, 2 );

	p->insert( new TTextField( m, "Zeit", 4, moVert ) );
	p->lastInserted->enableCard( 12, 0 );

	p->insert( new TTextField( m, "Stat./Fachabteilung", 4, moHor ) );
	p->lastInserted->enableCard( 16, 0 );
	p->lastInserted->enableCardLabel( 0, 2 );

	p->insert( new TNameField( m, "Name, Vorname", 29, moVert ) );
	p->lastInserted->enableCard( 20, 0 );
	p->lastInserted->enableCardLabel( 0, 0, 28 );

	p->insert( new TTextField( m, "Geburtsdatum", 8, moHor ) );
	p->lastInserted->enableCard( 0, 2 );
	p->lastInserted->enableCardLabel( 0, 1 );

	p->insert( new TTextField( m, "Strasse", 25, moDown ) );
	p->lastInserted->enableCard( 72, 0 );

	p->insert( new TTextField( m, "PLZ", 5 ) );
	p->lastInserted->enableCard( 49, 0 );

	p->insert( new TTextField( m, "Ort", 18 ) );
	p->lastInserted->enableCard( 54, 0 );

	p->insert( new TTextField( m, "Staatsangeh”rigkeit", 3 ) );
	p->lastInserted->enableCard( 97, 0 );

	p->insert( new TTextField( m, "Beh. Art", 1, moHor | moDown ) );
	p->lastInserted->enableCard( 3, 1 );

	p->insert( new TTextField( m, "Unterkunft", 1 ) );
	p->lastInserted->enableCard( 8, 2 );


	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Personalien II" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TRadioField( m, "Geschlecht",
								1,
								new TSItem( "M„nnlich",
								new TSItem( "Weiblich", 0 )),
								new TSItem( "M",
								new TSItem( "W", 0 )),
								moDown ) );
	p->lastInserted->enableCard( 2, 1 );
	p->lastInserted->enableCardLabel( 9, 1 );

	m.control.a.y ++;
	m.control.b.y ++;

	p->insert( new TRadioField( m, "Religion  ",
								2,
								new TSItem( "reformiert",
								new TSItem( "r”misch-katholisch",
								new TSItem( "keine",
								new TSItem( "christlich-katholisch",
								new TSItem( "jdisch",
								new TSItem( "islamisch",
								new TSItem( "budhistisch",
								new TSItem( "griech./russ. orthodox",
											0 )))))))),

								new TSItem( "R",
								new TSItem( "K",
								new TSItem( "-",
								new TSItem( "C",
								new TSItem( "J",
								new TSItem( "I",
								new TSItem( "B",
								new TSItem( "O", 0 )))))))),
								moDown ) );
	p->lastInserted->enableCard( 0, 1 );

	m.control.a.y += 7;
	m.control.b.y += 7;

	p->insert( new TRadioField( m, "Zivilstand",
								2,
								new TSItem( "ledig",
								new TSItem( "verheiratet",
								new TSItem( "geschieden",
								new TSItem( "getrennt",
								new TSItem( "verwitwet", 0 ))))),
								new TSItem( "ld",
								new TSItem( "vh",
								new TSItem( "gs",
								new TSItem( "gt",
								new TSItem( "vw", 0 ))))),
								moDown ) );
	p->lastInserted->enableCard( 100, 0 );

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Personalien III" );
	m.reset();

	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TTextField( m, "Name Hauptversicherter", 29, moVert ) );
	p->lastInserted->enableCard( 71, 1 );

	p->insert( new TTextField( m, "Geb.Datum", 6, moVert ) );
	p->lastInserted->enableCard( 100, 1 );

	p->insert( new TTextField( m, "Geburtsort", 15 ) );
	p->lastInserted->enableCard( 4, 1 );

	p->insert( new TTextField( m, "Beruf", 16, moHor ) );
	p->lastInserted->enableCard( 12, 2 );

	p->insert( new TTextField( m, "Versicherungsart", 1 ) );
	p->lastInserted->enableCard( 11, 2 );

	p->insert( new TTextField( m, "Name Kostentr„ger", 30, moVert ) );
	p->lastInserted->enableCard( 19, 1 );
	p->lastInserted->enableCardLabel( 0, 3, 28 );

	p->insert( new TTextField( m, "Strasse", 17, moHor ) );
	p->lastInserted->enableCard( 54, 1 );

	p->insert( new TTextField( m, "PLZ", 5, moHor ) );
	p->lastInserted->enableCard( 49, 1 );

	p->insert( new TTextField( m, "Ort", 18, moHor ) );
	p->lastInserted->enableCard( 102, 0 );

	f->insert( p );


	/* Contructing Page 4... */
	p = new TPage( "Arzt" );
	m.reset();

	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TTextField( m, "Arbeitgeber Name", 20, moVert ) );
	p->lastInserted->enableCard( 28, 2 );

	p->insert( new TTextField( m, "Angeh”rige", 38, moVert ) );
	p->lastInserted->enableCard( 48, 2 );

	p->insert( new TTextField( m, "Wahlleistung Arzt", 2, moHor ) );
	p->lastInserted->enableCard( 9, 2 );

	p->insert( new TTextField( m, "Name einw. Arzt", 26, moVert ) );
	p->lastInserted->enableCard( 86, 2 );

	p->insert( new TTextField( m, "PLZ", 5, moHor ) );
	p->lastInserted->enableCard( 112, 2 );

	p->insert( new TTextField( m, "Ort", 14, moHor ) );
	p->lastInserted->enableCard( 106, 1 );

	p->insert( new TTextField( m, "Fallart", 3, moHor ) );
	p->lastInserted->enableCard( 117, 2 );

	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Klinikum Hof" );
	sl->put( skPerson,				"Patient" );

	sl->put( skPersonList,			"~P~atienten" );
	sl->put( skNewPerson,			"Patienten ~e~infgen..." );
	sl->put( skDeletePerson,		"Patienten ~l~”schen" );
	sl->put( skEditPerson,			"Daten ~„~ndern..." );
	sl->put( skPrintPerson,			"~F~ormular drucken" );
	sl->put( skRawPrintPerson, 		"~D~aten drucken" );
	sl->put( skEncodeCard,			"~K~arte codieren" );

	sl->put( skHeapView,			"" );

	return sl;
}
