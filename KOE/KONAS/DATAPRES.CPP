#include "Form.H"
#include "FormFrm.H"

#include "EntryFld.H"
#include "EFldWin.H"


Window *Form::createWindow( void * )
{
        return new FormFrame( this );
}


Window *EntryField::createWindow( void *parent )
{
        return new EntryFieldWindow( this, (zWindow *)parent );
}
