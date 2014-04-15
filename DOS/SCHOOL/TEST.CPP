
#include "HashTabl.H"

#include <StdLib.H>
#include <IOStream.H>
#include <Time.H>

const int kHTSize = 1021;

void main()
{
	int data = 0;

	randomize();

	THashTable ht( kHTSize );

	Key keyList[kHTSize];
	for( int i = 0; i < kHTSize; i++ )
		keyList[i] = rand();

	cout << "Starting Test... " << endl << endl;

	for( i = 0; i < 21; i++ )
		{
		for( int c = 0; c < 50; c++ )
			ht.Insert( keyList[i * 50 + c], data );

		cout << "Load: " << ht.GetLoadRatio() << "   ";

		clock_t cl = clock();

		for( c = 0; c < 10000; c++ )
			ht.Find( keyList[random( kHTSize )], data );

		cout << "S: " << (int)(clock() - cl) << "  ";

		cl = clock();

		for( c = 0; c < 10000; c++ )
			ht.Find( keyList[random( kHTSize ) + kHTSize], data );

		cout << "U: " << (int)(clock() - cl) << endl;

		}


}



/* Output:
   =======

   Starting Test...

Load: 0.048972   S: 11  U: 16
Load: 0.096964   S: 12  U: 15
Load: 0.145935   S: 12  U: 16
Load: 0.194907   S: 11  U: 16
Load: 0.243879   S: 12  U: 16
Load: 0.292850   S: 12  U: 16
Load: 0.340842   S: 12  U: 16
Load: 0.389814   S: 12  U: 17
Load: 0.438785   S: 11  U: 16
Load: 0.486778   S: 12  U: 17
Load: 0.535749   S: 12  U: 17
Load: 0.584721   S: 13  U: 17
Load: 0.630754   S: 12  U: 17
Load: 0.679726   S: 13  U: 17
Load: 0.725759   S: 13  U: 18
Load: 0.774731   S: 14  U: 20
Load: 0.823702   S: 14  U: 22
Load: 0.870715   S: 16  U: 32
Load: 0.918707   S: 18  U: 47
Load: 0.965720   S: 22  U: 97
Load: 0.999021   S: 28  U: 225

*/