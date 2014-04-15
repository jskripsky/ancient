#include <FStream.H>
#include <String.H>
#include <StdIO.H>


void main()
{
	remove( "OldRes.Dat" );
	remove( "OldRes.Idx" );
	remove( "OldRes.Tab" );

	rename( "PList.Dat", "OldRes.Dat" );
	rename( "PList.Idx", "OldRes.Idx" );
	rename( "PList.Tab", "OldRes.Tab" );

	ifstream oldFile( "OldRes.Dat", ios::in | ios::binary );
	ofstream newFile( "PList.Dat", ios::out | ios::binary | ios::trunc );

	char *buffer = new char[4000];
	memset( buffer, 0, 4000 );

	cout << "Migration wird gestartet.....";

	int temp;
	long start;

	do
		{
		start = oldFile.tellg();

		oldFile.read( buffer, 0xB8 );
		newFile.write( buffer, 0xB8 );

		memset( buffer, 0, 21 );
		newFile.write( buffer, 21 );

		oldFile.read( buffer, 2412 - 0xB8 );
		newFile.write( buffer, 2412 - 0xB8 );


		// next record:
		temp = oldFile.get();
		oldFile.seekg( -1, ios::cur );
		}
	while( temp != EOF );

	cout << "beendet." << '\n' << '\r' << '\n' << '\r';

	cout << "Neue \"FORMDEF.RES\"-Datei installieren und \"PV /R\" starten."
		 << '\n' << '\r' << '\n' << '\r';

	delete[] buffer;
}
