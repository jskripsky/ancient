/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Samedan 								*/
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
	p = new TPage( "Personalien" );
	m.reset();

//	m.control.a.y -= 2;
//	m.control.b.y -= 2;

	p->insert( new TNameField( m, "Name   ", 30, moHor ) );
	p->lastInserted->enableCard( 0, 0 );
	p->lastInserted->enableCardLabel( 0, 0, 28 );

	p->insert( new TNameField( m, "Vorname", 15 ) );
	p->lastInserted->enableCard( 30, 0 );
	p->lastInserted->enableCardLabel( 0, 1 );

	p->insert( new TTextField( m, "Strasse", 30 ) );
	p->lastInserted->enableCard( 45, 0 );

	p->insert( new TTextField( m, "PLZ Ort", 30 ) );
	p->lastInserted->enableCard( 75, 0 );

	p->insert( new TNumericField( m, "Geburtsdatum", 8 ) );
	p->lastInserted->enableCard( 105, 0 );
	p->lastInserted->enableCardLabel( 18, 1 );

	p->insert( new TTextField( m, "Geschlecht", 1, moDown ) );
	p->lastInserted->enableCard( 113, 0 );
	p->lastInserted->enableCardLabel( 27, 1 );

	p->insert( new TTextField( m, "Behandlungsber.", 1 ) );
	p->lastInserted->enableCard( 114, 0 );

	p->insert( new TTextField( m, "Klasse", 1, moDown ) );
	p->lastInserted->enableCard( 115, 0 );

	p->insert( new TTextField( m, "Eintrittsart", 3 ) );
	p->lastInserted->enableCard( 116, 0 );

	p->insert( new TTextField( m, "Patientennr./Fall Nr.", 8 ) );
	p->lastInserted->enableCard( 0, 1 );
	p->lastInserted->enableCardLabel( 0, 2 );

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Eintritt/Arzt" );
	m.reset();

	p->insert( new TNumericField( m, "Eintrittsdatum", 8 ) );
	p->lastInserted->enableCard( 8, 1 );

	p->insert( new TTextField( m, "Einweisender Arzt", 26, moVert ) );
	p->lastInserted->enableCard( 16, 1 );

	p->insert( new TTextField( m, "Behandelnder Arzt", 26 ) );
	p->lastInserted->enableCard( 42, 1 );

	p->insert( new TNumericField( m, "Telefon privat", 20, ". /", moHor ) );
	p->lastInserted->enableCard( 68, 1 );

	p->insert( new TTextField( m, "Zivilstand", 5, moDown ) );
	p->lastInserted->enableCard( 88, 1 );

	p->insert( new TTextField( m, "Konfession", 4 ) );
	p->lastInserted->enableCard( 93, 1 );

	p->insert( new TTextField( m, "Beruf", 18 ) );
	p->lastInserted->enableCard( 97, 1 );

	p->insert( new TNumericField( m, "Eintrittszeit", 4, " .:" ) );
	p->lastInserted->enableCard( 115, 1 );

	f->insert( p );


	/* Contructing Page 3... */
	p = new TPage( "Diverses" );
	m.reset();

	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TTextField( m, "Kostentr„ger", 20, moVert ) );
	p->lastInserted->enableCard( 0, 2 );
	p->lastInserted->enableCardLabel( 0, 3 );

	p->insert( new TTextField( m, "Arbeitgeber", 28, moVert ) );
	p->lastInserted->enableCard( 20, 2 );

	p->insert( new TTextField( m, "Ferienadresse", 28, moVert ) );
	p->lastInserted->enableCard( 48, 2 );

	p->insert( new TTextField( m, "Angeh”rige", 28, moVert ) );
	p->lastInserted->enableCard( 76, 2 );

	p->insert( new TTextField( m, "Klinik 1 (Abt.Nr.)  ", 4, moHor ) );
	p->lastInserted->enableCard( 104, 2 );
	p->lastInserted->enableCardLabel( 18, 2 );

	p->insert( new TTextField( m, "Klinik 2 (Tisch Nr.)", 4 ) );
	p->lastInserted->enableCard( 108, 2 );
	p->lastInserted->enableCardLabel( 24, 2 );

	p->insert( new TTextField( m, "Telefon intern", 4 ) );
	p->lastInserted->enableCard( 112, 2 );

	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Spital Samedan" );
	sl->put( skPerson,				"Patient" );

	sl->put( skPersonList,			"~P~atienten" );
	sl->put( skNewPerson,			"Patienten ~e~infgen..." );
	sl->put( skDeletePerson,		"Patienten ~l~”schen" );
	sl->put( skEditPerson,			"Daten ~m~odifizieren..." );
	sl->put( skPrintPerson,			"~F~ormular drucken" );
	sl->put( skRawPrintPerson, 		"~S~tammblatt drucken" );
	sl->put( skEncodeCard,			"~K~arte codieren" );

	sl->put( skHeapView,			"" );

	sl->put( skOldDevice,			"" );
	sl->put( skFormatedRawPrint,	"" );
	sl->put( skNumRPCopiesDlg,		"" );

	sl->put( skAutoSave,			"" );

	sl->put( skFormDlgOK,			"~O~K" );
	sl->put( skFormDlgCancel,		"~A~bbrechen" );

	return sl;
}
