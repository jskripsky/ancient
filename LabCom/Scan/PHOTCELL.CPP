#include "Compiler.H"

#include "PhotCell.H"

#include "VInMod.H"

TPhotoCell::TPhotoCell( TVoltageInputModule *module ) :
	fModule( module )
{
}

#include <StdLib.H>

double TPhotoCell::GetIntensity()
{
	return (fModule->GetVoltage() / fModule->GetMaxVoltage());
}
