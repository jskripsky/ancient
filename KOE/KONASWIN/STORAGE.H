/*===========================================================================* 
 *====   KONAS   ============================================================*
 *===========================================================================*
 * Storage.H                                                                 *
 *===========================================================================*
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *===========================================================================*/

#ifndef STORAGE
#define STORAGE


#include "Types.H"

// "StorageUnit" ist eine abstrakte Klasse, die als Vermittler zwischen
// Objekten der "PersistentObjekt"-Klasse und dem effektiven permanenten
// "Speichermedium" fungiert. Je nachdem, welcher Klasse das verwendete
// "StorageUnit"-Objekt angeh”rt, wird eine Datei (oder ein Teil der Datei)
// oder eine Datenbank (oder eine Tabelle der Datenbank) als
// Permanentspeicher genutzt.

// Die zu speichernden Daten werden der "StorageUnit" sequentiell bergeben
// (und sp„ter in der gleichen Reihenfolge angefordert).
// ("Data Stream".)

// Dank der abstrakten "StorageUnit"-Klasse k”nnen alle Speicherungs- und
// Lesevorg„nge sp„ter in Dateien oder Datenbanken umgeleitet werden, ohne
// den Rest des Programms umschreiben zu mssen. Man stellt dem
// "PersistentObject" einfach ein Objekt anderer "StorageUnit"-Klasse zur
// Verfgung.


class StorageUnit
{
public:
	//=== constructors and destructor =====
	StorageUnit();
	virtual ~StorageUnit();

	virtual void open() = 0;
	virtual void close() = 0;

	//virtual void update() = 0; // JS: wirklich notwendig?

	
	virtual void writeLong( long ) = 0;
	virtual long readLong() = 0;

	virtual void writeShort( short ) = 0;
	virtual short readShort() = 0;

	virtual void writeChar( char ) = 0;
	virtual short readChar() = 0;

	virtual void writeBoolean( boolean ) = 0;
	virtual boolean readBoolean() = 0;

	virtual void writeString( const char *, long maxLength = 0 ) = 0;
        // Wird der "maxLength"-Parameter bergeben, k”nnen Subklassen diesen
        // Wert verwenden, um die interne Datenorganisation im Speichermedium
        // "auszurichten", um einen schnelleren Zugriff zu erreichen.

	virtual void readString( char *, long maxLength ) = 0;
        // Diese Methode liest einen String aus dem Daten-Stream und deponiert
        // ihn im bereitgestellten Speicher ("char *"), welcher vom Client
        // zuvor reserviert wurde. Dabei wird dieser mit maximal "maxLength"
        // Zeichen (Null-Byte exklusive) gefllt und das Null-Byte gesetzt
        // (d.h. "char text[10]" erlaubt "readString( text, 9 )").
        // Die Zeichen, die aus Platzmangel nicht gelesen wurden, werden
        // bersprungen, sodass danach mit dem Lesen der folgenden
        // Daten fortgefahren werden kann. 

        virtual char *readString() = 0;
        // Diese Methode ermittelt die L„nge des im Datenfluss folgenden
        // Strings und reserviert Speicher genau dieses Umfangs. Dann wird
        // der String effektiv ausgelesen und zurckgeliefert.
        // Es liegt nun am Objekt-Client, den Speicherplatz des String zu
        // verwalten und sp„ter freizusetzen.

	virtual void writeData( void *, long size ) = 0;
	virtual void readData( void *, long size ) = 0;


	//virtual void writeContainer( Container& ); // JS: to be replaced.
	//virtual void readContainer( Container& ); // JS: to be replaced.

	//virtual void writeStringContainer( Container& ); // JS: to be replaced.
	//virtual void readStringContainer( Container& ); // JS: to be replaced.
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


#endif
/*===================* 
 * End of Storage.H  *
 *===================*/