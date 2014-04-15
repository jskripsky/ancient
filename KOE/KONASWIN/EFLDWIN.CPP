#include "EFldWin.H"
#include "EntryFld.H"
#include "zApp.HPP"

//==========================================================
//===  constructors and destructor  ========================
//==========================================================

EntryFieldWindow::EntryFieldWindow( Field *field, zWindow *parent ) :
//	Presentation( field ),
	FieldWindow( field ),
	zEditLine( parent, new zSizer( 100, 50, 120, 30 ),
		ES_AUTOHSCROLL | WS_TABSTOP )
{
	window = this;
	text( getEntryField()->getText() );
	limitText( (int)getEntryField()->getMaxTextLength() );

	setNotifyChange( this, (NotifyProc)&EntryFieldWindow::changed );
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
	text( getEntryField()->getText() );
}


int EntryFieldWindow::changed( zEvent * )
{
	getEntryField()->setText( (char *)text() );
	return True;
}
