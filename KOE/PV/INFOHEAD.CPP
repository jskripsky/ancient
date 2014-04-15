/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Person Info Header Source File		    */
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "InfoHead.Use"
#include "FormDef\FormDef.Use"

#define Uses_TStreamableClass

#include <TV.H>
#include "InfoHead.H"
#include "FormDef\FormDef.H"

#include <String.H>


const stringLength = 80;


/*---- Constructors, Destructors ---------------*/

TInfoHead::TInfoHead() :
	TCollection( 1, 1 )
{
	shouldDelete = False;
}


TInfoHead::~TInfoHead()
{
}


/*---- Public Methods --------------------------*/

stringItem *TInfoHead::at( ccIndex index )
{
	return (stringItem *)TCollection::at( index );
}


ccIndex TInfoHead::append( ushort level, ushort maxLen )
{
	stringItem *strItem = new stringItem;
	strItem->level = level;
	strItem->maxLen = maxLen;
	TCollection::insert( strItem );
	return count - 1;
}


/*---- TStreamable Methods ---------------------*/

const char * const TInfoHead::name = "TInfoHead";


TStreamable *TInfoHead::build()
{
	return new TInfoHead( streamableInit );
}


void TInfoHead::write( opstream& os )
{
	TCollection::write( os );
}


void *TInfoHead::read( ipstream& is )
{
	TCollection::read( is );
	return this;
}


void TInfoHead::writeItem( void *obj, opstream& os )
{
	os.writeBytes( obj, sizeof( stringItem ) );
}


void *TInfoHead::readItem( ipstream& is )
{
	stringItem *strItem = new stringItem;
	is.readBytes( strItem, sizeof( stringItem ) );
	return strItem;
}


TStreamableClass RInfoHead( TInfoHead::name,
			 TInfoHead::build,
			 __DELTA(TInfoHead)
			   );
