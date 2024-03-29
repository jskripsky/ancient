#ifndef PERSIST
#define PERSIST


#include "Types.H"

class StorageUnit;


class PersistentObject
{
public:
	//=== constructors and destructor =====
	PersistentObject();
	virtual ~PersistentObject();

	//virtual const char *getID();
	//virtual void setID( const char *aID );

	virtual const char *getClassName() = 0;
        // Die Methode muss in konkreten Klassen implementiert werden
        // und den Klassen-Name als String liefern.

	void writeToStorage( StorageUnit& );
	void readFromStorage( StorageUnit& );
        // Diese Methoden kann der Client des Objekt aufgerufen, um die Daten
        // dieses Objekts speichern zu lassen.

protected:
	char *id;

	//=== storage =====
	virtual void write( StorageUnit& ) = 0;
	virtual void read( StorageUnit& ) = 0;
        // Diese Methoden m�ssen laufend von Subklassen ersetzt und erg�nzt
        // werden. Innerhalb der Methoden m�ssen alle neuen Daten (d.h. die
        // Werte aller neuen Variabeln) gespeichert werden.
        // Sie d�rfen vom Objekt-Client nicht direkt aufgerufen werden!
};


#endif