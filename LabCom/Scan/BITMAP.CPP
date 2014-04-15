#include "Compiler.H"

#include "Bitmap.H"

#include <FStream.H>
#include <String.H>

const int kSegmentSize = 10000;
const char kFileHeader[] = "JS Scan *.MAP";


TBitmap::TBitmap( int width, int height, TColor backGround ) :
	fWidth( width ),
	fHeight( height )
{
	SetupBitmapSegments();
	Clear( backGround );
}


TBitmap::~TBitmap()
{
	DestroyBitmapSegments();
}



void TBitmap::SetupBitmapSegments()
{
	fLinesPerSegment = kSegmentSize / sizeof( byte ) / fWidth;

	fNumberOfSegments = (fHeight / fLinesPerSegment);
	if( fHeight % fLinesPerSegment > 0 )
		fNumberOfSegments++;
	fBitmapSegments = new byte *[fNumberOfSegments];

	for( int i = 0; i < fNumberOfSegments; i++ )
		fBitmapSegments[i] = new byte[fWidth * fLinesPerSegment];
}


void TBitmap::DestroyBitmapSegments()
{
	for( int i = 0; i < fNumberOfSegments; i++ )
		delete[] fBitmapSegments[i];

	delete[] fBitmapSegments;
}


void TBitmap::Clear( TColor backGround )
{
	for( int y = 0; y < fHeight; y++ )
		for( int x = 0; x < fWidth; x++ )
			SetPixel( x, y, backGround );
}


void TBitmap::SetPixel( int x, int y, TColor newColor )
{
	if( (x < fWidth) && (y < fHeight) )
		(*GetPoint( x, y )) = Round( newColor.GetBrightness() * 0xFF );
}


TColor TBitmap::GetPixel( int x, int y )
{
	if( (x < fWidth) && (y < fHeight) )
		{
		return TColor( ((double)*GetPoint( x, y )) / 0xFF );
		}
	else
		return TColor();
}


void TBitmap::ScaleTo( int newHeight, int newWidth )
{
	DestroyBitmapSegments();
	fHeight = newHeight;
	fWidth = newWidth;

	SetupBitmapSegments();
	Clear();
}


void TBitmap::WriteToDisk( const char *fileName )
{
	ofstream os( fileName, ios::out | ios::binary | ios::trunc );
	if( !os )
		return;

	os.write( kFileHeader, strlen( kFileHeader ) + 1 );
	EBoolean compressed = kFalse;
	os.write( (char *)&compressed, sizeof( EBoolean ) );

	os.write( (char *)&fHeight, sizeof( fHeight ) );
	os.write( (char *)&fWidth, sizeof( fWidth ) );

	for( int y = 0; y < fHeight; y++ )
		for( int x = 0; x < fWidth; x++ )
			os.put( *GetPoint( x, y ) );

	os.close();
}


void TBitmap::ReadFromDisk( const char *fileName )
{
	ifstream is( fileName, ios::in | ios::binary );
	if( !is )
		return;

	char *header = new char[strlen( kFileHeader )];
	is.read( header, strlen( kFileHeader ) + 1 );
	EBoolean headerOK = (EBoolean)!strcmp( header, kFileHeader );
	delete[] header;

	if( !headerOK )
		return;

	DestroyBitmapSegments();

	EBoolean compressed;

	is.read( (char *)&compressed, sizeof( EBoolean ) );

	is.read( (char *)&fHeight, sizeof( fHeight ) );
	is.read( (char *)&fWidth, sizeof( fWidth ) );

	SetupBitmapSegments();
	Clear();

	for( int y = 0; y < fHeight; y++ )
		for( int x = 0; x < fWidth; x++ )
			*GetPoint( x, y ) = is.get();

	is.close();
}


byte *TBitmap::GetLine( int y )
{
	int segmentNumber = y / fLinesPerSegment;
	int lineNumber = y - (segmentNumber * fLinesPerSegment);

	return &(fBitmapSegments[segmentNumber][lineNumber * fWidth]);
}


byte *TBitmap::GetPoint( int x, int y )
{
	int segmentNumber = y / fLinesPerSegment;
	int lineNumber = y - (segmentNumber * fLinesPerSegment);

	return &(fBitmapSegments[segmentNumber][lineNumber * fWidth + x]);
}
