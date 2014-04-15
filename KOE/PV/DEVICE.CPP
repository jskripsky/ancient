/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Device Source File 		    			*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Device.Use"
#include "FormDef\FormDef.Use"

#include <TV.H>
#include "Device.H"
#include "FormDef\FormDef.H"
#include "Gadgets\Config.H"

#include <String.H>
#include <StdLib.H>
#include <CType.H>
#include <DOS.H>
#include <FCNTL.H>

#include <FStream.H>


/*---- Constructors, Destructors ---------------*/

TOutputDevice::TOutputDevice( ushort aMode ) :
	mode( aMode )
{
	switch( mode )
		{
		case text:
		case form:

			ushort numCopies = 0;

			if( (mode == text) && formDef->numRawPrintCopiesDlg )
				{
				TDialog *dlg = new TDialog( TRect( 27, 8, 53, 15 ),
											"Anzahl Kopien" );

				dlg->insert( new TButton( TRect( 8, 4, 18, 6 ), "~O~K",
										  cmOK, bfDefault ) );

				TInputLine *il = new TInputLine( TRect( 10, 2, 16, 3 ), 3 );
				dlg->insert( il );

				char string[4];

				do
					{
					strcpy( string, "1" );
					il->setData( string );

					TProgram::deskTop->execView( dlg );

					il->getData( string );
					numCopies = atoi( string );
					}
				while( numCopies == 0 );

				destroy( dlg );
				}

			if( formDef->oldDevice && (mode == form) )
				strcpy( portName, "NUL" );
			else
				config->getPrinterPortName( portName );

			device = new fpstream( portName, ios::out | ios::trunc );

			if( config->passThrough() )
				device->writeBytes( "\x1BJ\r", 3 );

			if( mode == form )
				device->writeBytes( "@BS", 3 );

			if( (mode == text) && formDef->formatedRawPrint )
				{
				*device << (char)esc << 'E';

				if( formDef->numRawPrintCopiesDlg )
					{
					*device << (char)esc;

					char string[6];
					strcpy( string, "&l" );

					char number[4];
					itoa( numCopies, number, 10 );
					strcat( string, number );
					strcat( string, "X" );

					device->writeBytes( string, strlen( string ) );
					}

				formatingInfo = new ifstream( "FORMAT.RES" );
				char number[7];
				number[6] = 0;

				formatingInfo->read( number, 6 );
				xOrigin = atoi( number );
				formatingInfo->seekg( 2, ios::cur );

				formatingInfo->read( number, 6 );
				yOrigin = atoi( number );
				formatingInfo->seekg( 2, ios::cur );
				}

			break;

		case card:
			config->getEncoderPortName( portName );
			open( portName );
			trackBuffer = new char[noTracks * trackLength];
			memset( trackBuffer, ' ', noTracks * trackLength );

			label = new char[noLines * lineLength];
			memset( label, ' ', noLines * lineLength );

			break;
		}
}


TOutputDevice::~TOutputDevice()
{
	switch( mode )
		{
		case text:
		case form:
			if( mode == text )
				*device << '\f';

			if( config->passThrough() )
				device->writeBytes( "\x1BK\r", 3 );

			if( (mode == text) && formDef->formatedRawPrint )
				{
				*device << (char)esc << 'E';
				delete formatingInfo;
				}

			break;

		case card:
			encodeCard();
			delete[] trackBuffer;
			close();
			break;
		}

	if( mode != card )
		{
		device->flush();
		device->close();
		delete device;
		}
}


/*---- Public Methods --------------------------*/

