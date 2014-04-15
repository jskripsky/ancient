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
**  tvDoubleField Class                                                     **
**  -------------------                                                     **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvDoubleField                                                 **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVDFIELD.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVDFIELD
#define TVDFIELD

#include "tvField.H"

class CardField;


class tvDoubleField : public tvField
{
public:
	// Basic tvObject Protocol
	// -----------------------

	tvDoubleField( tvFolder *aFolder );

	// Dialog Protocol
	// ---------------

	virtual Boolean handleNotification( TView * );

	virtual void fillDlg();


protected:
	// Dialog Protocol
	// ---------------

	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();


	int dataFields[2];
	int maxLength;

	CardField *cardFields[2];


protected:
	virtual void writeDataField( FormDevice * );



// TStreamable Protocol
// --------------------

protected:
	tvDoubleField( StreamableInit );

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