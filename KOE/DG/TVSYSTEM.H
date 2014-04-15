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
**  tvSystem Class                                                          **
**  --------------                                                          **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvSystem                                                      **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVSYSTEM.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVSYSTEM
#define TVSYSTEM

#include "tvObject.H"
#include "FormObj.H"

class FormDevice;

#define BytesPerCharacter	4
#define NumCharacters		128

struct Character
{
	uchar bytes[BytesPerCharacter];
	Boolean shift;
	char comment[31];

};


class tvSystem : public tvObject, public FormObj
{
public:
	// Basic tvObject Protocol
	// -----------------------

	tvSystem( tvFolder *aFolder );

	virtual void tvOpen();
	virtual Boolean tvClose();


	// Dialog Protocol
	// ---------------

	virtual Boolean handleNotification( TView * );
	virtual void fillDlg();
	virtual void undoDlg();


    void importSystem();


protected:
	// Dialog Protocol
	// ---------------

	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();


	char ID[21];

	int character;

	Character characters[NumCharacters];

	void *charsUndoData;


public:
	virtual void write( FormDevice * );

	static void blockClosing( FormDevice * );


// TStreamable Protocol
// --------------------

protected:
	tvSystem( StreamableInit );

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