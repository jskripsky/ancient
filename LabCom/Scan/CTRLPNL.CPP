#include "Compiler.H"

#include "Bitmap.H"
#include "BMPScan.H"


#define Uses_TButton
#define Uses_TCheckBoxes
#define Uses_TEvent
#define Uses_TProgram
#define Uses_TDeskTop
#define Uses_TStatusLine
#define Uses_TKeys
#include "CtrlPnl.H"

#include "BrgtInd.H"
#include "PrcntTxt.H"
#include "NumInptL.H"

#include "AboutBox.H"
#include "GrphcWnd.H"

#include "CPID.H"
#include "HC.H"

#include <ConIO.H>


const double saveTime = 30;

const char tempFileName[] = "Temp.Map";


TScanControlPanel::TScanControlPanel() :
	TWindowInit( &TScanControlPanel::initFrame ),
	TDialog( TRect( 2, 1, 76, 23 ), "Scan Control Panel" ),
	pulseTime( 0.1 ),
	stepsPerPulse( 10 ),
	scanning( False ),
	isShowingGraphicWindow( False ),
	lastPulseTime( 0 ),
	lastSaveTime( 0 )
{
	flags &= ~wfClose;

	TProgram::statusLine->show();
	TProgram::application->helpCtx = hcInitHardware;
	TProgram::statusLine->update();
	setupScanner();

	TProgram::application->helpCtx = hcSetupControlPanel;
	TProgram::statusLine->update();
	setupControls();

	int data = 0;
	lightRangeBottom->setData( &data );
	data = 1000;
	lightRangeTop->setData( &data );

	data = Round( 1000 * pulseTime );
	pulse->setData( &data );

	data = 500;
	brightness->setData( &data );
	contrast->setData( &data );

	data = 1000;
	xSize->setData( &data );
	ySize->setData( &data );

	steps->setData( &stepsPerPulse );

	suspendButton->setState( sfDisabled, True );
	suspendButton->hide();
	resumeButton->setState( sfDisabled, True );
	resumeButton->hide();

	stopButton->setState( sfDisabled, True );
	stopButton->hide();
	pulseIndicator->setState( sfDisabled, True );

	startButton->select();

	readSettingsFromDisk();
	bitmapScanner->GetBitmap()->ReadFromDisk( tempFileName );

	TProgram::application->helpCtx = hcNoContext;
	TProgram::statusLine->hide();
}


TScanControlPanel::~TScanControlPanel()
{
	bitmapScanner->GetBitmap()->WriteToDisk( tempFileName );
	writeSettingsToDisk();
	destroyScanner();
}


void TScanControlPanel::idle()
{
	static Boolean working = False;
	if( working )
		return;

	clock_t now = clock();
	double secondsElapsed = (now - lastPulseTime) / CLK_TCK;

	if( secondsElapsed > pulseTime )
		{
		working = True;

		if( ((now - lastSaveTime) / CLK_TCK) > saveTime )
			{
			bitmapScanner->GetBitmap()->WriteToDisk( tempFileName );
			lastSaveTime = now;
			}

		alternatePulseIndicator();

		for( int i = 0; i < stepsPerPulse; i++ )
			bitmapScanner->Tick();

		update();

		lastPulseTime = now;
		working = False;
		}
}


void TScanControlPanel::startScan()
{
	steps->setState( sfDisabled, True );

	startButton->setState( sfDisabled, True );
	startButton->hide();
	closeButton->setState( sfDisabled, True );
	closeButton->hide();

	suspendButton->setState( sfDisabled, False );
	suspendButton->show();

	stopButton->setState( sfDisabled, False );
	stopButton->show();

	showBitmapButton->select();

	steps->getData( &stepsPerPulse );

	scanning = True;
	bitmapScanner->Start();
}


