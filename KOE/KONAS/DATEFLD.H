#ifndef DATEFLD
#define DATEFLD


#include "Field.H"
#include "Date.H"


// Datumfeld.


class DateField : public Field
{
public:
	//=== constructors and destructor =====
	DateField();
	virtual ~DateField();

	virtual const char *getClassName();

	//=== general data handling =====
	virtual void initializeData();

	virtual boolean isFilledIn();
        // (Liefert in dieser Klasse den Wert der Variable "filledIn".)

	virtual const char *getString();

	virtual void setToDefault();


	//=== data storage =====
	virtual void writeData( StorageUnit& );
	virtual void readData( StorageUnit& );

	//=== field presentation =====
	virtual Window *createWindow( void *parent );
	virtual Printer *createPrinter( const char *printerID );


	//=== user data manipulation =====
	virtual boolean setDate( long year, Month month, char day );
        // Der Benutzer hat die Eingabe des Datums abgeschlossen. Es wird
        // nun an dieses Datenobjekt gesandt. ("filledIn" wird automatisch
        // auf "True" gestellt).

	virtual void getDate( long *year, Month *month, char *day );
        // Liefert das in diesem Feld gespeicherte Datum, indem es in die
        // �bergebenen Speicherpl�tze kopiert wird.

        virtual void clearDate();
        // Muss aufgerufen werden, sobald der Benutzer beginnt, das Datum
        // am Bildschirm zu editieren. Solange das Datum am Bildschirm nicht
        // vollst�ndig ist (z.B. "1.9" "3.8.192"), muss "filledIn" "False" sein.
        // Diese Methode setzt "filledIn" auf "False".

protected:
	Date date;

	boolean filledIn;
        // Solange dieses Feld-Objekt kein vollst�ndiges Datum enth�lt (es
        // wurde also "clearDate" und aber seitdem "setDate" noch nicht
        // aufgerufen), steht in dieser Variable "False".
};


#endif