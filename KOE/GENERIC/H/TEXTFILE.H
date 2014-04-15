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
**  TextFile Class                                                          **
**  --------------                                                          **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TextFile    											    	**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TEXTFILE.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TEXTFILE
#define TEXTFILE

#include <TV.H>

const	int Word		= 0,
		int Command		= 1,
		int Block		= 2,
		int File		= 3;


class ifstream;

class TextFile
{
public:
	TextFile() {};
	virtual ~TextFile();

	void reset();

	void addCommentStartString( char * );
	void addCommentEndString( char * );

	void addControlString( int Category, char * );
	void clearControlString( int Category, char * );

	void

	Boolean scanForString( char * );

	void setLimitString( char * );
	void clearLimitStrigng();
	void skipLimitString();

	void addWordLimitString( char * );	// usually Space, Comma,...

	void readBlock( char * );	// read until LimitString
	void readWord( char * );


protected:
	ifstream *stream;
};


#endif
