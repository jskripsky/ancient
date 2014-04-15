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
**  tvFormStaticText Class                                                  **
**  ----------------------                                                  **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvFormStaticText                                              **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFRMSTX.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVFRMSTX
#define TVFRMSTX

#include "tvFrmTxt.H"


class tvFormStaticText : public tvFormText
{
public:
	tvFormStaticText( tvFolder *aFolder, const char *aTitle );
	~tvFormStaticText();

	virtual void tvOpen();
	virtual void tvDelete();

	virtual void fillDlg();

	virtual Boolean handleNotification( TView * );

protected:
	char *text;

	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();


public:
	virtual void write( FormDevice * );


protected:
	tvFormStaticText( StreamableInit );

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
