/*===========================================================================* 
 *====   KONAS   ============================================================*
 *===========================================================================*
 * Person.H                                                                  *
 *===========================================================================*
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *===========================================================================*/

#ifndef PERSON
#define PERSON


#include "Persist.H"

class Form;
enum Mode { Read, Write };


class Person: public PersistentObject
{
public:
	//=== constructors and destructor =====
	Person();
	virtual ~Person();

        void connectToForm( Form *, boolean newPerson = False );
        void disconnectFromForm( boolean saveNewData = True );

        char *getIndexChainString();
        // Liefert z.B. "MÅller, Peter, 2.10.1950".
        // (Memory Ownership wird an den Objekt-Client Åbertragen.)

protected:
        char **idxStrings;
        // Speichert z.B. "MÅller", "Peter", "2.10.1950".

        //Form *form; // JS: redundant?

        virtual StorageUnit *createDataStorageUnit( Mode );

        virtual readDataIntoForm( StorageUnit& );
        virtual writeDataFromForm( StorageUnit& );

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


#endif
/*===================* 
 * End of Person.H   *
 *===================*/