void TScanControlPanel::stopScan()
{
	scanning = False;
	bitmapScanner->Stop();
	bitmapScanner->MovePenTo( TPlotterPoint( 0, 0 ), kTrue );
	update();

	stopButton->setState( sfDisabled, True );
	stopButton->hide();

	suspendButton->setState( sfDisabled, True );
	suspendButton->hide();
	resumeButton->setState( sfDisabled, True );
	resumeButton->hide();

	closeButton->setState( sfDisabled, False );
	closeButton->show();
	startButton->setState( sfDisabled, False );
	startButton->show();

	steps->setState( sfDisabled, False );

	startButton->select();
}


void TScanControlPanel::showAboutBox()
{
	hide();

	TAboutBox *aboutBox = new TAboutBox();
	TProgram::deskTop->insert( aboutBox );

	aboutBox->show();
	TProgram::deskTop->execView( aboutBox );
	aboutBox->hide();

	TProgram::deskTop->remove( aboutBox );

	destroy( aboutBox );

	show();

}


void TScanControlPanel::handleEvent( TEvent& event )
{
	TDialog::handleEvent( event );
	switch( event.what )
		{
		case evKeyboard:
			if( !scanning )
				{
				TPlotterPoint newPoint =
					bitmapScanner->GetPenPosition();
				TPlotterPoint res = bitmapScanner->GetResolution();

				switch( event.keyDown.keyCode )
					{
					case kbLeft:
						newPoint.fX -= res.fX;
						clearEvent( event );
						break;

					case kbUp:
						newPoint.fY -= res.fY;
						clearEvent( event );
						break;

					case kbRight:
						newPoint.fX += res.fX;
						clearEvent( event );
						break;

					case kbDown:
						newPoint.fY += res.fY;
						clearEvent( event );
						break;

					case kbHome:
						newPoint.fX = newPoint.fY = 0;
						clearEvent( event );
						break;

					case	kbEnd:
						newPoint.fX = newPoint.fY = 1;
						clearEvent( event );
						break;
					}
				bitmapScanner->MovePenTo( newPoint, kTrue );
				update();
				}
			break;

		case evCommand:
			switch( event.message.command )
				{
				case cmOK:
					startScan();
					clearEvent( event );
					break;

				case cmCancel:
					stopScan();
					clearEvent( event );
					break;

				case cmShowBitmap:
					TProgram::application->suspend();

					graphicWindow = new TGraphicWindow(
						bitmapScanner->GetBitmap() );

					isShowingGraphicWindow = True;

					while( !kbhit() )
						TProgram::application->idle();

					getch();

					isShowingGraphicWindow = False;
					delete graphicWindow;

					TProgram::application->resume();
					TProgram::application->redraw();

					clearEvent( event );
					break;

				case cmApplySettings:
					applyNewSettings();

					clearEvent( event );
					break;

				case cmSaveBitmap:
					saveBitmap();
					clearEvent( event );
					break;

				case cmLoadBitmap:
					loadBitmap();
					clearEvent( event );
					break;

				case cmClearBitmap:
					clearBitmap();
					clearEvent( event );
					break;

				case cmAbout:
					showAboutBox();
					clearEvent( event );
					break;
				}
			break;
		}
}


void TScanControlPanel::alternatePulseIndicator()
{
	ushort p;
	pulseIndicator->getData( &p );

	p = !p;

	pulseIndicator->setData( &p );
}


void TScanControlPanel::update()
{
	if( scanning && !bitmapScanner->isWorking() )
		stopScan();

	if( !isShowingGraphicWindow )
		{
		double b = bitmapScanner->GetLightIntensity() * 100;
		brightnessText->setData( &b );
		ushort bi = Round( b * 10 );
		brightnessIndicator->setData( &bi );

		TPlotterPoint p = bitmapScanner->GetPenPosition();
		double x = p.fX * 100;
		double y = p.fY * 100;

		penPositionX->setData( &x );
		penPositionY->setData( &y );
		}
	else
		graphicWindow->Update();
}
