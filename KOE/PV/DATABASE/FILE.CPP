/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database File Source File 		    	*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Database\File.Use"

#define Uses_TStreamableClass
#define Uses_TStreamable
#define Uses_TProgram

#include <TV.H>
#include "Database\File.H"

#include <Dir.H>
#include <StdLib.H>


/*---- Constructors, Destructors ---------------*/

TDBFile::TDBFile( const char *aFileName, ccIndex aMaxSpareRecs ) :
	fileName( newStr( aFileName ) ),
	maxSpareRecs( aMaxSpareRecs ),
	spareRecCount( 0 )
{
	file = new fpstream( fileName, ios::in | ios::out | ios::trunc );

	spareRecs = new RecordDescriptor[maxSpareRecs];

	file->flush();
	file->close();
}


TDBFile::~TDBFile()
{
//	file->flush();
//	file->close();
	delete file;

	delete[] fileName;
	delete[] spareRecs;
}


/*---- Public Methods --------------------------*/

void TDBFile::createRecord( RecordDescriptor *rd )
{
	file->open( fileName, ios::out | ios::nocreate | ios::noreplace );

	if( spareRecCount == 0 )
		{
		file->seekp( 0, ios::end );
		streampos endOfFile = file->tellg();
		if( endOfFile % (getRecordSize() + 2) != 0 )
			{
			file->flush();
			file->close();
			delete file;
			abort();
			}

		rd->position = endOfFile;
		}
	else
		{
		file->seekp( spareRecs[spareRecCount - 1].position );
		*rd = spareRecs[spareRecCount - 1];
		spareRecCount--;
		}

	file->close();
}


void TDBFile::deleteRecord( RecordDescriptor *rd )
{
	file->open( fileName, ios::out | ios::nocreate | ios::noreplace );

	file->seekp( rd->position );
	file->writeByte( 0 ); // inUse Flag
	file->writeByte( 0 ); // status Byte
//	file->writeBytes( "SPARE", 6 );
	file->flush();
	file->close();

	spareRecCount++;
	spareRecs[spareRecCount - 1] = *rd;
}


void TDBFile::writeRecord( RecordDescriptor *rd, void *rec )
{
	file->open( fileName, ios::out | ios::nocreate | ios::noreplace );

	file->seekp( rd->position );
	file->writeByte( 1 ); // inUse Flag
	file->writeByte( 0 ); // status Byte

	writeRecord( *file, rec );
	file->flush();
	file->close();
	rd->update = False;
}


void *TDBFile::readRecord( RecordDescriptor *rd, void *cacheSystem )
{
	file->open( fileName, ios::in | ios::nocreate | ios::noreplace );

	file->seekp( rd->position );
	uchar inUse = file->readByte();
	uchar status = file->readByte();

	inUse; // check!!
	status; // check!!

	void *rec = readRecord( *file, cacheSystem );
	file->close();
	rd->update = False;

	return rec;
}


/*---- TStreamable Methods ---------------------*/

TDBFile::TDBFile( StreamableInit )
{}


void TDBFile::write( opstream& os )
{
	os.flush();
	os.writeString( fileName );
	os.flush();

	os << (int)maxSpareRecs;
	os.flush();
	os << (int)spareRecCount;
	os.flush();
	os.writeBytes( spareRecs,
				   spareRecCount * sizeof( RecordDescriptor ) );
	os.flush();
}


void *TDBFile::read( ipstream& is )
{
	fileName = new char[MAXPATH];
	is.readString( fileName, MAXPATH );
	file = new fpstream();

	is >> (int)maxSpareRecs;
	spareRecs = new RecordDescriptor[maxSpareRecs];

	is >> (int)spareRecCount;
	is.readBytes( spareRecs,
				  spareRecCount * sizeof( RecordDescriptor ) );
	return this;
}
