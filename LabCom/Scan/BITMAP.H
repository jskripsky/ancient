#ifndef BITMAP
#define BITMAP

#include "Color.H"


/*
*/

class TBitmap
{
public:
	TBitmap( int width, int height, TColor backGround = TColor() );
	virtual ~TBitmap();

	void Clear( TColor backGround = TColor() );

	void SetPixel( int x, int y, TColor newColor );
	TColor GetPixel( int x, int y );

	int GetWidth()
		{ return fWidth; }
	int GetHeight()
		{ return fHeight; }

	void ScaleTo( int newHeight, int newWidth );

	void WriteToDisk( const char *fileName );
	void ReadFromDisk( const char *fileName );

	byte *GetLine( int y );

protected:
	void SetupBitmapSegments();
	void DestroyBitmapSegments();

	byte **fBitmapSegments;
	int fLinesPerSegment;
	int fNumberOfSegments;

	int fWidth, fHeight;

	byte *GetPoint( int x, int y );
};

#endif