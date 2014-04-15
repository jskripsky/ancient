#include "LstFldWn.H"
#include "SelFld.H"

#include "zApp.HPP"

declSlist( Entry );

//==========================================================
//===  constructors and destructor  ========================
//==========================================================

ListFieldWindow::ListFieldWindow( Field *field, zWindow *parent ) :
//	Presentation( field ),
	FieldWindow( field ),
	zListBoxUnsorted( parent, new zSizer( 100, 50, 120, 30 ),
		0 )
{
	window = this;

	EntrySlistIter *iter = getSelectionField()->getListIterator();

	Entry *e;
	while( (e = (*iter)()) != 0 )
		add( e->string );

	delete iter;

	setNotifySelChange( this, (NotifyProc)&ListFieldWindow::changed );
}


ListFieldWindow::~ListFieldWindow()
{
}


const char *ListFieldWindow::getClassName()
{
	return "ListFieldWindow";
}


void ListFieldWindow::update()
{
	selection( (int)getSelectionField()->getSelection() );
}


int ListFieldWindow::changed( zEvent * )
{
	getSelectionField()->setSelection( selection() );
	return True;
}
