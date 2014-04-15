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
**  TCard Class                                                             **
**  -----------                                                             **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TCard                                                         **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TCARD.CPP                                                  **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#include "TCard.H"

#include <String.H>


TCard::TCard() :
	TCollection( 16, 1 )
{}


void TCard::freeItem( void *item )
{
	delete (CardField *)item;
}


const char *const near TCard::name = "TCard";

TStreamableClass RTCard( TCard::name,
						 TCard::build,
						 __DELTA( TCard )
					   );


TCard::TCard( StreamableInit ) :
	TCollection( streamableInit )
	{}


TStreamable *TCard::build()
{
	return new TCard( streamableInit );
}


void *TCard::readItem( ipstream& is )
{
	CardField *cardField = new CardField;

	is >> cardField->tag;
	is >> cardField->length;
	is >> (int)cardField->format;

	is.readString( cardField->description, 40 );

	return cardField;
}


void TCard::writeItem( void *item, opstream& os )
{
	CardField *cardField = (CardField *)item;

	os << cardField->tag;
	os << cardField->length;
	os << (int)cardField->format;

	os.writeString( cardField->description );
}


CardField::CardField( int aTag, int aLength, const char *aDescription,
					  Format aFormat ) :
		tag( aTag ),
		length( aLength ),
		format( aFormat )
{
	strcpy( description, aDescription );
}

