#include "Compiler.H"

#include "VInMod.H"

const double kMaxVoltage = 5.00;


double TVoltageInputModule::GetVoltage()
{
	return ((double)GetData() * kMaxVoltage / 0xFF);
}


double TVoltageInputModule::GetMaxVoltage()
{
	return kMaxVoltage;
}


double TVoltageInputModule::GetResolution()
{
	return (kMaxVoltage / 0xFF);
}