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
**  TDataCollection Class                                                   **
**  ---------------------                                                   **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TDataCollection                                               **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TDATACOL.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#include "TDataCol.H"


TDataCollection::TDataCollection( ushort aDataSize, ccIndex aLimit,
								  ccIndex aDelta ) :
	TCollection( aLimit, aDelta ),
	dataSize( aDataSize )
{}


void TDataCollection::freeItem( void *item )
{
	delete[] ((char *)item);
}


const char *const near TDataCollection::name = "TDataCollection";

TStreamableClass RDataCollection( TDataCollection::name,
								  TDataCollection::build,
								  __DELTA( TDataCollection )
								);


TDataCollection::TDataCollection( StreamableInit ) :
	TCollection( streamableInit )
	{}


TStreamable *TDataCollection::build()
{
	return new TDataCollection( streamableInit );
}


void *TDataCollection::read( ipstream& is )
{
	is >> dataSize;
	TCollection::read( is );

	return this;
}


void TDataCollection::write( opstream& os )
{
	os << dataSize;
	TCollection::write( os );
}


void *TDataCollection::readItem( ipstream& is )
{
	void *data = new char[dataSize];
	is.readBytes( data, dataSize );

	return data;
}


void TDataCollection::writeItem( void *item, opstream& os )
{
	os.writeBytes( item, dataSize );
}
