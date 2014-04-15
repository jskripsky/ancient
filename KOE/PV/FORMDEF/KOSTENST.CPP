/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Kostenstellen     						*/
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
	p = new TPage( "Kostenstelle" );
	m.reset();

	p->insert( new TSpecCardTextField( m, "Nummer", 3 ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCard( 12, 0 );
	p->lastInserted->enableCardLabel( 0, 1 );
	p->lastInserted->setInfoLevel( ilNormal );

	p->insert( new TSpecCardTextField( m, "Bezeichnung", 29, moVert ) );
	p->lastInserted->makeNecessary();
	p->lastInserted->enableCardLabel( 0, 0 );
	p->lastInserted->setInfoLevel( ilNormal );

	p->insert( new THiddenConstField( m, "KOSTENSTELLE", 12 ) );
	p->lastInserted->enableCard( 0, 0 );

	p->insert( new THiddenConstField( m, "KOSTENSTELLE", 12 ) );
	p->lastInserted->enableCard( 0, 1 );

	p->insert( new THiddenConstField( m, "KOSTENSTELLE", 12 ) );
	p->lastInserted->enableCard( 0, 2 );

	f->insert( p );
	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"- (Kostenst.)" );
	sl->put( skPerson,				"Kostenstelle" );

	sl->put( skPersonList,			"~K~ostenstellen" );
	sl->put( skNewPerson,			"Kostenstelle ~e~infgen..." );
	sl->put( skDeletePerson,		"Kostenstelle ~l~”schen" );
	sl->put( skEditPerson,			"Daten ~„~ndern..." );
	sl->put( skPrintPerson,			"~F~ormular drucken" );
	sl->put( skRawPrintPerson, 		"~D~aten drucken" );
	sl->put( skEncodeCard,			"~K~arte codieren" );

	sl->put( skHeapView,			"" );

	sl->put( skOldDevice,			"" );
	sl->put( skFormatedRawPrint,	"" );
	sl->put( skNumRPCopiesDlg,		"" );

	sl->put( skAutoSave,			"" );

	sl->put( skFormDlgOK,			"" );
	sl->put( skFormDlgCancel,		"" );

	return sl;
}
