#include <FStream.H>
#include <String.H>
#include <StdIO.H>
#include <StdLib.H>


void main( int argc, char **argv )
{
	if( (argc != 2) && (argc != 4) )
		return;

	char yearChar;

	yearChar = argv[1][strlen( argv[1] ) - 1];

	long startNo = 0;
	long endNo = 99999;

	if( argc == 4 )
		{
		startNo = atol( argv[2] );
		endNo = atol( argv[3] );
		if( startNo > endNo )
			{
			long temp = endNo;
			endNo = startNo;
			startNo = temp;
			}
		}

	rename( "PList.Dat", "PListTmp.Dat" );

	ifstream oldFile( "PListTmp.Dat", ios::in | ios::binary );
	ofstream newFile( "PList.Dat", ios::out | ios::binary | ios::trunc );
	ofstream trashFile( "PlistDel.Dat", ios::out | ios::binary | ios::trunc );

	char *buffer = new char[4000];
	memset( buffer, 0, 4000 );

	cout << "Ausgew„hlte Eintr„ge werden gel”scht...";

	int temp;
	long start;

	do
		{
 //		start = oldFile.tellg();

		oldFile.read( buffer, 0x02F7 );

		int keepIt = 0;

		char *point = strchr( &buffer[2], '.' );
		if( point )
			{
			if( ((point[1] == '9') || (point[1] == '0')) &&
				(point[3] == '.') &&
				(point[5] == 0) &&
				(strlen( &buffer[2] ) <= 10) )
				{
				int oldLen = strlen( &buffer[2] );
				memmove(
					&buffer[2 + 10 - oldLen],
					&buffer[2],
					oldLen );

				memset( &buffer[2], '0', 10 - oldLen );
				buffer[12] = 0;
				}
			else
				{
					// bad format (one period, but rest corrupted)!
					keepIt = 1;
				}
			}
		else
			{
			if( strlen( &buffer[2] ) > 8 )
				{
					// bad format (no period, too long)!
					keepIt = 1;
				}
			else
				{
				int oldLen = strlen( &buffer[2] );
				memmove(
					&buffer[2 + 8 - oldLen],
					&buffer[2],
					oldLen );

				memset( &buffer[2], '0', 8 - oldLen );
				buffer[10] = 0;
				}

			buffer[12] = 0;
			buffer[11] = buffer[9];
			buffer[10] = '.';
			buffer[9] = buffer[8];
			buffer[8] = buffer[7];
			buffer[7] = '.';
			}

		long no;
		char tmp[6];
		memcpy( tmp, &buffer[2], 5 );
		tmp[5] = 0;
		no = atol( tmp );

		if( (buffer[9] != yearChar) ||
			(no < startNo) ||
			(no > endNo) ||
			keepIt )
			newFile.write( buffer, 0x02F7 );
		else
			trashFile.write( buffer, 0x02F7 );

		// next record:
		temp = oldFile.get();
		oldFile.seekg( -1, ios::cur );
		}
	while( temp != EOF );

	cout << "beendet." << '\n' << '\r' << '\n' << '\r';

	cout << "PV muss nun mit dem Parameter \"/R\" gestartet werden!" << '\n' << '\r'
			<< '\n' << '\r' << '\n' << '\r';

	delete[] buffer;


	remove( "PListTmp.Dat" );
}
