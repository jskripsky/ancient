/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Date Fields Source File    				*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Field\DateFlds.Use"

#define Uses_TStreamableClass
#define Uses_TInputLine

#include <TV.H>
#include "Field\DateFlds.H"

#include <String.H>
#include <CType.H>
#include <StdLib.H>
#include <DOS.H>


TDateField::TDateField( TMeasurements& m, const char *aLabel,
						ushort aStringLength, const char *format,
						ushort options ) :
	TTextField( m, aLabel, aStringLength, options )
{
	if( !format )
		{
		yearLen = 2;
		separator = '.';
		}
	else
		setupFormat( format );

	createControl( m );

	if( aLabel )
		createLabel( m, aLabel );
}


/*---- Public Methods --------------------------*/

Boolean TDateField::check()
{
	date sysDate;
	getdate( &sysDate );

	if( !TTextField::check() )
		return False;

	if( isEmpty() )
		return True;

	short day, month, year;

	char *string = new char[stringLength + 1];
	getString( string );

	char unknown;
	if( separator != '-' )
		unknown = '-';
	else
		unknown = '?';

	if(	strchr( string, unknown ) )
		{
		memset( string, unknown, stringLength );
		string[stringLength] = 0;

		string[2] = separator;
		string[5] = separator;

		control->setData( string );

		return True;
		}

	ushort pos = 0;

	day = readNumber( string, pos, 2 );
	month = readNumber( string, pos, 2 );
	year = readNumber( string, pos, 4 );

	delete[] string;

	if( (day == -1) || (day == 0) )
		day = sysDate.da_day;

	if( (month == -1) || (month == 0) )
		month = sysDate.da_mon;

	if( year == -1 )
		year = (short)sysDate.da_year;


	if( !validDate( day, month, year ) )
		{
		checkError( "Datum ist ungÅltig!" );
		return False;
		}
	else
		formatDate( day, month, year );

	return True;
}


/*---- Private Methods -------------------------*/

short TDateField::readNumber( const char *string, ushort& pos,
							  ushort maxLen )
{
	char *buffer = new char[maxLen + 1];

	while( !isdigit( string[pos] ) && (string[pos] != 0) )
		pos++;

	ushort start = pos;
	if( string[pos] == 0 )
		{
		delete[] buffer;
		return -1;
		}

	while( isdigit( string[pos] ) && (string[pos] != 0) &&
		   (pos - start < maxLen) )
		{
		buffer[pos - start] = string[pos];
		pos++;
		}
	buffer[pos - start] = '\0';

	short num = atoi( buffer );
	delete[] buffer;

	return num;
}


void TDateField::setupFormat( const char *format )
{
	ushort i = 0;

	while( isalpha( format[i] ) && (format[i] != ' ') )
		i++;
	separator = format[i];

	yearLen = 0;
	for( i = 0; format[i]; i++ )
		if( (format[i] == 'Y') || (format[i] == 'J') )
			yearLen++;
}


Boolean TDateField::validDate( short day, short month, short& year )
{
	ushort daysInMonth;

	if( year < 100 )
		year += 1900;


	if( year >= 2000 )
		return False;

	if( (month < 1) || (month > 12) )
		return False;

	switch( month )
		{
		case 4:
		case 6:
		case 9:
		case 11:
			daysInMonth = 30;
			break;

		default:
			daysInMonth = 31;
		}

	if( month == 2 )
		{
		if( year % 4 != 0 )
			daysInMonth = 28;
		else
			{
			if( year % 100 != 0 )
				daysInMonth = 29;
			else
				if( year % 400 != 0 )
					daysInMonth = 28;
				else
					daysInMonth = 29;
			}
		}

	if( (day < 1) || (day > daysInMonth) )
		return False;

	return True;
}


