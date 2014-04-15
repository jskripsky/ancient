/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Dielsdorf                            	*/
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

	p->insert( new TNameField( m, "Name   ", 30 ) );
	p->insert( new TNameField( m, "Vorname", 26 ) );

	p->insert( new TDateField( m, "Geburtsdatum", 10, "TT.MM.JJJJ" ) );

	p->insert( new TTextField( m, "PLZ    ", 4, moDown ) );
	p->insert( new TTextField( m, "Wohnort", 25, moNoSpace ) );
	p->insert( new TTextField( m, "Strasse", 26, moNoSpace ) );

	p->insert( new TTextField( m, "Telefon", 14 ) );

	p->insert( new TTextField( m, "Heimatort", 30, moVert ) );

	p->insert( new TNumericField( m, "AHV Nummer", 14, ".", moVert ) );

	p->insert( new TTextField( m, "Milit. Einteilung", 14, moVert ) );

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Zivilst./Konfession" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TRadioField( m, "Zivilstand",
								11,
								new TSItem( "ledig",
								new TSItem( "verheiratet",
								new TSItem( "geschieden",
								new TSItem( "getrennt",
								new TSItem( "verwitwet", 0 ))))),
								new TSItem( "ledig",
								new TSItem( "verheiratet",
								new TSItem( "geschieden",
								new TSItem( "getrennt",
								new TSItem( "verwitwet", 0 ))))),
								moDown ) );

	m.control.a.y += 4;
	m.control.b.y += 4;

	p->insert( new TRadioField( m, "Konfession",
								14,
								new TSItem( "reformiert",
								new TSItem( "r”misch-katholisch",
								new TSItem( "christlich-katholisch",
								new TSItem( "neuapostolisch",
								new TSItem( "freikirchlich",
								new TSItem( "jdisch",
								new TSItem( "islamisch",
								new TSItem( "budhistisch",
								new TSItem( "andere",
								new TSItem( "keine", 0 )))))))))),
								new TSItem( "reformiert",
								new TSItem( "r”misch-kath.",
								new TSItem( "christl.-kath.",
								new TSItem( "neuapostolisch",
								new TSItem( "freikirchlich",
								new TSItem( "jdisch",
								new TSItem( "islamisch",
								new TSItem( "budhistisch",
								new TSItem( "andere",
								new TSItem( "keine", 0 )))))))))),
								moDown ) );

	f->insert( p );

	/* Contructing Page 3... */
	p = new TPage( "Diverses" );
	m.reset();

	m.control.a.y -= 2;
	m.control.b.y -= 2;

	p->insert( new TTextField( m, "Anstell. als", 30 ) );

	p->insert( new TTextField( m, "Arbeitspl.", 26 ) );

	p->insert( new TDateField( m, "Eintritt  ", 10, "TT.MM.JJJJ" ) );

	p->insert( new TTextField( m, "Lehre/Schule", 30 ) );
	p->insert( new TTextField( m, "Diplomjahr  ", 11, moNoSpace ) );

	p->insert( new TTextField( m, "Letzter Arbeitsplatz", 30, moVert ) );

	p->insert( new TTextField( m, "Krankenkasse", 40, moHor ) );

	p->insert( new TTextField( m, "Eltern ", 30 ) );
	p->insert( new TTextField( m, "Adresse", 27, moNoSpace ) );
	p->insert( new TTextField( m, "Telefon", 14, moNoSpace ) );

	f->insert( p );

	/* Contructing Page 4... */
	p = new TPage( "Kinder" );
	m.reset();

	p->insert( new TNumericField( m, "Anzahl", 2 ) );

	p->insert( new TTextField( m, "Name Kind", 15, moVert | moDown ) );
	p->insert( new TDateField( m, "Geb.Datum",  8, "TT.MM.JJ" ) );
	for( int counter = 0; counter < 5; counter++ )
		{
		p->insert( new TTextField( m, 0, 15, moNoSpace | moDown ) );
		p->insert( new TDateField( m, 0,  8, "TT.MM.JJ" ) );
		}

	f->insert( p );
	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Dielsdorf" );
	sl->put( skPerson,				"Person" );

	sl->put( skPersonList,			"~P~ersonen" );
	sl->put( skNewPerson,			"Person ~e~infgen..." );
	sl->put( skDeletePerson,		"Person ~l~”schen" );
	sl->put( skEditPerson,			"Daten ~m~odifizieren..." );
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
