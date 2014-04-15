#include "KonasFrm.H"
#include "Form.H"
#include "FormWin.H"
#include "Constant.H"

#include "Field.H"

//==========================================================
//===  constructors and destructor  ========================
//==========================================================

KonasFrame::KonasFrame( const char *title ) :
	KonasApp(),
//	zDialogFrame( 0, new zSizer( 100, 100, 800, 480 ),
//		WS_CAPTION | WS_SYSMENU | WS_MINIMIZE, title )
	zDialogFrame( 0, zResId( ID_KONAS_PANEL ) )
{
	// FCF_TASKLIST!!!!

	setupPanel();
}


KonasFrame::~KonasFrame()
{
}


int KonasFrame::command( zCommandEvt *ce )
{
	switch( ce->cmd() )
		{
		case IDB_NEW_PERSON:
			{
			form->newPerson();
			form->getFormWindow()->changeToPage( 0, False );
			form->showWindow();
			char *string = new char[200];
			string[0] = 0;
			strcat( string, form->getFieldByID( "Name" )->getString() );
			strcat( string, ", " );
			strcat( string, form->getFieldByID( "Vorname" )->getString() );
			strcat( string, ", " );
			strcat( string, form->getFieldByID( "GeburtsDatum" )->getString() );

			personListBox->selection( personListBox->add( string ) );
			break;
         }

		case IDB_EDIT_PERSON:
			{
         personListBox->del( personListBox->selection() );
			form->getFormWindow()->changeToPage( 0, False );
			form->showWindow();
			char *string = new char[200];
			string[0] = 0;
			strcat( string, form->getFieldByID( "Name" )->getString() );
			strcat( string, ", " );
			strcat( string, form->getFieldByID( "Vorname" )->getString() );
			strcat( string, ", " );
			strcat( string, form->getFieldByID( "GeburtsDatum" )->getString() );

			personListBox->selection( personListBox->add( string ) );
			break;
			}
		case IDB_DELETE_PERSON:
			{
			zMessage message(
				0, "Soll dieser Eintrag wirklich gelöscht werden?",
            "Löschen",
				MB_YESNO | MB_ICONINFORMATION );
			if( message.isYes() )
				{
				int oldSel = personListBox->selection();
				personListBox->del( oldSel );
				personListBox->selection( oldSel - 1 );
            }
			}
			break;

					 case IDB_PRINT_PERSON:
					 case IDB_MC_PERSON:
								form->print();
                        break;

					 case IDB_PRINT_LIST:
					 case IDB_EXPORT_DATA:
								break;

					 case IDB_CLOSE:
//								show( SW_HIDE );
//								app->quit();
								break;

					 default:
								return False;
		  }

		  return True;
}

void KonasFrame::setupPanel()
{
	// ListBox fr Personenliste, Titel:

//		  zStaticText *personListTitle = new zStaticText(
//					 this, new zSizer( 40, 40, 400, 20 ), 0,
//					 "Personenliste", 0 );
//		  personListTitle->show();

//		  personListBox = new zListBoxUnsorted(
//					 this, new zSizer( 40, 60, 400, 380 ), 0, 0,
//					 ID_PERSONLIST_BOX );
	personListBox = new zListBox/*Unsorted*/( this, ID_PERSONLIST_BOX );
	personListBox->add( "Müller, Peter, 2.10.1951" );
	personListBox->add( "Germann, Franz, 18.3.1945" );
	personListBox->add( "Beorchia, Aldo, 1.6.1945" );
	personListBox->add( "Gebauer, Sandra, 13.1.1974" );
	personListBox->add( "Hubmann, Peter, 2.6.1923" );
	personListBox->add( "Werther, Max, 8.5.1944" );
	personListBox->add( "Frisch, Barbara, 1.5.1977" );
	personListBox->add( "Furger, Flavia, 3.12.1975" );

	personListBox->show();
   personListBox->selection( 0 );

		  // Buttons zur Manipulation einer Person:
/*
		  newPersonBtn = new zDefPushButton(
					 this, new zSizer( 480, 70, 270, 32 ),
					 BS_DEFPUSHBUTTON | WS_TABSTOP,
					 "&Neuen Patienten aufnehmen...", IDB_NEW_PERSON );
		  newPersonBtn->show();

		  editPersonBtn = new zPushButton(
					 this, new zSizer( 480, 115, 270, 32 ), 0,
					 "Patienten&daten ändern...", IDB_EDIT_PERSON );
		  editPersonBtn->show();

		  deletePersonBtn = new zPushButton(
					 this, new zSizer( 480, 160, 270, 32 ), 0,
					 "Eintrag &löschen", IDB_DELETE_PERSON );
        deletePersonBtn->show();

        // Buttons fr Druck und MC-Kodierung:

		  printPersonBtn = new zPushButton(
				this, new zSizer( 480, 240, 270, 32 ), 0,
				"Formular &drucken...", IDB_PRINT_PERSON );
		  printPersonBtn->show();

		  mcPersonBtn = new zPushButton(
				this, new zSizer( 480, 285, 270, 32 ), 0,
				"Karte &kodieren...", IDB_MC_PERSON );
		  mcPersonBtn->show();

		  // Buttons fr Listendruck und Datenexport:

		  printListBtn = new zPushButton(
				this, new zSizer( 480, 330, 270, 32 ), 0,
				"Reportliste drucken...", IDB_PRINT_LIST );
		  printListBtn->show();

		  exportDataBtn = new zPushButton(
				this, new zSizer( 480, 375, 270, 32 ), 0,
				"Daten exportieren...", IDB_EXPORT_DATA );
		  exportDataBtn->show();

		  // Button zum Schliessen vom Konas:

		  closeBtn = new zPushButton(
				this, new zSizer( 480, 400, 270, 32 ), 0,
				"Konas &schliessen", IDB_CLOSE );
		  closeBtn->show();
*/
}
