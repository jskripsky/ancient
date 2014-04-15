/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		LogFile Source File         			*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "LogFile.H"

#include <FStream.H>
#include <String.H>
#include <DOS.H>
#include <StdLib.H>


LogFile::LogFile( const char *fileName )
{
	file = new ofstream( fileName, ios::out | ios::app | ios::binary );
}


LogFile::~LogFile()
{
	file->close();
	delete file;
}


void LogFile::writeDate()
{
	date sysDate;
	getdate( &sysDate );

	file->write( (char *)&sysDate, sizeof( sysDate ) );
}


void LogFile::writeTime()
{
	struct time sysTime;
	gettime( &sysTime );

	file->write( (char *)&sysTime, sizeof( sysTime ) );
}


void LogFile::write( const char *text )
{
	file->write( text, strlen( text ) );
}


void LogFile::writeByte( char byte )
{
	file->put( byte );
}
