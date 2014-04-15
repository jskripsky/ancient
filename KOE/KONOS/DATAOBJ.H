#ifndef DATAOBJ
#define DATAOBJ


#include "Persist.H"


class Presentation;
class Window;


class DataObject : public PersistentObject
{
public:
	//=== constructors and destructor =====
	DataObject();
	virtual ~DataObject();

	void openWindow( void *parent );
	void closeWindow();
        // Der Objekt-Client ruft diese Methoden auf, um das Window-Objekt
        // (und das damit verbundene zWindow-Objekt) zu erstellen und zu
        // zerstîren. Beim Erstellen wird das zWindow-Objekt automatisch ins
        // zWindow von des Parents eingefÅgt und erscheint je nach dessen
        // Sichtbarkeit am Bildschirm oder nicht.


protected:
	Window *window;
        // Pointer auf das Window-Objekt (Null, falls keines existiert).

	virtual Window *createWindow( void *parent ) = 0;
        // Diese Methode muss von jeder konkreten Subklasse implementiert
        // werden. Sie muss ein Window-Objekt erstellen und zurÅckliefern.
        // Sie darf vom Objekt-Client nicht direkt aufgerufen werden!
};


#endif