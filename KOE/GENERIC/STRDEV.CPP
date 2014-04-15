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
**  StreamDevice Class                                                      **
**  ------------------                                                      **
**                                                                          **
**  Defined classes:                                                        **
**    - Class StreamDevice											    	**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: STRDEV.CPP                                                 **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#include "StrDev.H"

#include <FStream.H>
#include <String.H>


StreamDevice::StreamDevice( int port )
{
	char fileName[5];
	if( port == 0 )
		strcpy( fileName, "NUL" );
	else
		{
		if( port <= 3 )
			strcpy( fileName, "LPTx" );
		else
			{
			strcpy( fileName, "COMx" );
			port -= 3;
			}

		fileName[3] = (char)port + '0';
		}

	stream = new ofstream( fileName, ios::out | ios::binary | ios::trunc );
}


StreamDevice::StreamDevice( char *fileName )
{
	stream = new ofstream( fileName, ios::out | ios::binary | ios::trunc );
}


StreamDevice::~StreamDevice()
{
	stream->close();
	delete stream;
}


void StreamDevice::writeByte( unsigned char byte )
{
	*stream << byte;
}


void StreamDevice::writeText( const char *text )
{
	*stream << text;
}
