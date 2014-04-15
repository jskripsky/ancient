#include "Compiler.H"

#include "PlotArm.H"

#include "VOutMod.H"

#include <DOS.H>
#include <Math.H>

const double kFullMoveDuration = 2.0;
const double kImplicitCodeDelay = 0.001;
const double kMinimumDelay = 0.001;


TPlotterArm::TPlotterArm( TVoltageOutputModule *m, EDirection d ) :
	fModule( m ),
	fDirection( d ),
	fInPosition( kTrue ),
	fMoveStartTime( 0 ),
	fMoveDuration( 0 )
{
	MoveTo( 0, kTrue );
}


void TPlotterArm::MoveTo( double p, EBoolean asynchronously )
{
	double newPosition = p;
	if( fDirection == kNegative )
		newPosition = 1 - newPosition;

	double distance = fabs( p - GetPosition() );
	IsInPosition();
	fMoveDuration += CalculateMoveDuration( distance );

	fModule->SetVoltage( fModule->GetMaxVoltage() * newPosition );

	if( !asynchronously )
		{
		if( (fMoveDuration > kImplicitCodeDelay) &&
		    (fMoveDuration > kMinimumDelay) )
			delay( Round( fMoveDuration * 1000 ) );

		fInPosition = kTrue;
		fMoveDuration = 0;
		}
	else
		{
		fInPosition = kFalse;
		fMoveStartTime = clock();
		}
}


EBoolean TPlotterArm::IsInPosition()
{
	if( !fInPosition )
		{
		clock_t now = clock();
		if( ((now - fMoveStartTime) / CLK_TCK) >= fMoveDuration )
			{
			fInPosition = kTrue;
			fMoveDuration = 0;
			}
		}

	return fInPosition;
}


double TPlotterArm::GetPosition()
{
	double p = fModule->GetVoltage() / fModule->GetMaxVoltage();
	if( fDirection == kNegative )
		p = 1 - p;

	return p;
}


double TPlotterArm::GetResolution()
{
	return (fModule->GetResolution() / fModule->GetMaxVoltage());
}


double TPlotterArm::CalculateMoveDuration( double distance )
{
	return (distance * kFullMoveDuration);
}

