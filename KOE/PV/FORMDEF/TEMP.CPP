/*----------------------------------------------*/
/*												*/
/*		PV 1.0									*/
/*		Xxxx                               		*/
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

	p->insert( new TNameField( m, "Name", 28 ) );
//	p->lastInserted->enableCard( 0, 0 );
//	p->lastInserted->enableCardLabel( 0, 0, 27 );

	p->insert( new TTextField( m, "Geb./Ledigername", 20 ) );
//	p->lastInserted->enableCard( 30, 0 );
//	p->lastInserted->enableCardLabel( 0, 1 );

	p->insert( new THiddenConstField( m, "", 8 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TNameField( m, "Vorname", 18 ) );

	p->insert( new THiddenConstField( m, "", 10 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Anrede", 20 ) );
	p->insert( new TTextField( m, "Pflegeklasse", 10 ) );

	p->insert( new THiddenConstField( m, "", 10 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TDateField( m, "Geb.Datum", 10, "TT.MM.JJJJ" ) );
	p->insert( new TDateField( m, "E-Datum", 10, "TT.MM.JJJJ", moVert | moDown ) );
	p->insert( new TTextField( m, "Fallnummer", 8, moVert ) );
	p->insert( new TTextField( m, "PLZ, Ort", 30, moHor ) );
	p->insert( new TTextField( m, "Strasse ", 24, moNoSpace ) );

	p->insert( new THiddenConstField( m, "", 6 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Personalien II" );
	m.reset();

	p->insert( new TTextField( m, "Geschlecht", 1 ) );
//	p->insert( new TRadioField( m, "Geschlecht",
//								1,
//								new TSItem( "M„nnlich",
//								new TSItem( "Weiblich", 0 )),
//								new TSItem( "M",
//								new TSItem( "W", 0 )),
//								moDown ) );

	p->insert( new THiddenConstField( m, "", 9 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Behand.Bereich-Text", 10 ) );

	p->insert( new THiddenConstField( m, "", 96 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Einweisender Arzt", 28 ) );
	p->insert( new TTextField( m, "Hausarzt", 28 ) );

	p->insert( new THiddenConstField( m, "", 20 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Konfession", 10 ) );

	p->insert( new THiddenConstField( m, "", 10 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Beruf", 20 ) );

	p->insert( new THiddenConstField( m, "", 8 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Telefon priv.", 15 ) );

	p->insert( new THiddenConstField( m, "", 113 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Personalien III" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Arbeitgeber", 28 ) );
	p->insert( new TTextField( m, "Angeh”riger", 28 ) );

	p->insert( new TTextField( m, "PLZ, Ort Angeh”riger", 20 ) );
	p->insert( new TTextField( m, "Telefon Angeh”riger", 15 ) );

	p->insert( new THiddenConstField( m, "", 73 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Garant 1", 28 ) );

	p->insert( new THiddenConstField( m, "", 4 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Behandelte Abteilung", 8 ) );

	p->insert( new THiddenConstField( m, "", 1258 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new THiddenConstField( m, "$BC", 3 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,					"Xxxx" );
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

	sl->put( skPrintLog,			"" );

	sl->put( skConfirmNewPerson,	"" );
	sl->put( skDisableOptions,		"" );

	sl->put( skListWindowTitle,		"Patientendaten-Verwaltung" );

	sl->put( skExportData,			"" );

	return sl;
}
