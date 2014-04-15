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
**  TIntCollection Class                                                    **
**  --------------------                                                    **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TIntCollection                                                **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TINTCOL.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#include "TIntCol.H"


TIntCollection::TIntCollection( ccIndex aLimit, ccIndex aDelta ) :
	TCollection( aLimit, aDelta )
{
	shouldDelete = False;
}


const char *const near TIntCollection::name = "TIntCollection";

TStreamableClass RIntCollection( TIntCollection::name,
								 TIntCollection::build,
								 __DELTA( TIntCollection )
							   );


TIntCollection::TIntCollection( StreamableInit ) :
	TCollection( streamableInit )
	{}


TStreamable *TIntCollection::build()
{
	return new TIntCollection( streamableInit );
}


void *TIntCollection::readItem( ipstream& is )
{
	int i;
	is >> i;
	return (void *)i;
}


void TIntCollection::writeItem( void *item, opstream& os )
{
	os << (int)item;
}