void TDateField::formatDate( short day, short month, short year )
{
	char *string = new char[control->dataSize()];
	control->getData( string );

	for( int i = 0; i < 6; i++ )
		string[i] = ' ';

	string[2] = separator;
	string[5] = separator;
	string[6 + yearLen] = 0;

	char buffer[33];
	itoa( day, buffer, 10 );
	strncpy( &string[2 - strlen( buffer )], buffer, strlen( buffer ) );

	itoa( month, buffer, 10 );
	strncpy( &string[5 - strlen( buffer )], buffer, strlen( buffer ) );

	itoa( year, buffer, 10 );
	if( strlen( buffer ) == 1 )
		{
		buffer[2] = '\0';
		buffer[1] = buffer[0];
		buffer[0] = '0';
		}

	strcpy( &string[6], &buffer[4 - yearLen] );

	control->setData( string );
	delete[] string;
}


void TSystemDateField::setup()
{
	char *temp = new char[control->dataSize()];
	control->getData( temp );
	if( strlen( temp ) == 0 )
		{
		control->setData( "." );
		check();
		}
	delete[] temp;
}


TSystemTimeField::TSystemTimeField( TMeasurements& m, const char *aLabel,
									ushort options ) :
	TTextField( m, aLabel, 5, options )
	{}


void TSystemTimeField::setup()
{
	char *temp = new char[6];
	control->getData( temp );
	if( strlen( temp ) == 0 )
		{
		struct time sysTime;
		gettime( &sysTime );

		int pointer = 0;
		temp[0] = '0';

		if( sysTime.ti_hour < 10 )
			pointer++;

		itoa( sysTime.ti_hour, &temp[pointer], 10 );

		temp[2] = ':';
		pointer = 3;
		temp[3] = '0';

		if( sysTime.ti_min < 10 )
			pointer++;

		itoa( sysTime.ti_min, &temp[pointer], 10 );

		control->setData( temp );
		}

	delete[] temp;
}


Boolean TBirthDateField::validDate( short day, short month, short& year )
{
	if( !TDateField::validDate( day, month, year ) )
		return False;

	date sysDate;
	getdate( &sysDate );

	if( year > sysDate.da_year )
		return False;

	if( (year == sysDate.da_year) && (month > sysDate.da_mon) )
		return False;

	if( (year == sysDate.da_year) && (month == sysDate.da_mon) &&
		(day > sysDate.da_day) )
		return False;

	return True;
}

/*---- TStreamable Methods ---------------------*/

const char * const TDateField::name = "TDateField";
const char * const TSystemDateField::name = "TSystemDateField";
const char * const TSystemTimeField::name = "TSystemTimeField";
const char * const TBirthDateField::name = "TBirthDateField";


TDateField::TDateField( StreamableInit ) :
	TTextField( streamableInit )
	{ }


TSystemDateField::TSystemDateField( StreamableInit ) :
	TDateField( streamableInit )
	{ }


TSystemTimeField::TSystemTimeField( StreamableInit ) :
	TTextField( streamableInit )
	{ }


TBirthDateField::TBirthDateField( StreamableInit ) :
	TDateField( streamableInit )
	{ }


TStreamable *TDateField::build()
{
	return (TStreamable *)new TDateField( streamableInit );
}


TStreamable *TSystemDateField::build()
{
	return (TStreamable *)new TSystemDateField( streamableInit );
}


TStreamable *TSystemTimeField::build()
{
	return (TStreamable *)new TSystemTimeField( streamableInit );
}


TStreamable *TBirthDateField::build()
{
	return (TStreamable *)new TBirthDateField( streamableInit );
}


void TDateField::write( opstream& os )
{
	TTextField::write( os );
	os << yearLen;
	os << separator;
}


void *TDateField::read( ipstream& is )
{
	TTextField::read( is );
	is >> yearLen;
	is >> separator;
	return this;
}


TStreamableClass RDateField( TDateField::name,
			 TDateField::build,
			 __DELTA(TDateField)
			   );


TStreamableClass RSystemDateField( TSystemDateField::name,
			 TSystemDateField::build,
			 __DELTA(TSystemDateField)
			   );


TStreamableClass RSystemTimeField( TSystemTimeField::name,
			 TSystemTimeField::build,
			 __DELTA(TSystemTimeField)
			   );


TStreamableClass RBirthDateField( TBirthDateField::name,
			 TBirthDateField::build,
			 __DELTA(TBirthDateField)
			   );
