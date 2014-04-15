#include <FStream.H>

int main()
{
	char counter[3];
	for( int i = 0; i < 3; i++ )
		counter[i] = '0';

	ifstream counterFile( "Counter.Dat", ios::in | ios::binary );
	if( counterFile )
		{
		counterFile.read( counter, 3 );
		counterFile.close();
		}


	if( counter[2] < '9' )
		counter[2]++;
	else
		{
		counter[2] = '0';
		if( counter[1] < '9' )
			counter[1]++;
		else
			{
			counter[1] = '0';
			counter[0]++;
			}

		}


	ofstream counterFileOut( "Counter.Dat",
							 ios::out | ios::binary | ios::trunc );

	counterFileOut.write( counter, 3 );
	counterFileOut.close();


	return 0;
}