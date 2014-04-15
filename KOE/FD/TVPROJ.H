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


class tvProject : public tvDocument, public FormObj
{
public:
	tvProject( tvFolder *aFolder );

	virtual void insertObject( tvObject * );

	tvFolder *getFieldsFolder();

	void write();

protected:
	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();

	int fieldsFolder;


	virtual void writeDocument( opstream& );
	virtual void readDocument( ipstream& );


public:
	virtual void write( FormDevice * );


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