void TOutputDevice::print( deviceOptions& options, char *string )
{
	ushort stringLength = strlen( string );
	char *deviceString;

	switch( mode )
		{
		case text:
			if( formDef->formatedRawPrint )
				{
				int x, y;

				char number[7];
				number[6] = 0;

				formatingInfo->read( number, 6 );
				x = atoi( number );
				formatingInfo->seekg( 2, ios::cur );

				formatingInfo->read( number, 6 );
				y = atoi( number );
				formatingInfo->seekg( 2, ios::cur );

				x += xOrigin;
				y += yOrigin;

				char posString[2][7];
				itoa( x, posString[0], 10 );
				itoa( y, posString[1], 10 );

				*device << (char)esc << '*' << 'p';
				device->writeBytes( posString[0], strlen( posString[0] ) );
				*device << 'X';

				*device << (char)esc << '*' << 'p';
				device->writeBytes( posString[1], strlen( posString[1] ) );
				*device << 'Y';
				}

			device->writeBytes( string, stringLength );

			if( !formDef->formatedRawPrint )
				*device << '\r' << '\n';
			break;

		case form:
			if( !options.screenOnly )
				{
				deviceString = new char[options.fieldLength + 1];
				strcpy( deviceString, string );

				filterExtChars( deviceString, options.fieldLength );

				memset( &deviceString[stringLength], ' ',
						options.fieldLength - stringLength );
				device->writeBytes( deviceString, options.fieldLength );
				delete[] deviceString;
				}
			break;

		case card:
			if( options.card )
				strncpy( &trackBuffer[options.track * trackLength +
									  options.offset],
						 string,
						 options.length );
//				memcpy( &trackBuffer[options.track * trackLength +
//									 options.offset],
//						string,
//						options.length );

			if( options.cardLabel )
				strncpy( &label[options.labelLine * lineLength +
							   options.labelOffset],
						 string,
						 options.labelLength );

//				memcpy( &label[options.labelLine * lineLength +
//							   options.labelOffset],
//						string,
//						options.labelLength );
			break;
		}
}


void TOutputDevice::encodeCard()
{
	static Boolean resetDone = False;

	if( !resetDone || formDef->oldDevice )
		{
		writeCommand( "@" );
		checkStatus();
		if( !formDef->oldDevice )
			delay( 3000 );
		else
			delay( 1000 );

		resetDone = True;
		}

	filterExtChars( trackBuffer, noTracks * trackLength );

	static Boolean tracksSet = False;

	if( formDef->oldDevice )
		{
		writeCommand( "E" );
		checkStatus();

//		if( !tracksSet )
//			{
			writeCommand( "T2" );
			checkStatus();
			writeCommand( "T3" );
			checkStatus();
			tracksSet = True;
//			}
		}

	char trackCommand[3] = "Ix";

	for( char c = 0; c < noTracks; c++ )
		{
		trackCommand[1] = ((char)(c + '1'));

		int dataLen;

		if( formDef->oldDevice )
			switch( c )
				{
				case 0:
					dataLen = 76;
					break;

				case 1:
					dataLen = 36;
					for( int i = 0; i < dataLen; i++ )
						{
						int index = c * trackLength + i;
						switch( trackBuffer[index] )
							{
							case ' ':
								trackBuffer[index] = '0';
								break;

							case '.':
								trackBuffer[index] = 'D';
								break;
							}
						}

					break;

				case 2:
					dataLen = 104;
					break;
				}
		else
			dataLen = trackLength;

		writeCommand( trackCommand, &trackBuffer[c * trackLength],
					  dataLen );
		if( !formDef->oldDevice )
			checkStatus();
		else
			processEcho();
		}

	if( !formDef->oldDevice )
		{
		filterExtChars( label, noLines * lineLength );

		writeCommand( "N" );
		checkStatus();


		char command[3];
		command[0] = esc;
		command[2] = '\r';


		command[0] = 0x1C;
		command[1] = 'T';
		writeBytes( command, 3 );

		for( c = 0; c < noLines; c++ )
			{
			if( c == 0 )
				{
				command[1] = 'F';
				writeBytes( command, 2 );
				}
			else
				{
				command[1] = 'H';
				writeBytes( command, 2 );
				}

			char indent[2] = { ' ', ' ' };
			writeBytes( indent, sizeof( indent ) );
			writeBytes( &label[c * lineLength], lineLength );
			command[1] = '\r';
			command[2] = '\n';
			writeBytes( &command[1], 2 );
			}

		writeCommand( "O" );
		checkStatus();
		}

	writeCommand( "W" );
	checkStatus();

	if( !formDef->oldDevice )
		writeCommand( "A" );

	if( formDef->oldDevice )
		messageBox( "Bitte Karte einfhren, warten, bis "
					"der Kodiervorgang beendet ist und "
					"mit Enter best„tigen.", mfInformation | mfOKButton );

	writeCommand( "H" );
	if( formDef->oldDevice )
		checkStatus();
}


