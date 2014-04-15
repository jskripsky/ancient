#ifndef BMPSCAN
#define BMPSCAN

#include "Scanner.H"

#include "Color.H"
#include "Types.H"

/*
*/

class TBitmap;

class TBitmapScanner : public TScanner
{
public:
	TBitmapScanner( TPlotterArm *xArm, TPlotterArm *yArm, TPhotoCell *,
				 TBitmap *bitmap = 0 );
	virtual ~TBitmapScanner();

	TBitmap *GetBitmap();

	virtual void Start();
	virtual void Stop();

	virtual void Tick();

	EBoolean isWorking()
		{ return fWorking; }

	virtual double GetLightIntensity();

	void SetBrightness( double );
	void SetContrast( double );

	void SetFilter( TColor );

protected:
	EBoolean fWorking;
	int fX, fY;

	TBitmap *fBitmap;

	double fBrightness;
	double fContrast;
	TColor fFilter;

	void ScaleIntoRange( double& value, double bottom = 0, double top = 1 );
};

#endif