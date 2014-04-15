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
**  tvSystemsFolder Class                                                   **
**  ---------------------                                                   **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvSystemsFolder                                               **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVSYSFLD.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#include "tvSysFld.H"
#include "tvSystem.H"
#include "HelpCtx.H"
#include "FormDlg.H"
#include "TObjColl.H"

#include <String.H>


tvSystemsFolder::tvSystemsFolder( tvFolder *aFolder ) :
#ifndef ULRICH
	tvStaticTitleFolder( aFolder, "Systeme", True )
#else
	tvStaticTitleFolder( aFolder, "Terminalscancodes", True )
#endif
{
	setAttribute( oaDeletable, False );
}


void tvSystemsFolder::insertObject( tvObject * )
{
	tvStaticTitleFolder::insertObject( new tvSystem( this ) );
}


TObjDlg *tvSystemsFolder::createDlg()
{
	return( new TSTFolderDlg( TRect( 1, 1, 27, 21 ), this ) );
}


ushort tvSystemsFolder::getHelpCtx()
	{ return hcSystemsFolder; }


void tvSystemsFolder::write( FormDevice *formDevice )
{
	for( int i = 0; i < objects->getCount(); i++ )
		{
		tvSystem *formObj = (tvSystem *)objects->at( i );
		if( formObj )
			formObj->write( formDevice );
		}
}


const char *const near tvSystemsFolder::name = "tvSystemsFolder";

TStreamableClass RtvSystemsFolder( tvSystemsFolder::name,
								   tvSystemsFolder::build,
								   __DELTA( tvSystemsFolder )
								 );


tvSystemsFolder::tvSystemsFolder( StreamableInit ) :
	tvStaticTitleFolder( streamableInit )
	{}


TStreamable *tvSystemsFolder::build()
{
	return new tvSystemsFolder( streamableInit );
}
