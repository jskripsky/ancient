#ifndef KONASFRM
#define KONASFRM

#include "KonasApp.H"
#include "zApp.HPP"

// Die "Frame"-Klasse implementiert alle Elemente des "Master Panels".
// Dazu gehört die ListBox der Personenliste ("PersonList") und alle Buttons
// dieses Panels.


class KonasFrame : public zDialogFrame, public KonasApp
{
public:
	//=== constructors and destructor =====
	KonasFrame( const char *title );
	virtual ~KonasFrame();

protected:
        zListBox/*Unsorted*/ *personListBox;

        virtual int command( zCommandEvt* );

        void setupPanel();

        zDefPushButton *newPersonBtn;
        zPushButton *editPersonBtn;
        zPushButton *deletePersonBtn;

        zPushButton *printPersonBtn;
        zPushButton *mcPersonBtn;

        zPushButton *printListBtn;
        zPushButton *exportDataBtn;

        zPushButton *closeBtn;
};


#endif