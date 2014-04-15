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
**  tvMainFolder Class                                                      **
**  ------------------                                                      **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvMainFolder                                                  **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVMAINFL.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TProgram
#define Uses_TApplication
#define Uses_TEvent
#define Uses_TStreamableClass
#include "tvMainFl.H"
#include "tvDoc.H"
#include "HelpCtx.H"


tvMainFolder *mainFolder = 0;

// -----------------------
// Basic tvObject Protocol
// -----------------------

tvMainFolder::tvMainFolder( const char *aTitle, Boolean sorted ) :
	tvStaticTitleFolder( 0, aTitle, sorted )
{
	mainFolder = this;
}


Boolean tvMainFolder::tvClose()
{
	if( tvStaticTitleFolder::tvClose() )
		{
		TEvent event;
		event.what = evCommand;
		event.message.command = cmQuit;
		event.message.infoPtr = 0;
		TProgram::application->putEvent( event );
		return True;
		}
	else
		return False;
}


// ---------------
// Dialog Protocol
// ---------------

TObjDlg *tvMainFolder::createDlg()
{
	return( new TSTFolderDlg( TRect( 1, 3, 27, 19 ), this ) );
}


ushort tvMainFolder::getHelpCtx()
	{ return hcMainFolder; }


// -----------------
// Document Protocol
// -----------------

tvDocument *tvMainFolder::getDocument()
{
	return 0;
}


// --------------------
// TStreamable Protocol
// --------------------

const char *const near tvMainFolder::name = "tvMainFolder";

TStreamableClass RtvMainFolder( tvMainFolder::name,
								tvMainFolder::build,
								__DELTA( tvMainFolder )
							  );


tvMainFolder::tvMainFolder( StreamableInit ) :
	tvStaticTitleFolder( streamableInit )
{
	mainFolder = this;
	folder = 0;
}


TStreamable *tvMainFolder::build()
{
	return new tvMainFolder( streamableInit );
}


void tvMainFolder::write( opstream& os )
{
	tvStaticTitleFolder::write( os );

	os << (int)0x0100;
}


void *tvMainFolder::read( ipstream& is )
{
	tvStaticTitleFolder::read( is );

	int version;
	is >> version;

	return this;
}
