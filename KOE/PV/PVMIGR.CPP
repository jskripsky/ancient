/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		PV Source File    			    		*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "PV.Use"
#include "Gadgets\VerHead.Use"
#include "Gadgets\Config.Use"
#include "FormDef\FormDef.Use"

#define Uses_TStatusLine
#define Uses_TStatusDef
#define Uses_TStatusItem
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TKeys
#define Uses_TDeskTop
#define Uses_TView
#define Uses_THelpFile
#define Uses_THelpWindow
#define Uses_TWindow
#define Uses_MsgBox
#define Uses_ifpstream
#define Uses_ofpstream
#define Uses_fpstream

#include <TV.H>
#include <Help.H>
#include "PV.H"
#include "Gadgets\VerHead.H"
#include "Gadgets\Config.H"
#include "FormDef\FormDef.H"
#include "Defs\Commands.H"
#include "Defs\HelpCtx.H"
__link( RConfiguration );

#include <StdIO.H>
#include <StdLib.H>
#include <ConIO.H>

TFormDefinition *formDef = 0;
TConfiguration *config;
Boolean applEnding = False;

/*---- Main Function ---------------------------*/

int main( int argc, char **argv )
{
	argc; argv;

	remove( "OldPlist.Dat" );
	remove( "OldPlist.Idx" );
	int rc_dat = rename( "PList.Dat", "OldPlist.Dat" );
	int rc_idx = rename( "PList.Idx", "OldPlist.Idx" );

	if( (rc_dat == -1) || (rc_idx == -1) )
		{
		printf( "Dateien PLIST.DAT, PLIST.IDX k”nnen nicht ge”ffnet werden!\n\r" );
		printf( "Beliebige Taste drcken..." );
		getch();
		exit( EXIT_FAILURE );
		}

	TPV PV;

	PV.run();
	return 0;
}


/*---- Constructors, Destructors ---------------*/

TPV::TPV() :
	TProgInit( &TPV::initStatusLine,
			   &TPV::initMenuBar,
			   &TPV::initDeskTop ),
	listWindow( 0 ),
	heap( 0 ),
	startTimer( 0 )
{
//	strncpy( fileName, aFileName, 8 );
//	fileName[8] = 0;
//	char *point = strchr( fileName, '.' );
//	if( point != 0 )
//		*point = 0;

	createClockView();

	aboutDlg = new TAboutDialog();
	deskTop->insert( (TView *)aboutDlg );

//	loadHelp();
	readConfig();

	message( (TView *)aboutDlg, evCommand, cmFormDefInit, 0 );
	formDef = new TFormDefinition();

#ifdef RELEASE
	char *heapView = new char[strSize + 1];
	heapView[0] = 0;
	formDef->stringList->get( heapView, skHeapView );
	if( heapView[0] )
		createHeapView();
	delete[] heapView;
#else
	createHeapView();
#endif

	message( (TView *)aboutDlg, evCommand, cmListLoad, 0 );
	listWindow = new TListWindow();

	message( (TView *)aboutDlg, evCommand, cmInitDone, 0 );
}


TPV::~TPV()
{
	applEnding = True;

//	destroyHelp();
	writeConfig();

	if( listWindow )
		{
		deskTop->remove( (TView *)listWindow );
		destroy( (TObject *)listWindow );
		}

	destroy( (TObject *)formDef );
	destroy( (TObject *)aboutDlg );

	remove( clock );
	destroy( clock );

	if( heap )
		{
		remove( heap );
		destroy( heap );
		}
}


/*---- Public Methods --------------------------*/


/*---- Private Methods -------------------------*/

void TPV::readConfig()
{
	ifpstream configFile( "PV.Cfg", ios::nocreate );
	if( !configFile )
		config = new TConfiguration();
	else
		{
		TVersionHeader *verHead;
		configFile >> verHead;
		destroy( (TObject *)verHead );

		configFile >> config;
		configFile.close();
		}
}


void TPV::writeConfig()
{
	ofpstream configFile( "PV.Cfg", ios::trunc );

	TVersionHeader *verHead;
	verHead = new TVersionHeader( "PV Configuration", 0x0100 );
	configFile << verHead;
	destroy( (TObject *)verHead );

	configFile << config;
	configFile.close();
	destroy( (TObject *)config );
}


void TPV::loadHelp()
{
	fpstream *helpStrm = new fpstream( "PV.Hlp", ios::in | ios::nocreate );
	hlpFile = new THelpFile( *helpStrm );
	if( !(*helpStrm) )
		{
		messageBox( "Hilfe-Datei kann nicht ge”ffnet werden!",
					mfError | mfOKButton );
		destroy( hlpFile );
		hlpFile = 0;
		}
	else
		hlpWindow = new THelpWindow( hlpFile, hcNoContext );
}


void TPV::destroyHelp()
{
	if( hlpFile != 0 )
		{
		destroy( hlpWindow );
		delete hlpFile;
		}
}


void TPV::createHeapView()
{
	TRect r = getExtent();
	r.a.x = r.b.x - 13;
	r.a.y = r.b.y - 1;
	heap = new THeapView( r );
	insert( heap );
}


void TPV::createClockView()
{
	TRect r = getExtent();
	r.a.x = r.b.x - 9;
	r.b.y = r.a.y + 1;
	clock = new TClockView( r );
	insert( clock );
}
