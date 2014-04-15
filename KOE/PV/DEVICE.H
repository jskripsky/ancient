/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Device Include File		    			*/
/*												*/
/*----------------------------------------------*/

#ifndef DEVICE
#define DEVICE


const ushort text = 0;
const ushort form = 1;
const ushort card = 2;

const char esc = 27;


struct deviceOptions
{
	Boolean card;
	Boolean screenOnly;

	ushort fieldLength;

	char track;
	unsigned char offset;
	char length;

	Boolean cardLabel;
	char labelLine;
	char labelOffset;
	char labelLength;
};


const trackLength = 142; // old version: 120
const noTracks    = 3;

const lineLength  = 29;
const noLines	  = 6;


class TOutputDevice : private TObject
{
public:
	TOutputDevice( ushort aMode );
	~TOutputDevice();

	void print( deviceOptions&, char * );

	void encodeCard();
	void checkStatus();
	void processEcho();

	void writeCommand( char *command, char *data = 0, ushort dataLen = 0 );

	void open( const char * );
	void close();
	void readBytes( void *, ushort len );
	void writeBytes( void *, ushort len );

	ushort mode;

	ifstream *formatingInfo;
	int xOrigin, yOrigin;

private:

	void filterExtChars( char *, ushort len );

	char portName[5];
	char *fBuffer;
	fpstream *device;

	char *trackBuffer;
	char *label;

	ushort encoder;
};


#endif