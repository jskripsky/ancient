#ifndef FSSTORAG
#define FSSTORAG


#include "Storage.H"


// "StorageUnit"-Subklasse, welche dem Zugriff auf Dateien bzw. deren
// Daten dient.

// (FS: File System)


class FSStorageUnit : public StorageUnit
{
public:
	//=== constructors and destructor =====
	FSStorageUnit();
	virtual ~FSStorageUnit();

	virtual void open();
	virtual void close();

	virtual void update();

	virtual void writeLong( long );
	virtual void writeShort( short );
	virtual void writeBoolean( boolean );
	virtual void writeString( char *, long maxLength = 0 );

	virtual void writeData( void *, long size );

	virtual long readLong();
	virtual short readShort();
	virtual boolean readBoolean();
	virtual void readString( char *, long maxLength );

	virtual void readData( void *, long size );


protected:
	long file;

};


#endif