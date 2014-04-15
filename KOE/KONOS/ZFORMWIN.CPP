#include "zFormWin.H"
#include "Form.H"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

zFormWindow::zFormWindow( Form *form, zWindow *parent ) :
	Presentation( form ),
	FormWindow( form, parent ),
        zDialogFrame( parent, new zSizer(10, 10, 800, 500), DS_MODALFRAME,
                "Patient XY" )
{
        show();
        modal();
}


zFormWindow::~zFormWindow()
{
}


const char *zFormWindow::getClassName()
{
        return "zFormWindow";
}


/*
void zFormWindow::addNewPage()
{
}


void zFormWindow::removeLastPage()
{
}
*/
