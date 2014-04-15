/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Standard Fields Source File    			*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Field\StdFlds.Use"

#define Uses_TStreamableClass
#define Uses_TInputLine
#define Uses_TRadioButtons
#define Uses_TStringCollection

#include <TV.H>
#include "Field\StdFlds.H"
__link( RInputLine );
__link( RRadioButtons );
__link( RStringCollection );

#include <String.H>


TTextField::TTextField( TMeasurements& m, const char *aLabel,
						ushort aStringLength, ushort options ) :
	TField( m, TTextField::controlSize, aLabel, aStringLength, options )
{
	createControl( m );

	if( aLabel )
		createLabel( m, aLabel );
}


TRadioField::TRadioField( TMeasurements& m, const char *aLabel,
						  ushort aStringLength, TSItem *aStrings,
						  TSItem *aDeviceStrings, ushort options ) :
	TField( m, TRadioField::controlSize, aLabel, aStringLength, options ),
	strings( aStrings )
{
	short i = 0;
	TSItem *p;

	for( p = aDeviceStrings; p != 0; p = p->next )
		i++;

	deviceStrings = new TStringCollection( i, 0 );

	while( aDeviceStrings != 0 )
		{
		p = aDeviceStrings;
		deviceStrings->atInsert( deviceStrings->getCount(),
								 newStr( aDeviceStrings->value ) );
		aDeviceStrings = aDeviceStrings->next;
		delete p;
		}

	adjustRBMeasurements( m, aStrings );
	createControl( m );

	if( aLabel )
		createLabel( m, aLabel );
}


/*---- Public Methods --------------------------*/

void TTextField::createControl( TMeasurements& m )
{
	control = new TInputLine( m.control, stringLength + 1 );
}


void TTextField::getString( char *rec )
{
	control->getData( rec );
}


void TTextField::print( TOutputDevice& outputDevice )
{
	char *string = new char[stringLength + 1];
	getString( string );

	outputDevice.print( devOptions, string );

	delete[] string;
}


void TTextField::setInfo( TInfo& info )
{
	if( infoLevel > 0 )
		getString( (char *)info.at( infoIndex ) );
}


//void TForeNameField::setInfo( TInfo& info )
//{
//	if( infoLevel > 0 )
//    	info.at( infoIndex )
//}


Boolean TTextField::isEmpty()
{
	Boolean empty = False;
	char *string = new char[stringLength + 1];
	getString( string );

	if( string[0] == 0 )
		empty = True;

	delete[] string;
	return empty;
}


/*---- Private Methods -------------------------*/

TPoint TTextField::controlSize()
{
	TPoint temp = { 3, 1 };
	return temp;
}


/*---- Public Methods --------------------------*/

Boolean TNameField::check()
{
	if( !TTextField::check() )
		return False;

	deleteEndSpaces();
	return True;
}


void TNameField::deleteEndSpaces()
{
	char *string = new char[stringLength + 1];
	control->getData( string );

	int i = strlen( string ) - 2;

	while( string[i] == ' ' )
		{
		string[i] = 0;
		i--;
		}

	control->setData( string );
	delete[] string;
}


void TRadioField::createControl( TMeasurements& m )
{
	control = new TRadioButtons( m.control, strings );
}


void TRadioField::getString( char *rec )
{
	ushort value;
	control->getData( &value );

	memcpy( rec,
			deviceStrings->at( value ),
			stringLength + 1);
}


void TRadioField::print( TOutputDevice& outputDevice )
{
	char *string = new char[stringLength + 1];
	getString( string );

	outputDevice.print( devOptions, string );

	delete[] string;
}


void TRadioField::setInfo( TInfo& info )
{
	if( infoLevel > 0 )
		getString( (char *)info.at( infoIndex ) );
}


Boolean TRadioField::isEmpty()
{
	Boolean empty = False;
	char *string = new char[stringLength + 1];
	getString( string );

	if( string[0] == 0 )
		empty = True;

	delete[] string;
	return empty;
}


/*---- Private Methods -------------------------*/

TPoint TRadioField::controlSize()
{
	TPoint temp = { 10, 3 };
	return temp;
}

void TRadioField::adjustRBMeasurements( TMeasurements& m, TSItem *i )
{
	short c = 0;
	ushort maxlen = 0;
	TSItem *p;

	for( p = i; p != 0; p = p->next )
		{
		ushort len = strlen( p->value );

		if( len > maxlen )
			maxlen = len;
		c++;
		}

	m.control.b.x = m.control.a.x + maxlen + 7;
	m.control.b.y = m.control.a.y + c;
}


/*---- TStreamable Methods ---------------------*/

const char * const TTextField::name = "TTextField";


TTextField::TTextField( StreamableInit ) :
	TField( streamableInit )
{
	control = (TInputLine *)TInputLine::build();
}


TStreamable *TTextField::build()
{
	return (TStreamable *)new TTextField( streamableInit );
}


/*---- TStreamable Methods ---------------------*/

const char * const TNameField::name = "TNameField";


TStreamable *TNameField::build()
{
	return (TStreamable *)new TNameField( streamableInit );
}


/*---- TStreamable Methods ---------------------*/

const char * const TRadioField::name = "TRadioField";


TRadioField::TRadioField( StreamableInit ) :
	TField( streamableInit )
{
	control = (TRadioButtons *)TRadioButtons::build();
}


TStreamable *TRadioField::build()
{
	return (TStreamable *)new TRadioField( streamableInit );
}


void TRadioField::write( opstream& os )
{
	TField::write( os );
	os << deviceStrings;
}


void *TRadioField::read( ipstream& is )
{
	TField::read( is );
	is >> deviceStrings;
	return this;
}


TStreamableClass RTextField( TTextField::name,
			 TTextField::build,
			 __DELTA(TTextField)
			   );


TStreamableClass RNameField( TNameField::name,
			 TNameField::build,
			 __DELTA(TNameField)
			   );


TStreamableClass RRadioField( TRadioField::name,
			 TRadioField::build,
			 __DELTA(TRadioField)
			   );


