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
**  tvFormText Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvFormText                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFRMTXT.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVFRMTXT
#define TVFRMTXT

#include "tvFrmObj.H"


class tvFormText : public virtual tvFormObj
{
public:
	tvFormText( tvFolder *aFolder, const char *aTitle );

	virtual void tvOpen() {};
	virtual Boolean tvClose() { return True; }
	virtual void tvDelete() {};

	virtual Boolean handleNotification( TView * );

	virtual void fillDlg();

protected:
	int font;

	virtual TObjDlg *createDlg();


public:
	virtual void write( FormDevice * );


protected:
	tvFormText( StreamableInit );

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );
};


#endif