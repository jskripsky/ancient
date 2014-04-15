#ifndef COLOR
#define COLOR

#include "Types.H"

/*
*/

class TColor
{
public:
	TColor( double brightness = 0 );
//	TColor( double red, double green, double blue );

//	double GetRed();
//	double GetGreen();
//	double GetBlue();

	double GetBrightness();

protected:
//	byte fRed, fGreen, fBlue;
	byte fBrightness;
};

#endif