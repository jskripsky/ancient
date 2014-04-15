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
**  TUnique Class                                                           **
**  ------------                                                            **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TUnique                                                       **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TUNIQUE.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TNSCollection
#include "TUnique.H"
#include "THandMgr.h"


TNSCollection *TUnique::uniqueObjects = new TNSCollection( 10, 5 );


TUnique::TUnique()
{
	handle = handleMgr->createHandle();
	uniqueObjects->insert( this );
}


TUnique::~TUnique()
{
	uniqueObjects->remove( this );
}


void TUnique::deleteHandle()
{
	handleMgr->deleteHandle( handle );
}


TUnique *TUnique::getObject( int handle )
{
	for( int i = 0; i < uniqueObjects->getCount(); i++ )
		{
		TUnique *obj = (TUnique *)uniqueObjects->at( i );
		if( obj->getHandle() == handle )
			return obj;
		}
	return 0;
}


TUnique::TUnique( StreamableInit )
{
	uniqueObjects->insert( this );
}


void TUnique::write( opstream& os )
{
	os << handle;
}


void *TUnique::read( ipstream& is )
{
	is >> handle;

	if( handle == 0 )
		handle = handleMgr->createHandle();

	return this;
}
