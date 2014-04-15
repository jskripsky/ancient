/*===========================================================================* 
 *====   KONAS   ============================================================*
 *===========================================================================*
 * EFldPrn.H                                                                 *
 *===========================================================================*
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *===========================================================================*/

#ifndef EFLDPRN
#define EFLDPRN


#include "FieldPrn.H"


class EntryFieldPrint : public FieldPrint
{
public:
	//=== constructors and destructor =====
	EntryFieldPrint( Field * );
	virtual ~EntryFieldPrint();

	virtual const char *getClassName();

	//	virtual void print() = 0;
	virtual char *copyPrintString();


protected:
	//=== storage (PersistentObject) =====
//	virtual void write( StorageUnit& );
//	virtual void read( StorageUnit& );
};


#endif
/*===================* 
 * End of EFldPrn.H  *
 *===================*/