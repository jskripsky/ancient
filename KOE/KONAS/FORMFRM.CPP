#include "FormFrm.H"
#include "Form.H"
#include "Constant.H"
#include "Field.H"

declSlist(Field);


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

FormFrame::FormFrame( Form *form ) :
	Presentation( form ),
	FormWindow( form ),
        zDialogFrame( 0, new zSizer(150, 150, 800, 500),
                DS_MODALFRAME | WS_CAPTION, "Formular" )
{
        window = this;

        setupFields();

        setupPanel();
}


FormFrame::~FormFrame()
{
}


void FormFrame::setupFields()
{
        FieldSlistIter *iter = getForm()->getFieldsIterator();

        Field *f;
        while( f = (*iter)() )
                f->openWindow( window->parent() );

        delete iter;
}


void FormFrame::setupPanel()
{
        // Buttons zum Vorw„rts- und Rckw„rtsbl„ttern:

        zDefPushButton *nextPageBtn = new zDefPushButton(
                this, new zSizer( 580, 60, 190, 32 ), 0,
                "&N„chste Seite", IDB_NEXT_PAGE );
        nextPageBtn->show();

        zPushButton *prevPageBtn = new zPushButton(
                this, new zSizer( 580, 102, 190, 32 ), 0,
                "&Vorherige Seite", IDB_PREV_PAGE );
        prevPageBtn->show();

        // Buttons zum Schliessen und Rckg„ngigmachen der Žnderungen:

        zPushButton *undoBtn = new zPushButton(
                this, new zSizer( 580, 408, 190, 32 ), 0,
                "Žnderungen &rckg.", IDB_UNDO );
        undoBtn->show();

        zPushButton *closeBtn = new zPushButton(
                this, new zSizer( 580, 450, 190, 32 ), 0,
                "Formular &schliessen", IDB_CLOSE );
        closeBtn->show();
}


void FormFrame::changeToPage( long pageNumber )
{
}


const char *FormFrame::getClassName()
{
        return "FormFrame";
}


void FormFrame::hideFromScreen()
{
        FormWindow::hideFromScreen();
        //shutdown();
}

void FormFrame::showOnScreen()
{
        FormWindow::showOnScreen();
        acquireUserFocus();
        //modal();
}   


int FormFrame::command( zCommandEvt* ce )
{
        switch( ce->cmd() )
                {
                case IDB_CLOSE:
                        hideFromScreen();
                        break;

                default:
                        return False;
                }

        return True;
}
