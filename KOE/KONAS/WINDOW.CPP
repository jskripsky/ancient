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
	rectangle.cx = rectangle.cy = 1;
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


Rectangle Window::getRectangle()
{
	return rectangle;
}


void Window::setRectangle( Rectangle rect )
{
	rectangle = rect;
        adjustzWindowRect();
}


void Window::adjustzWindowRect()
{
        // zWindow->size, move......!!!!!!!!!!!
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
