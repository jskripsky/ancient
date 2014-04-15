#ifndef FLDPRES
#define FLDPRES


#include "Present.H"

class Field;

// "FieldPresentation" enth„lt Variabeln und Methoden, die sowohl in
// den Feld-Anzeige-Klassen als auch in den Feld-Druck-Klassen vorkommen.

// (Im Augenblick gibt es aber keine derartigen Methoden oder Variabeln,
// die nicht schon in "Presentation" enthalten sind).


class FieldPresentation : virtual public Presentation
{
public:
	//=== constructors and destructor =====
	FieldPresentation( DataObject * );
	virtual ~FieldPresentation();


protected:
	Field *getField();


protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


inline Field *FieldPresentation::getField()
	{ return (Field *)getDataObject(); }


#endif