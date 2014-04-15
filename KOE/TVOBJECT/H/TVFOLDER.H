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
**  tvFolder Class                                                          **
**  --------------                                                          **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvFolder                                                      **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFOLDER.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVFOLDER
#define TVFOLDER

#include "tvObject.H"


const int
	oaNew			= 1 << 0,
	oaEdit			= 1 << 1,
	oaMove			= 1 << 2,
	oaDelete		= 1 << 3;


class TObjCollection;
class TNSCollection;

class tvFolder : public tvObject
{
public:
	// Basic tvObject Protocol
	// -----------------------

	tvFolder( tvFolder *aFolder, const char *aTitle,
			  Boolean sorted = False );
	virtual ~tvFolder();

	virtual void tvDelete();

	// Object Management Protocol
	// --------------------------

	virtual void insertObject( tvObject * );
	virtual void editObject();
	virtual void deleteObject();

	virtual int getObjectActions();

	virtual Boolean isObjectDeletable();

	virtual TObjCollection *getObjects();

	// Dialog Protocol
	// ---------------

	virtual void fillDlg();

	virtual void update( tvObject * );

	virtual Boolean startMoveObject();
	virtual void endMoveObject();


protected:
	// Object Management Protocol
	// --------------------------

	int selectClass( TNSCollection *classes );

	// Dialog Protocol
	// ---------------

	virtual TObjDlg *createDlg();

protected:
	TObjCollection *objects;
	tvObject *movingObject;


// TStreamable Protocol
// --------------------

protected:
	tvFolder( StreamableInit );

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );
};


#endif
