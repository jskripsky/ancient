#include "Compiler.H"

#include "Color.H"

#include "Types.H"


TColor::TColor( double brightness )
{
//	fRed = fGreen = fBlue = Round( brightness * 0xFF );
	fBrightness = Round( brightness * 0xFF );
}

/*
TColor::TColor( double red, double green, double blue )
{
	fRed = Round( red * 0xFF );
	fGreen = Round( green * 0xFF );
	fBlue = Round( blue * 0xFF );
}
*/


double TColor::GetBrightness()
{
	return (((double)fBrightness) / 0xFF);
}


/*
double TColor::GetRed()
{
	return (((double)fRed) / 0xFF);
}


double TColor::GetGreen()
{
	return (((double)fGreen) / 0xFF);
}


double TColor::GetBlue()
{
	return (((double)fBlue) / 0xFF);
}
*/