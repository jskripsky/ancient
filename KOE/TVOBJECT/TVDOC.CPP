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
**  tvDocument Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvDocument                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVDOC.CPP                                                  **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_ofpstream
#define Uses_ifpstream
#include "tvDoc.H"
#include "TObjColl.H"

#include <String.H>
#include <StdLib.H>
#include <StdIO.H>


// -----------------------
// Basic tvObject Protocol
// -----------------------

tvDocument::tvDocument( tvFolder *aFolder, const char *aTitle,
						Boolean sorted ) :
	tvFolder( aFolder, aTitle, sorted ),
	objectsInMemory( True )
{
	memset( fileName, 0, sizeof( fileName ) );
	strcpy( fileName, "PRJ" );
	char number[5];
	itoa( getHandle(), number, 16 );
	memset( &fileName[3], '0', 5 - strlen( number ) );
	strcat( fileName, number );
	strcat( fileName, ".Fld" );

	writeFile();
}


tvDocument::~tvDocument()
{
	if( !objectsInMemory )
		readFile();
}


void tvDocument::tvOpen()
{
	if( !objectsInMemory )
		readFile();
	tvFolder::tvOpen();
}


Boolean tvDocument::tvClose()
{
	if( tvFolder::tvClose() )
		{
		if( objectsInMemory )
			writeFile();
		return True;
		}
	else
		return False;
}


void tvDocument::tvDelete()
{
	if( !objectsInMemory )
		readFile();
	remove( fileName );
	tvFolder::tvDelete();
}


// -----------------
// Document Protocol
// -----------------

tvDocument *tvDocument::getDocument()
{
	return this;
}


void tvDocument::writeDocument( opstream& os )
{
	os << (int)0x0100;

	tvFolder::write( os );
}


void tvDocument::readDocument( ipstream& is )
{
	int version;
	is >> version;

	tvFolder::read( is );
}


void tvDocument::writeFile()
{
	ofpstream prjFile( fileName, ios::trunc );
	writeDocument( prjFile );
	prjFile.close();
	destroy( objects );
	objectsInMemory = False;
}


void tvDocument::readFile()
{
	ifpstream prjFile( fileName, ios::nocreate );
	readDocument( prjFile );
	prjFile.close();
	objectsInMemory = True;
}


// --------------------
// TStreamable Protocol
// --------------------

tvDocument::tvDocument( StreamableInit ) :
	tvFolder( streamableInit ),
	objectsInMemory( False )
	{}


void tvDocument::write( opstream& os )
{
	tvObject::write( os );

	os << (int)0x0100;

	os.writeString( fileName );
}


void *tvDocument::read( ipstream& is )
{
	tvObject::read( is );

	int version;
	is >> version;

	is.readString( fileName, 13 );

	return this;
}
