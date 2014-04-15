/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Rinas              						*/
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
	p = new TPage( "Seite I" );
	m.reset();

	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TNameField( m, "Feld  1", 30, moVert ) );
	p->lastInserted->enableCard( 0, 0 );
	p->lastInserted->enableCardLabel( 0, 0, 29 );

	p->insert( new TTextField( m, "Feld  2", 30 ) );
	p->lastInserted->enableCard( 30, 0 );
	p->lastInserted->enableCardLabel( 0, 1, 29 );

	p->insert( new TTextField( m, "Feld  3", 30 ) );
	p->lastInserted->enableCard( 60, 0 );
	p->lastInserted->enableCardLabel( 0, 2, 29 );

	p->insert( new TTextField( m, "Feld  4", 30 ) );
	p->lastInserted->enableCard( 90, 0 );
	p->lastInserted->enableCardLabel( 0, 3, 29 );

	p->insert( new TTextField( m, "Feld  5", 30 ) );
	p->lastInserted->enableCard( 0, 1 );
	p->lastInserted->enableCardLabel( 0, 4, 29 );

	p->insert( new TTextField( m, "Feld  6", 30 ) );
	p->lastInserted->enableCard( 30, 1 );
	p->lastInserted->enableCardLabel( 0, 5, 29 );

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Seite II" );
	m.reset();

	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TTextField( m, "Feld  7", 30, moVert ) );
	p->lastInserted->enableCard( 60, 1 );

	p->insert( new TTextField( m, "Feld  8", 30 ) );
	p->lastInserted->enableCard( 90, 1 );

	p->insert( new TTextField( m, "Feld  9", 30 ) );
	p->lastInserted->enableCard( 0, 2 );

	p->insert( new TTextField( m, "Feld  10", 30 ) );
	p->lastInserted->enableCard( 30, 2 );

	p->insert( new TTextField( m, "Feld  11", 30 ) );
	p->lastInserted->enableCard( 60, 2 );

	p->insert( new TTextField( m, "Feld  12", 30 ) );
	p->lastInserted->enableCard( 90, 2 );

	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Rinas Test MCS1000" );
	sl->put( skPerson,				"Patient" );

	sl->put( skPersonList,			"~P~atienten" );
	sl->put( skNewPerson,			"Patienten ~e~infgen..." );
	sl->put( skDeletePerson,		"Patienten ~l~”schen" );
	sl->put( skEditPerson,			"Daten ~„~ndern..." );
	sl->put( skPrintPerson,			"~F~ormular drucken" );
	sl->put( skRawPrintPerson, 		"~D~aten drucken" );
	sl->put( skEncodeCard,			"~K~arte codieren" );
	return sl;
}
