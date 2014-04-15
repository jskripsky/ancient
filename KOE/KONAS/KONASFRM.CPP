#include "KonasFrm.H"
#include "Form.H"
#include "Constant.H"

//==========================================================
//===  constructors and destructor  ========================
//==========================================================

KonasFrame::KonasFrame( const char *title ) :
        KonasApp(),
        zDialogFrame( 0, new zSizer( 100, 100, 800, 480 ),
                WS_CAPTION | WS_SYSMENU | WS_MINIMIZE, title )
{
        // FCF_TASKLIST!!!!

        setupPanel();

        form->openWindow();
}


KonasFrame::~KonasFrame()
{
        form->closeWindow();
}


int KonasFrame::command( zCommandEvt *ce )
{
        switch( ce->cmd() )
                {
                case IDB_NEW_PERSON:
                        form->showWindow();
                        break;

                case IDB_EDIT_PERSON:
                case IDB_DELETE_PERSON:
                        break;

                case IDB_PRINT_PERSON:
                case IDB_MC_PERSON:
                        break;

                case IDB_PRINT_LIST:
                case IDB_EXPORT_DATA:
                        break;

                case IDB_CLOSE:
                        show( SW_HIDE );
                        app->quit();
                        break;

                default: 
                        return False;
        }

        return True;
}

void KonasFrame::setupPanel()
{
        // ListBox fr Personenliste, Titel:

        zStaticText *personListTitle = new zStaticText(
                this, new zSizer( 40, 40, 400, 20 ), 0,
                "Personenliste", 0 );
        personListTitle->show();

        personListBox = new zListBoxUnsorted(
                this, new zSizer( 40, 60, 400, 380 ), 0, 0,
                ID_PERSONLIST_BOX );
        personListBox->add( "Mller, Peter, 2.10.1950" );
        personListBox->add( "Name, Vorname, Geburtsdatum" );
        personListBox->add( "Name, Vorname, Geburtsdatum" );
        personListBox->show();

        // Buttons zur Manipulation einer Person:

        newPersonBtn = new zDefPushButton(
                this, new zSizer( 480, 70, 270, 32 ), 0,
                "&Neuen Patienten aufnehmen...", IDB_NEW_PERSON );
        newPersonBtn->show();

        editPersonBtn = new zPushButton(
                this, new zSizer( 480, 115, 270, 32 ), 0,
                "Patienten&daten „ndern...", IDB_EDIT_PERSON );
        editPersonBtn->show();

        deletePersonBtn = new zPushButton(
                this, new zSizer( 480, 160, 270, 32 ), 0,
                "Eintrag &l”schen", IDB_DELETE_PERSON );
        deletePersonBtn->show();

        // Buttons fr Druck und MC-Kodierung:

        printPersonBtn = new zPushButton( this, new zSizer( 480, 240, 270, 32 ), 0,
                "Formular &drucken...", IDB_PRINT_PERSON );
        printPersonBtn->show();

        mcPersonBtn = new zPushButton( this, new zSizer( 480, 285, 270, 32 ), 0,
                "Karte &kodieren...", IDB_MC_PERSON );
        mcPersonBtn->show();

        // Buttons fr Listendruck und Datenexport:

        printListBtn = new zPushButton( this, new zSizer( 480, 330, 270, 32 ), 0,
                "Reportliste drucken...", IDB_PRINT_LIST );
        printListBtn->show();

        exportDataBtn = new zPushButton( this, new zSizer( 480, 375, 270, 32 ), 0,
                "Daten exportieren...", IDB_EXPORT_DATA );
        exportDataBtn->show();

        // Button zum Schliessen vom Konas:

        closeBtn = new zPushButton( this, new zSizer( 480, 400, 270, 32 ), 0,
                "Konas &schliessen", IDB_CLOSE );
        closeBtn->show();
}
