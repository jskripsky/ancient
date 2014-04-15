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
**  Dialog Class                                                            **
**  ------------                                                            **
**                                                                          **
**  Declared classes:                                                       **
**    - Class Dialog     												    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: DIALOG.H                                                   **
**                                                                          **
*****************************************************************************/

#ifndef DIALOG
#define DIALOG

#include "StrDev.H"

class Dialog : public virtual StreamDevice
{
public:
	Dialog();

	virtual void sendField( int field, int start, int end );
	virtual void sendNumericField( int field, int start, int end );
	virtual void sendCompoundField( int field1, int field2, int maxLength );

	virtual void sendMCReaderField( int track, int start, int end );

	virtual void sendKey( char character );
	virtual void sendKeyByScanCode( char scanCode );

	virtual void registerScanCode( char *scanCode, Boolean shift );
};


#endif
