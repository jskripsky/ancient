#ifndef MLEFLD
#define MLEFLD


#include "Field.H"


// Die Klasse "MLEField" realisiert das mehrzeilige Textfeld.

// Die zu dieser Klasse geh”rende Anzeige-Klasse ist "MLEFieldWindow"
// ("MLEFWin.H").

// (MLE: Multi Line Entry)

struct Line
{
        char *text;
        boolean carriageReturn;
}

class MLEField : public Field
{
public:
	//=== constructors and destructor =====
	MLEField();
	virtual ~MLEField();

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
	virtual Window *createWindow( void *parent );
        //virtual FieldPrinter *createPrinter( const char *printerID );


	//=== data manipulation =====

        //=== metadata interface =====
	virtual long getMaxTextLength();
        // Liefert die maximale Textl„nge, die dieses Feld erlaubt.

protected:
	Line *lines;
        // Der Text, der sich im Augenblick in diesem Feld befindet.

protected:
	//=== form design / metadata =====
        long lineLength;
	long maxTextLength;

        char *defaultText;
        // Default-String dieses MLE-Felds ("" falls kein Default existiert).  

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


#endif