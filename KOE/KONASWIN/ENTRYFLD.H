#ifndef ENTRYFLD
#define ENTRYFLD


#include "Field.H"
#include "FormDef.H"


// Die Klasse "EntryField" realisiert das Textfeld.

// Die zu dieser Klasse geh”rende Anzeige-Klasse ist "EntryFieldWindow"
// ("EFldWin.H").

class EntryField : public Field
{
public:
	//=== constructors and destructor =====
	EntryField();
	virtual ~EntryField();

	virtual const char *getClassName();


	//=== general data handling =====
	virtual void initializeData();

	virtual boolean isFilledIn();

	virtual const char *getString();

	virtual void setToDefault();


	//=== data storage =====
	virtual void writeData( StorageUnit& );
	virtual void readData( StorageUnit& );

	//=== field presentation =====
	virtual Window *createWindow( zWindow *parent );
	virtual FieldPrint *createPrint( const char *printerID );


	//=== data manipulation =====
	virtual void setText( const char *newText );
	virtual const char *getText();
        // Setzt und liefert der aktuellen Text des Feldes.
        // ("Memory Ownership" des gelieferten Strings bei "getText" bleibt
        // bei diesem Objekt.)

        //=== metadata interface =====
	virtual long getMaxTextLength();
        // Liefert die maximale Textl„nge, die dieses Feld erlaubt.

protected:
	char *text;
        // Der Text, der sich im Augenblick in diesem Feld befindet.

protected:
	//=== form design / metadata =====
	long maxTextLength;
        char *defaultText;
        // Default-String dieses Textfelds ("" falls kein Default existiert).  

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );

	friend Form *createFormDefinition();
};


#endif