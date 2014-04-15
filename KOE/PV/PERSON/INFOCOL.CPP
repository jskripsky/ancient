/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Person Info Collection Source File		*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "FormDef\FormDef.Use"

#define Uses_TStreamableClass
#define Uses_TProgram

#include <TV.H>
#include "Person\InfoCol.H"
#include "FormDef\FormDef.H"
#include "Database\DataBase.H"
#include "Database\Buffer.H"

#include <String.H>


int TInfoCollection::instances = 0;
TBuffer *TInfoCollection::buffers[10];

static ushort itemCounter;

/*---- Constructors, Destructors ---------------*/

TInfoCollection::TInfoCollection() :
	TCollection( 10, 0 )
{
	shouldDelete = False;

	init();

	for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
		{
		stringItem *strItem = formDef->infoHead->at( i );
		char *string = (char *)buffers[i]->getArea();
		memset( string, 0, strItem->maxLen + 1 );
		insert( string );
		}
}


TInfoCollection::~TInfoCollection()
{
	for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
		{
		buffers[i]->releaseArea( at( 0 ) );
		atRemove( 0 );
		}

	instances--;

	if( instances == 0 )
		for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
			delete buffers[i];
}


void TInfoCollection::init()
{
	if( instances == 0 )
		for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
			{
			stringItem *strItem = formDef->infoHead->at( i );
			buffers[i] = new TBuffer( strItem->maxLen + 1, 60 );
			}

	instances++;
}


/*---- TStreamable Methods ---------------------*/

const char * const TInfoCollection::name = "TInfoCollection";

TInfoCollection::TInfoCollection( StreamableInit ) :
	TCollection( streamableInit )
{
	shouldDelete = False;

	init();
}


TStreamable *TInfoCollection::build()
{
	return new TInfoCollection( streamableInit );
}


void TInfoCollection::write( opstream& os )
{
	itemCounter = 0;
	TCollection::write( os );
}


void *TInfoCollection::read( ipstream& is )
{
	itemCounter = 0;
	TCollection::read( is );
	return this;
}


void TInfoCollection::writeItem( void *obj, opstream& os )
{
	stringItem *strItem = formDef->infoHead->at( itemCounter );
	os.writeBytes( (char *)obj, strItem->maxLen + 1 );

	itemCounter++;
}


void *TInfoCollection::readItem( ipstream& is )
{
	stringItem *strItem = formDef->infoHead->at( itemCounter );
	char *string = (char *)buffers[itemCounter]->getArea();

	is.readBytes( string, strItem->maxLen + 1 );
	itemCounter++;

	return string;
}


TStreamableClass RInfoCollection( TInfoCollection::name,
								  TInfoCollection::build,
								  __DELTA(TInfoCollection)
								);
