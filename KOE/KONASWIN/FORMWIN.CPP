#include "FormWin.H"
#include "Form.H"
#include "Field.H"
#include "Storage.H"

#include "zApp.HPP"

declSlist( pageTitle );

//==========================================================
//===  constructors and destructor  ========================
//==========================================================

FormWindow::FormWindow( Form *form ) :
//	Presentation( form ),
	Window( form ),
   pageTitles( new pageTitleSlist() ),
	numberOfPages( 0 )
{
	formArea.x = 10;
	formArea.y = 10;
	formArea.cx = 200;
	formArea.cy = 150;

	// create top-level window, insert into desktop.
}


FormWindow::~FormWindow()
{
	// remove top-level window from desktop, destroy it.
}


void FormWindow::attachField( Field *f )
{
	f->openWindow( window );
}


void FormWindow::addNewPage( char *title )
{
	pageTitles->append( title );
	numberOfPages++;
}


struct Rectangle FormWindow::getFormArea()
{
	return formArea;
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
