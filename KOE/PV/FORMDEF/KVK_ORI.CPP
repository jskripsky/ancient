/*----------------------------------------------*/
/*                                              */
/*              PV 1.0                          */
/*              Demo-Programm KVK               */
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
	p = new TPage( "Personalien" );
	m.reset();

//	m.control.a.y -= 2;
//	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Adel   ", 15 ) );

	p->insert( new TNameField( m, "Name   ", 28 ) );

	p->insert( new TNameField( m, "Vorname", 28 ) );

	p->insert( new TTextField( m, "Titel  ", 15 ) );

	p->insert( new TDateField( m, "Geburtsdatum  ", 8, "TT.MM.JJ" ) );

	p->insert( new TTextField( m, "Strasse ", 28 ) );

	p->insert( new TTextField( m, "Wohnsitz", 3 ) );
	p->insert( new TNumericField( m, "PLZ", 7, " -", moHor ) );

	p->insert( new TTextField( m, "Ort     ", 23, moHor ) );

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Versicherung" );
	m.reset();
	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Garant Name", 28 ) );

	p->insert( new TTextField( m, "Garant Nummer", 7 ) );

	p->insert( new TTextField( m, "Versicherungs-Nummer", 12 ) );

	p->insert( new TTextField( m, "VKNR", 5 ) );

	p->insert( new TTextField( m, "Versich.Status", 4 ) );

	p->insert( new TTextField( m, "Status Erg„nzung", 3 ) );

	p->insert( new TNumericField( m, "Gltigkeit", 4, " .-/" ) );


	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Koelliker AG" );
	sl->put( skPerson,				"Patient" );

	sl->put( skPersonList,			"~P~atienten" );
	sl->put( skNewPerson,			"Patienten ~e~infgen..." );
	sl->put( skDeletePerson,		"Patienten ~l~”schen" );
	sl->put( skEditPerson,			"Daten ~m~odifizieren..." );
	sl->put( skPrintPerson,			"~F~ormular drucken" );
	sl->put( skRawPrintPerson,		"~D~aten drucken" );
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
