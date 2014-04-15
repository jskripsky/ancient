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
**  tvDocument Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvDocument                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVDOC.H                                                    **
**                                                                          **
*****************************************************************************/

#ifndef TVDOC
#define TVDOC

#include "tvFolder.H"


class tvDocument : public tvFolder
{
public:
	// Basic tvObject Protocol
	// -----------------------

	tvDocument( tvFolder *aFolder, const char *aTitle,
				Boolean sorted = False );
	virtual ~tvDocument();

	virtual void tvOpen();
	virtual Boolean tvClose();
	virtual void tvDelete();

	// Object Management Protocol
	// --------------------------

	virtual void insertObject( tvObject * ) = 0;

	// Document Protocol
	// -----------------

    Boolean isDocumentLoaded();

	void writeFile();
	void readFile();

	virtual tvDocument *getDocument();

protected:
	// Document Protocol
	// -----------------

	virtual void writeDocument( opstream& );
	virtual void readDocument( ipstream& );

	char fileName[13];
	Boolean objectsInMemory;


// TStreamable Protocol
// --------------------

protected:
	tvDocument( StreamableInit );

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );
};


inline Boolean tvDocument::isDocumentLoaded()
	{ return objectsInMemory; }


#endif
