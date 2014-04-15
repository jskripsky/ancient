/*===========================================================================*
 *====   KONAS   ============================================================*
 *===========================================================================*
 * Field.H                                                                   *
 *===========================================================================*
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *===========================================================================*/

#ifndef FIELD
#define FIELD

#include "FormDef.H"
#include "DataObj.H"

class FieldWindow;
class FieldPrinter;
class Form;
class FormWindow;
class FieldPrint;


// "Field" ist eine abstrakte Klasse, von der alle konkreten Feld-Klassen
// (Daten-Klassen) abgeleitet werden.
// (Beispiele fÅr Subklassen: Textfeld, Zahlenfeld und Auswahlfeld)

// Als Ableitung von "PersistentObject" kann es seine Daten speichern.
// Als Ableitung von "DataObject" kann es ein Anzeige- und ein Druck-Objekt
// erstellen.

// Jede "Field"-Subklasse verwaltet neben ihren Meta-Daten (z.B. die max.
// TextlÑnge beim Textfeld) auch die effektiven (Benutzer-)Daten (z.B. den
// effektiven Textstring beim Textfeld).

// Ausserdem mÅssen konkrete Subklassen einiger Methoden implementieren,
// auf deren Aufruf jedes Feld-Objekt reagieren muss.

// Alle Objekte dieser Klasse (bzw. der Subklassen) "befinden" sich wÑhrend
// ihrer Life-Time im Form-Objekt. (Kurz nach ihrer Entstehung werden sie mit
// Hilfe der "attachToForm"-Methode ins Form-Objekt eingefÅgt.)


class Field : public DataObject
{
public:
	//=== constructors and destructor =====
	Field();
	virtual ~Field();

	//=== user data handling =====
        // Die folgenden Methoden mÅssen von Subklassen implementiert werden.
        // Sie beschÑftigen sich mit den effektiven Daten (d.h. den
        // Benutzerdaten) des Feldes.

	virtual void initializeData() = 0;
        // Initialisiert alle Variablen, die die effektiven Daten des Feldes
        // speichern. (Bsp.: Ein Textfeld muss hier Speicher fÅr seine String-
        // Variable reservieren.)

	virtual boolean isFilledIn() = 0;
        // Liefert True, falls das Feld ausgefÅllt ist, sonst False.
		  // (Liefert ein obligatorisches Feld hier False, erscheint eine
		  // Fehlermeldung.)

	virtual const char *getString() = 0;
		  // Liefert die effektiven Daten des Feldes in Textform, als String.
		  // (Der Client darf den Speicher des gelieferten Strings nicht
		  // freisetzen.)
        // (Diese Methode wird bei der Zusammenstellung des Index-Eintrag-
        // Strings (z.B. "MÅller, Peter, 20.1.1950") verwendet.)

	virtual void setToDefault() = 0;
        // Setzt die effektiven Daten zurÅck zu ihrem Default.
        // (Bsp.: Ein Textfeld kopiert seinen Default-String in die
        // Benutzer-String Variable. Aus "Ackerstr. 24, 54300 Bogenhausen" wird
        // z.B. "unbekannt")

	virtual boolean validate();
        // Liefert True, falls die effektiven Daten plausibel sind, sonst False.
		  // Bei unplausiblen Daten wird eine Fehlermeldung angezeigt
        // ("FieldWindow::errorMessage").
        // Diese Methode ruft auch "isFilledIn" auf. Ist dieses Feld
        // obligatorisch und "isFilledIn" antwortet mit "False", so wird
        // eine Fehlermeldung ("FieldWindow::errorMessage") ausgegeben
        // und False zurÅckgeliefert.
		  // (Siehe auch "FieldWindow::validate".)

	//=== user data storage =====
	virtual void writeData( StorageUnit& ) = 0;
	virtual void readData( StorageUnit& ) = 0;
        // Diese Methoden mÅssen implementiert werden, um die effektiven
        // Daten (also die Benutzer-Daten) des Feldes zu speichern oder zu
        // lesen.


	//=== field presentation (DataObject) =====
   virtual Window *createWindow( zWindow *parent ) = 0;
	virtual FieldPrint *createPrint( const char *printerID ) = 0;

	//=== form =====
	void attachToForm( Form * );
        // Muss vom Objekt-Client aufgerufen werden, um dieses Objekt
        // an das Form-Objekt zu "hÑngen". Dadurch wird der Form-Pointer
        // (Form *form)  gesetzt und das Form-Objekt Åber dieses neue Objekt
		  // informiert.


	//=== window =====
	FieldWindow *getWindow();
		  // Liefer den Wert der Variable "window".


		  // Die folgenden vier Zeilen haben vorlÑufig nur interne Bedeutung:
	virtual const char *getID();
	virtual void setID( const char *aID );

protected:
	char *id;


protected:
	Form *form;
		  // Zeigt auf das Form-Objekt, in welchem sich dieses Feld befindet
        // (sonst Null).


protected:
	//=== form design / metadata =====
	boolean obligatory;
        // Speichert, ob dies ein obligatorisches oder fakultatives Feld ist.

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
		  // Diese Methoden mÅssen in Subklassen ersetzt und ergÑnzt werden,
		  // um alle Meta-Daten zu speicher und zu lesen.

	friend Form *createFormDefinition();
};


#endif
/*===================* 
 * End of Field.H    *
 *===================*/