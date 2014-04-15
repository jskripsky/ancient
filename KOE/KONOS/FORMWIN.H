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
	FormWindow( Form *form, zWindow *parent );
	virtual ~FormWindow();

protected:
	Form *getForm();


protected:
	//=== form design / metadata =====
	long numberOfPages;

	virtual void addNewPage();
	virtual void removeLastPage();

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


inline Form *FormWindow::getForm()
	{ return (Form *)getDataObject(); }


#endif