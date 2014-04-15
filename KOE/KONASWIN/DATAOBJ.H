/*===========================================================================* 
 *====   KONAS   ============================================================*
 *===========================================================================*
 * DataObj.H                                                                 *
 *===========================================================================*
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *===========================================================================*/

#ifndef DATAOBJ
#define DATAOBJ


#include "Persist.H"


class Presentation;
class Window;
class zWindow;


// "DataObject" ist eine abstrakte Klasse, von der alle Klassen abgeleitet
// werden, die sich mit der Verwaltung und Manipulation von Daten
// beschÑftigen.
// Die einzige direkte Verbindung zu PrÑsentations-Objekten ist die Variable
// "window" und die Methode "createWindow" (siehe Bemerkung).

// Als Ableitung von "PersistentObject" kînnen alle Subklassen von
// "DataObject" ihre Daten speichern.


class DataObject : public PersistentObject
{
public:
	//=== constructors and destructor =====
	DataObject();
	virtual ~DataObject();

	void openWindow( zWindow *parent = 0 );
	void closeWindow();
		  // Der Objekt-Client ruft diese Methoden auf, um das Window-Objekt
		  // (und das damit verbundene zWindow-Objekt) zu erstellen und zu
		  // zerstîren. Beim Erstellen wird das zWindow-Objekt automatisch ins
		  // zWindow des Parents eingefÅgt und erscheint je nach dessen
		  // Sichtbarkeit am Bildschirm oder nicht.

	void showWindow();
	void hideWindow();
	// JS: !!!!!!

protected:
	Window *window;
        // Pointer auf das Window-Objekt (Null, falls im Augenblick keines
        // existiert).

	virtual Window *createWindow( zWindow *parent ) = 0;
		  // Diese Methode muss von jeder konkreten Subklasse implementiert
        // werden. Sie muss ein Window-Objekt erstellen und zurÅckliefern.
        // Sie darf vom Objekt-Client nicht direkt aufgerufen werden!
        // (Statt dessen bedient sich der Objekt-Client der "openWindow" und
        // "closeWindow"-Methoden.)
        // Bemerkung zur Implementation: Indem man die Implementationen
        // (dieser Methode) bei allen konkreten Subklassen in einer einzigen
        // Datei (Vorschlag: "DataPres.CPP") ablegt, sind alle Klassen-
        // Verbindungen (bzw. Klassen-Zugehîrigkeiten) an einem Ort
        // gespeichert. Dies trÑgt zur öbersichtlichkeit bei und
        // unterstreicht ausserdem nochmals die Trennung von Daten und
        // PrÑsentation.
};


#endif
/*===================* 
 * End of DataObj.H  *
 *===================*/