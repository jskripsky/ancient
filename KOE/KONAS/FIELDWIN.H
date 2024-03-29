/*===========================================================================* 
 *====   KONAS   ============================================================*
 *===========================================================================*
 * FieldWin.H                                                                *
 *===========================================================================*
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *===========================================================================*/

#ifndef FIELDWIN
#define FIELDWIN

#include "FldPres.H"
#include "Window.H"

class FormWindow;

// "FieldWindow" ist eine abstrakte Klasse, von der alle Anzeige-Klassen f�r
// Feld-Objekte direkt oder indirekt abgeleitet werden.

// "FieldWindow-Objekte" sollten ihre Daten-Objekte ("Field") immer
// "up-to-date" halten.
// Bsp.: Dr�ckt der Benutzer in einem Textfeld eine Taste, so muss das
// Window-Objekt sofort den neuen Text ermitteln und an das Daten-Objekt
// schicken.
// (Nur dank diesem Prinzip k�nnen Verkn�pfungen sofort reagieren.)
// Macht es keinen Sinn, das Daten-Objekt laufend upzudaten (z.B. in einem
// Datum-Feld kann sich w�hrend der Eingabe ein unvollst�ndiges Datum
// befinden), so sollte der Update-Vorgang auf den Zeitpunkt verschoben
// werden, da das Feld den "Eingabe-Focus" verliert.

// JS: Bemerkungen zum Label!!


class FieldWindow : public FieldPresentation, public Window
{
public:
	//=== constructors and destructor =====
	FieldWindow( Field * );
        // Erstellt u.a. auch das zWindow-Object des Feld-Labels ("label").

	virtual ~FieldWindow();
        // Zerst�rt "label".


        long getPageNumber();
        // Liefert den Wert der Variable "pageNumber".

        void createLabel();

	virtual void update() = 0;
        // Diese Methode wird vom Feld-Objekt ("Field") aufgerufen, wenn
        // dessen Daten sich ge�ndert haben. Die Implementation diese Methode
        // muss dann das Bildschirmelement updaten.
        // (Dies erlaubt Real-Time Updates der Daten.)

	virtual boolean validate() = 0;
        // Obwohl diese Methode den selben Zweck wie "Field::validate"
        // erf�llt, gibt es einen charakteristischen Unterschied. Hier werden
        // "visuelle" Fehler (z.B. Datum "1111995" anstatt "11.1.1995")
        // entdeckt, w�hrend "Field::validate" "logische" Fehler
        // (z.B. Datum 31.2.1995) aufsp�rt, die ein tieferes Wissen �ber die
        // Daten erfordern.

	void incLockCount();
	void decLockCount();
        // Diese Methoden werden vom Objekt-Client aufgerufen, um die Aus-
        // oder Einblendung zu veranlassen. Da mehrere Clients die Ausblendung
        // w�nschen k�nnen, wird ein interner Ausblendungs-Z�hler laufend
        // inkrementiert. Ist der Wert des Z�hlers ungleich 0, ist das
        // Bildschirmelement ausgeblendet (siehe "lock"). Erst wenn der Z�hler
        // wieder den Wert 0 erreicht, wird eingeblendet ("unlock"). 
        // Diese Methoden werden vom Verkn�pfungs-Protokoll aufgerufen.

	virtual void showErrorMessage( const char *errorText );
        // Diese Methode muss eine modale Message-Box zeigen, die eine
        // "Fehler"-Meldung enth�lt (z.B. Datumfeld: "Das eingegebene Datum
        // ist ung�ltig!"). Noch bevor diese Message-Box erscheint, wird aber
        // noch die "acquireUserFocus"-Methode aufgerufen, sodass das
        // "fehlerhafte" Feld aktiv ist.
        // Diese Methode wird von "Field::validate" oder
        // "FieldWindow::validate" aufgerufen.


protected:
	long lockCount;
        // Ausblendungs-Z�hler (siehe "incLockCount", "decLockCount").

	virtual void lock();
	virtual void unlock();
        // Diese Methoden f�hren die effektive Ein- und Ausblendung des
        // Bildschirmelements durch (es sollte aber nicht vollkommen
        // unsichtbar gemacht werden, sondern nur etwas blasser erscheinen
        // (disabled) und vom Benutzer nicht mehr aktiviert oder editiert werden
        // k�nnen). Sie werden von "incLockCount" und "decLockCount"
        // aufgerufen.

	//=== form design / metadata =====
        FormWindow *getFormWindow();
        // Methode zu internen Zwecken (um Zugriff auf
        // "FormWindow::getFormArea" zu erlangen).

	long pageNumber;

        virtual void adjustzWindowRect();
        // (Siehe Klasse "Window" f�r eine allgemeine Beschreibung.)
        // Diese Implementation der Methode �bermittelt die "rectangle"-Daten,
        // um eine bestimmte Distanz verschoben, an das zWindow-Objekt.
        // Dadurch erh�lt das Bildschirm-Formular einen "Rand". Enth�lt die
        // "rectangle"-Structure f�r "x" und "y" z.B. 0, so erscheint das
        // Bildschirmelement nicht direkt in der linken, oberen Ecke des
        // Formular-Fensters (dicht am Fenster-Rahmen), sondern leicht nach
        // unten, rechts versetzt.


        //=== field label =====
	char *labelText;
        zWindow *label;
        // (genauere Klasse: "zStaticText")
        
        Rectangle labelRectangle;
        // relativ zu den "rectangle"-Werten.


protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


#endif
/*===================* 
 * End of FieldWin.H *
 *===================*/