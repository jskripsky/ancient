#include "Compiler.H"

#include "BMPScan.H"
#include "Bitmap.H"

#define Uses_TFileDialog
#define Uses_TProgram
#define Uses_TDeskTop
#include "CtrlPnl.H"
#include "NumInptL.H"


void TScanControlPanel::loadBitmap()
{
	TFileDialog *fd = new TFileDialog( "*.Map", "Load Bitmap", "~N~ame",
								fdOKButton, 0 );

	if( TProgram::deskTop->execView( fd ) != cmCancel )
		{
		char fileName[MAXPATH];
		fd->getFileName(fileName);
		bitmapScanner->GetBitmap()->ReadFromDisk( fileName );
		}

	delete fd;

	int width = Round(
		(double)bitmapScanner->GetBitmap()->GetWidth() / 256 * 1000 );

	int height = Round(
		(double)bitmapScanner->GetBitmap()->GetHeight() / 256 * 1000 );

	xSize->setData( &width );
	ySize->setData( &height );
}


void TScanControlPanel::saveBitmap()
{
	TFileDialog *fd = new TFileDialog( "*.Map", "Save Bitmap", "~N~ame",
								fdOKButton, 0 );
	if( TProgram::deskTop->execView( fd ) != cmCancel )
		{
		char fileName[MAXPATH];
		fd->getFileName( fileName );
		bitmapScanner->GetBitmap()->WriteToDisk( fileName );
		}

	delete fd;
}


void TScanControlPanel::clearBitmap()
{
	int width;
	int height;
	xSize->getData( &width );
	ySize->getData( &height );

	bitmapScanner->GetBitmap()->ScaleTo(
		Round( (double)height / 1000 * 256 ),
		Round( (double)width / 1000 * 256 ) );

	bitmapScanner->GetBitmap()->Clear();
}
