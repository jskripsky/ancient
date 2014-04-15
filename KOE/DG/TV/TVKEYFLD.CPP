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
**  tvKeyFolder Class                                                       **
**  -----------------                                                       **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvKeyFolder                                                   **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVKEYFLD.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#include "tvKeyFld.H"
#include "tvKey.H"
#include "HelpCtx.H"


tvKeyFolder::tvKeyFolder( tvFolder *aFolder ) :
#ifndef ULRICH
	tvStaticTitleFolder( aFolder, "Tasten", False )
#else
	tvStaticTitleFolder( aFolder, "Tastendefinitionen", False )
#endif
{
	setAttribute( oaDeletable, False );
}


void tvKeyFolder::insertObject( tvObject * )
{
	tvStaticTitleFolder::insertObject( new tvKey( this ) );
}


TObjDlg *tvKeyFolder::createDlg()
{
	return( new TSTFolderDlg( TRect( 1, 1, 27, 21 ), this ) );
}


ushort tvKeyFolder::getHelpCtx()
	{ return hcKeyFolder; }


const char *const near tvKeyFolder::name = "tvKeyFolder";

TStreamableClass RtvKeyFolder( tvKeyFolder::name,
							   tvKeyFolder::build,
							   __DELTA( tvKeyFolder )
							 );


tvKeyFolder::tvKeyFolder( StreamableInit ) :
	tvStaticTitleFolder( streamableInit )
	{}


TStreamable *tvKeyFolder::build()
{
	return new tvKeyFolder( streamableInit );
}
