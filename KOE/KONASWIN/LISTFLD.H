#ifndef LISTFLD
#define LISTFLD


#include "Field.H"

class EntrySlist;
class EntrySlistIter;


// "ListField" ist die Grundklasse fÅr alle Feld-Klassen, die eine Auswahl
// (meistens ein Element) aus einer Liste von Elementen zulassen.

// (Bildschirm: RadioButtons/ListBox)


struct Entry
{
        long handle;
        char *string;
};

class ListField : public Field
{
public:
	//=== constructors and destructor =====
	ListField();
	virtual ~ListField();


	//=== data manipulation =====
	EntrySlistIter *getListIterator();

protected:
	EntrySlist *list;


protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );

};


#endif