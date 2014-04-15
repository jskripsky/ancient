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
**  tvDialog Class                                                          **
**  --------------                                                          **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvDialog                                                      **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVDIALOG.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVDIALOG
#define TVDIALOG

#include "tvFolder.H"
#include "FormObj.H"

class FormDevice;


class tvDialog : public tvFolder, public FormObj
{
public:
	// Basic tvObject Protocol
	// -----------------------

	tvDialog( tvFolder *aFolder );

	// Object Management Protocol
	// --------------------------

	virtual void insertObject( tvObject * );

	// Dialog Protocol
	// ---------------

	virtual Boolean handleNotification( TView * );
	virtual void fillDlg();

	// Folder Protocol
	// ---------------

	virtual int compareWith( tvObject& );

protected:
	// Dialog Protocol
	// ---------------

	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();

	enum Key { NoKey, Shift1, Shift2 };
	Key key;
	int number;


public:
	virtual void write( FormDevice * );


// TStreamable Protocol
// --------------------

protected:
	tvDialog( StreamableInit );

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
