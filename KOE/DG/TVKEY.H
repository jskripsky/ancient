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
**  tvKey Class                                                             **
**  -----------                                                             **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvKey                                                         **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVKEY.H                                                    **
**                                                                          **
*****************************************************************************/

#ifndef TVKEY
#define TVKEY

#include "tvObject.H"
#include "FormObj.H"

class FormDevice;

enum Type { Character, ScanCode };


class tvKey : public tvObject, public FormObj
{
public:
	// Basic tvObject Protocol
	// -----------------------

	tvKey( tvFolder *aFolder );

	// Dialog Protocol
	// ---------------

	virtual Boolean handleNotification( TView * );
	virtual void fillDlg();

protected:
	// Dialog Protocol
	// ---------------

	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();


	Type type;

	int character;
	char scanCode;


public:
	virtual void write( FormDevice * );



// TStreamable Protocol
// --------------------

protected:
	tvKey( StreamableInit );

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