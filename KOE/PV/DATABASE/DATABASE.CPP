/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database Source File 		    		*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Database\Database.Use"

#define Uses_TStreamableClass

#include "Database\Cache.H"
#include "Database\Database.H"
#include "Database\IdxFile.H"
#include "Database\DataFile.H"
#include "Database\Buffer.H"
#include <TV.H>

#include <String.H>
#include <Dir.H>

#define NumIndexCacheItems      100 //!!!!!!!!!!!!!!!
#define NumDataCacheItems		3 //!!!!!!!!!!!!!!!

#define maxBufferItems			200
__link( RDBIndexFile );
__link( RDBDataFile );


/*---- Constructors, Destructors ---------------*/

TDataBase::TDataBase( const char *aIndexFileName, const char *aDataFileName,
					  ccIndex aMaxSpareRecords ) :
	TSortedCollection( 500, 100 ),
	indexFile( new TDBIndexFile( aIndexFileName, aMaxSpareRecords ) ),
	dataFile( new TDBDataFile( aDataFileName, aMaxSpareRecords ) ),
	indexCache( new TDBCache( indexFile, NumIndexCacheItems ) ),
	dataCache( new TDBCache( dataFile, NumDataCacheItems ) ),
    numBufferItems( 0 )
{
	shouldDelete = False;
	duplicates = True;

	buffer = new TBuffer( sizeof( RecordDescriptor ), maxBufferItems );
}


TDataBase::~TDataBase()
{
	delete indexCache;
	delete dataCache;
	delete indexFile;
	delete dataFile;

//	delete buffer;
}


/*---- Public Methods --------------------------*/

void *TDataBase::entryAt( ccIndex index )
{
	TDBEntry *entry = (TDBEntry *)indexCache->getItem(
		(RecordDescriptor *)TCollection::at( index ) );

	entry->dataBase = this;

	return entry;
}

ccIndex TDataBase::insert( void *item )
{
	TDBEntry *entry = (TDBEntry *)item;
	entry->dataBase = this;

	entry->connectToCache( indexCache );
	entry->record->connectToCache( dataCache );

	dataCache->insertIntoFile( &entry->recordDescriptor, entry->record );

//	RecordDescriptor *descriptor = new RecordDescriptor;
	if( numBufferItems == maxBufferItems )
		{
		buffer = new TBuffer( sizeof( RecordDescriptor ), maxBufferItems );
		numBufferItems = 0;
		}

	RecordDescriptor *descriptor = (RecordDescriptor *)buffer->getArea();
	numBufferItems++;

	indexCache->insertIntoFile( descriptor, entry );

	return TSortedCollection::insert( descriptor );;
}


void *TDataBase::keyOf( void *item )
{
	TDBEntry *entry =
		(TDBEntry *)indexCache->getItem( (RecordDescriptor *)item );
	return entry->getKey();
//	return item;
}


ccIndex TDataBase::reOrder( ccIndex index )
{
	TDBEntry *entry = (TDBEntry *)TSortedCollection::at( index );
	TSortedCollection::atRemove( index );

	return TSortedCollection::insert( entry );
}


void TDataBase::setUpdateFlag( void *item, void *cacheSystem )
{
	((TDBCache *)cacheSystem)->setUpdateFlag( item );
}


/*---- Protected Methods -----------------------*/


TDBRecord *TDataBase::loadRecord( TDBEntry *entry )
{
	return (TDBRecord *)dataCache->getItem( &entry->recordDescriptor );
}


/*---- Private Methods -------------------------*/

void TDataBase::freeItem( void *item )
{
	TDBEntry *entry =
		(TDBEntry *)indexCache->getItem( (RecordDescriptor *)item );

	dataCache->removeFromFile( &entry->recordDescriptor );
	indexCache->removeFromFile( (RecordDescriptor *)item );

//	delete (RecordDescriptor *)item;
//	buffer->releaseArea( item );  // Disabled for Herisau only!!!!!!
}


int TDataBase::compare( void *key1, void *key2 )
{
	char *string1, *string2;
	string1 = strupr( newStr( (char *)key1 ) );
	string2 = strupr( newStr( (char *)key2 ) );

//	string1 = new char[81];
//	string2 = new char[81];

//	TDBEntry *entry1 =
//		(TDBEntry *)indexCache->getItem( (RecordDescriptor *)key1 );
//	((TDBEntry *)entry1)->getKey( string1, 80 );
//
//	TDBEntry *entry2 =
//		(TDBEntry *)indexCache->getItem( (RecordDescriptor *)key2 );
//	((TDBEntry *)entry2)->getKey( string2, 80 );

//	strupr( string1 );
//	strupr( string2 );

	int result = strcmp( string1, string2 );
	delete[] string1;
	delete[] string2;

	return result;
}


/*---- TStreamable Methods ---------------------*/

const char * const TDataBase::name = "TDataBase";


TDataBase::TDataBase( StreamableInit ) :
	TSortedCollection( streamableInit ),
	numBufferItems( 0 )
{
	shouldDelete = False;

	buffer = new TBuffer( sizeof( RecordDescriptor ), maxBufferItems );
}


TStreamable *TDataBase::build()
{
	return new TDataBase( streamableInit );
}


void TDataBase::write( opstream& os )
{
	dataCache->flush();
	os.flush();
	indexCache->flush();
	os.flush();

	TSortedCollection::write( os );
	os.flush();
	os << indexFile;
	os.flush();
	os << dataFile;
	os.flush();
}


void *TDataBase::read( ipstream& is )
{
	TSortedCollection::read( is );
	duplicates = True;
	is >> indexFile;
	is >> dataFile;

	indexCache = new TDBCache( indexFile, NumIndexCacheItems );
	dataCache = new TDBCache( dataFile, NumDataCacheItems );

	return this;
}


void TDataBase::writeItem( void *obj, opstream& os )
{
	os.writeBytes( obj, sizeof( RecordDescriptor ) );
}


void *TDataBase::readItem( ipstream& is )
{
//	RecordDescriptor *descriptor = new RecordDescriptor;
	if( numBufferItems == maxBufferItems )
		{
		buffer = new TBuffer( sizeof( RecordDescriptor ), maxBufferItems );
		numBufferItems = 0;
		}

	RecordDescriptor *descriptor = (RecordDescriptor *)buffer->getArea();
	numBufferItems++;

	is.readBytes( descriptor, sizeof( RecordDescriptor ) );
	return descriptor;
}


TStreamableClass RDataBase( TDataBase::name,
							TDataBase::build,
							__DELTA(TDataBase)
						  );
