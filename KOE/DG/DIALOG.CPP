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
**  Defined classes:                                                        **
**    - Class Dialog     												    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: DIALOG.CPP                                                 **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#include "Dialog.H"

#define ScanCodeTag1		0xFD
#define ScanCodeTag2		0xFD

#define FieldStartTag		0xFC
#define NormalFieldTag		0xFA
#define CompoundFieldTag    0xFB
#define NumericFieldTag		0xF0


Dialog::Dialog()
{
}


void Dialog::sendField( int field, int start, int end )
{
	writeByte( FieldStartTag );
	writeByte( NormalFieldTag );

	writeByte( (char)field );
	writeByte( (char)start );
	writeByte( (char)end );
}


void Dialog::sendNumericField( int field, int start, int end )
{
	writeByte( FieldStartTag );
	writeByte( NumericFieldTag );

	writeByte( (char)field );
	writeByte( (char)start );
	writeByte( (char)end );
}


void Dialog::sendCompoundField( int field1, int field2, int maxLength )
{
	writeByte( FieldStartTag );
	writeByte( CompoundFieldTag );

	writeByte( (char)field1 );
	writeByte( (char)field2 );
	writeByte( (char)maxLength );
}


void Dialog::sendMCReaderField( int track, int start, int end )
{
	writeByte( 0xFE );
	writeByte( 0xFA );

	writeByte( (char)track );

	writeByte( (char)start );
	writeByte( (char)end );
}


void Dialog::sendKey( char character )
{
	writeByte( character );
}


void Dialog::sendKeyByScanCode( char scanCode )
{
	writeByte( ScanCodeTag1 );
	writeByte( ScanCodeTag2 );
	writeByte( scanCode );
}


void Dialog::registerScanCode( char *scanCode, Boolean shift )
{
	for( int i = 0; i < 4; i++ )
		writeByte( scanCode[i] );

	if( shift )
		writeByte( 1 );
	else
		writeByte( 0 );
}
