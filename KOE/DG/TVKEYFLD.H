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
**  tvKeyFolder Class                                                       **
**  -----------------                                                       **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvKeyFolder                                                   **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVKEYFLD.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVKEYFLD
#define TVKEYFLD

#include "tvStFldr.H"


class tvKeyFolder : public tvStaticTitleFolder
{
public:
	tvKeyFolder( tvFolder *aFolder );

	virtual void insertObject( tvObject * );

	virtual Priority getPriority();

protected:
	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();


protected:
	tvKeyFolder( StreamableInit );

public:
	static const char * const near name;
	static TStreamable *build();

private:
	virtual const char *streamableName() const
		{ return name; }
};


inline Priority tvKeyFolder::getPriority()
	{ return High; }


#endif
