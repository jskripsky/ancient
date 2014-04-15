/*****************************************************************************
**                                                                          **
**                                                                          **
**  DOS Dialog Generator                                                    **
**  ====================                                                    **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  tvSystemsFolder Class                                                   **
**  ---------------------                                                   **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvSystemsFolder                                               **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVSYSFLD.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVSYSFLD
#define TVSYSFLD

#include "tvStFldr.H"
#include "FormObj.H"

class FormDevice;


class tvSystemsFolder : public tvStaticTitleFolder, public FormObj
{
public:
	tvSystemsFolder( tvFolder *aFolder );

	virtual void insertObject( tvObject * );

	virtual Priority getPriority();

protected:
	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();


public:
	virtual void write( FormDevice * );


protected:
	tvSystemsFolder( StreamableInit );

public:
	static const char * const near name;
	static TStreamable *build();

private:
	virtual const char *streamableName() const
		{ return name; }
};


inline Priority tvSystemsFolder::getPriority()
	{ return High; }


#endif
