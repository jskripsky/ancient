/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Page Source File        				*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Page.Use"

#define Uses_TView
#define Uses_TStreamableClass

#include <TV.H>
#include "Page.H"
__link( RTextField );
__link( RNameField );
__link( RRadioField );
__link( RNumericField );
__link( RDateField );
__link( RSpecCardTextField );
__link( RHiddenConstField );
__link( RSystemDateField );
__link( RSystemTimeField );
__link( RBirthDateField );
__link( RListField );

__link( RPNumberField );
__link( RSchwyzPNumberField );
__link( RControlField );


#include <String.H>


/*---- Constructors, Destructors ---------------*/

TPage::TPage( char *aTitle ) :
	TCollection( 10, 5 ),
	page( TRect( 0, 0, 42, 17 ) ),
	dataOffSet( 0 )
{
	strncpy( pageTitle, aTitle, sizeof( pageTitle ) - 1 );
	page.insert( new TView( page.getExtent() ) );
}


/*---- Public Methods --------------------------*/

void TPage::move( TPoint distance )
{
	page.moveTo( distance.x, distance. y );
}


void TPage::registerInfo( TInfoHead& info )
{
	for( ccIndex i = 0; i < count; i++ )
		((TField *)TCollection::at( i ))->registerInfo( info );
}


void TPage::setInfo( TInfo& info )
{
	for( ccIndex i = 0; i < count; i++ )
		((TField *)TCollection::at( i ))->setInfo( info );
}


void TPage::setAccessCode( TInfo& info )
{
	for( ccIndex i = 0; i < count; i++ )
		((TField *)TCollection::at( i ))->setAccessCode( info );
}


void TPage::print( TOutputDevice& outputDevice )
{
	for( ccIndex i = 0; i < count; i++ )
		((TField *)TCollection::at( i ))->print( outputDevice );
}


Boolean TPage::checkFields()
{
	for( ccIndex i = 0; i < count; i++ )
		if(	!((TField *)TCollection::at( i ))->check() )
			return False;

	return True;
}


void TPage::setData( void *data )
{
	page.setData( (char *)data + dataOffSet );

	for( int i = 0; i < count; i++ )
		{
		((TField *)at( i ))->setup();

		if( !((TField *)at( i ))->isHidden() )
			((TField *)at( i ))->select();
		}

	for( i = 0; ((TField *)at( i ))->isHidden(); i++ );

	((TField *)at( i ))->select();
}


void TPage::getData( void *data )
{
	page.getData( (char *)data + dataOffSet );
}


void TPage::insert( TField *field )
{
	TCollection::insert( field );
	field->insertInto( &page );
	lastInserted = field;
}


void TPage::insertInto( TGroup *grp )
{
	grp->lock();
	grp->insert( &page );

	grp->unlock();
}


void TPage::removeFrom( TGroup *grp )
{
	grp->lock();
	grp->remove( &page );
	grp->unlock();
}


/*---- TStreamable Methods ---------------------*/

const char * const TPage::name = "TPage";


TPage::TPage( StreamableInit streamableInit ) :
	TCollection( streamableInit ),
	page( TRect( 0, 0, 42, 17 ) )
{
	page.insert( new TView( page.getExtent() ) );
}


TStreamable *TPage::build()
{
	return new TPage( streamableInit );
}


void TPage::write( opstream& os )
{
	TCollection::write( os );
	os.writeString( pageTitle );
	os << dataOffSet;
}


void *TPage::read( ipstream& is )
{
	TCollection::read( is );
	is.readString( pageTitle, titleLength );
	is >> dataOffSet;
	return this;
}


void TPage::writeItem( void *obj, opstream& os )
{
	os << (TField *)obj;
}


void *TPage::readItem( ipstream& is )
{
	TField *field;
	is >> field;
	field->insertInto( &page );
	return field;
}


TStreamableClass RPage( TPage::name,
			 TPage::build,
			 __DELTA(TPage)
			   );
