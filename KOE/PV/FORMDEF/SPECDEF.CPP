/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Pfaefers Form Definition Source File 	*/
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
	p = new TPage( "Patientendaten I" );
	m.reset();

	p->insert( new TTextField( m, "Aufnahmenummer",  8 ) );
	p->insert( new TNameField( m, "Name", 32, moVert ) );
	p->insert( new TTextField( m, "Geburtsname", 20, moHor ) );
	p->insert( new TTextField( m, "Geburtsdatum", 8 ) );
	p->insert( new TTextField( m, "PLZ", 5, moDown ) );
	p->insert( new TTextField( m, "Wohnort", 23 ) );
	p->insert( new TTextField( m, "Strasse", 29 ) );
	p->insert( new TTextField( m, "Familienstand", 1 ) );
	p->insert( new TTextField( m, "Geschlecht", 1, moRight ) );

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Patientendaten II" );
	m.reset();

	p->insert( new TTextField( m, "Herkunftsschlssel", 2 ) );
	p->insert( new TTextField( m, "Staatsangeh”rigkeit", 2, moDown ) );
	p->insert( new TTextField( m, "Religion", 1, moDown ) );
	p->insert( new TTextField( m, "Einweisungsart", 2, moDown ) );
	p->insert( new TTextField( m, "Aufnahmedatum", 6, moDown ) );
	p->insert( new TTextField( m, "Aufnahmeuhrzeit", 4, moDown ) );
	p->insert( new TTextField( m, "Klinik/Station", 4, moDown ) );
	p->insert( new TTextField( m, "Pflegesatzschlssel", 2, moDown ) );
	p->insert( new TTextField( m, "Zimmerzuschlagkennz.", 2, moDown ) );

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Entlass./Kostentr." );
	m.reset();

	p->insert( new TTextField( m, "Liquidationskennz.", 2 ) );
	p->insert( new TTextField( m, "Entlassungsdatum", 4 ) );
	p->insert( new TTextField( m, "Entlassungsuhrzeit", 4 ) );
	p->insert( new TTextField( m, "Entlassungsart", 1 ) );
	p->insert( new TTextField( m, "Externes Krankenhaus", 1 ) );
	p->insert( new TTextField( m, "Kostentr„gerschlssel", 4 ) );
	p->insert( new TTextField( m, "Kostentr„gername", 29, moVert ) );
	p->insert( new TTextField( m, "PLZ", 5, moVert ) );
	p->insert( new TTextField( m, "Ort", 11 ) );

	f->insert( p );

	/* Contructing Page 4... */
	p = new TPage( "Stammversicherter" );
	m.reset();
	m.control.a.y++; m.control.b.y++;

	p->insert( new TTextField( m, "Aktenzeichen Kostentr„ger", 30, moVert ) );
	p->insert( new TTextField( m, "Mitgliedsart", 1, moHor ) );
	p->insert( new TTextField( m, "Name Stammversicherter", 26, moVert ) );
	p->insert( new TTextField( m, "Geburtsdatum Stammvers.", 8, moHor ) );
	p->insert( new TTextField( m, "Beruf Stammvers.", 20, moVert ) );
	p->insert( new TTextField( m, "Arbeitgeber Stammvers.", 25, moVert ) );

	f->insert( p );

	/* Contructing Page 5... */
	p = new TPage( "Angeh”rige/Arzt" );
	m.reset();
	m.control.a.y++; m.control.b.y++;

	p->insert( new TTextField( m, "Name n„chster Angeh”riger", 32, moVert ) );
	p->insert( new TTextField( m, "PLZ", 5, moVert ) );
	p->insert( new TTextField( m, "Wohnort", 23 ) );
	p->insert( new TTextField( m, "Strasse", 30 ) );
	p->insert( new TTextField( m, "Telefon Angeh.", 12, moHor ) );
	p->insert( new TTextField( m, "Schlssel einweisender Arzt", 4 ) );
	p->insert( new TTextField( m, "Name einweisender Arzt", 28, moVert ) );

	f->insert( p );



	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"-" );
	sl->put( skPerson,				"Patient" );

	sl->put( skPersonList,			"~P~atienten" );
	sl->put( skNewPerson,			"Patienten ~e~infgen..." );
	sl->put( skDeletePerson,		"Patienten ~l~”schen" );
	sl->put( skEditPerson,			"Daten ~„~ndern..." );
	sl->put( skPrintPerson,			"~F~ormular drucken" );
	sl->put( skRawPrintPerson, 		"~D~aten drucken" );
	return sl;
}
