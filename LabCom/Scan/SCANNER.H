#ifndef SCANNER
#define SCANNER

#include "Plotter.H"

/*
*/
class TPhotoCell;

class TScanner : public TPlotter
{
public:
	TScanner( TPlotterArm *xArm, TPlotterArm *yArm, TPhotoCell * );
	virtual ~TScanner();

	void SetLightRange( double bottom, double top );
	virtual double GetLightIntensity();

protected:
	TPhotoCell *fPhotoCell;

	double fRangeTop;
	double fRangeBottom;
};

#endif