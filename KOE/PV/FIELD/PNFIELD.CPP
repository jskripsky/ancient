/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		PNumberField Source File    			*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Field\PNField.Use"

#define Uses_TStreamableClass

#include <TV.H>
#include "Field\PNField.H"

#include <FStream.H>
#include <String.H>
#include <CType.H>
#include <StdLib.H>
#include <DOS.H>


TPNumberField::TPNumberField( TMeasurements& m, const char *aLabel,
							  ushort aStringLength,
							  const char *aNumberRangeFilename,
							  ushort options ) :
	TTextField( m, aLabel, aStringLength, options )
{
	strcpy( numberRangeFilename, aNumberRangeFilename );
}


/*---- Public Methods --------------------------*/

void TPNumberField::setup()
{
/*
	char *temp = new char[control->dataSize()];
	control->getData( temp );
	if( strlen( temp ) == 0 )
		{
		long start, end;
		long number;

		ifstream inFile( "PNumber.Dat", ios::in | ios::binary );
		if( !inFile )
			{
			getNumberRange( &start, &end );
			number = start;
			}
		else
			{
			inFile.read( (char *)&start, sizeof( start ) );
			inFile.read( (char *)&end, sizeof( end ) );

			inFile.read( (char *)&number, sizeof( number ) );
			inFile.close();

			if( number == end )
				{
				// Warning/Error Message

				number = 0;
				}
			else
				number++;
			}

		ofstream outFile( "PNumber.Dat", ios::out | ios::binary |
						  ios::trunc );

		outFile.write( (char *)&start, sizeof( start ) );
		outFile.write( (char *)&end, sizeof( end ) );

		outFile.write( (char *)&number, sizeof( number ) );
		outFile.close();

		temp[0] = '1';

		date sysDate;
		getdate( &sysDate );

		temp[1] = (sysDate.da_year % 10) + '0';

		temp[2] = '0';
		temp[3] = '0';
		temp[4] = '0';
		temp[5] = '0';
		temp[6] = '0';

		char numberString[10];
		ltoa( number, numberString, 10 );
		strcpy( &temp[7 - strlen( numberString )], numberString );

		int check = 10 - (((temp[0] - '0') * 7 +
						   (temp[1] - '0') * 9 +
						   (temp[2] - '0') * 3 +
						   (temp[3] - '0') * 1 +
						   (temp[4] - '0') * 7 +
						   (temp[5] - '0') * 9 +
						   (temp[6] - '0') * 3) % 10);

		if( check == 10 )
			check = 0;

		temp[7] = check + '0';

		temp[8] = 0;

		control->setData( temp );
		}
	delete[] temp;

//	control->setState( sfDisabled, True );
*/
}


Boolean TPNumberField::check()
{
	if( !TTextField::check() )
		return False;

	char *temp = new char[control->dataSize()];
	control->getData( temp );

	int length = strlen( temp );
	if( length != stringLength )
		{
		checkError( "Patientennr. ist ungltig!" );
		return False;
		}

	int check = 10 - (((temp[0] - '0') * 7 +
					   (temp[1] - '0') * 9 +
					   (temp[2] - '0') * 3 +
					   (temp[3] - '0') * 1 +
					   (temp[4] - '0') * 7 +
					   (temp[5] - '0') * 9 +
					   (temp[6] - '0') * 3) % 10);

	if( check == 10 )
		check = 0;

	int checkChar = temp[7] - '0';
	delete[] temp;

	if( check != checkChar )
		{
		checkError( "Patientennr. ist ungltig!" );
		return False;
		}

//	control->setState( sfDisabled, False );

	return True;
}


void TPNumberField::getNumberRange( long *start, long *end )
{
	ifstream file( numberRangeFilename, ios::in | ios::binary );
	if( !file )
		{
		*start = 0;
		*end = 10000;
		return;
		}

	char startString[10];
	char endString[10];

	int temp;
	int pointer = 0;

	startString[0] = 0;
	endString[0] = 0;

	do
		{
		temp = file.get();
		startString[pointer] = temp;

		pointer++;
		}
	while( (temp != '-') && isdigit( temp ) && (pointer <= 9) &&
		   (temp != EOF) );

	startString[pointer - 1] = 0;

	pointer = 0;

	do
		{
		temp = file.get();
		endString[pointer] = temp;

		pointer++;
		}
	while( (temp != '-') && isdigit( temp ) && (pointer <= 9) &&
		   (temp != EOF) );

	endString[pointer - 1] = 0;

	*start = atol( startString );
	*end = atol( endString );
}


