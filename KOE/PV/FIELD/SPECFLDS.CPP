/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Special Fields Source File    			*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Field\SpecFlds.Use"

#define Uses_TStreamableClass
#define Uses_TInputLine

#include <TV.H>
#include "Field\SpecFlds.H"

#include <String.H>


THiddenConstField::THiddenConstField( TMeasurements& m, char *aText,
									  ushort aStringLength ) :
	TField( m, THiddenConstField::controlSize, 0, aStringLength, 0 )
{
	strcpy( text, aText );
}



/*---- Public Methods --------------------------*/

void THiddenConstField::getString( char *rec )
{
	memcpy( rec, text, stringLength + 1);
}


void THiddenConstField::print( TOutputDevice& outputDevice )
{
	char *string = new char[stringLength + 1];
	getString( string );

	outputDevice.print( devOptions, string );

	delete[] string;
}


void TSpecCardTextField::print( TOutputDevice& outputDevice )
{
	if( outputDevice.mode == card )
		{
		for( int i = 0; i < 3; i++ )
			{
			TTextField::print( outputDevice );
			devOptions.track++;
			}
		devOptions.track -= i;
		}
	else
		TTextField::print( outputDevice );
}


/*---- Private Methods -------------------------*/

TPoint THiddenConstField::controlSize()
{
	TPoint temp = { 0, 0 };
	return temp;
}


/*---- TStreamable Methods ---------------------*/

const char * const TSpecCardTextField::name = "TSpecCardTextField";

const char * const THiddenConstField::name = "THiddenConstField";


TSpecCardTextField::TSpecCardTextField( StreamableInit ) :
	TTextField( streamableInit )
	{ }


THiddenConstField::THiddenConstField( StreamableInit ) :
	TField( streamableInit )
	{ }


TStreamable *TSpecCardTextField::build()
{
	return (TStreamable *)new TSpecCardTextField( streamableInit );
}


TStreamable *THiddenConstField::build()
{
	return (TStreamable *)new THiddenConstField( streamableInit );
}


void THiddenConstField::write( opstream& os )
{
	os << stringLength;
	os << necessary;

	os.writeBytes( &devOptions, sizeof( devOptions ) );

	os << infoLevel;
	if( infoLevel > 0 )
		os << infoIndex;

	os.writeString( text );
}


void *THiddenConstField::read( ipstream& is )
{
	is >> stringLength;
	is >> (int)necessary;

	is.readBytes( &devOptions, sizeof( devOptions ) );

	is >> infoLevel;
	if( infoLevel > 0 )
		is >> infoIndex;

	is.readString( text, 39 );
	return this;
}


TStreamableClass RHiddenConstField( THiddenConstField::name,
			 THiddenConstField::build,
			 __DELTA(THiddenConstField)
			   );


TStreamableClass RSpecCardTextField( TSpecCardTextField::name,
			 TSpecCardTextField::build,
			 __DELTA(TSpecCardTextField)
			   );
