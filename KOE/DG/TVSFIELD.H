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
**  tvSingleField Class                                                     **
**  -------------------                                                     **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvSingleField                                                 **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVSFIELD.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVSFIELD
#define TVSFIELD

#include "tvField.H"

class CardField;


class tvSingleField : public tvField
{
public:
	// Basic tvObject Protocol
	// -----------------------

	tvSingleField( tvFolder *aFolder );

	// Dialog Protocol
	// ---------------

	virtual Boolean handleNotification( TView * );

	virtual void fillDlg();


protected:
	// Dialog Protocol
	// ---------------

	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();


	int dataField;
	int start;
	int end;
	Boolean numeric;

	CardField *cardField;


protected:
	virtual void writeDataField( FormDevice * );



// TStreamable Protocol
// --------------------

protected:
	tvSingleField( StreamableInit );

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