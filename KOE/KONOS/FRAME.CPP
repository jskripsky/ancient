#include "Frame.H"
#include "Form.H"

//==========================================================
//===  constructors and destructor  ========================
//==========================================================

Frame::Frame( zWindow *parent, zSizer *sizer, DWORD winStyle,
        const char *title ) :
        zAppFrame( parent, sizer, winStyle, title )
{
        form = new Form();
        form->openWindow( this );
}

Frame::~Frame()
{
}
