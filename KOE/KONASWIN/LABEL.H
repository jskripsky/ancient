/*===========================================================================* 
 *====   KONAS   ============================================================*
 *===========================================================================*
 * Label.H                                                                   *
 *===========================================================================*
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *===========================================================================*/

#ifndef LABEL
#define LABEL


#include "zApp.HPP"
#include "Window.H"
#include "FormDef.H"


class zWindow;
class Field;


class Label : public zStaticText, public Window
{
public:
	//=== constructors and destructor =====
	Label( Field *, zWindow *parent );

	virtual ~Label();

	virtual const char *getClassName();

protected:
	//=== form design / metadata =====

	virtual void adjustzWindowRect();


protected:
	//=== storage (PersistentObject) =====
	//virtual void write( StorageUnit& );
	//virtual void read( StorageUnit& );

	friend Form *createFormDefinition();
};


#endif
/*===================*
 * End of Label.H    *
 *===================*/