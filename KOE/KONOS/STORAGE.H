#ifndef STORAGE
#define STORAGE


#include "Types.H"

//template <class item> class Container;
//class PersistentObject;


class StorageUnit
{
public:
	//=== constructors and destructor =====
	StorageUnit();
	virtual ~StorageUnit();

	virtual void open() = 0;
	virtual void close() = 0;

	virtual void update() = 0;

	//virtual void startIDBlock( const char *ID ) = 0;
	//virtual void endIDBlock() = 0;

	//virtual boolean openIDBlock( const char *ID ) = 0;


	virtual void writeLong( long ) = 0;
	virtual long readLong() = 0;

	virtual void writeShort( short ) = 0;
	virtual short readShort() = 0;

	virtual void writeChar( char ) = 0;
	virtual short readChar() = 0;

	virtual void writeBoolean( boolean ) = 0;
	virtual boolean readBoolean() = 0;

	virtual void writeString( const char *, long maxLength = 0 ) = 0;
	virtual void readString( char *, long maxLength ) = 0;

        virtual char *readString() = 0;

	virtual void writeData( void *, long size ) = 0;
	virtual void readData( void *, long size ) = 0;


//	virtual void writeContainer( Container<PersistentObject *>& );
//	virtual void readContainer( Container<PersistentObject *>& );
//
//	virtual void writeStringContainer( Container<char *>& );
//	virtual void readStringContainer( Container<char *>& );
};


inline void operator >> ( StorageUnit& su, long& l )
	{ l = su.readLong(); }

inline void operator << ( StorageUnit& su, long l )
	{ su.writeLong( l ); }

inline void operator >> ( StorageUnit& su, short& s )
	{ s = su.readShort(); }

inline void operator << ( StorageUnit& su, short s )
	{ su.writeShort( s ); }

inline void operator >> ( StorageUnit& su, boolean& b )
	{ b = su.readBoolean(); }

inline void operator << ( StorageUnit& su, boolean b )
	{ su.writeBoolean( b ); }

inline void operator >> ( StorageUnit& su, char& c )
	{ c = su.readChar(); }

inline void operator << ( StorageUnit& su, char c )
	{ su.writeChar( c ); }


//inline void operator >> ( StorageUnit& su,
//						  Container<PersistentObject *>& c )
//	{ su.readContainer( c ); }
//
//inline void operator << ( StorageUnit& su,
//						  Container<PersistentObject *>& c )
//	{ su.writeContainer( c ); }


//inline void operator >> ( StorageUnit& su,
//						  Container<char *>& sc )
//	{ su.readStringContainer( sc ); }
//
//inline void operator << ( StorageUnit& su,
//						  Container<char *>& sc )
//	{ su.writeStringContainer( sc ); }


//inline void operator >> ( ipstream& is, TBackground*& cl )
//    { return is >> (void *&)cl; }

//inline opstream& operator << ( opstream& os, TBackground* cl )
//    { return os << (TStreamable *)cl; }


#endif