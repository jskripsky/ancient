#include "Compiler.H"

#include "Scanner.H"

#include "PhotCell.H"


TScanner::TScanner( TPlotterArm *xArm, TPlotterArm *yArm,
				TPhotoCell *photoCell ) :
	TPlotter( xArm, yArm ),
	fPhotoCell( photoCell ),
	fRangeTop( 1 ),
	fRangeBottom( 0 )
{
}


TScanner::~TScanner()
{
	delete fPhotoCell;
}


void TScanner::SetLightRange( double bottom, double top )
{
	if( top == bottom )
		{
		top = 1;
		bottom = 0;
		}

	if( top < bottom )
		{
		double temp = top;
		top = bottom;
		bottom = temp;
		}

	fRangeTop = top;
	fRangeBottom = bottom;
}


double TScanner::GetLightIntensity()
{
	double intensity = fPhotoCell->GetIntensity();

	if( intensity > fRangeTop )
		intensity = fRangeTop;

	if( intensity < fRangeBottom )
		intensity = fRangeBottom;

	intensity = (intensity - fRangeBottom) / (fRangeTop - fRangeBottom);
	return intensity;
}
