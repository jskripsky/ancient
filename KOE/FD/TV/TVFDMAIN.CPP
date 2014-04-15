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
**  tvFDMainFolder                                                          **
**  --------------                                                          **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvFDMainFolder												**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFDMAIN.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#include "tvFDMain.H"
#include "tvProj.H"


void tvFDMainFolder::insertObject( tvObject * )
{
	tvMainFolder::insertObject( new tvProject( this ) );
}


const char *const near tvFDMainFolder::name = "tvFDMainFolder";

TStreamableClass RtvFDMainFolder( tvFDMainFolder::name,
								  tvFDMainFolder::build,
								  __DELTA( tvFDMainFolder )
								);


tvFDMainFolder::tvFDMainFolder( StreamableInit ) :
	tvMainFolder( streamableInit )
	{}


TStreamable *tvFDMainFolder::build()
{
	return new tvFDMainFolder( streamableInit );
}


void tvFDMainFolder::write( opstream& os )
{
	os << (int)0x0100;

	tvMainFolder::write( os );
}


void *tvFDMainFolder::read( ipstream& is )
{
	int version;
	is >> version;

	tvMainFolder::read( is );
	return this;
}
