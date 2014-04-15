/*****************************************************************************
**                                                                          **
**                                                                          **
**  Form Designer                                                           **
**  =============                                                           **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  FormDevice Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Defined classes:                                                        **
**    - Class FormDevice  											        **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: FORMDEV.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TNSCollection
#include "FormDev.H"
#include "FormObj.H"

#include <FStream.H>
#include <StdLib.H>
#include <String.H>


FormDevice::FormDevice() :
	convertZero( True ),
	customBlocks( new TNSCollection( 5, 1 ) ),
	customBlockClosing( 0 )
{
	*stream << "%&#";
	newLine();
	newLine();
}


FormDevice::~FormDevice()
{
	if( customBlocks->getCount() > 0 )
		writeCustomBlocks();
	delete customBlocks;

	*stream << "%"; newLine();
	*stream << '\x1A';
}


void FormDevice::openBlock( const char *title )
{
	lastTitle = newStr( title );
	*stream << '#';
	*stream << title;
	newLine();
}


void FormDevice::closeBlock()
{
	if( customBlockClosing )
		{
		customBlockClosing( this );
		customBlockClosing = 0;
		}
	else
		standardBlockClosing();

	newLine();
	newLine();

	delete[] lastTitle;
}


void FormDevice::standardBlockClosing()
{
	disableZeroConversion();
	writeByte( 0 );
	enableZeroConversion();
}


void FormDevice::newLine()
{
	*stream << '\r' << '\n';
}


void FormDevice::writeByte( unsigned char value )
{
	if( convertZero && (value == 0) )
		value = 0xF3;

	char string[3];
	itoa( value, string, 16 );

	if( strlen( string ) == 1 )
		{
		string[2] = 0;
		string[1] = string[0];
		string[0] = '0';
		}

	*stream << string << ", ";
}


void FormDevice::writeNumber( int value )
{
	char string[6];
	itoa( value, string, 10 );
	*stream << string << ", ";
}


void FormDevice::writeComment( const char *text )
{
	*stream << "\t * " << text;
}


void FormDevice::registerCustomBlockClosing(
	void (*blockClosing)(FormDevice *) )
{
	customBlockClosing = blockClosing;
}


void FormDevice::addCustomBlock( FormObj *formObj )
{
	customBlocks->insert( formObj );
}


void FormDevice::writeCustomBlocks()
{
	for( int i = 0; i < customBlocks->getCount(); i++ )
		((FormObj *)customBlocks->at( i ))->
			writeCustomBlock( this );
	customBlocks->removeAll();
}
