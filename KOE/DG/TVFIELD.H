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
**  tvField Class                                                           **
**  -------------                                                           **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvField                                                       **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFIELD.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TVFIELD
#define TVFIELD

#include "tvObject.H"
#include "FormObj.H"

class FormDevice;
class TCard;

#define numDistinctKeys		6

enum Time { Before, After };


class tvField : public tvObject, public FormObj
{
public:
	// Basic tvObject Protocol
	// -----------------------

	tvField( tvFolder *aFolder, const char *aTitle );

	// Dialog Protocol
	// ---------------

	virtual Boolean handleNotification( TView * );

	virtual void fillDlg();

	// Shadow Protocol
	// ---------------

	virtual void invalidateShadow( tvObject *shadow );


protected:

	struct Key
		{
		int handle;
		int times;
		} keys[2][numDistinctKeys];

	TCard *card;

	Boolean init;


public:
	virtual void write( FormDevice * );

protected:
	virtual void writeDataField( FormDevice * ) = 0;



// TStreamable Protocol
// --------------------

protected:
	tvField( StreamableInit );

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );
};


#endif