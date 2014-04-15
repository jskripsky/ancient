/*----------------------------------------------*/
/*												*/
/*		PV 1.0									*/
/*		Herisau Personal						*/
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

	/* Contructing Page... */
	p = new TPage( "Personalien" );
	m.reset();

	p->insert( new TNameField( m, "Name   ", 28 ) );
	p->lastInserted->enableCard( 0, 1 );
	p->lastInserted->enableCardLabel( 0, 0, 27 );

	p->insert( new TNameField( m, "Vorname", 18 ) );
	p->lastInserted->enableCard( 20, 0 );
	p->lastInserted->enableCardLabel( 0, 1 );

//	p->insert( new THiddenConstField( m, "", 72 ) );
//	p->lastInserted->enableCard( 48, 0 );

//	p->insert( new THiddenConstField( m, "", 2 ) );
//	p->lastInserted->enableCard( 0, 1 );

	p->insert( new TNumericField( m, "Personalnr.", 4, "." ) );
	p->lastInserted->enableCard( 82, 0 );
	p->lastInserted->enableCardLabel( 0, 2 );

//	p->insert( new THiddenConstField( m, "", 113 ) );
//	p->lastInserted->enableCard( 7, 1 );

//	p->insert( new THiddenConstField( m, "", 120 ) );
//	p->lastInserted->enableCard( 0, 2 );

	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,					"Herisau Personal" );
	sl->put( skPerson,						"Person" );

	sl->put( skPersonList,                  "~P~ersonal" );
	sl->put( skNewPerson,                   "Eintrag ~e~infgen..." );
	sl->put( skDeletePerson,                "Eintrag ~l~”schen" );
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
