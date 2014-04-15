/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Samedan (franz”sisch)					*/
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
	p = new TPage( "Donn‚es personelles" );
	m.reset();

//	m.control.a.y -= 2;
//	m.control.b.y -= 2;

	p->insert( new TNameField( m, "Nom   ", 30, moHor ) );
	p->lastInserted->enableCard( 0, 0 );
	p->lastInserted->enableCardLabel( 0, 0, 28 );

	p->insert( new TNameField( m, "Pr‚nom", 15 ) );
	p->lastInserted->enableCard( 30, 0 );
	p->lastInserted->enableCardLabel( 0, 1 );

	p->insert( new TTextField( m, "Rue", 30 ) );
	p->lastInserted->enableCard( 45, 0 );

	p->insert( new TTextField( m, "NPL Lieu", 30 ) );
	p->lastInserted->enableCard( 75, 0 );

	p->insert( new TNumericField( m, "Date naiss.", 8 ) );
	p->lastInserted->enableCard( 105, 0 );
	p->lastInserted->enableCardLabel( 18, 1 );

	p->insert( new TTextField( m, "Sex", 1, moDown ) );
	p->lastInserted->enableCard( 113, 0 );
	p->lastInserted->enableCardLabel( 27, 1 );

	p->insert( new TTextField( m, "Endroit s‚ance", 1 ) );
	p->lastInserted->enableCard( 114, 0 );

	p->insert( new TTextField( m, "Classe", 1, moDown ) );
	p->lastInserted->enableCard( 115, 0 );

	p->insert( new TTextField( m, "Motif admiss.", 3 ) );
	p->lastInserted->enableCard( 116, 0 );

	p->insert( new TTextField( m, "No du cas", 8 ) );
	p->lastInserted->enableCard( 0, 1 );
	p->lastInserted->enableCardLabel( 0, 2 );

	f->insert( p );

	/* Contructing Page 2... */
	p = new TPage( "Entr‚e/M‚decin" );
	m.reset();

	p->insert( new TNumericField( m, "Date admiss.", 8 ) );
	p->lastInserted->enableCard( 8, 1 );

	p->insert( new TTextField( m, "Envoy‚ par", 26, moVert ) );
	p->lastInserted->enableCard( 16, 1 );

	p->insert( new TTextField( m, "M‚decin soignant", 26 ) );
	p->lastInserted->enableCard( 42, 1 );

	p->insert( new TNumericField( m, "T‚l. priv‚", 20, ". /", moHor ) );
	p->lastInserted->enableCard( 68, 1 );

	p->insert( new TTextField( m, "Et.civil", 5, moDown ) );
	p->lastInserted->enableCard( 88, 1 );

	p->insert( new TTextField( m, "Confession", 4 ) );
	p->lastInserted->enableCard( 93, 1 );

	p->insert( new TTextField( m, "Profession", 18 ) );
	p->lastInserted->enableCard( 97, 1 );

	p->insert( new TNumericField( m, "Heure admiss.", 4, " .:" ) );
	p->lastInserted->enableCard( 115, 1 );

	f->insert( p );


	/* Contructing Page 3... */
	p = new TPage( "Divers" );
	m.reset();

	m.control.a.y++;
	m.control.b.y++;

	p->insert( new TTextField( m, "Caisse maladie/Assurance", 20, moVert ) );
	p->lastInserted->enableCard( 0, 2 );
	p->lastInserted->enableCardLabel( 0, 3 );

	p->insert( new TTextField( m, "Employeur", 28, moVert ) );
	p->lastInserted->enableCard( 20, 2 );

	p->insert( new TTextField( m, "Adresse actuelle", 28, moVert ) );
	p->lastInserted->enableCard( 48, 2 );

	p->insert( new TTextField( m, "Adresse … contacter", 28, moVert ) );
	p->lastInserted->enableCard( 76, 2 );

	p->insert( new TTextField( m, "Clinique 1 (No unit‚)", 4, moHor ) );
	p->lastInserted->enableCard( 104, 2 );
	p->lastInserted->enableCardLabel( 18, 2 );

	p->insert( new TTextField( m, "Clinique 2 (No table)", 4 ) );
	p->lastInserted->enableCard( 108, 2 );
	p->lastInserted->enableCardLabel( 24, 2 );

	p->insert( new TTextField( m, "T‚l. lit", 4 ) );
	p->lastInserted->enableCard( 112, 2 );

	f->insert( p );

	return f;
}


TStrListMaker *TSpecDefinition::initStringList()
{
	TStrListMaker *sl = new TStrListMaker( strSize, indexSize );

	sl->put( skCorporation,			"Spital Samedan" );
	sl->put( skPerson,				"Patient" );

	sl->put( skPersonList,			"Nom, pr‚nom" );
	sl->put( skNewPerson,			"~N~ouvelle saisie" );
	sl->put( skDeletePerson,		"~E~xtinction" );
	sl->put( skEditPerson,			"~M~odific. des donn‚es" );
	sl->put( skPrintPerson,			"Imprimer ~f~ormulaire" );
	sl->put( skRawPrintPerson, 		"Imprimer fiche ~b~ase" );
	sl->put( skEncodeCard,			"Coder une ~c~arte" );

	sl->put( skHeapView,			"" );

	sl->put( skOldDevice,			"" );
	sl->put( skFormatedRawPrint,	"" );
	sl->put( skNumRPCopiesDlg,		"" );

	sl->put( skAutoSave,			"" );

	sl->put( skFormDlgOK,			"~O~K" );
	sl->put( skFormDlgCancel,		"~C~anceler" );

	sl->put( skPrintLog,			"" );

	sl->put( skConfirmNewPerson,	"" );
	sl->put( skDisableOptions,		"" );

	sl->put( skListWindowTitle,		"Gestion patients / personnel" );

	sl->put( skExportData,			"" );

	return sl;


	// "Optionen", "Programm verlassen",
	// "N„chste Seite", "Vorherige Seite",
	// StatusLine
}
