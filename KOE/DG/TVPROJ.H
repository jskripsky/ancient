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
**  tvProject Class                                                         **
**  ---------------                                                         **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvProject                                                     **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVPROJ.H                                                   **
**                                                                          **
*****************************************************************************/

#ifndef TVPROJ
#define TVPROJ

#include "tvDoc.H"
#include "FormObj.H"

class FormDevice;


class tvProject : public tvDocument, public FormObj
{
public:
	tvProject( tvFolder *aFolder );

	virtual void insertObject( tvObject * );


	void write();

	tvFolder *getKeyFolder();


protected:
	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();

	int keyFolder;


public:
	virtual void write( FormDevice * );

protected:
	virtual void writeObjects( FormDevice * );


protected:
	tvProject( StreamableInit );

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
