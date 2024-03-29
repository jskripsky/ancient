#ifndef SELFLD
#define SELFLD


#include "ListFld.H"


// "SelectionField" ist die Klasse des sogenannten Auswahlfelds.
// Bei diesem Feld darf zu jedem Zeitpunkt ein einziges Element der Liste
// gew�hlt (markiert) sein.

// Wichtig: Obwohl w�hrend der Life-Time dieser Objekte die Eintragsnummer
// des gew�hlten Elements gespeichert wird, wird bei der permanenten
// Datenspeicherung ("writeData") das "Handle" des Eintrags ("entry::handle)
// an die StorageUnit �bergeben.
// Dies erlaubt das nachtr�gliche Erg�nzen und �ndern der Liste (die ein Teil
// der Anpassungs-Daten ist).


class SelectionField : public ListField
{
public:
	//=== constructors and destructor =====
	SelectionField();
	virtual ~SelectionField();

	virtual const char *getClassName();

	//=== general data handling =====
	boolean isFilledIn();

	virtual const char *getString();

	virtual void setToDefault();
	virtual boolean validate();


	//=== data storage =====
	virtual void writeData( StorageUnit& );
	virtual void readData( StorageUnit& );

	//=== field presentation =====
	virtual Window *createWindow( void *parent );
	virtual Printer *createPrinter( const char *printerID );


	//=== data manipulation =====
	void setSelection( long number );
	long getSelection();

protected:
	long selection;
        // Die aktuelle Auswahl des Felds.


protected:
	//=== form design / metadata =====
	long defaultSelection;
        // "setToDefault" scrhreibt diesen Wert in die Variable "selection"

	long noSelection;
        // Ist beim Aufruf von "isFilledIn" selection == noSelection liefert
        // die Methode "False" zur�ck.

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );

};


#endif