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
**  tvMCReaderProject Class                                                 **
**  -----------------------                                                 **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvMCReaderProject                                             **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVMCPROJ.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVMCPROJ
#define TVMCPROJ

#include "tvProj.H"


class tvMCReaderProject : public tvProject
{
public:
	tvMCReaderProject( tvFolder *aFolder );

	virtual int getObjectActions();

protected:
	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();


protected:
	virtual void writeObjects( FormDevice * );


protected:
	tvMCReaderProject( StreamableInit );

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
