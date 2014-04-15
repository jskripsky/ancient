#ifndef FORMWIN
#define FORMWIN


#include "Window.H"

class Form;
class FieldWindow;
class zWindow;


class FormWindow : public Window
{
public:
	//=== constructors and destructor =====
	FormWindow( Form *form );
	virtual ~FormWindow();

        Rectangle getFormArea();

protected:
	Form *getForm();


protected:
	//=== form design / metadata =====
	long numberOfPages;
        char **pageTitles;

        Rectangle formArea;
        

	virtual void addNewPage( char *title );

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


inline Form *FormWindow::getForm()
	{ return (Form *)getDataObject(); }


#endif