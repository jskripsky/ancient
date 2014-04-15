#include "FStream.H"


int main( int argc, char *argv[] )
{
	if( argc < 2 )
		return 1;

	ifstream file( argv[1] );
	if( !file )
		return 2;

	unsigned int numOfLines = 1;

	while( !file.eof() )
		{
		char temp;
		file.get( temp );
		if( temp == '\n' )
			numOfLines++;
		}

	cout << "Number of lines: " << numOfLines;
	return 0;
}