/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		LogPrinter Source File         			*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "LogPrint.H"
#include "FormDef\FormDef.Use"
#include "Person\Info.Use"

#include <TV.H>
#include "FormDef\FormDef.H"
#include "Gadgets\Config.H"
#include "Person\Info.H"

#include <FStream.H>
#include <String.H>
#include <DOS.H>
#include <StdLib.H>


LogPrinter::LogPrinter( int aMode, date *aLogDate ) :
	logDate( aLogDate ),
	mode( aMode ),
	line( 0 )
{
	char portName[13];
	config->getPrinterPortName( portName );

	printer = new ofstream( portName, ios::out | ios::trunc | ios::binary );

	printer->put( 0x1b );
	printer->put( 0x40 );

	printer->put( 0x1b );
	printer->put( 0x4d );

	printer->put( 0x1b );
	printer->put( 0x6c );
	printer->put( 0x08 );
}


LogPrinter::~LogPrinter()
{
	printer->put( 0x1b );
	printer->put( 0x50 );

	printer->put( 0x1b );
	printer->put( 0x6c );
	printer->put( 0x00 );

	printer->put( '\f' );

	printer->close();
	delete printer;
}


void LogPrinter::writeEntry( TInfo *info )
{
	if( line == 40 )
		{
		printer->put( '\f' );
		line = 0;
		}

	if( line == 0 )
		{
		char title[80];

		switch( mode )
			{
			case 0:
				strcpy( title, "Protokoll (in Behandlung) vom " );
				break;

			case 1:
				strcpy( title, "Protokoll (entlassen) vom " );
				break;

			case 2:
				strcpy( title, "Protokoll (station„r) vom " );
				break;

			case 3:
				strcpy( title, "Protokoll (D13 Eigenunfall entl.) vom " );
				break;

			case 4:
				strcpy( title, "Protokoll (D13 Eigenunfall stat.) vom " );
				break;

			case 5:
				strcpy( title, "Protokoll (D13 entlassen) vom " );
				break;

			case 6:
				strcpy( title, "Protokoll (D13 station„r) vom " );
				break;

			}

		write( title );

		writeDate( logDate );

		startNewLine();
		startNewLine();

		line += 2;
		}

	TPerson *person = (TPerson *)info->getRecord();
	char *data = new char[TPerson::dataSize()];
	memcpy( data, person->getData(), TPerson::dataSize() );

	write( &data[0x3C], 8 ); write( " " );

	write( &data[0], 30 ); write( " " );
	write( &data[31], 15 ); write( " " );

	write( &data[0x2F], 10 ); write( " " );

	switch( data[0x3A] )
		{
		case 0:
			write( "M", 1 );
			break;

		case 1:
			write( "W", 1 );
			break;
		}

	startNewLine();
	line++;

	write( &data[0x54], 30 ); write( " " );
	write( &data[0x73], 8 ); write( " " );
	write( &data[0x7C], 20 ); write( " " );

	startNewLine();
	line++;

	switch( data[0x194] )
		{
		case 0:
			write( "Selbst", 12 );
			break;

		case 1:
			write( "Rettungwagen", 12 );
			break;

		case 2:
			write( "Notarztwagen", 12 );
			break;

		case 3:
			write( "Hubschrauber", 12 );
			break;
		}

	write( " " );

	write( &data[0x16B], 30 ); write( " " );

	switch( data[0xCB] )
		{
		case 1:
			write( "Allg.", 5 );
			break;

		case 2:
			write( "Priv.", 5 );
			break;
		}
	write( " " );

	write( &data[0xCD], 30 );

	startNewLine();
	line++;

	write( &data[0x0F6], 38 ); write( " " );
	write( &data[0x11D], 38 ); write( " " );
	write( &data[0x144], 38 );

	startNewLine();
	line++;

	startNewLine();
	line++;

	delete[] data;
}


void LogPrinter::writeDate( date *sysDate )
{
	char string[5];

	if( sysDate->da_day > 10 )
		itoa( sysDate->da_day, string, 10 );
	else
		{
		string[0] = ' ';
		itoa( sysDate->da_day, &string[1], 10 );
		}

	printer->write( string, 2 );
	printer->write( ".", 1 );

	if( sysDate->da_mon > 10 )
		itoa( sysDate->da_mon, string, 10 );
	else
		{
		string[0] = ' ';
		itoa( sysDate->da_mon, &string[1], 10 );
		}

	printer->write( string, 2 );
	printer->write( ".", 1 );

	itoa( sysDate->da_year, string, 10 );
	printer->write( &string[2], 2 );

	printer->write( " ", 1 );
}


void LogPrinter::writeTime( struct time *sysTime )
{
	char string[3];

	if( sysTime->ti_hour > 10 )
		itoa( sysTime->ti_hour, string, 10 );
	else
		{
		string[0] = ' ';
		itoa( sysTime->ti_hour, &string[1], 10 );
		}

	printer->write( string, 2 );
	printer->write( ":", 1 );

	if( sysTime->ti_min > 10 )
		itoa( sysTime->ti_min, string, 10 );
	else
		{
		string[0] = '0';
		itoa( sysTime->ti_min, &string[1], 10 );
		}

	printer->write( string, 2 );

	printer->write( "  ", 2 );
}


void LogPrinter::write( const char *text, int length )
{
	int len = length;

	if( len == 0 )
		len = strlen( text );

	char *string = new char[len + 1];
	strncpy( string, text, len );
	string[len] = 0;

	for( int i = strlen( string ); i < len; i++ )
		string[i] = ' ';

	printer->write( string, len );

	delete[] string;
}


void LogPrinter::startNewLine()
{
	printer->put( '\r' );
	printer->put( '\n' );
}