void TOutputDevice::checkStatus()
{
	if( formDef->oldDevice )
		return; //!!!!!!!!!!!!!

	int counter = 0;
	char status;
	char cr;

	readBytes( &cr, 1 );
	do
		{
		status = cr;
		readBytes( &cr, 1 );
		counter++;
		}
	while( (cr != '\r') && (counter <= 3) );

	if( status != '!' )
		{
		sound( 1000 );
		delay( 1000 );
		nosound();
		}
}


void TOutputDevice::processEcho()
{
	if( formDef->oldDevice )
		return; //!!!!!!!!!!!!!

	int counter = 0;
	char cr;

	do
		{
		readBytes( &cr, 1 );
		counter++;
		}
	while( (cr != '\r') && (counter <= 200) );
}


void TOutputDevice::writeCommand( char *command, char *data,
								  ushort dataLen )
{
	char temp = esc;
	writeBytes( &temp, sizeof( temp ) );

	writeBytes( command, strlen( command ) );

	if( data )
		{
		if( dataLen > 0 )
			writeBytes( data, dataLen );
		else
			writeBytes( data, strlen( data ) );
		}

	temp = '\r';
	writeBytes( &temp, sizeof( temp ) );
	if( formDef->oldDevice )
		delay( 200 ); //!!!!!!!
}


void TOutputDevice::open( const char *portName )
{
	_dos_open( portName, O_RDWR, (int *)&encoder );
}


void TOutputDevice::close()
{
	_dos_close( encoder );
}


void TOutputDevice::readBytes( void *buffer, ushort len )
{
	unsigned temp;
	_dos_read( encoder, buffer, len, &temp );
}


void TOutputDevice::writeBytes( void *buffer, ushort len )
{
	unsigned temp;
	_dos_write( encoder, buffer, len, &temp );
}


/*---- Private Methods -------------------------*/

void TOutputDevice::filterExtChars( char *string, ushort len )
{
	if( mode == card )
		for( int i = 0; i < len; i++ )
			string[i] = toupper( string[i] );


	for( int i = 0; i < len; i++ )
		switch( string[i] )
			{
			case 0:
				string[i] = ' ';
				break;

			case 'Ž':
				string[i] = '[';
				break;
			case '„':
				if( mode != card )
					string[i] = '{';
				else
					string[i] = '[';
				break;

			case 'š':
				string[i] = ']';
				break;
			case '':
				if( mode != card )
					string[i] = '}';
				else
					string[i] = ']';
				break;

			case '™':
				string[i] = '\\';
				break;
			case '”':
				if( mode != card )
					string[i] = '|';
				else
					string[i] = '\\';
				break;

			case '€':
				string[i] = 'C';
				break;
			case '‡':
				string[i] = 'c';
				break;

			case '‚':
			case 'Š':
			case 'ˆ':
				string[i] = 'e';
				break;

			case '':
				string[i] = 'E';
				break;

			case '…':
			case ' ':
				string[i] = 'a';
				break;

			case '“':
				string[i] = 'o';
				break;

			case '–':
				string[i] = 'u';
				break;

			case 'á':
				string[i] = 's';
				break;
			}
}