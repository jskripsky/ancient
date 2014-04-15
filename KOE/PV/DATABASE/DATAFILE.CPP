/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database DataFile Source File   		*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#define Uses_TStreamableClass
#define Uses_TStreamable
#define Uses_fpstream

#include <TV.H>
#include "Database\DataFile.H"
#include "Database\Record.H"

#include "Person\Person.H"

__link( RInfo );
__link( RPerson );


/*---- Constructors, Destructors ---------------*/

TDBDataFile::TDBDataFile( const char *aFileName, ccIndex aMaxSpareRecs ) :
	TDBFile( aFileName, aMaxSpareRecs )
{}


/*---- Protected Methods -----------------------*/

void *TDBDataFile::readRecord( fpstream& s, void *cacheSystem )
{
	TPerson *rec = new TPerson( streamableInit );
	rec->read( s );

	rec->connectToCache( cacheSystem );

	return rec;
}


void TDBDataFile::writeRecord( fpstream& s, void *rec  )
{
	((TPerson *)rec)->write( s );
}


int TDBDataFile::getRecordSize()
{
	return TPerson::dataSize();
}


/*---- TStreamable Methods ---------------------*/

const char * const TDBDataFile::name = "TDBDataFile";


TDBDataFile::TDBDataFile( StreamableInit ) :
	TDBFile( streamableInit )
{}


TStreamable *TDBDataFile::build()
{
	return new TDBDataFile( streamableInit );
}


TStreamableClass RDBDataFile( TDBDataFile::name,
							  TDBDataFile::build,
							  __DELTA(TDBDataFile)
							);
