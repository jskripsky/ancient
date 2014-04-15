#include "Compiler.H"

#include "BMPScan.H"

#include "Bitmap.H"
#include "PlotArm.H"

const double kNeutral = 0.5;
const double kGray  = 0.5;
const double kWhite = 1.0;
const double kBlack = 0.0;


TBitmapScanner::TBitmapScanner( TPlotterArm *xArm, TPlotterArm *yArm,
						  TPhotoCell *photoCell, TBitmap *bitmap ) :
	TScanner( xArm, yArm, photoCell ),
	fBitmap( bitmap ),
	fWorking( kFalse ),
	fBrightness( kNeutral ),
	fContrast( kNeutral ),
	fFilter( TColor( kWhite ) )
{
	if( !fBitmap )
		fBitmap = new TBitmap(
//			Round( 1 / fXArm->GetResolution() ) + 1,
//			Round( 1 / fYArm->GetResolution() ) + 1 );
			128, 128 );
}


TBitmapScanner::~TBitmapScanner()
{
	if( fWorking )
		Stop();

	delete fBitmap;
}


TBitmap *TBitmapScanner::GetBitmap()
{
	return fBitmap;
}


void TBitmapScanner::Start()
{
	fX = fY = 0;
	MovePenTo( TPlotterPoint( 0, 0 ), kTrue );
	fWorking = kTrue;
}


void TBitmapScanner::Stop()
{
	fWorking = kFalse;
	MovePenTo( TPlotterPoint( 0, 0 ), kTrue );
}


void TBitmapScanner::Tick()
{
	if( !fWorking )
		return;

	if( !IsPenInPosition() )
		return;

	fBitmap->SetPixel( fX, fY, TColor( GetLightIntensity() ) );

/*
	if( fY % 2 == 0 )
		{
		if( fX < (fBitmap->GetWidth() - 1) )
			fX++;
		else
			fY++;
		}
	else
		{
		if( fX > 0 )
			fX--;
		else
			fY++;
		}

	if( fY < fBitmap->GetHeight() )
		MovePenTo( TPlotterPoint( fX * fXArm->GetResolution(),
							 fY * fYArm->GetResolution() ) );
	else
		Stop();
*/

	if( fX < (fBitmap->GetWidth() - 1) )
		fX++;
	else
		{
		fY++;
		fX = 0;
		}

	if( fY < fBitmap->GetHeight() )
		MovePenTo( TPlotterPoint( fX * fXArm->GetResolution(),
							 fY * fYArm->GetResolution() ) );
	else
		Stop();

}


double TBitmapScanner::GetLightIntensity()
{
	double intensity = TScanner::GetLightIntensity();

	if( fBrightness != kNeutral )
		{
		intensity += (fBrightness - kNeutral) / kGray;
		ScaleIntoRange( intensity );
		}

	if( fContrast != kNeutral )
		{
		double shift = (fContrast - kNeutral);

		if( intensity > kGray )
			{
			intensity += shift;
			ScaleIntoRange( intensity, kGray, kWhite );
			}
		else
			{
			intensity -= shift;
			ScaleIntoRange( intensity, kBlack, kGray );
			}
		}

	return intensity;
}


void TBitmapScanner::SetBrightness( double brightness )
{
	fBrightness = brightness;
}


void TBitmapScanner::SetContrast( double contrast )
{
	fContrast = contrast;
}


void TBitmapScanner::ScaleIntoRange( double& value, double bottom,
							  double top )
{
	if( value < bottom )
		value = bottom;
	else
		if( value > top )
			value = top;
}
