#include "Compiler.H"

#include "VOutMod.H"

const double kMaxVoltage = 2.55;


TVoltageOutputModule::TVoltageOutputModule( TBoard *b ) :
	TOutputModule( b )
{
	SetVoltage( 0 );
}


void TVoltageOutputModule::SetVoltage( double v )
{
	if( v > kMaxVoltage )
		v = kMaxVoltage;
	if( v < 0 )
		v = 0;

	SetData( Round( v * 0xFF / kMaxVoltage ) );
}


double TVoltageOutputModule::GetVoltage()
{
	return ((double)GetData() * kMaxVoltage / 0xFF );
}


double TVoltageOutputModule::GetMaxVoltage()
{
	return kMaxVoltage;
}


double TVoltageOutputModule::GetResolution()
{
	return (kMaxVoltage / 0xFF);
}
