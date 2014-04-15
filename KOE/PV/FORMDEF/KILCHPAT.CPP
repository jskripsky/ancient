/*----------------------------------------------*/
/*												*/
/*		PV 1.0									*/
/*		Sanatorium Kilchberg, Kurzaufnahme		*/
/*		Form Definition Source File				*/
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
	p->lastInserted->enableCardLabel( 20, 4 );

	p->insert( new TNameField( m, "Name, Vorname", 30, moVert ) );
	p->lastInserted->enableCard( 0, 0 );
	p->lastInserted->enableCardLabel( 0, 1, 28 );

	p->insert( new TTextField( m, "Strasse, Nr.", 30, moVert ) );
	p->lastInserted->enableCard( 30, 0 );
	p->lastInserted->enableCardLabel( 0, 2, 28 );

	p->insert( new TTextField( m, "PLZ, Wohnort", 30, moVert ) );
	p->lastInserted->enableCard( 60, 0 );
	p->lastInserted->enableCardLabel( 0, 3, 28 );

	p->insert( new TDateField( m, "Geburtsdatum", 10, "TT.MM.JJJJ", moDown ) );
	p->lastInserted->enableCard( 105, 0 );
	p->lastInserted->enableCardLabel( 0, 4 );

	p->insert( new TTextField( m, "Geschlecht", 1, moHor ) );
	p->lastInserted->enableCard( 115, 0 );
	p->lastInserted->enableCardLabel( 11, 4 );

	p->insert( new TDateField( m, "Eintrittsdatum", 10, "TT.MM.JJJJ",
							   moDown ) );
	p->lastInserted->enableCard( 98, 1 );

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
								new TSItem( "ledig       ",
								new TSItem( "verheiratet ",
								new TSItem( "geschieden  ",
								new TSItem( "getrennt    ",
								new TSItem( "verwitwet   ", 0 ))))),
								moDown ) );

	p->lastInserted->enableCard( 0, 2 );

	m.control.a.y += 4;
	m.control.b.y += 4;

	p->insert( new TRadioField( m, "Klasse    ",
								5,
								new TSItem( "PRIV.",
								new TSItem( "PRIV. AKUT",
								new TSItem( "PRIV. E",
								new TSItem( "HALBPRIV.",
								new TSItem( "HP AKUT",
								new TSItem( "HP E+B4",
								new TSItem( "ALLG.",
								new TSItem( "ALLG. AKUT",
								new TSItem( "BLI",
								new TSItem( "UNBEK.", 0 )))))))))),
								new TSItem( "PRIVAT      ",
								new TSItem( "PRIVAT AKUT ",
								new TSItem( "PRIVAT E    ",
								new TSItem( "HALBPRIVAT  ",
								new TSItem( "HP AKUT     ",
								new TSItem( "HP E+E4     ",
								new TSItem( "ALLGEMEIN   ",
								new TSItem( "ALLG. AKUT  ",
								new TSItem( "BLI         ",
								new TSItem( "UNBEKANNT   ", 0 )))))))))),
								moDown ) );
	p->lastInserted->enableCard( 108, 1);

	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,					"Sanatorium Kilchberg" );
	sl->put( skPerson,						"Patient" );

	sl->put( skPersonList,                  "~P~atienten" );
	sl->put( skNewPerson,                   "Patienten ~e~infgen..." );
	sl->put( skDeletePerson,                "Patienten ~l~”schen" );
	sl->put( skEditPerson,                  "Daten ~m~odifizieren..." );
	sl->put( skPrintPerson,                 "~F~ormular drucken" );
	sl->put( skRawPrintPerson,              "~D~aten drucken" );
	sl->put( skEncodeCard,                  "~K~arte codieren" );

	sl->put( skHeapView,			"" );

	sl->put( skOldDevice,			"" );
	sl->put( skFormatedRawPrint,	"" );
	sl->put( skNumRPCopiesDlg,		"" );

	sl->put( skAutoSave,			"" );

	sl->put( skFormDlgOK,			"~O~K" );
	sl->put( skFormDlgCancel,		"~A~bbrechen" );


	return sl;
}
