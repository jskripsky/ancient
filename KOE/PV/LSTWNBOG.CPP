/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		List Window Bogenhausen Source File 	*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "ListWin.Use"
#include "Person\Info.Use"

#include <TV.H>
#include "ListWin.H"
#include "LogPrint.H"
#include "Person\Info.H"

#include <FStream.H>
#include <String.H>
#include <DOS.H>
#include <DIR.H>
#include <StdLib.H>


class pvofstream : public ofstream
{
public:
	pvofstream( const char *fileName, int m = ios::out, int p = filebuf::openprot ) :
		ofstream( fileName, m, p )
		{}

	virtual ostream& write(const signed char*, int n);
};


ostream& pvofstream::write(const signed char *data, int n )
{
	signed char *buffer = new signed char[n];
	memcpy( buffer, data, n );

	Boolean endOfString = False;

	for( int i = 0; i < n; i++ )
		{
		if( buffer[i] == 0 )
			endOfString = True;

		if( endOfString )
			buffer[i] = ' ';
		}

	ofstream::write( buffer, n );

	delete[] buffer;

	return *this;
}


void TListWindow::BogenhausenExport( TInfo *info )
{
	TPerson *person = (TPerson *)info->getRecord();

	signed char *data = new char[TPerson::dataSize()];
	memcpy( data, person->getData(), TPerson::dataSize() );

	char fileName[13];
	strcpy( fileName, &data[0x3C] );
	strcat( fileName, ".Pat" );

	mkdir( "Export" );

	char fullpath[13 + 7];
	strcpy( fullpath, "EXPORT\\" );
	strcat( fullpath, fileName );

	pvofstream file( fullpath, ios::out | ios::trunc );

	signed char blanks[80];
	memset( blanks, 0, sizeof( blanks ) );


	file << "A";

	switch( info->getAccessCode() )
		{
		case 1:
		case 3:
		case 5:
			file << "A";
			break;

		case 2:
		case 4:
		case 6:
			file << "S";
			break;
		}

	file << "11";

	file << '0';
	file.write( &data[0x3C], 8 );

	file.write( data, 30 );
	file.write( blanks, 10 );

	file.write( &data[0x1F], 15 );

	file.write( blanks, 10 );
	file.write( blanks, 30 );

	strcpy( blanks, &data[0x2F] );
	if( blanks[0] == ' ' )
		blanks[0] = '0';
	if( blanks[3] == ' ' )
		blanks[3] = '0';
	file.write( blanks, 10 );
	memset( blanks, 0, sizeof( blanks ) );

	file.write( blanks, 30 );

	file.write( blanks, 2 );

	switch( data[0x3A] )
		{
		case 0:
			file << 'M';
			break;

		case 1:
			file << 'W';
			break;
		}

	file.write( blanks, 3 );
	file.write( blanks, 2 );
	file.write( blanks, 20 );

	file.write( &data[0x54], 30 );
	file.write( &data[0x73], 8 );
	file.write( &data[0x7C], 20 );

	file.write( blanks, 2 );
	file.write( blanks, 20 );
	file.write( blanks, 60 );
	file.write( blanks, 1 );
	file.write( blanks, 1 );

	file << "\n";


	file << "A";

	switch( info->getAccessCode() )
		{
		case 1:
		case 3:
		case 5:
			file << "A";
			break;

		case 2:
		case 4:
		case 6:
			file << "S";
			break;
		}

	file << "21";

	file << '0';
	file.write( &data[0x3C], 8 );

	file.write( blanks, 30 );

	strcpy( blanks, &data[0x45] );
	if( blanks[0] == ' ' )
		blanks[0] = '0';
	if( blanks[3] == ' ' )
		blanks[3] = '0';
	file.write( blanks, 8 );
	memset( blanks, 0, sizeof( blanks ) );

	strcpy( blanks, &data[0x4E] );
	blanks[2] = '.';
	file.write( blanks, 5 );
	memset( blanks, 0, sizeof( blanks ) );

	switch( data[0x17F + 21] )
		{
		case 0:
			file.write( "A3", 2 );
			strcpy( blanks, "Selbst" );
			break;

		case 1:
			file.write( "A1", 2 );
			strcpy( blanks, "Rettungwagen" );
			break;

		case 2:
			file.write( "A2", 2 );
			strcpy( blanks, "Notarztwagen" );
			break;

		case 3:
			file.write( "A4", 2 );
			strcpy( blanks, "Hubschrauber" );
			break;
		}

	file.write( blanks, 20 );
	memset( blanks, 0, sizeof( blanks ) );

	file.write( blanks, 3 );
	file.write( blanks, 10 );
	file.write( blanks, 30 );

	file.write( &data[0x5D7 + 21], 38 );
	file.write( &data[0x5D7 + 39 + 21], 38 );
	file.write( &data[0x5D7 + 78 + 21], 38 );
	file.write( &data[0x5D7 + 177 + 21], 6 );

	formDialog->changeToPageNo( 2, False );
	TField *field = formDialog->currentPage()->at( 0 );
	field->getString( blanks );
	file.write( blanks, 10 );

	memset( blanks, 0, sizeof( blanks ) );
	file.write( blanks, 4 );  // blanks?

//	file.write( blanks, 3 );
//	memset( blanks, 0, sizeof( blanks ) );
//	file.write( blanks, 1 );

//	file.write( blanks, 5 );  // No blanks!
//	file.write( blanks, 2 );  // No blanks!

	formDialog->changeToPageNo( 2, False );
	field = formDialog->currentPage()->at( 0 );
	field->getString( blanks );

	Boolean specialStation = False;
	int stationNum;

	if( strncmp( blanks, "04", 2 ) == 0 )
		{
		specialStation = True;
		file.write( "N", 5 );
		}

	if( strncmp( blanks, "05", 2 ) == 0 )
		{
		specialStation = True;
		file.write( "OINT", 5 );
		}

	if( strncmp( blanks, "08", 2 ) == 0 )
		{
		specialStation = True;
		file.write( "B", 5 );
		}

	if( strncmp( blanks, "31B", 3 ) == 0 )
		{
		specialStation = True;
		file.write( "N", 5 );
		}

	if( strncmp( blanks, "32", 2 ) == 0 )
		{
		specialStation = True;
		file.write( "N", 5 );
		}

	if( strncmp( blanks, "35", 2 ) == 0 )
		{
		specialStation = True;
		file.write( "R", 5 );
		}

	if( strncmp( blanks, "14", 2 ) == 0 )
		{
		specialStation = True;
		file.write( "AKUT", 5 );
		}

	if( strncmp( blanks, "15", 2 ) == 0 )
		{
		specialStation = True;
		file.write( "AKUT", 5 );
		}

	if( strncmp( blanks, "18", 2 ) == 0 )
		{
		specialStation = True;
		file.write( "AKUT", 5 );
		}

	if( strncmp( blanks, "33", 2 ) == 0 )
		{
		specialStation = True;
		file.write( "AKUT", 5 );
		}

	if( strncmp( blanks, "34", 2 ) == 0 )
		{
		specialStation = True;
		file.write( "AKUT", 5 );
		}
	memset( blanks, 0, sizeof( blanks ) );

	if( specialStation )
		{
		file.write( "01", 2 );
		file.write( blanks, 5 );
		file.write( blanks, 2 );
		}
	else
	switch( info->getAccessCode() )
		{
		case 1:
		case 3:
		case 5:
			if( data[0xCB] == 1 )
				{
				file.write( "AMB", 5 );
				file.write( "02", 2 );
				file.write( blanks, 5 );
				file.write( blanks, 2 );
				}
			else
				{
				file.write( blanks, 5 );
				file.write( blanks, 2 );
				file.write( blanks, 5 );
				file.write( blanks, 2 );
				}

			break;

		case 2:
		case 4:
		case 6:
			if( data[0xCB] == 1 )
				{
				file.write( "AKUT", 5 );
				file.write( "01", 2 );
				file.write( blanks, 5 );
				file.write( blanks, 2 );
				}
			else
				{
				file.write( "AKUT", 5 );
				file.write( "01", 2 );
				file.write( "ML", 5 );
				file.write( "04", 2 );
				}

			break;

		}


	file.write( blanks, 5 * 7 );
	file.write( blanks, 10 );
	file.write( blanks, 1 );

	file << "\n";


	file << "A";

	switch( info->getAccessCode() )
		{
		case 1:
		case 3:
		case 5:
			file << "A";
			break;

		case 2:
		case 4:
		case 6:
			file << "S";
			break;
		}

	file << "41";

	file << '0';
	file.write( &data[0x3C], 8 );

	file.write( blanks, 3 );
	file.write( data, 30 );

	file.write( blanks, 10 );
	file.write( blanks, 30 );
	file.write( blanks, 8 );
	file.write( blanks, 20 );
	file.write( blanks, 20 );
	file.write( blanks, 30 );
	file.write( blanks, 30 );
	file.write( blanks, 8 );
	file.write( blanks, 20 );
	file.write( blanks, 20 );

//	file.write( &data[0xB8 + 21], 9 );
	formDialog->changeToPageNo( 1, False );
	field = formDialog->currentPage()->at( 0 );
	field->getString( blanks );
	if( info->getAccessCode() != 1 )
		file.write( blanks, 9 ); // No blanks!
	else
		file.write( "DIVSONA", 9 );

	memset( blanks, 0, sizeof( blanks ) );

	file.write( blanks, 20 );
	file.write( blanks, 1 );
	file.write( blanks, 10 );


	file << "\n";


	if( info->getAccessCode() == 1 )
		{
		file << "A";

		switch( info->getAccessCode() )
			{
			case 1:
			case 3:
			case 5:
				file << "A";
				break;

			case 2:
			case 4:
			case 6:
				file << "S";
				break;
			}

		file << "51";

		file << '0';
		file.write( &data[0x3C], 8 );

		if( info->getAccessCode() != 1 )
			file.write( blanks, 9 );
		else
			file.write( "DIVSONA", 9 );

		strcpy( blanks, &data[0x99] );
		file.write( blanks, 30 ); //Name KrKasse
		memset( blanks, 0, sizeof( blanks ) );

		strcpy( blanks, &data[0x91] );
		file.write( blanks, 30 ); // Kassennr.
		memset( blanks, 0, sizeof( blanks ) );

		strcpy( blanks, &data[0xB6] );
		file.write( blanks, 30 ); //Versnr.
		memset( blanks, 0, sizeof( blanks ) );

		strcpy( blanks, &data[0xC3] );
		file.write( blanks, 8 ); //Status
		memset( blanks, 0, sizeof( blanks ) );

		file.write( blanks, 20 );

		file << "\n";
		}


	if( data[0xCB] == 2 )
		{
		file << "A";

		switch( info->getAccessCode() )
			{
			case 1:
			case 3:
			case 5:
				file << "A";
				break;

			case 2:
			case 4:
			case 6:
				file << "S";
				break;
			}

		file << "61";

		file << '0';
		file.write( &data[0x3C], 8 );

		char name[100];
		strcpy( name, data );
		strcat( name, " " );
		strcat( name, &data[0x1F] );
		name[30] = 0;
		file.write( name, 30 ); //Name Vorname

		file.write( blanks, 20 );
		file.write( blanks, 30 );
		file.write( blanks, 30 );
		file.write( blanks, 8 );
		file.write( blanks, 20 );
		file.write( blanks, 45 );
		file.write( blanks, 8 );
		file.write( blanks, 12 );
		file.write( blanks, 30 );
		file.write( blanks, 9 );

		file << "\n";
		}

	formDialog->changeToPageNo( noPage, False );

	delete[] data;
}


void TListWindow::BogenhausenProtocol( TInfo *info )
{
	info;
}