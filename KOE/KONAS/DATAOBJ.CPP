#include "DataObj.H"
#include "Window.H"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

DataObject::DataObject()
{
}


DataObject::~DataObject()
{
}


void DataObject::openWindow( void *parent )
{
	window = createWindow( parent );
}


void DataObject::closeWindow()
{
	delete window;
}


void DataObject::showWindow()
{
        window->showOnScreen();
}


void DataObject::hideWindow()
{
        window->hideFromScreen();
}
