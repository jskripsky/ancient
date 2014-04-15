#ifndef FRAME
#define FRAME


#include "zApp.HPP"

class Form;


class Frame : public zAppFrame
{
public:
	//=== constructors and destructor =====
	Frame( zWindow *parent, zSizer *sizer, DWORD winStyle,
                const char *title );
	virtual ~Frame();

protected:
        Form *form;
};


#endif