#ifndef ZFORMWIN
#define ZFORMWIN


#include "FormWin.H"
#include "zApp.HPP"


class zFormWindow : public FormWindow, public zDialogFrame
{
public:
	//=== constructors and destructor =====
	zFormWindow( Form *form, zWindow *parent );
	virtual ~zFormWindow();

	virtual const char *getClassName();

protected:
//	virtual void addNewPage();
//	virtual void removeLastPage();
};


#endif