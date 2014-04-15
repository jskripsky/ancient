/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Numeric Fields Source File    			*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Field\NumFlds.Use"

#define Uses_TStreamableClass
#define Uses_TInputLine

#include <TV.H>
#include "Field\NumFlds.H"

#include <String.H>
#include <CType.H>


TNumericField::TNumericField( TMeasurements& m, const char *aLabel,
							  ushort aStringLength, const char *aValidChars,
							  ushort options ) :
	TTextField( m, aLabel, aStringLength, options )
{
	if( aValidChars )
		validChars = newStr( aValidChars );
	else
		validChars = newStr( "" );

	createControl( m );

	if( aLabel )
		createLabel( m, aLabel );
}


TNumericField::~TNumericField()
{
	delete[] validChars;
}


/*---- Public Methods --------------------------*/

Boolean TNumericField::check()
{
	if( !TTextField::check() )
		return False;

	Boolean checkStatus = True;
	char *string = new char[stringLength + 1];
	getString( string );

	for( int i = 0; string[i]; i++ )
		if( !isdigit( string[i] ) )
			if( strchr( validChars, string[i] ) == NULL )
				checkStatus = False;

	delete[] string;

	if( checkStatus == False )
		checkError( "Feld darf nur Ziffern enthalten!" );

	return checkStatus;
}


/*---- Private Methods -------------------------*/



/*---- TStreamable Methods ---------------------*/

const char * const TNumericField::name = "TNumericField";


TNumericField::TNumericField( StreamableInit ) :
	TTextField( streamableInit ),
	validChars( new char[21] )
	{ }


TStreamable *TNumericField::build()
{
	return (TStreamable *)new TNumericField( streamableInit );
}


void TNumericField::write( opstream& os )
{
	TTextField::write( os );
	if( strlen( validChars ) > 20 )
		validChars[20] = 0;
	os.writeString( validChars );
}


void *TNumericField::read( ipstream& is )
{
	TTextField::read( is );
	is.readString( validChars, 20 );
	return this;
}


TStreamableClass RNumericField( TNumericField::name,
			 TNumericField::build,
			 __DELTA(TNumericField)
			   );
