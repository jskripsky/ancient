/*----------------------------------------------*/
/*												*/
/*		PV 1.0									*/
/*		Herisau                            		*/
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

	p->insert( new TNumericField( m, "Patientennr.  ", 7, "." ) );
	p->lastInserted->enableCard( 0, 1 );
	p->lastInserted->enableCardLabel( 20, 1 );

	p->insert( new TNameField( m, "Name   ", 30 ) );
	p->lastInserted->enableCard( 0, 0 );
	p->lastInserted->enableCardLabel( 0, 0, 27 );

	p->insert( new TNameField( m, "Vorname", 18 ) );
	p->lastInserted->enableCard( 30, 0 );
	p->lastInserted->enableCardLabel( 0, 1 );

	p->insert( new TTextField( m, "Strasse, Nr.", 24 ) );
	p->lastInserted->enableCard( 48, 0 );

	p->insert( new TTextField( m, "PLZ, Ort    ", 24 ) );
	p->lastInserted->enableCard( 72, 0 );

	p->insert( new TRadioField( m, "Geschlecht",
								1,
								new TSItem( "M„nnlich",
								new TSItem( "Weiblich", 0 )),
								new TSItem( "M",
								new TSItem( "W", 0 )),
								moDown ) );
	p->lastInserted->enableCard( 115, 2 );
	p->lastInserted->enableCardLabel( 26, 2 );

	m.control.a.y ++;
	m.control.b.y ++;

	p->insert( new TDateField( m, "Geburtsdatum  ", 8, "TT.MM.JJ", moDown ) );
	p->lastInserted->enableCard( 7, 1 );
	p->lastInserted->enableCardLabel( 15, 2 );

	p->insert( new TNumericField( m, "Telefon Privat", 15, " .-/" ) );
	p->lastInserted->enableCard( 96, 2 );

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Konf./Zivilst." );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TRadioField( m, "Konfession",
								1,
								new TSItem( " ",
								new TSItem( "reformiert",
								new TSItem( "katholisch",
								new TSItem( "orthodox",
								new TSItem( "neuap.",
								new TSItem( "diverse",
								new TSItem( "konfessionslos", 0 ))))))),

								new TSItem( " ",
								new TSItem( "R",
								new TSItem( "K",
								new TSItem( "O",
								new TSItem( "N",
								new TSItem( "D",
								new TSItem( "-", 0 ))))))),
								moDown ) );
	m.control.a.y += 6;
	m.control.b.y += 6;

	p->insert( new TRadioField( m, "Zivilstand",
								3,
								new TSItem( " ",
								new TSItem( "ledig",
								new TSItem( "verheiratet",
								new TSItem( "verwitwet",
								new TSItem( "geschieden",
								new TSItem( "keine Angaben", 0 )))))),
								new TSItem( " ",
								new TSItem( "led",
								new TSItem( "vrh",
								new TSItem( "vrw",
								new TSItem( "gsc",
								new TSItem( "k.A", 0 )))))),
								moDown ) );

	m.control.a.y += 5;
	m.control.b.y += 5;

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Arbeitgeber/Žrzte" );
	m.reset();

	p->insert( new TTextField( m, "Beruf", 23 ) );
	p->lastInserted->enableCard( 96, 0 );

	p->insert( new TTextField( m, "Arbeitgeber Name", 24, moVert ) );
	p->lastInserted->enableCard( 48, 2 );

	p->insert( new TTextField( m, "Arbeitgeber Wohnort", 24, moNoSpace ) );
	p->lastInserted->enableCard( 72, 2 );

	p->insert( new TTextField( m, "Einw. Arzt Name", 24, moVert ) );
	p->lastInserted->enableCard( 23, 1 );

	p->insert( new TTextField( m, "Einw. Arzt Wohnort", 24, moNoSpace ) );
	p->lastInserted->enableCard( 47, 1 );

	p->insert( new TTextField( m, "Hausarzt Name", 24, moVert ) );
	p->lastInserted->enableCard( 71, 1 );

	p->insert( new TTextField( m, "Hausarzt Wohnort", 24, moNoSpace ) );
	p->lastInserted->enableCard( 95, 1 );

	f->insert( p );

	/* Contructing Page 4... */
	p = new TPage( "Eintritt" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TDateField( m, "Eintrittsdatum", 8, "TT.MM.JJ",
							   moDown ) );
	p->lastInserted->enableCard( 15, 1 );
	p->lastInserted->enableCardLabel( 0, 2 );

	p->insert( new TNumericField( m, "Eintrittszeit ", 5, ": " ) );

	p->insert( new TRadioField( m, "Eintrittscode ",
								1,
								new TSItem( "Krankheit",
								new TSItem( "Unfall",
								new TSItem( "Geburt", 0 ))),
								new TSItem( "K",
								new TSItem( "U",
								new TSItem( "G", 0 ))),
								moDown ) );
	p->lastInserted->enableCard( 116, 2 );

	m.control.a.y += 2;
	m.control.b.y += 2;

	p->insert( new TRadioField( m, "Klasse        ",
								4,
								new TSItem( "1er P.",
								new TSItem( "2er P.",
								new TSItem( "Allg.",
								new TSItem( "Ambulant", 0 )))),
								new TSItem( "1erP",
								new TSItem( "2erP",
								new TSItem( "Allg",
								new TSItem( "    ", 0 )))),
								moDown ) );
	p->lastInserted->enableCard( 111, 2 );
	p->lastInserted->enableCardLabel( 9, 2 );

	m.control.a.y += 3;
	m.control.b.y += 3;

	p->insert( new TRadioField( m, "Stat./Ambulant",
								9,
								new TSItem( "station„r",
								new TSItem( "ambulant", 0 )),
								new TSItem( "Station„r",
								new TSItem( "Ambulant", 0 )),
								moDown ) );
	p->lastInserted->enableCardLabel( 9, 3 );

	m.control.a.y += 1;
	m.control.b.y += 1;

	f->insert( p );

	/* Contructing Page 5... */
	p = new TPage( "Diverses" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TRadioField( m, "Taxkatogorie",
								1,
								new TSItem( " ",
								new TSItem( "Selbstzahler",
								new TSItem( "Krankenkasse",
								new TSItem( "SUVA",
								new TSItem( "IV",
								new TSItem( "EMU",
								new TSItem( "Priv.V.",
								new TSItem( "Frsorge", 0 )))))))),
								new TSItem( " ",
								new TSItem( "S",
								new TSItem( "K",
								new TSItem( "S",
								new TSItem( "I",
								new TSItem( "E",
								new TSItem( "P",
								new TSItem( "F", 0 )))))))),
								moDown ) );
	p->lastInserted->enableCard( 111, 2 );

	m.control.a.y += 7;
	m.control.b.y += 7;

	p->insert( new TTextField( m, "Kostenstelle", 30, moDown | moVert ) );

	p->insert( new TTextField( m, "Kostentr„ger Name", 24, moVert ) );
	p->lastInserted->enableCard( 0, 2 );

	p->insert( new TTextField( m, "Kostentr„ger Wohnort", 24, moNoSpace ) );
	p->lastInserted->enableCard( 24, 2 );

	p->insert( new THiddenConstField( m, "", 2 ) );
	p->lastInserted->enableCard( 117, 2 );

	p->insert( new THiddenConstField( m, "", 1 ) );
	p->lastInserted->enableCard( 119, 0 );

	p->insert( new THiddenConstField( m, "", 1 ) );
	p->lastInserted->enableCard( 119, 1 );

	p->insert( new THiddenConstField( m, "", 1 ) );
	p->lastInserted->enableCard( 119, 2 );

	p->insert( new THiddenConstField( m, "/", 1 ) );
	p->lastInserted->enableCardLabel( 25, 2 );

	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,					"Herisau" );
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
