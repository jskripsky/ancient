/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Version Header Source File 		    	*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Gadgets\VerHead.Use"

#define Uses_TStreamableClass

#include <TV.H>
#include "Gadgets\VerHead.H"

#include <String.H>


/*---- Constructors, Destructors ---------------*/

TVersionHeader::TVersionHeader( const char *description, ushort verNumber )
{
	strcpy( dataDescription, description );
	number = verNumber;
}


/*---- TStreamable Methods ---------------------*/

const char * const TVersionHeader::name = "TVersionHeader";


TStreamable *TVersionHeader::build()
{
	return new TVersionHeader( streamableInit );
}


void TVersionHeader::write( opstream& os )
{
	os.writeString( dataDescription );
	os << number;
}


void *TVersionHeader::read( ipstream& is )
{
	is.readString( dataDescription, sizeof( dataDescription ) );
	is >> number;
	return this;
}


TStreamableClass RVersionHeader( TVersionHeader::name,
			 TVersionHeader::build,
			 __DELTA(TVersionHeader)
			   );
