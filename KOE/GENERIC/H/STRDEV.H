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
**  Declared classes:                                                       **
**    - Class StreamDevice											    	**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: STRDEV.H                                                   **
**                                                                          **
*****************************************************************************/

#ifndef STRDEV
#define STRDEV

#include <TV.H>


class ofstream;

class StreamDevice
{
public:
	StreamDevice() {};

	StreamDevice( int port );
	StreamDevice( char *fileName );

	virtual ~StreamDevice();

	virtual void writeByte( unsigned char );
	virtual void writeText( const char * );

protected:
	ofstream *stream;
};


#endif
