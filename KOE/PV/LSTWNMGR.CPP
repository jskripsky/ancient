/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		List Window Source File 		    	*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "ListWin.Use"
#include "Device.Use"
#include "FormDef\FormDef.Use"
#include "Gadgets\Gadgets.Use"

#define Uses_TDeskTop
#define Uses_TProgram
#define Uses_TButton
#define Uses_MsgBox
#define Uses_ifpstream

#include <TV.H>
#include "ListWin.H"
#include "Device.H"
#include "FormDef\FormDef.H"
#include "Gadgets\Config.H"
#include "Defs\Commands.H"
#include "Defs\HelpCtx.H"

#include <DOS.H>
#include <String.H>

extern Boolean isDirty;
extern Boolean isSaveable;

/*---- Constructors, Destructors ---------------*/

TListWindow::TListWindow() :
	TWindowInit( &TListWindow::initFrame ),
	TDialog( TRect( 0, 0, 80, 23 ), "Personen-Verwaltung" )
{
	helpCtx = hcListWin;
	flags &= ~(wfClose | wfMove);

	insert( scrollBar = new TScrollBar( TRect( 46, 3, 47, 21 ) ) );

	insert( (TView *)(box = new TAlphaListBox( TRect( 4, 3, 46, 21 ),
											   scrollBar )) );

	char *string = new char[strSize + 1];
	formDef->stringList->get( string, skPersonList );
	insert( new TLabel( TRect( 3, 2, 46, 3 ), string, (TView *)box ) );

	formDef->stringList->get( string, skNewPerson );
	insert( new TButton( TRect( 50, 3, 75,  5 ), string,
						 cmNewPerson, bfNormal | bfLeftJust ) );

	formDef->stringList->get( string, skDeletePerson );
	insert( new TButton( TRect( 50, 5, 75,  7 ), string,
						 cmDeletePerson, bfNormal | bfLeftJust ) );

	formDef->stringList->get( string, skEditPerson );
	insert( new TButton( TRect( 50, 7, 75,  9 ), string,
						 cmEditPerson, bfNormal | bfLeftJust ) );

	formDef->stringList->get( string, skPrintPerson );
	insert( new TButton( TRect( 50, 10, 75, 12 ), string,
						 cmPrintPerson, bfNormal | bfLeftJust ) );

	formDef->stringList->get( string, skRawPrintPerson );
	insert( new TButton( TRect( 50, 12, 75, 14 ), string,
						 cmRawPrintPerson, bfNormal | bfLeftJust ) );

	formDef->stringList->get( string, skEncodeCard );
	insert( new TButton( TRect( 50, 14, 75, 16 ), string,
						 cmEncodeCard, bfNormal | bfLeftJust ) );

	delete[] string;

	insert( new TButton( TRect( 51, 18, 74, 20 ), "Programm ~v~erlassen",
						 cmQuit, bfNormal | bfLeftJust ) );

	box->select();
	formDialog = new( TFormDialog );
}


TListWindow::~TListWindow()
{
	isSaveable = False;
	destroy( (TObject *)formDialog );
}


/*---- Public Methods --------------------------*/

void TListWindow::setState( ushort aState, Boolean enable )
{
	static Boolean firstTime = True;

	TDialog::setState( aState, enable );

	char prefix[11];
	prefix[10] = 0;
	char suffix;

	streampos pos;

	if( (aState & sfVisible) && enable && firstTime )
		{
		firstTime = False;
		ifpstream oldList( "OldPList.Dat", ios::in | ios::binary );

		do
			{
			pos = oldList.tellg();

			do
				{
				oldList.readBytes( prefix, 10 );
				if( memcmp( prefix, "spareRec", 8 ) == 0 )
					oldList.seekg( 2, ios::cur );
				}
			while( memcmp( prefix, "spareRec", 8 ) == 0 );

			if( oldList.tellg() == pos )
				break;

			if( prefix[1] != '[' ) // korrekt geloeschter Eintrag
				oldList.seekg( -12, ios::cur );

			TInfo *info = new TInfo();

// Conversion:
// ===========

// Herzogen Length: 756

			char *data = (char *)info->person()->data();

			oldList.readBytes( data, 756 );
			if( prefix[1] != '[' ) // korrekt geloeschter Eintrag
				{
				data[0] = '9';
				data[1] = '9';
				}

			lock();

			box->insert( info );
			message( this, evCommand, cmEditPerson, 0 );
			box->select();

			unlock();

			oldList.readBytes( &suffix, 1 );
			}
		while( !(oldList.eof()) );

		oldList.close();
		message( TProgram::application, evCommand, cmQuit, 0 );
		}
/*	TDialog::setState( aState, enable );

	if( (aState & sfVisible) && enable )
		if( box->list()->getCount() == 0 )
			message( this, evCommand, cmNewPerson, 0 );
*/
}


