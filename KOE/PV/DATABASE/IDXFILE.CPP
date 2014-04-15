/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database IndexFile Source File   		*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "FormDef\FormDef.Use"

#define Uses_TStreamableClass
#define Uses_TStreamable
#define Uses_fpstream

#define Uses_TCollection

#include <TV.H>
#include "FormDef\FormDef.H"
#include "Database\IdxFile.H"
#include "Database\Entry.H"

#include "Person\Info.H"

__link( RInfo );
__link( RPerson );

extern Boolean controlField;


/*---- Constructors, Destructors ---------------*/

TDBIndexFile::TDBIndexFile( const char *aFileName, ccIndex aMaxSpareRecs ) :
	TDBFile( aFileName, aMaxSpareRecs )
{}


/*---- Protected Methods -----------------------*/

void *TDBIndexFile::readRecord( fpstream& s, void *cacheSystem )
{
	TInfo *rec = new TInfo( streamableInit );
	rec->read( s );

	rec->connectToCache( cacheSystem );

	return rec;
}


void TDBIndexFile::writeRecord( fpstream& s, void *rec  )
{
	((TInfo *)rec)->write( s );
}


int TDBIndexFile::getRecordSize()
{
	int recSize = 0;
	for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
		{
		stringItem *strItem = formDef->infoHead->at( i );
		recSize += strItem->maxLen + 1;
		}

	recSize += sizeof( RecordDescriptor );
	if( controlField )
		recSize += sizeof( int );

	return recSize;
}


/*---- TStreamable Methods ---------------------*/

const char * const TDBIndexFile::name = "TDBIndexFile";


TDBIndexFile::TDBIndexFile( StreamableInit ) :
	TDBFile( streamableInit )
{}


TStreamable *TDBIndexFile::build()
{
	return new TDBIndexFile( streamableInit );
}


TStreamableClass RDBIndexFile( TDBIndexFile::name,
							   TDBIndexFile::build,
							   __DELTA(TDBIndexFile)
							 );
