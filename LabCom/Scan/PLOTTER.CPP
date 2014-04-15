#include "Compiler.H"

#include "Plotter.H"

#include "PlotArm.H"


TPlotter::TPlotter( TPlotterArm *xArm, TPlotterArm *yArm ) :
	fXArm( xArm ),
	fYArm( yArm ),
	fPenPosition( TPlotterPoint( 0, 0 ) )
{
	MovePenTo( fPenPosition, kTrue );
}


TPlotter::~TPlotter()
{
	delete fXArm;
	delete fYArm;
}


void TPlotter::MovePenTo( TPlotterPoint p, EBoolean asynchronously )
{
	if( p.fX < 0 )
		p.fX = 0;
	if( p.fX > 1 )
		p.fX = 1;

	if( p.fY < 0 )
		p.fY = 0;
	if( p.fY > 1 )
		p.fY = 1;

	fXArm->MoveTo( p.fX, asynchronously );
	fYArm->MoveTo( p.fY, asynchronously );
	fPenPosition = p;
}


EBoolean TPlotter::IsPenInPosition()
{
	return (EBoolean)(fXArm->IsInPosition() && fYArm->IsInPosition());
}


TPlotterPoint TPlotter::GetPenPosition()
{
	return fPenPosition;
}


TPlotterPoint TPlotter::GetResolution()
{
	return TPlotterPoint( fXArm->GetResolution(), fYArm->GetResolution() );
}
