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
**  tvMCReaderField Class                                                   **
**  ---------------------                                                   **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvMCReaderField                                               **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVMCRFLD.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVMCRFLD
#define TVMCRFLD

#include "tvField.H"

class CardField;


class tvMCReaderField : public tvField
{
public:
	// Basic tvObject Protocol
	// -----------------------

	tvMCReaderField( tvFolder *aFolder );

	// Dialog Protocol
	// ---------------

	virtual Boolean handleNotification( TView * );

	virtual void fillDlg();


protected:
	// Dialog Protocol
	// ---------------

	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();


	int track;
	int start;
	int end;

	CardField *cardField;


protected:
	virtual void writeDataField( FormDevice * );



// TStreamable Protocol
// --------------------

protected:
	tvMCReaderField( StreamableInit );

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