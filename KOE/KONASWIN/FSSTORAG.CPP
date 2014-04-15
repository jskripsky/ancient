#include "FSStorag.H"

#include <String.H>


FSStorageUnit::FSStorageUnit()
{
}


FSStorageUnit::~FSStorageUnit()
{
}


void FSStorageUnit::writeLong( long l )
{
	file->write( (const char *)&l, sizeof( l ) );
}


void FSStorageUnit::writeShort( short s )
{
	file->write( (const char *)&s, sizeof( s ) );
}


void FSStorageUnit::writeBoolean( boolean b )
{
	file->write( (const char *)&b, sizeof( b ) );
}


void FSStorageUnit::writeString( char *str, long maxLength )
{
	if( maxLength == 0 )
		writeLong( strlen( str ) );
	else
		writeLong( maxLength );

	file->write( (const char *)str, strlen( str ) );

	if( maxLength > 0 )
		for( int o = strlen( str ); o < maxLength; o++ )
			file->put( (char)0 );
}


void FSStorageUnit::writeData( void *d, long size )
{
	file->write( (const char *)d, (int)size );
}


long FSStorageUnit::readLong()
{
	long l;
	file->read( (char *)&l, sizeof( l ) );
	return l;
}


short FSStorageUnit::readShort()
{
	short s;
	file->read( (char *)&s, sizeof( s ) );
	return s;
}


boolean FSStorageUnit::readBoolean()
{
	boolean b;
	file->read( (char *)&b, sizeof( b ) );
	return b;
}


void FSStorageUnit::readString( char *str, long maxLength )
{
	long fileStringLen = readLong();
	if( fileStringLen < maxLength )
		{
		file->read( str, (int)fileStringLen );
		str[(int)fileStringLen] = 0;
		}
	else
		{
		file->read( str, (int)maxLength );
		str[(int)maxLength] = 0;
		file->seekg( fileStringLen - maxLength, ios::cur );
		}
}


void FSStorageUnit::readData( void *d, long size )
{
	file->read( (char *)d, (int)size );
}
