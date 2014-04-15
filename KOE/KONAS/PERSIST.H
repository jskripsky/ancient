/*===========================================================================* 
 *====   KONAS   ============================================================*
 *===========================================================================*
 * Persist.H                                                                 *
 *===========================================================================*
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *===========================================================================*/

#ifndef PERSIST
#define PERSIST


#include "Types.H"

class StorageUnit;

// "PersistentObject" ist eine abstrakte Klasse, von der alle Klassen abgeleitet
// werden, die ihre Daten permanent speichern und einlesen k”nnen mssen.

// Subklassen werden neue Daten einfhren (meistens in Form von neuen
// Variabeln). Damit auch die Werte dieser neuen Variabeln gespeichert und 
// eingelesen werden, mssen die Methoden "write" und "read" ersetzt und
// erg„nzt werden. (Mit "Erg„nzen" ist gemeint, dass die neuen
// Implementationen dieser beiden Methoden zuerst die Implementationen der
// direkten Super-Klasse aufrufen und danach erst mit neuen Code fortfahren).
// Die Implementationen der "write" und "read"-Methoden mssen berein-
// stimmen, d.h. die sequentielle Datenspeicherung muss in der gleichen
// Reihenfolge ablaufen (z.B. "schreibe Variable A, B, D und schliesslich C"
// und "lese A, B, D und C").

// Die tats„chliche Speicherung geschieht im bereitgestellten Objekt der
// Klasse "StorageUnit" (bzw. deren Ableitung). Alle zu speichernden Daten
// werden sequentiell an dieses Objekt bergeben. Je nach Klasse dieses
// Objekts landen die Daten dann in einer Datei oder in einer Datenbank.
// Der Lesevorgang arbeitet analog.

// Wichtig: Soll ein "PersistentObject"-Objekt ("von aussen") aufgefordert
// werden, seine Daten in einer "StorageUnit" zu speichern, muss der
// Objekt-Client dazu die Methode "writeToStorage" verwenden, da nur dann
// wichtige Informationen, wie z.B. der Klassenname ebenfalls gespeichert
// werden. Dasselbe gilt fr den Leseaufruf ("readFromStorage").

 
class PersistentObject
{
public:
	//=== constructors and destructor =====
	PersistentObject();
	virtual ~PersistentObject();

	virtual const char *getClassName() = 0;
        // Die Methode muss in konkreten Klassen implementiert werden
        // und den Klassen-Namen als String liefern.

	void writeToStorage( StorageUnit& );
	void readFromStorage( StorageUnit& );
        // Diese Methoden kann der Client des Objekt aufgerufen, um die Daten
        // dieses Objekts speichern zu lassen.

protected:
	//=== storage =====
	virtual void write( StorageUnit& ) = 0;
	virtual void read( StorageUnit& ) = 0;
        // Diese Methoden mssen laufend von Subklassen ersetzt und erg„nzt
        // werden. Innerhalb der Methoden mssen alle neuen Daten (d.h. die
        // Werte aller neuen Variabeln) gespeichert werden.
        // Sie drfen vom Objekt-Client nicht direkt aufgerufen werden!
};


#endif
/*===================* 
 * End of Persist.H  *
 *===================*/