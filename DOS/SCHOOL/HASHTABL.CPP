#include "HashTabl.H"


enum ECellState { kEmpty, kOccupied, kDeleted };
const int kNoAddress = -1;

struct TCell
{
	Key fKey;
	ECellState fState;

	int fData;
};



THashTable::THashTable( int size ) :
	fSize( size ),
	fCount( 0 )
{
	fTable = new TCell[fSize];
	for( int i = 0; i < fSize; i++ )
		fTable[i].fState = kEmpty;
}


THashTable::~THashTable()
{
	delete[] fTable;
}


Boolean THashTable::Insert( Key key, int data )
{
	int dest = CalculateHome( key );
	int step = CalculateStep( key );

	while( fTable[dest].fState == kOccupied )
		{
		if( fTable[dest].fKey == key )
			{
			if( fTable[dest].fData == data )
				return True;
			else
				return False;
			}

		dest = (dest + step) % fSize;
		}

	if( fCount < (fSize - 1) )
		{
		if( fTable[dest].fState == kEmpty )
			fCount++;

		fTable[dest].fState = kOccupied;
		fTable[dest].fKey = key;
		fTable[dest].fData = data;

		return True;
		}
	else
		return False;
}


Boolean THashTable::Find( Key key, int &data )
{
	int addr = FindAddress( key );

	if( addr == kNoAddress )
		return False;
	else
		{
		data = fTable[addr].fData;
		return True;
		}
}


Boolean THashTable::Delete( Key key )
{
	int addr = FindAddress( key );
	if( addr == kNoAddress )
		return False;
	else
		{
		fTable[addr].fState = kDeleted;
		return True;
		}
}


float THashTable::GetLoadRatio()
{
	return ((float)fCount / (float)fSize);
}


int THashTable::FindAddress( Key key )
{
	int addr = CalculateHome( key );
	int step = CalculateStep( key );

	while( (fTable[addr].fState != kEmpty) &&
		   ((fTable[addr].fState == kDeleted) ||
		   (fTable[addr].fKey != key)) )
		addr = (addr + step) % fSize;

	if( fTable[addr].fState == kEmpty )
		return kNoAddress;
	else
		return addr;
}


int THashTable::CalculateHome( Key key )
{
	return (key % fSize);
}


int THashTable::CalculateStep( Key key )
{
//	return (key % fSize);
	return 3;
}