void TListWindow::handleEvent( TEvent& event )
{
	Boolean temp;
	TDialog::handleEvent( event );
	if( event.what == evCommand )
		{
		switch( event.message.command )
			{
			case cmNewPerson:
				isSaveable = False;

				TInfo *info = new TInfo();

				if( lowMemory() )
					{
					destroy( (TObject *)info );
					TProgram::application->outOfMemory();
					break;
					}
				box->insert( info );

				openForm( True );
				box->update();
				box->select();

				isSaveable = True;
				break;

			case cmEditPerson:
				isSaveable = False;

				openForm();
				box->update();
				box->select();

				isSaveable = True;
				break;

			case cmDeletePerson:
				isSaveable = False;

				if( box->list()->getCount() > 1 )
					if( messageBox( "Soll diese Person wirklich gel”scht werden?",
									mfConfirmation | mfYesButton | mfNoButton ) ==
						cmYes )
						{
						box->free();
						box->update();
						box->select();
						if( box->list()->getCount() == 0 )
							message( this, evCommand, cmNewPerson, 0 );
						}

				box->select();

				isSaveable = True;
				break;

			case cmPrintPerson:
				temp = isSaveable;
				isSaveable = False;

				print( form );
				box->select();

				isSaveable = temp;
				break;

			case cmRawPrintPerson:
				temp = isSaveable;
				isSaveable = False;

				print( text );
				box->select();

				isSaveable = temp;
				break;

			case cmEncodeCard:
				temp = isSaveable;
				isSaveable = False;

				print( card );
				box->select();

				isSaveable = temp;
				break;

			case cmSaveList:
				box->writeListFile();
				break;

			default:
				return;
			}
		clearEvent( event );
		}
}


/*---- Private Methods -------------------------*/

void TListWindow::print( ushort mode )
{
	TDialog *statusDlg = new TDialog( TRect( 20, 9, 58, 14),
									  "Drucken / Kodieren..." );
	TStaticText *st;

	switch( mode )
		{
		case form:
			st = new TStaticText( TRect( 7, 2, 32, 3 ),
								  "Formular wird gedruckt..." );
			break;

		case text:
			st = new TStaticText( TRect( 7, 2, 32, 3 ),
								  "Daten werden gedruckt..." );
			break;

		case card:
			st = new TStaticText( TRect( 9, 2, 31, 3 ),
								  "Karte wird codiert..." );
			break;
        }

	statusDlg->insert( st );
	TProgram::deskTop->insert( statusDlg );

	formDialog->loadPerson( box->focusedPerson() );

	TOutputDevice *printer;
	printer = new TOutputDevice( mode );

	formDialog->print( *printer );
	delete printer;

	TProgram::deskTop->remove( statusDlg );
	destroy( statusDlg );
}


void TListWindow::openForm( Boolean newPerson )
{
	formDialog->loadPerson( box->focusedPerson(), newPerson );
	message( (TView *)formDialog, evCommand, cmOK, 0 );

//	formDialog->loadPerson( box->focusedPerson(), newPerson );
//	hide();
//	TProgram::deskTop->execView( (TView *)formDialog );
//	show();
};
