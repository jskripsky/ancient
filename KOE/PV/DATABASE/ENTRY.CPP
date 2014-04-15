/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database Entry Source File 		    	*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "DataBase\Entry.Use"

#include "DataBase\Entry.H"
#include "DataBase\Record.H"
#include "DataBase\DataBase.H"
#include <TV.H>

#include <String.H>


/*---- Constructors, Destructors ---------------*/

TDBEntry::TDBEntry() :
	TDBRecord(),
	record( 0 )
{}


/*---- Public Methods --------------------------*/

TDBRecord *TDBEntry::getRecord()
{
	if( dataBase )
		{
		TDBRecord *r = dataBase->loadRecord( this );
		r->dataBase = dataBase;
		return r;
		}
	else
		{
		if( record )
			record->dataBase = dataBase;
		return record;
		}
}


void TDBEntry::attachRecord( TDBRecord *rec )
{
	record = rec;
	rec->dataBase = dataBase;
}


void TDBRecord::setUpdateFlag()
{
	dataBase->setUpdateFlag( this, cache );
}


/*---- TStreamable Methods ---------------------*/

void TDBEntry::write( opstream& os )
{
	os.writeBytes( &recordDescriptor, sizeof( RecordDescriptor ) );
}


void *TDBEntry::read( ipstream& is )
{
	is.readBytes( &recordDescriptor, sizeof( RecordDescriptor ) );
	return this;
}
