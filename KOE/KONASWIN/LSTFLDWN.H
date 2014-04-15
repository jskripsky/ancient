#ifndef LSTFLDWN
#define LSTFLDWN


#include "FieldWin.H"
#include "zApp.HPP"

class SelectionField;


class ListFieldWindow : public zListBoxUnsorted, public FieldWindow
{
public:
	//=== constructors and destructor =====
	ListFieldWindow( Field *, zWindow *parent );
	virtual ~ListFieldWindow();

	virtual const char *getClassName();

	int changed( zEvent * );

protected:
	SelectionField *getSelectionField();

	virtual void update();
};


inline SelectionField *ListFieldWindow::getSelectionField()
	{ return (SelectionField *)dataObject; }


#endif
