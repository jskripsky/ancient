#include "Compiler.H"

#include "Board.H"

#include "UniCom.H"
#include <DOS.H>
#include <StdLib.H>

const byte kSynchByte = 0x00;
const byte kInitByte = 0x00;

const double kRecoveryDelay = 0;


TBoard::TBoard( EBoolean dumpMode ) :
	fDumpMode( dumpMode ),
	fModulesCount( 0 ),
	fLastTime( 0 )
{
	if( !fDumpMode )
		initcom();
}


TBoard::~TBoard()
{
	for( ; fModulesCount > 0; fModulesCount-- )
		delete fModules[fModulesCount - 1];
}


void TBoard::AdoptModule( TModule *m )
{
	fData[fModulesCount] = kInitByte;
	fModules[fModulesCount] = m;
	fModulesCount++;
}


int TBoard::GetData( TModule& m )
{
	TransferData();
	int i = 0;
	while( fModules[i] != &m )
		i++;

	return fData[i];
}


void TBoard::SetData( TModule& m, int b )
{
	int i = 0;
	while( fModules[i] != &m )
		i++;

	fData[i] = b;
	TransferData();
}


void TBoard::TransferData()
{
//	clock_t now = clock();
//	double secondsElapsed = (now - fLastTime) / CLK_TCK;

//	if( secondsElapsed < kRecoveryDelay )
//		delay( Round( (kRecoveryDelay - secondsElapsed) * 1000 ) );

	SetData();
	GetData();

//	fLastTime = clock();
}


void TBoard::GetData()
{
	for( int i = 0; i < fModulesCount; i++ )
		if( fModules[i]->GetType() == TModule::kInput )
			{
			if( !fDumpMode )
				fData[i] = rxcharw();
			else
				fData[i] = rand() % 256;
			}
}


void TBoard::SetData()
{
	if( !fDumpMode )
		{
		int c = 0;
		for( int i = 0; i < fModulesCount; i++ )
			if( fModules[i]->GetType() == TModule::kOutput )
				{
				txcharw( fData[i] );
				c++;
				}

		if( c == 0 )
			txcharw( kSynchByte );
		}
}
