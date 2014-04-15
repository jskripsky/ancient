#ifndef WINDOW
#define WINDOW


#include "Present.H"


class zWindow;

struct Rectangle
{
	short x, y;
	short cx, cy;
};


class Window : virtual public Presentation
{
public:
	//=== constructors and destructor =====
        Window( DataObject *, zWindow *aParent );
        virtual ~Window();

        virtual Rectangle getRectangle();
        virtual void setRectangle( Rectangle rect );

        zWindow *getzWindow();

protected:
        zWindow *parent;
        zWindow *window;
        // Pointer auf das zWindow-Objekt, welches zu diesem Objekt geh”rt.

protected:
	//=== form design / metadata =====
	Rectangle rectangle;


protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


inline zWindow *Window::getzWindow()
        { return window; }


#endif