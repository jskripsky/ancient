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
**  TObjCollection Classes                                                  **
**  ------------------------                                                **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TObjCollection                                                **
**    - Class TObjSortedCollection                                          **
**                                                                          **
**                                                                          **
**  Module Name: TOBJCOLL.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_TStreamableTypes
#include "TObjColl.H"
#include "tvObject.H"


TObjCollection::TObjCollection( ccIndex aLimit, ccIndex aDelta ) :
	TSortedCollection( aLimit, aDelta )
{
	sorted = False;
	duplicates = True;
}


ccIndex TObjCollection::insert( void *item )
{
	if( sorted )
		return TSortedCollection::insert( item );
	else
		return TCollection::insert( item );
}


ccIndex TObjCollection::indexOf( void *item )
{
	return TCollection::indexOf( item );
}


int TObjCollection::compare( void *key1, void *key2 )
{
	tvObject *obj1 = (tvObject *)key1;
	tvObject *obj2 = (tvObject *)key2;

	if( obj1 == obj2 )
		return 0;

	if( !obj1 )
		return 1;

	if( !obj2 )
		return -1;

	if( obj1->getPriority() != obj2->getPriority() )
		{
		if( obj1->getPriority() < obj2->getPriority() )
			return 1;
		else
			return -1;
		}
	else
		return obj1->compareWith( *obj2 );
}


void TObjCollection::freeItem( void *item )
{
	if( item )
		delete (tvObject *)item;
}


const char *const near TObjCollection::name = "TObjCollection";

TStreamableClass RObjCollection( TObjCollection::name,
								 TObjCollection::build,
								 __DELTA( TObjCollection )
								 );


TObjCollection::TObjCollection( StreamableInit ) :
	TSortedCollection( streamableInit )
	{}


TStreamable *TObjCollection::build()
{
	return new TObjCollection( streamableInit );
}


void TObjCollection::write( opstream& os )
{
	os << (int)0x0100;

	TSortedCollection::write( os );
	os << (int)sorted;
}


void *TObjCollection::read( ipstream& is )
{
	int version;
	is >> version;

	TSortedCollection::read( is );
	is >> (int)sorted;

	return this;
}


void TObjCollection::writeItem( void *item, opstream& ps )
{
//	os << (tvObject *)item;

	P_id_type index;
	tvObject *t = (tvObject *)item;
	if( t == 0 )
		ps.writeByte( pstream::ptNull );
	else
		if( (index = ps.find( t )) != P_id_notFound )
			{
			ps.writeByte( pstream::ptIndexed );
			ps.writeWord( index );
			}
		else
			{
			ps.writeByte( pstream::ptObject );

			ps.writeByte( '[' );
			ps.writeString( t->streamableName() );

//			if( pstream::types->lookup( t->streamableName() ) == 0 )
//				ps->error( peNotRegistered, *t );
//			else
//				{
				ps.registerObject( t );
				t->write( ps );
//				}

			ps.writeByte( ']' );
			}
}


void *TObjCollection::readItem( ipstream& is )
{
//	tvObject *o;
//	is >> o;

	tvObject *t;

	char ch = is.readByte();
	switch( ch )
		{
		case pstream::ptNull:
			t = 0;
			break;
//		case pstream::ptIndexed:
//			{
//			P_id_type index = is.readWord();
//			t = (void *)is.find( index );
//			assert( t != 0 );
//			break;
//			}
		case pstream::ptObject:
			{
			ch = is.readByte();
//			assert( ch == '[' );
			char name[128];
			is.readString( name, sizeof name );
			const TStreamableClass *pc = ipstream::types->lookup( name );

//			if( t == 0 )
				t = (tvObject *)pc->build();

			is.registerObject( (char *)t - pc->delta );
			t->read( is );

			ch = is.readByte();
//			assert( ch == ']' );

//			const TStreamableClass *pc = is.readPrefix();

//			t = is.readData( pc, 0 );
//			is.readSuffix();
			break;
			}
//		default:
//			is.error( pstream::peInvalidType );
//			break;
		}
	return t;

//	return o;
}
