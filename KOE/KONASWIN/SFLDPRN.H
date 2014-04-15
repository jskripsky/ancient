/*===========================================================================* 
 *====   KONAS   ============================================================*
 *===========================================================================*
 * SFldPrn.H                                                                 *
 *===========================================================================*
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *===========================================================================*/

#ifndef SFLDPRN
#define SFLDPRN


#include "FieldPrn.H"
#include "FormDef.H"

class EntrySlist;


class SelectionFieldPrint : public FieldPrint
{
public:
	//=== constructors and destructor =====
	SelectionFieldPrint( Field * );
	virtual ~SelectionFieldPrint();

	virtual const char *getClassName();

	//	virtual void print() = 0;
	virtual char *copyPrintString();

protected:
	EntrySlist *list;


protected:
	//=== storage (PersistentObject) =====
//	virtual void write( StorageUnit& );
//	virtual void read( StorageUnit& );

	friend Form *createFormDefinition();
};


#endif
/*===================*
 * End of SFldPrn.H  *
 *===================*/