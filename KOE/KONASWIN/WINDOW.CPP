#include "Window.H"
#include "Storage.H"

#include "zApp.HPP"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

Window::Window( DataObject *dataObject ) :
	Presentation( dataObject )
{
	rectangle.x = rectangle.y = 0;
	rectangle.cx = rectangle.cy = 10;
}


Window::~Window()
{
}


void Window::hideFromScreen()
{
        window->show( SW_HIDE );
}


void Window::showOnScreen()
{
        window->show();
}


void Window::acquireUserFocus()
{
        window->setFocus();
}


struct Rectangle Window::getRectangle()
{
	return rectangle;
}


void Window::setRectangle( struct Rectangle rect )
{
	rectangle = rect;
	adjustzWindowRect();
}


void Window::adjustzWindowRect()
{
	zRect r( rectangle.x, rectangle.y, rectangle.x + rectangle.cx,
		rectangle.y + rectangle.cy );

	window->move( r );
}


//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================

void Window::write( StorageUnit& su )
{
	su.writeData( &rectangle, sizeof( rectangle ) );
}


void Window::read( StorageUnit& su )
{
	su.readData( &rectangle, sizeof( rectangle ) );
}
