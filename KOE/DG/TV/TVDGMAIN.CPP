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
**  tvDGMainFolder                                                          **
**  --------------                                                          **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvDGMainFolder												**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVDGMAIN.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_ifpstream
#include "tvDGMain.H"
#include "tvProj.H"
#include "tvMCProj.H"
#include "TObjColl.H"

#include "tvSysFld.H"
#include "TCard.H"
#include "TLBCol.H"


tvDGMainFolder::tvDGMainFolder() :
	tvMainFolder( "Dialog Generator", True )
{
	loadCard();
	loadCharacters();

	tvObject *systemsFld = new tvSystemsFolder( this );
	objects->insert( systemsFld );
	systemsFolder = systemsFld->getHandle();
}


void tvDGMainFolder::insertObject( tvObject * )
{
#ifndef ULRICH
	tvMainFolder::insertObject( new tvProject( this ) );
#else
	tvMainFolder::insertObject( new tvMCReaderProject( this ) );
#endif
}


tvFolder *tvDGMainFolder::getSystemsFolder()
{
	return (tvFolder *)tvObject::getObject( systemsFolder );
}


void tvDGMainFolder::loadCard()
{
	ifpstream cardFile( "Card.Res", ios::nocreate );
	cardFile >> card;
	cardFile.close();
}


void tvDGMainFolder::loadCharacters()
{
	ifpstream charactersFile( "Chars.Res", ios::nocreate );
	int num;
	charactersFile >> num;

	characters = new TLBCollection( num, 1 );

	for( int i = 0; i < num; i++ )
		characters->insert( charactersFile.readString() );

	charactersFile.close();
}


const char *const near tvDGMainFolder::name = "tvDGMainFolder";

TStreamableClass RtvDGMainFolder( tvDGMainFolder::name,
								  tvDGMainFolder::build,
								  __DELTA( tvDGMainFolder )
								);


tvDGMainFolder::tvDGMainFolder( StreamableInit ) :
	tvMainFolder( streamableInit )
{
	loadCard();
	loadCharacters();
}


TStreamable *tvDGMainFolder::build()
{
	return new tvDGMainFolder( streamableInit );
}


void tvDGMainFolder::write( opstream& os )
{
	tvMainFolder::write( os );

	os << (int)0x0100;

	os << systemsFolder;
}


void *tvDGMainFolder::read( ipstream& is )
{
	tvMainFolder::read( is );

	int version;
	is >> version;

	is >> systemsFolder;
	return this;
}
