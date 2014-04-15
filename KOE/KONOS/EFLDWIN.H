#ifndef EFLDWIN
#define EFLDWIN


#include "FieldWin.H"
#include "zApp.HPP"


class EntryFieldWindow : public FieldWindow, public zEditLine
{
public:
	//=== constructors and destructor =====
	EntryFieldWindow( Field *, zWindow *parent );
	virtual ~EntryFieldWindow();

	virtual const char *getClassName();

protected:
	virtual void update();

	virtual boolean validate();
};


#endif