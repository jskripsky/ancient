#include "EFldWin.H"
#include "EntryFld.H"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

EntryFieldWindow::EntryFieldWindow( Field *field, zWindow *parent ) :
	Presentation( field ),
	FieldWindow( field, parent ),
        zEditLine( parent, new zSizer( 10, 10, 100, 30 ) )
{
        show();
}


EntryFieldWindow::~EntryFieldWindow()
{
}


const char *EntryFieldWindow::getClassName()
{
        return "EntryFieldWindow";
}


void EntryFieldWindow::update()
{
}


boolean EntryFieldWindow::validate()
{
        return True;
}
