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
#define Uses_TVMemMgr

#include <TV.H>
#include <Help.H>
#include "PV.H"
#include "Gadgets\VerHead.H"
#include "Gadgets\Config.H"
#include "FormDef\FormDef.H"
#include "Defs\Commands.H"
#include "Defs\HelpCtx.H"
#include "ImpListW.H"
__link( RConfiguration );

#include <StdIO.H>
#include <ConIO.H>
#include <StdLib.H>
#include <String.H>
#include <CType.H>
#include <IOStream.H>

TFormDefinition *formDef = 0;
TConfiguration *config;
Boolean applEnding = False;

const int	NoOption	=    0,
			Error		= 1000,
			Help		=    1,
			Refresh		=    2,
			EnableMenu	=	 3;

int cmdLineOptions = NoOption;


/*---- Main Function ---------------------------*/

int main( int argc, char **argv )
{
	for( int i = 1; i < argc; i++ )
		{
		char *arg = argv[i];
		if( (arg[0] == '\\') || (arg[0] == '/') ||
			(arg[0] == '-')  || (arg[0] == '+') )
			arg++;

		switch( toupper( arg[0] ) )
			{
			case 'R':
				cmdLineOptions = Refresh;
				break;

			case 'O':
				cmdLineOptions = EnableMenu;
				break;

			case '?':
				cmdLineOptions = Help;
				break;

			default:
				cmdLineOptions = Error;
			}
		}

	switch( cmdLineOptions )
		{
		case Error:
			cerr << "Unbekannter Parameter!" << endl << endl;

		case Help:
			cout << endl;
			cout << " Parameter:" << endl;
			cout << " ==========" << endl << endl;
			cout << " /R   Datenbank neu aufbauen (Refresh)." << endl;
			cout << " /O   Men 'Optionen' aktivieren." << endl << endl;

			cout << endl << endl;
			cout << " << Beliebige Taste drcken... >>"; endl;
			getch();
			return 0;

		default:
			TPV PV;

			PV.run();
			return 0;
		}
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
//	TVMemMgr::resizeSafetyPool( 10 * DEFAULT_SAFETY_POOL_SIZE );

	createClockView();

	aboutDlg = new TAboutDialog();
	deskTop->insert( (TView *)aboutDlg );

//	loadHelp();
	readConfig();

	message( (TView *)aboutDlg, evCommand, cmFormDefInit, 0 );
	formDef = new TFormDefinition();

	if( formDef->disableOptions && (cmdLineOptions != EnableMenu) )
		menuBar->setState( sfDisabled, True );

#ifdef RELEASE
	char *heapView = new char[maxStringLength + 1];
	heapView[0] = 0;
	formDef->stringList->get( heapView, skHeapView );
	if( heapView[0] )
		createHeapView();
	delete[] heapView;
#else
	createHeapView();
#endif

	message( (TView *)aboutDlg, evCommand, cmListLoad, 0 );

	fstream tabFile( "PList.Tab", ios::nocreate | ios::in | ios::out );
	if( !(!tabFile) )
		{
		char status[3];
		tabFile.seekg( -3, ios::end );
		tabFile.read( status, 3 );
		if( strcmp( "OK", status ) == 0 )
			{
			tabFile.seekp( -3, ios::end );
			tabFile.write( "NG", 3 );
			}
		else
			{
			messageBoxRect( TRect( 15, 7, 65, 18 ),
						"Die Index-Dateien der Datenbank sind "
						"fehlerhaft oder nicht synchronisiert.\n",
						mfError | mfOKButton );

			cmdLineOptions = Refresh;
			}
		}

	ifstream datFile( "PList.Dat", ios::nocreate );
	if( (!tabFile && !(!datFile)) || (cmdLineOptions == Refresh) )
		{
		datFile.close();
		if( !(!tabFile) )
			tabFile.close();


		int rc_dat;

		if( cmdLineOptions == Refresh )
			{
			::remove( "PList___.Dat" );
			::remove( "PList___.Idx" );
			::remove( "PList___.Tab" );

			rc_dat = rename( "PList.Dat", "PList___.Dat" );
			rename( "PList.Idx", "PList___.Idx" );
			rename( "PList.Tab", "PList___.Tab" );
			}
		else
			{
			::remove( "OldPList.Dat" );
			::remove( "OldPList.Idx" );

			rc_dat = rename( "PList.Dat", "OldPList.Dat" );
			rename( "PList.Idx", "OldPList.Idx" );
			}


		if( rc_dat == -1 )
			{
			printf( "Die Datei PLIST.DAT kann nicht ge”ffnet werden!\n\r" );
			printf( "Beliebige Taste drcken..." );
			getch();
			exit( EXIT_FAILURE );
			}

		messageBoxRect( TRect( 15, 7, 65, 18 ),
					"Die Datenbank wird neu aufgebaut.\n"
					"Dies wird l„ngere Zeit in Anspruch nehmen.\n"
					"Drcken Sie zweimal Enter, um den Vorgang zu starten.",
					mfInformation | mfOKButton );

		if( cmdLineOptions == Refresh )
			listWindow = new TImportListWindow( Normal );
		else
			listWindow = new TImportListWindow( OldFormat );
		}
	else
		{
		tabFile.close();
		datFile.close();

		char *title = new char[maxStringLength + 1];
		formDef->stringList->get( title, skListWindowTitle );

		listWindow = new TListWindow( title );
		delete[] title;
		}

	message( (TView *)aboutDlg, evCommand, cmInitDone, 0 );
}


TPV::~TPV()
{
	applEnding = True;

	if( listWindow )
		{
		deskTop->remove( (TView *)listWindow );
		destroy( (TObject *)listWindow );
		}

	destroy( (TObject *)formDef );
	destroy( (TObject *)aboutDlg );

	ofstream tabFile( "PList.Tab", ios::nocreate | ios::out | ios::in );
	tabFile.seekp( 0, ios::end );
	tabFile.write( "OK", 3 );
	tabFile.close();

//	destroyHelp();
	writeConfig();

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
