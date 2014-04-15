#include <FStream.H>
#include <String.H>
#include <StdIO.H>
#include <StdLib.H>


void main()
{
	remove( "PList01.Dat" );
	remove( "PList02.Dat" );

	ifstream oldFile( "PList.Dat", ios::in | ios::binary );

	ofstream newFile1( "PList01.Dat", ios::out | ios::binary | ios::trunc );
	ofstream newFile2( "PList02.Dat", ios::out | ios::binary | ios::trunc );

	char *buffer = new char[4000];
	memset( buffer, 0, 4000 );

	cout << "PList.Dat wird aufgeteilt....";

	int temp;
	long start;

	do
		{
		start = oldFile.tellg();

		oldFile.read( buffer, 2412 );

		char date[9];
		strcpy( date, &buffer[0x47] );
		date[2] = 0;
		date[5] = 0;

//		int day = atoi( &date[0] );
		int month = atoi( &date[3] );
		int year = atoi( &date[6] );

		// 1.4.1995 und sp„ter --> 1
		// Rest --> 2

		if( (year > 95) || (year < 10) ||
			((year == 95) && (month >= 4)) )
			newFile1.write( buffer, 2412 );
		else
			newFile2.write( buffer, 2412 );


		// next record:
		temp = oldFile.get();
		oldFile.seekg( -1, ios::cur );
		}
	while( temp != EOF );

	cout << "beendet." << '\n' << '\r' << '\n' << '\r';

	cout << "PList01.Dat und PList02.Dat jeweils zu PList.Dat umbenennen" << '\n' << '\r'
			<< "und \"PV /R\" starten."
			<< '\n' << '\r' << '\n' << '\r';

	delete[] buffer;
}
