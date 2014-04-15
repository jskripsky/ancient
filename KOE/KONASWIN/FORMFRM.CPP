#include "FormFrm.H"
#include "Form.H"
#include "Constant.H"
#include "Field.H"
#include "FieldWin.H"

declSlist( Field );
declSlist( pageTitle );


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

FormFrame::FormFrame( Form *form ) :
//	Presentation( form ),
	FormWindow( form ),
//	zDialogFrame( 0, new zSizer(150, 150, 800, 500),
//	DS_MODALFRAME | WS_CAPTION, "Formular" ),
	zDialogFrame( 0, zResId( ID_FORM_PANEL ) ),
	showingPage( 0 )
{
		  window = this;

//        setupFields();

//        setupPanel();
}


FormFrame::~FormFrame()
{
}


void FormFrame::setupFields()
{
	FieldSlistIter *iter = getForm()->getFieldsIterator();

	Field *f;
	while( (f = (*iter)()) != 0 )
		f->openWindow( this );

	delete iter;
}


void FormFrame::setupPanel()
{
	// Titel der Seite

	pageTitleStxt = new zStaticText( this, IDS_PAGE_TITLE );

	// Buttons zum Vorw„rts- und Rckw„rtsbl„ttern:
/*
		  zDefPushButton *nextPageBtn = new zDefPushButton(
					 this, new zSizer( 580, 60, 190, 32 ),
					 BS_DEFPUSHBUTTON | WS_TABSTOP,
					 "&Nächste Seite", IDB_NEXT_PAGE );
		  nextPageBtn->show();

		  zPushButton *prevPageBtn = new zPushButton(
					 this, new zSizer( 580, 102, 190, 32 ), 0,
					 "&Vorherige Seite", IDB_PREV_PAGE );
		  prevPageBtn->show();

		  // Buttons zum Schliessen und Rckg„ngigmachen der Žnderungen:

		  zPushButton *undoBtn = new zPushButton(
					 this, new zSizer( 580, 408, 190, 32 ), 0,
					 "Änderungen &rückg.", IDB_UNDO );
		  undoBtn->show();

		  zPushButton *closeBtn = new zPushButton(
					 this, new zSizer( 580, 450, 190, 32 ), 0,
					 "Formular &schliessen", IDB_CLOSE );
		  closeBtn->show();
*/
}


boolean FormFrame::changeToPage( long newPage, boolean check )
{
	boolean result = True;

	FieldSlistIter *iter = getForm()->getFieldsIterator();

	Field *f;
	if( check )
		while( (f = (*iter)()) != 0 )
			{
			if( (f->getWindow()->getPageNumber() == showingPage) &&
				!f->validate() )
				{
				result = False;
				break;
				}
			}

	if( result == True )
		{
		iter->reset();
		boolean firstField = True;

		while( (f = (*iter)()) != 0 )
			if( f->getWindow()->getPageNumber() == newPage )
				{
				f->showWindow();
				if( firstField )
					{
					f->getWindow()->acquireUserFocus();
					firstField = False;
					}
				}
			else
				f->hideWindow();

		pageTitleSlistIter ptIter( pageTitles );
		char *newTitle;
		for( int c = 0; c <= newPage; c++ )
			newTitle = ptIter();

		pageTitleStxt->text( newTitle );

		showingPage = newPage;
		}

	delete iter;

	return result;
}


const char *FormFrame::getClassName()
{
        return "FormFrame";
}


void FormFrame::hideFromScreen()
{
	shutdown();
	FormWindow::hideFromScreen();
}


void FormFrame::showOnScreen()
{
	FormWindow::showOnScreen();
	acquireUserFocus();
   changeToPage( 0, False );
	modal();
}


int FormFrame::command( zCommandEvt* ce )
{
	switch( ce->cmd() )
		{
		case IDB_NEXT_PAGE:
			if( showingPage < (numberOfPages - 1) )
				changeToPage( showingPage + 1 );
			else
				changeToPage( 0 );
			break;

		case IDB_PREV_PAGE:
			if( showingPage > 0 )
				changeToPage( showingPage - 1 );
			else
				changeToPage( numberOfPages - 1 );
			break;

		case IDB_CLOSE:
			if( changeToPage( 0 ) )
				hideFromScreen();
			break;

		default:
			return False;
		}

	return True;
}
