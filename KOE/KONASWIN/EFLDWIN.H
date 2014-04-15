#ifndef EFLDWIN
#define EFLDWIN


#include "FieldWin.H"
#include "zApp.HPP"

class EntryField;


// Die Klasse "EntryFieldWindow" realisiert die Anzeige des Textfelds.

// Die zu dieser Klasse geh”rende Daten-Klasse ist "EntryField"
// ("EntryFld.H").


class EntryFieldWindow : public zEditLine, public FieldWindow
{
public:
	//=== constructors and destructor =====
	EntryFieldWindow( Field *, zWindow *parent );
	virtual ~EntryFieldWindow();

	virtual const char *getClassName();

	int changed( zEvent * );

protected:
	EntryField *getEntryField();

	virtual void update();
};


inline EntryField *EntryFieldWindow::getEntryField()
	{ return (EntryField *)dataObject; }


#endif
