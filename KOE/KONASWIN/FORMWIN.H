#ifndef FORMWIN
#define FORMWIN


#include "Window.H"

class Form;
class Field;
class FieldWindow;
class zWindow;

typedef char pageTitle;
class pageTitleSlist;


class FormWindow : public Window
{
public:
	//=== constructors and destructor =====
	FormWindow( Form *form );
	virtual ~FormWindow();

	virtual boolean changeToPage( long newPage, boolean check = True ) = 0;

	struct Rectangle getFormArea();

	void attachField( Field * );
	virtual void setupPanel() = 0;

	virtual void addNewPage( char *title );

protected:
	Form *getForm();


protected:
	//=== form design / metadata =====
	long numberOfPages;
	pageTitleSlist *pageTitles;

	struct Rectangle formArea;


protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


inline Form *FormWindow::getForm()
	{ return (Form *)getDataObject(); }


#endif