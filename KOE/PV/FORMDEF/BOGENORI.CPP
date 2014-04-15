/*----------------------------------------------*/
/*                                              */
/*              PV 1.0                          */
/*              Bogenhausen                     */
/*              Form Definition Source File     */
/*                                              */
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

	p->insert( new TNameField( m, "Name   ", 30 ) );
	p->lastInserted->makeNecessary();

	p->insert( new TNameField( m, "Vorname", 15, moNoSpace ) );
	p->lastInserted->makeNecessary();

	m.control.a.y --; //!!!
	m.control.b.y --; //!!!

	p->insert( new TBirthDateField( m, "Geb.datum", 10, "TT.MM.JJJJ" ) );
	p->lastInserted->setInfoLevel( ilNormal );
	p->lastInserted->makeNecessary();

	p->insert( new TRadioField( m, "Geschlecht",
								1,
								new TSItem( "M„nnlich",
								new TSItem( "Weiblich", 0 )),
								new TSItem( "M",
								new TSItem( "W", 0 )),
								moDown ) );

	m.control.a.y ++;
	m.control.b.y ++;

	m.control.a.y --; //!!!
	m.control.b.y --; //!!!

	p->insert( new TPNumberField( m, "Aufnahmenr.", 8, "Bereich.Ini",
								  moDown | moVert ) );
	p->lastInserted->setInfoLevel( ilNormal );
	p->lastInserted->makeNecessary();

	p->insert( new TSystemDateField( m, "Datum", 8, "TT.MM.JJ" ) );
	p->lastInserted->makeNecessary();

	p->insert( new TSystemTimeField( m, "Zeit" ) );
	p->lastInserted->makeNecessary();

	p->insert( new TTextField( m, "Strasse", 30, moHor ) );
	p->lastInserted->makeNecessary();

	p->insert( new TTextField( m, "PLZ    ", 8, moHor | moNoSpace ) );
	p->lastInserted->makeNecessary();

	p->insert( new TTextField( m, "Ort    ", 20, moHor | moNoSpace ) );
	p->lastInserted->makeNecessary();

	m.control.a.y --; //!!!
	m.control.b.y --; //!!!

	p->insert( new TTextField( m, "Kassennr.", 7, moVert ) );
	p->insert( new TTextField( m, "Krankenkassenname", 28, moRight ) );

	m.control.a.y --; //!!!
	m.control.b.y --; //!!!

	p->insert( new TRadioField( m, "Allgemein/Privat", 10,
								new TSItem( "",
								new TSItem( "Allgemein",
								new TSItem( "Privat", 0 ))),
								new TSItem( "",
								new TSItem( "Akut     2",
								new TSItem( "Akut ML  1", 0 ))),
								moHor ) );
	p->lastInserted->makeNecessary();

	m.control.a.y += 2;
	m.control.b.y += 2;

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Kostentr„ger" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TListField( m, "Kostentr„ger", 25,
							   "KOSTENTR.LST", 11, moDown | moVert ) );
	p->lastInserted->makeNecessary();

	m.control.a.y += 10;
	m.control.b.y += 10;

	p->insert( new TTextField( m, "Zusatzinfo (z.B. Krzel, Adresse)", 38,
							   moVert ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Station" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TListField( m, "Befund an/Entlassen auf:", 24,
							   "STATION.LST", 16, moDown | moVert ) );
	p->lastInserted->setInfoLevel( ilNormal );
	p->lastInserted->makeNecessary();

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Personalien" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TRadioField( m, "Eingeliefert durch",
								20,
								new TSItem( "Selbst",
								new TSItem( "Rettungswagen",
								new TSItem( "Notarztwagen",
								new TSItem( "Hubschrauber", 0 )))),
								new TSItem( "Selbst",
								new TSItem( "Rettungswagen",
								new TSItem( "Notarztwagen",
								new TSItem( "Hubschrauber", 0 )))),
								moDown | moVert ) );

	m.control.a.y += 3;
	m.control.b.y += 3;

	p->insert( new TTextField( m, "Arbeitgeber Name, Str., PLZ, Ort", 30,
							   moVert ) );
	p->insert( new TTextField( m, 0, 30, moNoSpace ) );
	p->insert( new TTextField( m, 0, 28, moNoSpace ) );

	f->insert( p );

	/* Contructing Page 4... */
	p = new TPage( "Anamnese" );
	m.reset();

