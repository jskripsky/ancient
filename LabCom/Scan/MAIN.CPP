#include "Compiler.H"

#include "Types.H"
#include "ScanApp.H"

#include <ConIO.H>
#include <StdIO.H>
#include <String.H>


int main( int argc, char **argv )
{
	Boolean dumpMode = False;
	Boolean invalidParameters = False;

	if( argc > 1 )
		{
		if( argc == 2 )
			{
			strlwr( argv[1] );
			if( strcmp( argv[1], "/dump" ) == 0 )
				dumpMode = True;
			else
				invalidParameters = True;
			}
		else
			invalidParameters = True;
	}

	if( invalidParameters )
		{
		printf( "\n" );
		printf( "Syntax:\n" );
		printf( "=======\n\n" );
		printf( "Scan [/dump]\n\n\n" );

		printf( "Press any key to continue.\n" );
		getch();
		}
	else
		{
		TScanApplication scanApp( dumpMode );
		scanApp.run();
		}

	return 0;
}
