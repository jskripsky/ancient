/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Person Source File 		    			*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Person\Person.Use"
#include "FormDef\FormDef.Use"

#define Uses_TStreamableClass

#include <TV.H>
#include "Person\Person.H"
#include "FormDef\FormDef.H"
#include "Database\Buffer.H"

#include "Mem.H"


int TPerson::instances = 0;
TBuffer *TPerson::buffer = 0;


/*---- Constructors, Destructors ---------------*/

TPerson::TPerson( const TPerson& person )
{
	initData();
	*this = person;
}


TPerson::TPerson( CreationInit )
{
	initData();
	memset( data, 0, dataSize() );
}


TPerson::~TPerson()
{
	buffer->releaseArea( data );

///	instances--;
///	if( instances == 0 )
///		delete buffer;

/*
	delete[] data;
*/
}


void TPerson::initData()
{
///	if( instances == 0 )
///		buffer = new TBuffer( dataSize(), 10 );
///
///	instances++;

	if( !buffer )
		buffer = new TBuffer( dataSize(), 10 );

	data = buffer->getArea();

/*
	data = new char[dataSize()];
*/
}


/*---- Public Methods --------------------------*/

TPerson& TPerson::operator = ( const TPerson& person )
{
	memcpy( data, person.data, ((TPerson&)person).dataSize() );
	return *this;
}


ushort TPerson::dataSize()
{
	return TForm::dataSize();
}


/*---- TStreamable Methods ---------------------*/

const char * const TPerson::name = "TPerson";


TPerson::TPerson( StreamableInit ) :
	TDBRecord( streamableInit )
{
	initData();
}


TStreamable *TPerson::build()
{
	return new TPerson( streamableInit );
}


void TPerson::write( opstream& os )
{
	os.writeBytes( data, dataSize() );
}


void *TPerson::read( ipstream& is )
{
	is.readBytes( data, dataSize() );
	return this;
}


TStreamableClass RPerson( TPerson::name,
			 TPerson::build,
			 __DELTA(TPerson)
			   );