/*---- TStreamable Methods ---------------------*/

const char * const TPNumberField::name = "TPNumberField";


TPNumberField::TPNumberField( StreamableInit ) :
	TTextField( streamableInit )
{}


TStreamable *TPNumberField::build()
{
	return (TStreamable *)new TPNumberField( streamableInit );
}


void TPNumberField::write( opstream& os )
{
	TTextField::write( os );
	os.writeString( numberRangeFilename );
}


void *TPNumberField::read( ipstream& is )
{
	TTextField::read( is );
	is.readString( numberRangeFilename, 13 );
	return this;
}


TStreamableClass RPNumberField( TPNumberField::name,
			 TPNumberField::build,
			 __DELTA(TPNumberField)
			   );



TSchwyzPNumberField::TSchwyzPNumberField( TMeasurements& m,
							  const char *aLabel,
							  ushort aStringLength,
							  const char *aNumberRangeFilename,
							  ushort options ) :
	TTextField( m, aLabel, aStringLength, options )
{
	strcpy( numberRangeFilename, aNumberRangeFilename );
}


/*---- Public Methods --------------------------*/

void TSchwyzPNumberField::setup()
{
	char *temp = new char[control->dataSize()];
	control->getData( temp );
	if( strlen( temp ) == 0 )
		{
		long start, end;
		long number;

		ifstream inFile( "PNumber.Dat", ios::in | ios::binary );
		if( !inFile )
			{
			getNumberRange( &start, &end );
			number = start;
			}
		else
			{
			inFile.read( (char *)&start, sizeof( start ) );
			inFile.read( (char *)&end, sizeof( end ) );

			inFile.read( (char *)&number, sizeof( number ) );
			inFile.close();

			if( number == end )
				{
				// Warning/Error Message

				number = 0;
				}
			else
				number++;
			}

		ofstream outFile( "PNumber.Dat", ios::out | ios::binary |
						  ios::trunc );

		outFile.write( (char *)&start, sizeof( start ) );
		outFile.write( (char *)&end, sizeof( end ) );

		outFile.write( (char *)&number, sizeof( number ) );
		outFile.close();

		temp[0] = '1';

		date sysDate;
		getdate( &sysDate );

		memset( temp, 0, control->dataSize() );

		char numberString[10];
		ltoa( number, numberString, 10 );
		strcpy( &temp[control->dataSize() - 1 - strlen( numberString )],
				numberString );

		control->setData( temp );
		}
	delete[] temp;

	control->setState( sfDisabled, True );
}


Boolean TSchwyzPNumberField::check()
{
	if( !TTextField::check() )
		return False;

	control->setState( sfDisabled, False );

	return True;
}


void TSchwyzPNumberField::getNumberRange( long *start, long *end )
{
	ifstream file( numberRangeFilename, ios::in | ios::binary );
	if( !file )
		{
		*start = 0;
		*end = 10000;
		return;
		}

	char startString[10];
	char endString[10];

	int temp;
	int pointer = 0;

	startString[0] = 0;
	endString[0] = 0;

	do
		{
		temp = file.get();
		startString[pointer] = temp;

		pointer++;
		}
	while( (temp != '-') && isdigit( temp ) && (pointer <= 9) &&
		   (temp != EOF) );

	startString[pointer - 1] = 0;

	pointer = 0;

	do
		{
		temp = file.get();
		endString[pointer] = temp;

		pointer++;
		}
	while( (temp != '-') && isdigit( temp ) && (pointer <= 9) &&
		   (temp != EOF) );

	endString[pointer - 1] = 0;

	*start = atol( startString );
	*end = atol( endString );
}


/*---- TStreamable Methods ---------------------*/

const char * const TSchwyzPNumberField::name = "TSchwyzPNumberField";


TSchwyzPNumberField::TSchwyzPNumberField( StreamableInit ) :
	TTextField( streamableInit )
{}


TStreamable *TSchwyzPNumberField::build()
{
	return (TStreamable *)new TSchwyzPNumberField( streamableInit );
}


void TSchwyzPNumberField::write( opstream& os )
{
	TTextField::write( os );
	os.writeString( numberRangeFilename );
}


void *TSchwyzPNumberField::read( ipstream& is )
{
	TTextField::read( is );
	is.readString( numberRangeFilename, 13 );
	return this;
}


TStreamableClass RSchwyzPNumberField( TSchwyzPNumberField::name,
			 TSchwyzPNumberField::build,
			 __DELTA(TSchwyzPNumberField)
			   );

