/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		List Box Source File 		    		*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "ListBox.Use"
#include "FormDef\FormDef.Use"

#define Uses_TDialog
#define Uses_TStaticText
#define Uses_ifpstream
#define Uses_ofpstream
#define Uses_TDeskTop
#define Uses_TProgram

#include <TV.H>
#include "ListBox.H"
#include "FormDef\FormDef.H"
#include "Gadgets\VerHead.H"
__link( RVersionHeader );
__link( RInfo );

#include <String.H>
#include <StdLib.H>
#include <Dir.H>


const char *stdListFileName = "PList";
const char *stdListFileExt  = ".Dat";


/*---- Constructors, Destructors ---------------*/

TAlphaListBox::TAlphaListBox( const TRect& bounds,
							  TScrollBar *aScrollBar ) :
	TSortedListBox( bounds, 1, aScrollBar )
{
	options &= ~ofBuffered;

	TDataBase *list;

	ifpstream listFile( "PList.Tab", ios::nocreate );

	if( !listFile )
		list = new TDataBase( "PList.Idx", "PList.Dat", 500 );
	else
		{
//		TVersionHeader *verHead;
//		listFile >> verHead;
//		destroy( (TObject *)verHead );

		listFile >> list;
		listFile.close();
		}

	if( list )
		newList( (TSortedCollection *)list );
	else
		exit( EXIT_FAILURE );
}


TAlphaListBox::~TAlphaListBox()
{
	writeListFile();
	newList( 0 );
}


/*---- Public Methods --------------------------*/

void TAlphaListBox::writeListFile()
{
	if( list() )
		{
		ofpstream listFile( "PList.Tab", ios::trunc );

		TDialog *statusDlg = new TDialog( TRect( 20, 9, 60, 14),
										  "Speichern" );
		statusDlg->insert( new TStaticText( TRect( 7, 2, 34, 3 ),
										"Daten werden gespeichert..." ) );
		TProgram::deskTop->insert( statusDlg );

//		TVersionHeader *verHead;
//		verHead = new TVersionHeader( "Person List Data", 0x0100 );
//		listFile << verHead;
//		destroy( (TObject *)verHead );

		listFile << list();
		listFile.close();

		TProgram::deskTop->remove( statusDlg );
		destroy( statusDlg );
		}
}


void TAlphaListBox::getText( char *dest, short item, short maxLen )
{
	TInfo *info;
	info = (TInfo *)(list()->entryAt( item ));

	info->getString( dest, ilNormal, maxLen );
}


TInfo *TAlphaListBox::focusedPerson()
{
	return (TInfo *)list()->entryAt( focused );
}


void TAlphaListBox::insert( TInfo *info )
{
	ccIndex index;
	index = list()->insert( info );
	setRange( range + 1 );
//	TProgram::application->idle();

	focusItem( index );
//	TProgram::application->idle();
}


void TAlphaListBox::free()
{
	if( list()->getCount() == 0 )
		return;

	list()->atFree( focused );
	setRange( range - 1 );
}


void TAlphaListBox::update()
{
	if( list()->getCount() == 0 )
		return;

	focusItem( list()->reOrder( focused ) );
	drawView();
}
