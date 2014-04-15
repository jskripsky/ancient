/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Schwyz             						*/
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

	p->insert( new TNameField( m, "Name   ", 25 ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 10, 0 );
	p->lastInserted->enableCardLabel( 0, 0 );

	p->insert( new TNameField( m, "Vorname", 18, moNoSpace ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 35, 0 );
	p->lastInserted->enableCardLabel( 0, 1, 15 );

	p->insert( new TRadioField( m, "Geschlecht",
								1,
								new TSItem( "M„nnlich",
								new TSItem( "Weiblich", 0 )),
								new TSItem( "M",
								new TSItem( "W", 0 )),
								moDown ) );
	p->lastInserted->enableCard( 63, 0 );
	p->lastInserted->enableCardLabel( 11, 2 );

	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TDateField( m, "Geburtsdatum", 10, "TT.MM.JJJJ" ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 53, 0 );
	p->lastInserted->enableCardLabel( 0, 2 );
	p->lastInserted->setInfoLevel( ilNormal );

	p->insert( new TRadioField( m, "Religion",
								3,
								new TSItem( "-",
								new TSItem( "r”m.kath.",
								new TSItem( "evangelisch",
								new TSItem( "orthodox",
								new TSItem( "Moslem",
								new TSItem( "andere",
								new TSItem( "konf.-los", 0 ))))))),
								new TSItem( "-",
								new TSItem( "RK",
								new TSItem( "EVA",
								new TSItem( "ORT",
								new TSItem( "MOS",
								new TSItem( "APND",
								new TSItem( "KEI", 0 ))))))),
								moDown ) );
	p->lastInserted->enableCard( 67, 0 );

	m.control.a.y += 5;
	m.control.b.y += 5;

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Adresse/Eintritt" );
	m.reset();
//	m.control.a.y -= 2;
//	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Strasse", 25 ) );
	p->lastInserted->enableCard( 70, 0 );

	p->insert( new TTextField( m, "PLZ", 5 ) );
	p->lastInserted->enableCard( 95, 0 );

	p->insert( new TTextField( m, "Ort", 20 ) );
	p->lastInserted->enableCard( 100, 0 );

	p->insert( new TRadioField( m, "Eintritts-Typ",
								4,
								new TSItem( "NOTF",
								new TSItem( "ACHI",
								new TSItem( "AMB",
								new TSItem( "APG™",
								new TSItem( "APHO",
								new TSItem( "APLI",
								new TSItem( "APWE",
								new TSItem( "ATAG",
								new TSItem( "SCHR",
								new TSItem( "STAT",
								new TSItem( "VOR", 0 ))))))))))),
								new TSItem( "NOTF",
								new TSItem( "ACHI",
								new TSItem( "AMB",
								new TSItem( "APG™",
								new TSItem( "APHO",
								new TSItem( "APLI",
								new TSItem( "APWE",
								new TSItem( "ATAG",
								new TSItem( "SCHR",
								new TSItem( "STAT",
								new TSItem( "VOR", 0 ))))))))))),
								moDown ) );
	p->lastInserted->enableCard( 125, 1 );

	m.control.a.y += 10;
	m.control.b.y += 10;

	p->insert( new TDateField( m, "Eintrittsdatum", 8, "TT.MM.JJ" ) );
	p->lastInserted->enableCard( 129, 1 );
	p->lastInserted->enableCardLabel( lineLength - 8, 2 );

//	p->insert( new TNumericField( m, "Eintrittszeit", 5, ".:" ) );

	f->insert( p );


	/* Contructing Page 3... */
	p = new TPage( "Eintr.Art/Fall" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TRadioField( m, "Eintritts-Art    ",
								8,
								new TSItem( "Chroni.",
								new TSItem( "Geb/Saeg",
								new TSItem( "Krankh.",
								new TSItem( "Mutters.",
								new TSItem( "Schwang.",
								new TSItem( "Unfall", 0 )))))),
								new TSItem( "Chroni.",
								new TSItem( "Geb/Saeg",
								new TSItem( "Krankh.",
								new TSItem( "Mutters.",
								new TSItem( "Schwang.",
								new TSItem( "Unfall", 0 )))))),
								moDown ) );
	p->lastInserted->enableCard( 18, 2 );

	m.control.a.y += 2;
	m.control.b.y += 2;

	p->insert( new TRadioField( m, "Fall",
								4,
								new TSItem( "CHI",
								new TSItem( "GER",
								new TSItem( "GYN",
								new TSItem( "MED",
								new TSItem( "OPH",
								new TSItem( "ORL",
								new TSItem( "ORT",
								new TSItem( "PED",
								new TSItem( "SAEZ",
								new TSItem( "URO", 0 )))))))))),
								new TSItem( "CHI",
								new TSItem( "GER",
								new TSItem( "GYN",
								new TSItem( "MED",
								new TSItem( "OPH",
								new TSItem( "ORL",
								new TSItem( "ORT",
								new TSItem( "PED",
								new TSItem( "SAEZ",
								new TSItem( "URO", 0 )))))))))),
								moDown ) );
	p->lastInserted->enableCard( 26, 2 );


	m.control.a.y += 9;
	m.control.b.y += 9;

	p->insert( new THiddenConstField( m, "PR", 2 ) );
	p->lastInserted->enableCard( 140, 2 );
	p->lastInserted->enableCardLabel( lineLength - 4 - 7 - 3, 1 );

	p->insert( new TSchwyzPNumberField( m, "Patientennr.", 7, "Bereich.Ini",
										moDown ) );
	p->lastInserted->enableCard( 0, 0 );
	p->lastInserted->enableCardLabel( lineLength - 4 - 7, 1 );

	p->insert( new THiddenConstField( m, ".", 1 ) );
	p->lastInserted->enableCardLabel( lineLength - 4, 1 );

	p->insert( new THiddenConstField( m, "001", 3 ) );
	p->lastInserted->enableCard( 7, 0 );
	p->lastInserted->enableCardLabel( lineLength - 3, 1 );

	p->insert( new THiddenConstField( m, "/", 1 ) );
	p->lastInserted->enableCardLabel( 10, 2 );

	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Schwyz" );
	sl->put( skPerson,				"Patient" );

	sl->put( skPersonList,			"~P~atienten" );
	sl->put( skNewPerson,			"Patienten ~e~infgen..." );
	sl->put( skDeletePerson,		"" );
	sl->put( skEditPerson,			"Daten ~„~ndern..." );
	sl->put( skPrintPerson,			"" );
	sl->put( skRawPrintPerson, 		"" );
	sl->put( skEncodeCard,			"~K~arte codieren" );

	sl->put( skHeapView,			"" );

	sl->put( skOldDevice,			"" );
	sl->put( skFormatedRawPrint,	"" );
	sl->put( skNumRPCopiesDlg,		"" );

	sl->put( skAutoSave,			"" );

	sl->put( skFormDlgOK,			"" );
	sl->put( skFormDlgCancel,		"" );

	sl->put( skPrintLog,			"" );

	sl->put( skConfirmNewPerson,	"" );
	sl->put( skDisableOptions,		"" );

	sl->put( skListWindowTitle,		"Patientendaten-Verwaltung" );

	sl->put( skExportData,			"" );

	return sl;
}
