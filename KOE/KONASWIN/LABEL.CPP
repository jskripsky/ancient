#include "Label.H"
#include "Field.H"
#include "FieldWin.H"
#include "FormWin.H"
#include "Storage.H"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

Label::Label( Field *field, zWindow *parent ) :
	zStaticText( parent, new zSizer( 0, 0, 100, 20 ) ),
	Window( field )
{
	window = this;
	text( (const char *)(((FieldWindow *)field->getWindow())->labelText) );
}


Label::~Label()
{
}


const char *Label::getClassName()
{
	return "Label";
}


void Label::adjustzWindowRect()
{
	Window::adjustzWindowRect();

	zRect r( rectangle.x, rectangle.y, rectangle.x + rectangle.cx,
		rectangle.y + rectangle.cy );

//	struct Rectangle border = getFormWindow()->getFormArea();
	r += zPoint( 10, 25 );

	zDialogUnit duA( r.left(), r.top() );
	zDialogUnit duB( r.right(), r.bottom() );

	zRect newR( duA.physical().x(), duA.physical().y(),
					duB.physical().x(), duB.physical().y() );

	window->move( newR );
}


//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================


