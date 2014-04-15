/*===========================================================================* 
 *====   KONAS   ============================================================*
 *===========================================================================*
 * Present.H                                                                 *
 *===========================================================================*
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *===========================================================================*/

#ifndef PRESENT
#define PRESENT


#include "Persist.H"


class DataObject;


// "Presentation" ist eine abstrakte Klasse, von der alle Pr„sentations-
// Klassen (Anzeige oder Druck) direkt oder indirekt abgeleitet werden.
// (Alle Klassen, die der Anzeige dienen, werden von der Subklasse "Window"
// abgeleitet.)

// Als Ableitung von "PersistentObject" kann es seine Daten speichern.

// Jedes Objekt dieser Klasse besitzt automatisch einen Pointer auf das
// Daten-Objekt, zu welchem es geh”rt. Dieser enth„lt w„hrend der gesamten
// Life-Time unseres "Presentation"-Objekts einen korrekten Wert.

// Es wird empfohlen, das jede Subklasse eine Methode einfhrt, die diesen
// Daten-Objekt-Pointer zurckliefert, und zwar auf die echte Klasse des
// Daten-Objekts gecastet.
// (Erkl„rung: Arbeitet eine Subklasse z.B. mit einem Daten-Objekt
// der Klasse"DateField" zusammen, hat es durch den "DataObject *"-Pointer
// keinen Zugriff auf Methoden, die erst in der "DateField"-Klasse eigefhrt
// wurden. Wird nun die neue "getDateField"-Methode verwendet, muss der
// Pointer nicht jedes Mal explizit gecastet werden.)

// Jede Field-Subklasse verwaltet neben seinen Meta-Daten (z.B. die max.
// Textl„nge beim Textfeld) auch die effektiven (Benutzer-)Daten (z.B. den
// effektiven Textstring beim Textfeld).

// Ausserdem mssen konkrete Subklassen einige Methoden implementieren,
// auf die jedes Feld-Objekt reagieren muss.


class Presentation : /*virtual*/ public PersistentObject
{
public:
	//=== constructors and destructor =====
	Presentation( DataObject * );
        // Dem Constructor muss der Pointer auf das Daten-Objekt bergeben
        // werden, zu welchem dieses Objekt geh”rt.

	virtual ~Presentation();


protected:
	DataObject *dataObject;
        // Pointer auf das DataObject-Objekt (Null, falls keines existiert).

	virtual DataObject *getDataObject();
        // Vorlage fr Subklassen. Diese sollten eine Methode in der Form
        // "[ClassName] *get[ClassName]()" besitzen, die den dataObject-
        // Pointer zurckliefern, und zwar auf seine echte Klasse gecastet.


protected:
	//=== storage (PersistentObject) =====
        //virtual void write( StorageUnit& ); // JS: redundant in this Class?
        //virtual void read( StorageUnit& ); // JS: redundant in this Class?
};


#endif
/*===================*
 * End of Present.H  *
 *===================*/