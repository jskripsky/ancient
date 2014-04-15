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
**  tvFormTextField Class                                                   **
**  ---------------------                                                   **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvFormTextField                                               **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFRMTF.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TVFRMTF
#define TVFRMTF

#include "tvFrmFld.H"
#include "tvFrmTxt.H"


class tvFormTextField : public tvFormField, public tvFormText
{
public:
	tvFormTextField( tvFolder *aFolder, const char *aTitle );

	virtual void tvOpen();
	virtual Boolean tvClose();
	virtual void tvDelete();

	virtual void fillDlg();

	virtual Boolean handleNotification( TView * );

protected:
	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();


public:
	virtual void write( FormDevice * );


protected:
	tvFormTextField( StreamableInit );

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
