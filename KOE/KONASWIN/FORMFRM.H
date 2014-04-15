#ifndef FORMFRM
#define FORMFRM


#include "FormWin.H"
#include "zApp.HPP"


class FormFrame : public zDialogFrame, public FormWindow
{
public:
	//=== constructors and destructor =====
	FormFrame( Form *form );
	virtual ~FormFrame();

	virtual boolean changeToPage( long newPage, boolean check = True );

	virtual const char *getClassName();

	virtual void hideFromScreen();
	virtual void showOnScreen();

	virtual void setupPanel();

protected:
	long showingPage;
	zStaticText *pageTitleStxt;

	void setupFields();

	virtual int command( zCommandEvt* );
};


#endif