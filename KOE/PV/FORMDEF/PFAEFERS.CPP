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
	p = new TPage( "Personalien I" );
	m.reset();

	p->insert( new TTextField( m, "Personalnr.", 10 ) );
	p->lastInserted->enableCardLabel( 20, 0 );

	p->insert( new TNameField( m, "Name, Vorname", 34, moVert ) );
	p->lastInserted->enableCardLabel( 0, 0, 20 );
	p->lastInserted->enableCard( 0, 0 );

	p->insert( new TTextField( m, "Strasse", 25, moHor ) );
	p->lastInserted->enableCardLabel( 0, 1 );
	p->insert( new TTextField( m, "PLZ", 7 ) );
	p->lastInserted->enableCardLabel( 0, 2 );
	p->insert( new TTextField( m, "Wohnort", 22 ) );
	p->lastInserted->enableCardLabel( 0, 3 );
	p->insert( new TTextField( m, "Tel.Nr.", 17 ) );
	p->lastInserted->enableCardLabel( 0, 4 );
	p->insert( new TTextField( m, "Geburtsdatum", 8 ) );
	p->lastInserted->enableCardLabel( 0, 5 );
	p->insert( new TTextField( m, "Geschlecht", 1, moDown ) );
	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Personalien II" );
	m.reset();

	p->insert( new TTextField( m, "Heimatort/Nation", 20 ) );
	p->insert( new TTextField( m, "Bewilligungsart", 3 ) );
	p->insert( new TTextField( m, "Bewilligungsdauer", 8 ) );
	p->lastInserted->disablePrint();

	p->insert( new TTextField( m, "AHV Nummer", 14 ) );
	p->insert( new TTextField( m, "Konfession", 8 ) );
	p->insert( new TTextField( m, "Zivilstand", 8 ) );
	p->insert( new TTextField( m, "Vorname/M„dchenname Ehegatte", 26,
							   moVert ) );
	p->insert( new TTextField( m, "Geburtsdatum", 8, moHor ) );

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Familie" );
	m.reset();

	p->insert( new TTextField( m, "Familienzulage", 3 ) );

	p->insert( new TTextField( m, "Name Kind", 12, moVert | moDown ) );
	p->insert( new TTextField( m, "Geb.Datum",  8 ) );
	for( int counter = 0; counter < 5; counter++ )
		{
		p->insert( new TTextField( m, 0, 12, moNoSpace | moDown ) );
		p->insert( new TTextField( m, 0, 8 ) );
		}

	p->insert( new TTextField( m, "Angeh. Name", 25, moHor ) );
	p->insert( new TTextField( m, "Angeh. Adr.", 25 ) );
	p->insert( new TTextField( m, "Angeh. Adr.", 25 ) );

	f->insert( p );

	/* Contructing Page 4... */
	p = new TPage( "Versicherungen" );
	m.reset();

	p->insert( new TTextField( m, "KKasse/Sekt.", 25 ) );
	p->insert( new TTextField( m, "Unfallvers.", 25 ) );
	p->insert( new TTextField( m, "Zusatzvers.", 3 ) );
	p->insert( new TTextField( m, "Milit. Eint.", 25 ) );
	p->insert( new TTextField( m, "Grad", 10 ) );

	p->insert( new TTextField( m, "Eintr.Datum", 8, moVert | moDown ) );
	p->insert( new TTextField( m, "Austr.Datum", 8 ) );

	p->insert( new TTextField( m, "Funktion", 25, moHor ) );
	p->insert( new TTextField( m, "Abteilung", 18 ) );

	f->insert( p );

	/* Contructing Page 5... */
	p = new TPage( "Bank" );
	m.reset();

	p->insert( new TTextField( m, "Int. Tel.Nr./Abt.", 10 ) );
	p->insert( new TTextField( m, "ZimmerNr./Wohnung", 10 ) );
	p->insert( new TTextField( m, "Tel.Nr. Zimmer/Wohnung", 3 ) );
	p->insert( new TTextField( m, "Bank/Post", 35 ) );
	p->insert( new TTextField( m, "InstitutNr.", 18 ) );
	p->insert( new TTextField( m, "KontoNr.", 25 ) );
	p->insert( new TTextField( m, "Vers./Spark.", 35 ) );
	p->insert( new TTextField( m, "Steuersparverein", 4 ) );
	p->insert( new TTextField( m, "Quellensteuer   ", 4, moNoSpace ) );

	f->insert( p );

	/* Contructing Page 6... */
	p = new TPage( "Einstellungen" );
	m.reset();

	m.control.a.y += 2; m.control.b.y += 2;
	TField *fld = new TTextField( m, "von", 8 );
	TPoint point = { 0, 0 };
	fld->attachStaticText( point, "Bisherige Einstellungen "
								"beim Kanton" );
	p->insert( fld );
	p->lastInserted->disablePrint();
	p->insert( new TTextField( m, "bis", 8 ) );
	p->lastInserted->disablePrint();

	for( counter = 0; counter < 5; counter++ )
		{
		p->insert( new TTextField( m, "   ", 8, moNoSpace | moDown ) );
		p->lastInserted->disablePrint();
		p->insert( new TTextField( m, "   ", 8 ) );
		p->lastInserted->disablePrint();
		}

	p->insert( new TTextField( m, "Total Jahre", 4, moDown ) );
	p->insert( new TTextField( m, "Total Monate", 4, moDown ) );

	f->insert( p );

	/* Contructing Page 7... */
	p = new TPage( "Bef”rderungen" );
	m.reset();

	p->insert( new TTextField( m, "Funktions-Code", 18 ) );
	p->insert( new TTextField( m, "Einstufung DBO", 30, moNoSpace ) );

	p->insert( new TTextField( m, "Bef”rd.Dat.", 8, moVert ) );
	p->insert( new TTextField( m, "Einstufung/Stunden", 15 ) );

	for( counter = 0; counter < 8; counter++ )
		{
		p->insert( new TTextField( m, 0, 8, moDown | moNoSpace ) );
		p->insert( new TTextField( m, 0, 15 ) );
		}

	p->insert( new TTextField( m, "Besch„ft.Grad/Lohnproz.", 10, moHor ) );
	p->insert( new TTextField( m, "Rechnungsabschnitt", 8 ) );

	f->insert( p );

	/* Contructing Page 8... */
	p = new TPage( "Adressen" );
	m.reset();

	p->insert( new TTextField( m, "KontoNr.", 12 ) );
	p->insert( new TTextField( m, "Stellenplan-Nr.", 10 ) );

	p->insert( new TTextField( m, "Std.Lohn", 5, moVert | moDown ) );
	p->insert( new TTextField( m, "Std/Woch", 5 ) );

	p->insert( new TTextField( m, "Zuzug von", 80 ) );
	p->lastInserted->disablePrint();

	p->insert( new TTextField( m, 0, 80, moNoSpace ) );
	p->lastInserted->disablePrint();

	p->insert( new TTextField( m, "Wegzugadresse", 80, moNoSpace ) );
	p->lastInserted->disablePrint();
	p->insert( new TTextField( m, 0, 80, moNoSpace ) );
	p->lastInserted->disablePrint();

	p->insert( new TTextField( m, "Neuer Arbeitgeber", 80 ) );
	p->lastInserted->disablePrint();

	f->insert( p );

	/* Contructing Page 9... */
	p = new TPage( "Schlssel" );
	m.reset();

	m.control.a.y += 3;
	m.control.b.y += 3;
	fld = new TTextField( m, "Klinik   ", 2 );
	point.x = m.control.a.x;
	point.y = m.control.a.y - 1;
	fld->attachStaticText( point, "Anz." );
	p->insert( fld );

	fld = new TTextField( m, 0, 8, moVert );
	point.x = m.control.a.x;
	point.y = m.control.a.y - 1;
	fld->attachStaticText( point, "Nummer" );
	p->insert( fld );

	fld = new TTextField( m, 0, 8, moVert );
	point.x = m.control.a.x;
	point.y = m.control.a.y - 1;
	fld->attachStaticText( point, "Ausg.Datum" );
	p->insert( fld );

	fld = new TTextField( m, "Garderobe", 2, moHor | moNoSpace | moDown );
	point.x = 0; point.y = 0;
	fld->attachStaticText( point, "Schlsselausgabe" );
	p->insert( fld );
	p->insert( new TTextField( m, 0, 8, moVert ) );
	p->insert( new TTextField( m, 0, 8 ) );

	p->insert( new TTextField( m, "Zimmer   ", 2,
							   moHor | moNoSpace | moDown ) );
	p->insert( new TTextField( m, 0, 8, moVert ) );
	p->insert( new TTextField( m, 0, 8 ) );

	p->insert( new TTextField( m, "Wohnung  ", 2,
							   moHor | moNoSpace | moDown ) );
	p->insert( new TTextField( m, 0, 8, moVert ) );
	p->insert( new TTextField( m, 0, 8 ) );

	p->insert( new TTextField( m, "Briefk.  ", 2,
							   moHor | moNoSpace | moDown ) );
	p->insert( new TTextField( m, 0, 8, moVert ) );
	p->insert( new TTextField( m, 0, 8 ) );

	p->insert( new TTextField( m, "Garage   ", 2,
							   moHor | moNoSpace | moDown ) );
	p->insert( new TTextField( m, 0, 8, moVert ) );
	p->insert( new TTextField( m, 0, 8 ) );

	p->insert( new TTextField( m, "Waschk.  ", 2,
							   moHor | moNoSpace | moDown ) );
	p->insert( new TTextField( m, 0, 8, moVert ) );
	p->insert( new TTextField( m, 0, 8 ) );

	p->insert( new TTextField( m, "Benzin   ", 2,
							   moHor | moNoSpace | moDown ) );
	p->insert( new TTextField( m, 0, 8, moVert ) );
	p->insert( new TTextField( m, 0, 8 ) );

	p->insert( new TTextField( m, 0, 15, moDown ) );
	p->insert( new TTextField( m, "         ", 2,
							   moHor | moNoSpace | moDown ) );
	p->insert( new TTextField( m, 0, 8, moVert ) );
	p->insert( new TTextField( m, 0, 8 ) );


/*** old version:: ***
	p->insert( new TTextField( m, "Reserve  ", 2,
							   moHor | moNoSpace | moDown ) );
	p->insert( new TTextField( m, 0, 8, moVert ) );
	p->insert( new TTextField( m, 0, 8 ) );

	p->insert( new TTextField( m, 0, 5, moNoSpace | moDown | moVert ) );
	p->lastInserted->disablePrint();
	p->insert( new TTextField( m, 0, 2, moVert  ) );
	p->lastInserted->disablePrint();
	p->insert( new TTextField( m, 0, 8 ) );
	p->lastInserted->disablePrint();
	p->insert( new TTextField( m, 0, 8 ) );
 *********************/

	f->insert( p );
	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Pf„fers" );
	sl->put( skPerson,				"Person" );

	sl->put( skPersonList,			"~P~ersonen" );
	sl->put( skNewPerson,			"Person ~e~infgen..." );
	sl->put( skDeletePerson,		"Person ~l~”schen" );
	sl->put( skEditPerson,			"Daten ~„~ndern..." );
	sl->put( skPrintPerson,			"~F~ormular drucken" );
	sl->put( skRawPrintPerson, 		"~D~aten drucken" );
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
