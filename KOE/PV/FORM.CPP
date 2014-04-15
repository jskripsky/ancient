/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Form Source File 		        		*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Form.Use"
#include "Person\Person.Use"

#define Uses_TStreamableClass

#include <TV.H>
#include "Form.H"
#include "Person\Person.H"
__link( RPage );


ushort TForm::usDataSize = 0;


/*---- Constructors, Destructors ---------------*/

TForm::TForm() :
	TCollection( 10, 5 )
{
}


/*---- Public Methods --------------------------*/

void TForm::adjust( TPoint distance )
{
	for( ccIndex i = 0; i < count; i++ )
		at( i )->move( distance );
}


void TForm::registerInfo( TInfoHead& info )
{
	for( ccIndex i = 0; i < count; i++ )
		at( i )->registerInfo( info );
}


void TForm::insert( TPage *page )
{
	page->setDataOffSet( usDataSize );

	TCollection::insert( page );
	usDataSize += page->dataSize();
}


/*---- TStreamable Methods ---------------------*/

const char * const TForm::name = "TForm";


TStreamable *TForm::build()
{
	return new TForm( streamableInit );
}


void TForm::write( opstream& os )
{
	TCollection::write( os );
	os << usDataSize;
}


void *TForm::read( ipstream& is )
{
	TCollection::read( is );
	is >> usDataSize;
	return this;
}


void TForm::writeItem( void *obj, opstream& os )
{
	os << (TPage *)obj;
}


void *TForm::readItem( ipstream& is )
{
	TPage *page;
	is >> page;
	return page;
}


TStreamableClass RForm( TForm::name,
			 TForm::build,
			 __DELTA(TForm)
			   );
