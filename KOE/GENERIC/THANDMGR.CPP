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
**  THandleMgr Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Defined classes:                                                        **
**    - Class THandleMgr                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: THANDMGR.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#include "THandMgr.H"
#include "TIntCol.H"

THandleMgr *handleMgr;


THandleMgr::THandleMgr() :
	lastHandle( 0 ),
	freeHandles( new TIntCollection( 10, 5 ) )
	{}


THandleMgr::~THandleMgr()
{
	delete freeHandles;
}


int THandleMgr::createHandle()
{
	int h;
	if( freeHandles->getCount() > 0 )
		{
		h = (int)freeHandles->at( 0 );

		freeHandles->atRemove( 0 );
		return h;
		}
	else
		lastHandle++;

	return lastHandle;
}


void THandleMgr::deleteHandle( int handle )
{
	if( handle < lastHandle )
		freeHandles->insert( (void *)handle );
	else
		{
		lastHandle--;
		while( isHandleFree( lastHandle ) )
			{
			freeHandles->remove( (void *)lastHandle );
			lastHandle--;
			}
		}
}


Boolean THandleMgr::isHandleFree( int handle )
{
	for( int i = 0; i < freeHandles->getCount(); i++ )
		if( (int)freeHandles->at( i ) == handle )
			return True;

	return False;
}


const char *const near THandleMgr::name = "THandleMgr";

TStreamableClass RHandleMgr( THandleMgr::name,
							 THandleMgr::build,
							 __DELTA( THandleMgr )
						   );


THandleMgr::THandleMgr( StreamableInit ) :
	freeHandles( new TIntCollection( 10, 5 ) )
	{}


TStreamable *THandleMgr::build()
{
	return new THandleMgr( streamableInit );
}


void THandleMgr::write( opstream& os )
{
	os << (int)0x0100;

	os << lastHandle;
	os << freeHandles;
}


void *THandleMgr::read( ipstream& is )
{
	int version;
	is >> version;

	is >> lastHandle;
	is >> freeHandles;
	return this;
}
