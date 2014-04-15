/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		DemoVersion        						*/
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
	p = new TPage( "Mitarbeiter" );
	m.reset();

	p->insert( new TTextField( m, "Titel", 10 ) );

	p->insert( new TNameField( m, "Name   ", 30 ) );

	p->insert( new TNameField( m, "Vorname", 15, moNoSpace ) );

	p->insert( new TDateField( m, "Geburtsdatum", 10, "TT.MM.JJJJ", moHor ) );
	p->lastInserted->setInfoLevel( ilNormal );

/*	p->insert( new TRadioField( m, "Geschlecht",
								2,
								new TSItem( "M„nnlich",
								new TSItem( "Weiblich",
								new TSItem( "S„ugling m„nnlich",
								new TSItem( "S„ugling weiblich",
								0 )))),
								new TSItem( "M",
								new TSItem( "W",
								new TSItem( "SM",
								new TSItem( "SW",
								0 )))),
								moDown ) ); */

	p->insert( new TTextField( m, "Abteilung/Kostenstelle", 30, moVert ) );
	p->insert( new TTextField( m, "Funktion", 30, moVert ) );
	p->insert( new TTextField( m, "Zuordnung   ", 5, moHor ) );
	p->insert( new TTextField( m, "Berechtigung", 2, moHor | moDown | moNoSpace ) );

	m.control.a.y += 3;
	m.control.b.y += 3;

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Passwort" );
	m.reset();
//	m.control.a.y -= 2;
//	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Passwort", 8 ) );
	p->insert( new THiddenConstField( m, "$BS", 3 ) );

	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"DemoVersion" );
	sl->put( skPerson,				"Mitarbeiter" );

	sl->put( skPersonList,			"~P~erson" );
	sl->put( skNewPerson,			"Person ~e~infgen..." );
	sl->put( skDeletePerson,		"Person ~l~”schen" );
	sl->put( skEditPerson,			"Daten ~„~ndern..." );
	sl->put( skPrintPerson,			"~F~ormular drucken" );
	sl->put( skRawPrintPerson, 		"" );
	sl->put( skEncodeCard,			"" );

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

	sl->put( skListWindowTitle,		"Personendaten-Verwaltung" );

	sl->put( skExportData,			"" );

	return sl;
}
