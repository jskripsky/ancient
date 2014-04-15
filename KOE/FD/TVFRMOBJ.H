/*****************************************************************************
**                                                                          **
**                                                                          **
**  Form Designer                                                           **
**  =============                                                           **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  tvFormObj Class                                                         **
**  ---------------                                                         **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvFormObj                                                     **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFRMOBJ.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVFRMOBJ
#define TVFRMOBJ

#include "Pos.H"
#include "tvObject.H"
#include "FormObj.H"


class tvFormObj : public tvObject, public FormObj
{
public:
	tvFormObj( tvFolder *aFolder, const char *aTitle );

	virtual Boolean handleNotification( TView * );

	virtual void fillDlg();

	virtual int compareWith( tvObject& );

protected:
	Pos pos;
	Pos size;

	virtual TObjDlg *createDlg();


public:
	virtual void write( FormDevice * );


protected:
	tvFormObj( StreamableInit );

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );
};


#endif