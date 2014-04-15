#include "FormWin.H"
#include "Form.H"
#include "Storage.H"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

FormWindow::FormWindow( Form *form, zWindow *parent ) :
	Presentation( form ),
	Window( form, parent ),
	numberOfPages( 1 )
{
	// create top-level window, insert into desktop.

}


FormWindow::~FormWindow()
{
	// remove top-level window from desktop, destroy it.
}


void FormWindow::addNewPage()
{
}


void FormWindow::removeLastPage()
{
}


//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================

void FormWindow::write( StorageUnit& su )
{
	Window::write( su );
        su << numberOfPages;
}


void FormWindow::read( StorageUnit& su )
{
	Window::read( su );
	su >> numberOfPages;
}
