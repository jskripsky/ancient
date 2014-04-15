#ifndef EFLDWIN
#define EFLDWIN


#include "FieldWin.H"
#include "zApp.HPP"


// Die Klasse "EntryFieldWindow" realisiert die Anzeige des Textfelds.

// Die zu dieser Klasse geh”rende Daten-Klasse ist "EntryField"
// ("EntryFld.H").


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