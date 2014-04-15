#include "Form.H"
#include "zFormWin.H"

#include "EntryFld.H"
#include "EFldWin.H"


Window *Form::createWindow( void *parent )
{
        return new zFormWindow( this, (zWindow *)parent );
}


Window *EntryField::createWindow( void *parent )
{
        return new EntryFieldWindow( this, (zWindow *)parent );
}
