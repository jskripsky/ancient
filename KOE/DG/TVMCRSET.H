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
**  tvMCReaderSettings Class                                                **
**  ------------------------                                                **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvMCReaderSettings                                            **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVMCRSET.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVMCRSET
#define TVMCRSET

#include "tvObject.H"
#include "FormObj.H"


#define NumTracks		3

class FormDevice;

class tvMCReaderSettings : public tvObject, public FormObj
{
public:
	// Basic tvObject Protocol
	// -----------------------

	tvMCReaderSettings( tvFolder *aFolder );

	// Folder Protocol
	// ---------------

	virtual Priority getPriority();


	// Dialog Protocol
	// ---------------

	virtual Boolean handleNotification( TView * );
	virtual void fillDlg();

protected:
	// Dialog Protocol
	// ---------------

	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();


	enum MCReaderType
		{ Track1, Track2, Track3, Track12, Track23, Track123 }
		mcReaderType;

	Boolean tracks[NumTracks];


public:
	virtual void write( FormDevice * );

	static void blockClosing( FormDevice * );


// TStreamable Protocol
// --------------------

protected:
	tvMCReaderSettings( StreamableInit );

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


inline Priority tvMCReaderSettings::getPriority()
	{ return High; }


#endif