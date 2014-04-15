/*===========================================================================* 
 *====   KONAS   ============================================================*
 *===========================================================================*
 * FieldPrn.H                                                                *
 *===========================================================================*
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *===========================================================================*/

#ifndef FIELDPRN
#define FIELDPRN


#include "FldPres.H"


class FieldPrint : public /*Field*/Presentation
{
public:
	//=== constructors and destructor =====
	FieldPrint( Field * );
	virtual ~FieldPrint();

//	virtual void print() = 0;
	virtual char *copyPrintString() = 0;

	void disable()
   	{ enabled = False; }

protected:
	boolean enabled;

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


#endif
/*===================* 
 * End of FieldPrn.H *
 *===================*/