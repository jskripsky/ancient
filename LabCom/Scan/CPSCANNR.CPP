#include "Compiler.H"

#include "Board.H"
#include "VOutMod.H"
#include "VInMod.H"

#include "PlotArm.H"
#include "PhotCell.H"
#include "BMPScan.H"

#define Uses_TProgram

#include "CtrlPnl.H"
#include "ScanApp.H"


void TScanControlPanel::setupScanner()
{
	board = new TBoard( (EBoolean)
		((TScanApplication *)TProgram::application)->isDumpModeOn() );

	TVoltageOutputModule *vOutModuleX = new TVoltageOutputModule( board );
	TVoltageOutputModule *vOutModuleY = new TVoltageOutputModule( board );

	TVoltageInputModule *vInModule = new TVoltageInputModule( board );

	bitmapScanner = new TBitmapScanner(
		new TPlotterArm( vOutModuleX ),
		new TPlotterArm( vOutModuleY, TPlotterArm::kNegative ),
//		new TPlotterArm( vOutMod ), // Temp!
//		new TPlotterArm( vOutMod ), // Temp!
		new TPhotoCell( vInModule  ) );
}


void TScanControlPanel::destroyScanner()
{
	delete bitmapScanner;
	delete board;
}
