/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		ListFile Source File         			*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "ListFile.H"

#include <FStream.H>
#include <String.H>


ListFile::ListFile( const char *fileName, int aStringLength ) :
	stringLength( aStringLength ),
	endOfFile( 0 )
{
	file = new ifstream( fileName, ios::in | ios::binary );
}


ListFile::~ListFile()
{
	delete file;
}



void ListFile::getNextItem( char *screen, char *printer )
{
	int temp = 0;

	int pointer = 0;

	while( (temp != '=') && (pointer <= ScreenStringLength) &&
		   (temp != EOF) )
		{
		temp = file->get();
		screen[pointer] = temp;

		pointer++;
		}

	screen[pointer - 1] = 0;

	pointer = 0;

	while( (temp != '\n') && (temp != '\r') && (pointer <= stringLength) &&
		   (temp != EOF) )
		{
		temp = file->get();

		printer[pointer] = temp;
		pointer++;
		}

	printer[pointer - 1] = 0;

	while( ((temp == '\n') || (temp == '\r') || (temp == ' ')) &&
		   (temp != EOF) )
		temp = file->get();

	if( temp == EOF )
		endOfFile = 1;
	else
		file->seekg( -1, ios::cur );
}
