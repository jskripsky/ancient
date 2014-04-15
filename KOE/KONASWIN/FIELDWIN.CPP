#include "FieldWin.H"
#include "Field.H"
#include "Label.H"
#include "Storage.H"
#include "FormWin.H"

#include "zApp.HPP"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

FieldWindow::FieldWindow( Field *field ) :
//	Presentation( field ),
	Window( field ),
//	FieldPresentation( field ),
	lockCount( 0 ),
	labelText( 0 ),
	label( 0 ),
	pageNumber( 0 )
{
}


FieldWindow::~FieldWindow()
{
	if( label )
		delete label;
}


void FieldWindow::createLabel()
{
	label = new Label( (Field *)dataObject, window->parent() );
}


boolean FieldWindow::validate()
{
	return True;
}


void FieldWindow::hideFromScreen()
{
	Window::hideFromScreen();
	if( label )
		label->hideFromScreen();
}


void FieldWindow::showOnScreen()
{
	Window::showOnScreen();
	if( label )
		label->showOnScreen();
}


void FieldWindow::incLockCount()
{
	if( lockCount == 0 )
		lock();

	lockCount++;
}


void FieldWindow::decLockCount()
{
	if( lockCount > 0 )
		{
		lockCount--;

		if( lockCount == 0 )
			unlock();
		}
}


void FieldWindow::lock()
{
        //!!!!!!!!!!!!!!!!!
}


void FieldWindow::unlock()
{
		  //!!!!!!!!!!
}


void FieldWindow::showErrorMessage( const char *errorText )
{
        acquireUserFocus();

        zMessage *message = new zMessage( 0, errorText, "Fehler" );
		  delete message;
}


FormWindow *FieldWindow::getFormWindow()
{
	return (FormWindow *)window->parent();
}


void FieldWindow::adjustzWindowRect()
{
	Window::adjustzWindowRect();

	zRect r( rectangle.x, rectangle.y, rectangle.x + rectangle.cx,
		rectangle.y + rectangle.cy );

//	struct Rectangle border = getFormWindow()->getFormArea();
	r += zPoint( 10, 25 );

	zDialogUnit duA( r.left(), r.top() );
	zDialogUnit duB( r.right(), r.bottom() );

	zRect newR( duA.physical().x(), duA.physical().y(),
					duB.physical().x(), duB.physical().y() );

	window->move( newR );
}


//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================

void FieldWindow::write( StorageUnit& su )
{
//	/*Field*/Presentation::write( su );
	su << pageNumber;
}


void FieldWindow::read( StorageUnit& su )
{
//	/*Field*/Presentation::write( su );
	su >> pageNumber;
}
