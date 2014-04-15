/*****************************************************************************
**                                                                          **
**                                                                          **
**  DOS Form Designer                                                       **
**  =================                                                       **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  tvFormFolder Class                                                      **
**  ------------------                                                      **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvFormFolder                                                  **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFORM.H                                                   **
**                                                                          **
*****************************************************************************/

#ifndef TVFORM
#define TVFORM

#include "tvFolder.H"
#include "FormObj.H"


class tvFormFolder : public tvFolder, public FormObj
{
public:
	tvFormFolder( tvFolder *aFolder );

	virtual void insertObject( tvObject * );

	virtual Boolean handleNotification( TView * );

	virtual void fillDlg();

protected:
	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();

	enum FormType { Formular, Etikette };
	FormType type;
	int number;


public:
	virtual void write( FormDevice * );
    static void blockClosing( FormDevice * );


protected:
	tvFormFolder( StreamableInit );

public:
	static const char * const near name;
	static TStreamable *build();

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


#endif
