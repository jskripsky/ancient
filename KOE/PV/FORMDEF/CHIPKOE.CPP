/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Chip Koelliker							*/
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

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new THiddenConstField( m, "", 3 ) );

	p->insert( new TTextField( m, "Fremdnr.", 7 ) );

	p->insert( new THiddenConstField( m, "", 1 ) );

	p->insert( new TTextField( m, "Anrede  ", 8 ) );
	p->insert( new TNameField( m, "Nachname", 30 ) );
	p->insert( new TNameField( m, "Vorname ", 20 ) );
	p->insert( new TTextField( m, "Strasse ", 30 ) );
	p->insert( new TTextField( m, "Land    ", 3 ) );
	p->insert( new TTextField( m, "PLZ", 6 ) );
	p->insert( new TTextField( m, "Wohnort ", 30 ) );
	p->insert( new TTextField( m, "Geb.Datum", 10 ) );
	p->insert( new TTextField( m, "Geschlecht", 1, moDown ) );
	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Patient" );
	m.reset();

	p->insert( new TTextField( m, "Eintrittsdatum", 10 ) );
	p->insert( new TTextField( m, "Systemdatum", 13 ) );
	p->insert( new TTextField( m, "Patientennr.", 7 ) );
	p->insert( new TTextField( m, "Fallnr.", 4 ) );
	p->insert( new TTextField( m, "Kurzbez. Kasse  ", 6 ) );
	p->insert( new TTextField( m, "Orge AG Kurzbez.", 6 ) );
	p->insert( new TTextField( m, "Orge AE Kurzbez.", 6 ) );
	p->insert( new TTextField( m, "Patiententyp", 3 ) );
	p->insert( new TTextField( m, "Patienten-Kat.", 10 ) );
	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Diverses I" );
	m.reset();

	p->insert( new TTextField( m, "Kurzbez. BA", 15 ) );
	p->insert( new TTextField( m, "Kurzbez. Tarif", 2 ) );
	p->insert( new TTextField( m, "Detailkl. aus Fall", 3 ) );
	p->insert( new TTextField( m, "2. Anschriftsz.", 30 ) );
	p->insert( new TTextField( m, "Land Steuerdomizil", 3 ) );
	p->insert( new TTextField( m, "PLZ", 6 ) );
	p->insert( new TTextField( m, "Ort", 30 ) );
	p->insert( new TTextField( m, "Telefon Patient", 30 ) );
	p->insert( new TTextField( m, "Nation", 3 ) );
	p->insert( new TTextField( m, "Brgerort", 30 ) );
	f->insert( p );

	/* Contructing Page 4... */
	p = new TPage( "Diverses II" );
	m.reset();

	p->insert( new TTextField( m, "Kurzbez. Kontaktperson", 15 ) );
	p->insert( new TTextField( m, "Adressnummer KP", 8 ) );
	p->insert( new TTextField( m, "Name KP", 30 ) );
	p->insert( new TTextField( m, "Tel. Nr. KP", 30 ) );
	p->insert( new TTextField( m, "Tel. Nr. KP", 30 ) );
	p->insert( new TTextField( m, "Kurzbemerkung", 30 ) );
	p->insert( new TTextField( m, "AHV-Nummer", 14 ) );
	p->insert( new TTextField( m, "Konfession", 3 ) );
	p->insert( new TTextField( m, "Zivilstand", 3 ) );
	p->insert( new TTextField( m, "Beruf", 30 ) );
	f->insert( p );

	/* Contructing Page 5... */
	p = new TPage( "Diverses III" );
	m.reset();

	p->insert( new TTextField( m, "Unfallcode", 1 ) );
	p->insert( new TTextField( m, "Depotpflicht", 1, moDown ) );
	p->insert( new TTextField( m, "Fallpauschale", 1, moDown ) );
	p->insert( new TTextField( m, "Selbstzahler", 1, moDown ) );
	p->insert( new TTextField( m, "Garantentyp", 2 ) );
	p->insert( new TTextField( m, "Zimmerbez.", 12 ) );
	p->insert( new TTextField( m, "Zimmer Tel.Nr.", 7 ) );
	p->insert( new TTextField( m, "Diagnose", 8 ) );
	p->insert( new TTextField( m, "Bemerkung 1", 30, moVert ) );

	f->insert( p );

	/* Contructing Page 6... */
	p = new TPage( "Arbeitgeber" );
	m.reset();

	p->insert( new TTextField( m, "Kurzbez. AG", 15 ) );
	p->insert( new TTextField( m, "Adressnr. AG", 8 ) );
	p->insert( new TTextField( m, "Name AG", 30 ) );
	p->insert( new TTextField( m, "Ort AG ", 30 ) );
	p->insert( new TTextField( m, "Teil 1 AG", 30 ) );
	p->insert( new TTextField( m, "Vers.Nr. AG", 15 ) );

	f->insert( p );

	/* Contructing Page 7... */
	p = new TPage( "Einweisender Arzt" );
	m.reset();

	p->insert( new TTextField( m, "Adressnr. EA", 8 ) );
	p->insert( new TTextField( m, "Kurzbez. EA ", 15 ) );
	p->insert( new TTextField( m, "Anrede EA   ", 8 ) );
	p->insert( new TTextField( m, "Titel EA    ", 10 ) );
	p->insert( new TTextField( m, "Name EA", 30, moVert ) );

//	p->insert( new THiddenConstField( m, "", 791 ) );
	p->insert( new THiddenConstField( m, "", 791 + 48 ) );

	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Chip Koelliker" );
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
