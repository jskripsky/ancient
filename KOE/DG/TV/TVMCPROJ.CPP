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
**  tvMCReaderProject Class                                                 **
**  -----------------------                                                 **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvMCReaderProject                                             **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVMCPROJ.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#include "tvMCProj.H"
#include "TProjDlg.H"
#include "TObjColl.H"
#include "HelpCtx.H"
#include "tvDialog.H"
#include "tvMCRSet.H"


tvMCReaderProject::tvMCReaderProject( tvFolder *aFolder ) :
	tvProject( aFolder )
{
	if( !objectsInMemory )
		readFile();

	objects->insert( new tvDialog( this ) );
	objects->insert( new tvMCReaderSettings( this ) );

	writeFile();
}


int tvMCReaderProject::getObjectActions()
{
	return tvProject::getObjectActions() & ~oaNew & ~oaDelete;
}


TObjDlg *tvMCReaderProject::createDlg()
{
	return( new TProjectDlg( TRect( 1, 1, 28, 21 ), this ) );
}


ushort tvMCReaderProject::getHelpCtx()
	{ return hcProject; }


void tvMCReaderProject::writeObjects( FormDevice *formDevice )
{
	((tvMCReaderSettings *)objects->at( 0 ))->write( formDevice );
	((tvDialog *)objects->at( 2 ))->write( formDevice );
}


const char *const near tvMCReaderProject::name = "tvDGMCReaderProject";

TStreamableClass RtvMCReaderProject( tvMCReaderProject::name,
									 tvMCReaderProject::build,
									 __DELTA( tvMCReaderProject )
								   );


tvMCReaderProject::tvMCReaderProject( StreamableInit ) :
	tvProject( streamableInit )
	{}


TStreamable *tvMCReaderProject::build()
{
	return new tvMCReaderProject( streamableInit );
}


void tvMCReaderProject::write( opstream& os )
{
	tvProject::write( os );

	os << (int)0x0100;
}


void *tvMCReaderProject::read( ipstream& is )
{
	tvProject::read( is );

	int version;
	is >> version;

	return this;
}
