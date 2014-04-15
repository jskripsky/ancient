/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Laufen             						*/
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

	p->insert( new TNumericField( m, "Patientennr.", 12, "." ) );

	p->insert( new TNameField( m, "Name   ", 26 ) );
	p->lastInserted->makeNecessary();

	p->insert( new TNameField( m, "Vorname", 14, moNoSpace ) );

	p->insert( new TTextField( m, "Strasse, Nr.", 30 ) );
	p->insert( new TTextField( m, "PLZ, Ort", 25 ) );

	p->insert( new TNumericField( m, "Telefon-Nr.", 13, " -/" ) );

	p->insert( new TDateField( m, "Geburtsdatum", 10, "TT.MM.JJJJ" ) );

	p->insert( new TRadioField( m, "Geschlecht",
								1,
								new TSItem( "M„nnlich",
								new TSItem( "Weiblich", 0 )),
								new TSItem( "M",
								new TSItem( "W", 0 )),
								moDown ) );
	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TTextField( m, "Brgerort", 27 ) );

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Personalien II" );
	m.reset();
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TRadioField( m, "Zivilstand",
								13,
								new TSItem( "ledig",
								new TSItem( "verheiratet",
								new TSItem( "geschieden",
								new TSItem( "getrennt",
								new TSItem( "verwitwet", 0 ))))),
								new TSItem( "ledig",
								new TSItem( "verheiratet",
								new TSItem( "geschieden",
								new TSItem( "getrennt",
								new TSItem( "verwitwet", 0 ))))),
								moDown ) );

	m.control.a.y += 4;
	m.control.b.y += 4;

	p->insert( new TRadioField( m, "Konfession",
								13,
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
								new TSItem( "r”m.-kath.",
								new TSItem( "chri.kath.",
								new TSItem( "reformiert",
								new TSItem( "jdisch",
								new TSItem( "islamisch",
								new TSItem( "budhistisch",
								new TSItem( "gr.russ.orth.",
								new TSItem( "andere", 0 ))))))))),
								moDown ) );

	m.control.a.y += 8;
	m.control.b.y += 8;

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Angeh”rige/Garanten" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Angeh”rige", 40, moVert ) );
	p->insert( new TTextField( m, 0, 40, moNoSpace ) );
	p->insert( new TTextField( m, 0, 40, moNoSpace ) );

	p->insert( new TTextField( m, "Beruf/Arbeitgeber", 40, moVert ) );
	p->insert( new TTextField( m, 0, 40, moNoSpace ) );
	p->insert( new TTextField( m, 0, 40, moNoSpace ) );

	p->insert( new TTextField( m, "Garanten", 55, moVert ) );
	p->insert( new TTextField( m, 0, 55, moNoSpace ) );
	p->insert( new TTextField( m, 0, 55, moNoSpace ) );

	f->insert( p );

	/* Contructing Page 4... */
	p = new TPage( "Eintritt" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Behandelnder Arzt", 40, moVert ) );

	p->insert( new TTextField( m, "Einweisender Arzt", 42, moVert ) );

	p->insert( new TDateField( m, "Eintr.Datum", 10, "TT.MM.JJJJ", moHor ) );
	p->insert( new TTextField( m, "Abteilung/Klasse", 13 ) );

	p->insert( new TTextField( m, "Frhere Eintritte", 17, moVert ) );
	p->insert( new TTextField( m, 0, 27, moNoSpace ) );

	m.control.a.y++;
	m.control.b.y++;

	f->insert( p );

	/* Contructing Page 5... */
	p = new TPage( "Aufnahme" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Bermerkungen", 55, moVert ) );
	p->insert( new TTextField( m, 0, 55, moNoSpace ) );
	p->insert( new TTextField( m, 0, 55, moNoSpace ) );

	p->insert( new TTextField( m, "Klinik           ", 6, moHor ) );
	p->insert( new TTextField( m, "Aufgenommen durch", 8 ) );

	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Laufen" );
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
