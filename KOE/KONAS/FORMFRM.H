#ifndef FORMFRM
#define FORMFRM


#include "FormWin.H"
#include "zApp.HPP"


class FormFrame : public FormWindow, public zDialogFrame
{
public:
	//=== constructors and destructor =====
	FormFrame( Form *form );
	virtual ~FormFrame();

        void changeToPage( long pageNumber );

	virtual const char *getClassName();

        virtual void hideFromScreen();
        virtual void showOnScreen();


protected:
        void setupFields();
        void setupPanel();

        virtual int command( zCommandEvt* );
};


#endif