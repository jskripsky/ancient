/*===========================================================================* 
 *====   KONAS   ============================================================*
 *===========================================================================*
 * Window.H                                                                  *
 *===========================================================================*
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *===========================================================================*/

#ifndef WINDOW
#define WINDOW


#include "Present.H"


class zWindow;

struct Rectangle
{
	short x, y;
	short cx, cy;
};


// "Window" ist eine abstrakte Klasse, von der alle Anzeige-Klassen
// direkt oder indirekt abgeleitet werden.

// Die "Window"-Klasse hat keinen direkten Kontakt mit seinem
// Bildschirmelement und dem Benutzer. Dazu wird ein eine "zWindow"-Klasse
// verwendet.

// Jedes "Window"-Objekt arbeitet intern mit einem zWindow-Objekt zusammen.
// Es reagiert auf Befehle seines Daten-Objekts und leitet sie an das
// zWindow-Objekt weiter, wo sie "effektiv" ausgefÅhrt werden.

// Um die explizite Verbindung zwischen "Window"- und "zWindow"-Objekten zu
// umgehen, kînnen die konkrete "Window"-Subklasse sowohl von der gewÅnschten
// "Window"-Klasse als auch von der gewÅnschten "zWindow"-Klasse abgeleitet
// werden (multiple inheritance). Dadurch entfÑllt das Problem der Verbindung.

// Als Ableitung von "PersistentObject" kînnen Subklassen von "Window" ihre
// Daten speichern.

// Wichtig fÅr Subklassen: "Window" ist virtuell von der Klasse "Presentation"
// abgeleitet.

// Wichtig: Sobald der Constructor aufgefÅhrt worden ist, muss die Variable
// "window" auf das zWindow-Objekt zeigen!

class Window : /*virtual*/ public Presentation
{
public:
	//=== constructors and destructor =====
        Window( DataObject * );
        // Alle Subklassen mÅssen in ihrem Constructor ein zWindow-Objekt
        // erstellen (dessen Parent "aParent" wird) und irgendwie mit diesem
        // Objekt verbinden (empfohlene Strategie: "multiple inheritance").
		  // Wichtig: Nach der AusfÅhrung des Constructors muss "window"
        // auf das zWindow-Objekt zeigen.

        virtual ~Window();
        // Subklassen mÅssen in ihrem Destructor ihr zWindow-Objekt zerstîren
        // (geschieht bei der "multiple inheritance"-Strategie automatisch).

	virtual void hideFromScreen();
	virtual void showOnScreen();
		  // (modal window override!)
        // JS: old comment (FieldWindow::hide.../show...)!!!!! :
        // Diese Methoden werden beim Seitenwechsel des Formulars vom
        // Form-Objekt aufgerufen, damit nur die Felder sichtbar sind, die
        // sich auf der aktuellen Seite befinden.

        virtual void acquireUserFocus();
        // Gibt dem zWindow-Objekt den "Focus".

		  struct Rectangle getRectangle();
        void setRectangle( struct Rectangle rect );
        // Diese Methoden setzen und liefern die Position und Dimensionen des
        // zWindows. (Diesen Angaben sind meistens relativ zum Parent-zWindow,
        // kînnen aber von Subklassen auch anderst interpretiert werden.
        // Siehe dazu "adjustzWindowRect".)

        zWindow *getzWindow();
        // Liefert das zWindow-Objekt, mit dem dieses Objekt verbunden ist.

protected:
        zWindow *window;
        // Pointer auf das zWindow-Objekt, welches zu diesem Objekt gehîrt.

protected:
	//=== form design / metadata =====
	struct Rectangle rectangle;

   virtual void adjustzWindowRect();
        // Diese Methode Åbermittelt die "rectangle"-Daten an das zWindow-
        // Objekt. Sie wird automatisch von der "setRectangle"-Methode
        // aufgerufen.
        // Subklassen mÅssen diese Methode ersetzen, um die Daten der
        // "rectangle"-Variable anderst zu interpretieren (siehe Klasse
        // "FieldWindow" fÅr ein Beispiel).
 

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
        // Diese Methoden speichern die Variable "rectangle". Subklassen
        // mÅssen ersetzen und ergÑnzen.
};


inline zWindow *Window::getzWindow()
        { return window; }


#endif
/*===================* 
 * End of Window.H   *
 *===================*/