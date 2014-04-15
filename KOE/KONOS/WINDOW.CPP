#include "Window.H"
#include "Storage.H"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

Window::Window( DataObject *dataObject, zWindow *aParent ) :
	Presentation( dataObject ),
	parent( aParent )
{
	rectangle.x = rectangle.y = 0;
	rectangle.cx = rectangle.cy = 1;
}


Window::~Window()
{
}


Rectangle Window::getRectangle()
{
	return rectangle;
}


void Window::setRectangle( Rectangle rect )
{
	rectangle = rect;
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
