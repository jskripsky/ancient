#include "DataObj.H"
#include "Window.H"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

DataObject::DataObject() :
	window( 0 )
{
}


DataObject::~DataObject()
{
}


void DataObject::openWindow( zWindow *parent )
{
	window = createWindow( parent );
}


void DataObject::closeWindow()
{
	delete window;
	window = 0;
}


void DataObject::showWindow()
{
        window->showOnScreen();
}


void DataObject::hideWindow()
{
        window->hideFromScreen();
}