//	m.control.a.y ++;
//	m.control.b.y ++;

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Hauptversicherter", 30, moHor ) );
	p->insert( new TBirthDateField( m, "Geb.datum        ", 10, "TT.MM.JJJJ",
									moHor | moNoSpace ) );

	p->insert( new TRadioField( m, "Status",
								3,
								new TSItem( "HV",
								new TSItem( "FAM",
								new TSItem( "REN", 0 ))),
								new TSItem( "HV",
								new TSItem( "FAM",
								new TSItem( "REN", 0 ))),
								moDown | moHor ) );

	m.control.a.y += 2;
	m.control.b.y += 2;

	p->insert( new THiddenConstField( m, "Anamnese", 8 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Anamnese", 38, moVert ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );

	f->insert( p );

	/* Contructing Page 5... */
	p = new TPage( "Aufnahmebefund" );
	m.reset();

//	m.control.a.y ++;
//	m.control.b.y ++;

	p->insert( new THiddenConstField( m, "Aufnahmebefund", 14 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Aufnahmebefund", 38, moVert ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );

	f->insert( p );

	/* Contructing Page 6... */
	p = new TPage( "Diagnose/Behandlung" );
	m.reset();

//	m.control.a.y ++;
//	m.control.b.y ++;

	p->insert( new THiddenConstField( m, "Diagnose", 8 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Aufnahmediagnose", 38, moVert ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );

	p->insert( new THiddenConstField( m, "Behandlung", 10 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Behandlung", 38, moVert ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );

	f->insert( p );

	/* Contructing Page 7... */
	p = new TPage( "Sonstiges" );
	m.reset();

//	m.control.a.y ++;
//	m.control.b.y ++;
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new THiddenConstField( m, "Medikamente + Leistungen", 24 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Medikamente + Leistungen", 38, moVert ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 38, moNoSpace ) );
	p->insert( new TTextField( m, 0, 40, moNoSpace ) );

	p->insert( new THiddenConstField( m, "  ", 2 ) );
	m.control.a.y -= 2;
	m.control.b.y -= 2;

//	p->insert( new TRadioField( m, "D13-Eigenunfall",
//								4,
//								new TSItem( "Nein",
//								new TSItem( "Ja", 0 )),
//								new TSItem( "Nein",
//								new TSItem( "Ja", 0 )),
//								moHor | moDown ) );

//	m.control.a.y ++;
//	m.control.b.y ++;

	p->insert( new TDateField( m, "Nachschau am", 8, "TT.MM.JJ", moHor | moDown ) );
	p->insert( new TNumericField( m, "Uhr", 5, ":" ) );

	p->insert( new TControlField( m, "Ambulant/Station„r",
								  1,
								  new TSItem( "in Behandlung",
								  new TSItem( "entlassen/verlegt",
								  new TSItem( "station„r aufgenommen",
								  new TSItem( "D13-Eigenunfall",
								  new TSItem( "D13 entlassen/verlegt",
								  new TSItem( "D13 station„r aufgen.", 0 )))))),
								  new TSItem( "1",
								  new TSItem( "2",
								  new TSItem( "3",
								  new TSItem( "4",
								  new TSItem( "5",
								  new TSItem( "6", 0 )))))),
								  moDown | moVert ) );

	f->insert( p );

	/* Contructing Page 7... */
	p = new TPage( "Konsil„rzte" );
	m.reset();

	m.control.a.y ++;
	m.control.b.y ++;

	p->insert( new TTextField( m, "Arzt Name", 30, moVert ) );
	p->insert( new TTextField( m, "Konsilarzt 1", 30 ) );
	p->insert( new TTextField( m, "Konsilarzt 2", 30 ) );
	p->insert( new TTextField( m, "Konsilarzt 3", 30 ) );
	p->insert( new TTextField( m, "Konsilarzt 4", 30 ) );

	f->insert( p );


	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Krankenhaus Mnchen Bogenhausen" );
	sl->put( skPerson,				"Patient" );

	sl->put( skPersonList,			"~P~atienten" );
	sl->put( skNewPerson,			"~N~euer Patient..." );
	sl->put( skDeletePerson,		"" );
	sl->put( skEditPerson,			"Daten ~m~odifizieren..." );
	sl->put( skPrintPerson,			"~F~ormular drucken" );
	sl->put( skRawPrintPerson,		"" );
	sl->put( skEncodeCard,			"" );

	sl->put( skHeapView,			"" );

	sl->put( skOldDevice,			"" );
	sl->put( skFormatedRawPrint,	"" );
	sl->put( skNumRPCopiesDlg,		"" );

	sl->put( skAutoSave,			"" );

	sl->put( skFormDlgOK,			"" );
	sl->put( skFormDlgCancel,		"" );

	sl->put( skPrintLog,			"~R~eportliste..." );

	sl->put( skConfirmNewPerson,	"1" );
	sl->put( skDisableOptions,		"1" );

	sl->put( skListWindowTitle,		"Patientendaten-Verwaltung" );

	sl->put( skExportData,			"Daten ~e~xportieren..." );

	return sl;
}
