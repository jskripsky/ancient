/*****************************************************************************
**                                                                          **
**                                                                          **
**  DOS Form Designer                                                       **
**  =================                                                       **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  TNInputLine Classes                                                     **
**  -------------------                                                     **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TNRightJustInputLine                                          **
**    - Class TNNumericInputLine                                            **
**                                                                          **
**                                                                          **
**  Module Name: TNINPUTL.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TEvent
#define Uses_TKeys
#include "TNInputL.H"

#include <String.H>
#include <CType.H>
#include <StdLib.H>


void TNRightJustInputLine::draw()
{
	int length = strlen( data );
	char *oriData = data;
	curPos += maxLen - length;
	selEnd += maxLen - length;
	selStart += maxLen - length;

	char *newData = new char[maxLen + 1];
	memset( newData, ' ', maxLen - length );
	newData[maxLen - length] = 0;

	strcat( newData, oriData );
	data = newData;

	TNInputLine::draw();

	delete[] newData;
	data = oriData;
	curPos -= maxLen - length;
	selEnd -= maxLen - length;
	selStart -= maxLen - length;
}


TNNumericInputLine::TNNumericInputLine( const TRect& bounds, int aMaxLen,
										int aFractionDigits ) :
	TNRightJustInputLine( bounds, aMaxLen ),
	fractionDigits( aFractionDigits )
{
}


void TNNumericInputLine::handleEvent( TEvent& event )
{
	if( ((state & sfSelected) != 0) &&
		(event.what == evKeyDown) )
		switch( ctrlToArrow( event.keyDown.keyCode ) )
			{
			case kbLeft:
			case kbRight:
			case kbHome:
			case kbEnd:
			case kbBack:
			case kbDel:
			case kbIns:
				break;

			default:
				if( (event.keyDown.charScan.charCode >= ' ') &&
					(event.keyDown.charScan.charCode != '.') &&
					!isdigit( event.keyDown.charScan.charCode ) )
					{
					clearEvent( event );
					return;
					}

				int num;
				getData( &num );

				if( (event.keyDown.charScan.charCode == '0') &&
					(num == 0) )
					{
					clearEvent( event );
					return;
					}
		}

	TNRightJustInputLine::handleEvent( event );
}


void TNNumericInputLine::getData( void *rec )
{
	int multiplier = 1;
	for( int i = 0; i < fractionDigits; i++ )
		multiplier *= 10;

	long number = atol( data ) * multiplier;

	char *point = strchr( data, '.' );
	if( point && (multiplier > 1) )
		{
		char *fraction = new char[fractionDigits + 1];
		strncpy( fraction, point + 1, fractionDigits );

		Boolean pastEnd = False;
		for( i = 0; i < fractionDigits; i++ )
			{
			if( fraction[i] == 0 )
				pastEnd = True;

			if( !isdigit( fraction[i] ) || pastEnd )
				fraction[i] = '0';
			}

		fraction[i] = 0;
		number += atol( fraction );
		delete[] fraction;
		}

	long limit = 1;
	for( i = 0; i < maxLen; i++ )
		limit *= 10;

	if( fractionDigits > 0 )
		limit /= 10;

	while( number > limit )
		number /= 10;

	*((int *)rec) = number;
}


void TNNumericInputLine::setData( void *rec )
{
	itoa( *((int *)rec), data, 10 );
	if( fractionDigits > 0 )
		{
		if( strlen( data ) == maxLen )
			data[maxLen - 1] = 0;

		for( int i = strlen( data ); i < (fractionDigits + 1); i++ )
			data[i] = '0';

		data[i + 1] = 0;

		for( int c = 0; c < fractionDigits; c++, i-- )
			data[i] = data[i - 1];

		data[i] = '.';
		}
	drawView();
}


TNHexInputLine::TNHexInputLine( const TRect& bounds, int aMaxLen ) :
	TNRightJustInputLine( bounds, aMaxLen )
{
}


void TNHexInputLine::handleEvent( TEvent& event )
{
	if( ((state & sfSelected) != 0) &&
		(event.what == evKeyDown) )
		switch( ctrlToArrow( event.keyDown.keyCode ) )
			{
			case kbLeft:
			case kbRight:
			case kbHome:
			case kbEnd:
			case kbBack:
			case kbDel:
			case kbIns:
				break;

			default:
				if( ((event.keyDown.charScan.charCode < 'a') ||
					 (event.keyDown.charScan.charCode > 'f')) &&
					((event.keyDown.charScan.charCode < 'A') ||
					 (event.keyDown.charScan.charCode > 'F')) &&
					isalpha( event.keyDown.charScan.charCode ) )
					{
					clearEvent( event );
					return;
					}

				int num;
				getData( &num );

				if( (event.keyDown.charScan.charCode == '0') &&
					(num == 0) )
					{
					clearEvent( event );
					return;
					}
		}

	TNRightJustInputLine::handleEvent( event );
}


void TNHexInputLine::getData( void *rec )
{
	int number = 0;

	int posMultiplier = 1;

	for( int pos = strlen( data ) - 1; pos >= 0; pos-- )
		{
		char temp = data[pos];
		if( isdigit( temp ) )
			temp -= '0';
		else
			if( isupper( temp ) )
				temp -= 'A' - 10;
			else
				temp -= 'a' - 10;

		number += posMultiplier * temp;
		posMultiplier *= 16;
		}

	if( maxLen <= 2 )
		*(unsigned char *)rec = (unsigned char)number;
	else
		*((int *)rec) = number;
}


void TNHexInputLine::setData( void *rec )
{
	char *tempData = new char[maxLen + 1];

	if( maxLen <= 2 )
		itoa( (int)((unsigned char)(*(int *)rec)), tempData, 16 );
	else
		itoa( *((int *)rec), tempData, 16 );

	for( int i = 0; i < maxLen - strlen( tempData ); i++ )
		data[i] = '0';

	data[i] = 0;
	strcat( data, tempData );

	delete[] tempData;

	strupr( data );
	drawView();
}
