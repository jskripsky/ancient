#include "Form.H"
#include "FormFrm.H"

#include "EntryFld.H"
#include "EFldWin.H"

#include "SelFld.H"
#include "LstFldWn.H"
//#include "RdFldWin.H"

Window *Form::createWindow( zWindow * )
{
	return new FormFrame( this );
}


Window *EntryField::createWindow( zWindow *parent )
{
	return new EntryFieldWindow( this, parent );
}


Window *SelectionField::createWindow( zWindow *parent )
{
	Window *w;
	switch( displayType )
		{
		case RadioButtons:
			w = 0;
			//w = new RadioFieldWindow( this, parent );
			break;

		case ListBox:
			w = new ListFieldWindow( this, parent );
			break;
		}
	return w;
}
