// Copyright (c) 1995 Juraj Skripsky.
// Revision: 0.5
// Date: xx.11.1995

#ifndef CTRLPNL
#define CTRLPNL

#define Uses_TDialog
#include <TV.H>
#include <Time.H>


/*
*/

class TButton;
class TInputLine;
class TCheckBoxes;
class TBrightnessIndicator;
class TPercentageText;
class TNumericInputLine;

class TBoard;
class TVoltageOutputModule;
class TVoltageInputModule;

class TBitmapScanner;

class TGraphicWindow;


class TScanControlPanel : public TDialog
{
public:
	TScanControlPanel();
	virtual ~TScanControlPanel();

	void idle();

	void showAboutBox();

protected:
	virtual void handleEvent( TEvent& event );

	void setupScanner();
	void destroyScanner();

	void setupControls();

	void startScan();
	void stopScan();

	void update();
	void alternatePulseIndicator();

	void loadBitmap();
	void saveBitmap();
	void clearBitmap();

	void applyNewSettings();

	void writeSettingsToDisk();
	void readSettingsFromDisk();


	double pulseTime;
	int stepsPerPulse;

	Boolean scanning;
	Boolean isShowingGraphicWindow;

	TGraphicWindow *graphicWindow;


	// Scanning Framework:
	TBitmapScanner *bitmapScanner;

	// LabCom Framework:
	TBoard *board;


	// Settings:
	TNumericInputLine *lightRangeTop;
	TNumericInputLine *lightRangeBottom;

	TNumericInputLine *pulse;

	TNumericInputLine *brightness;
	TNumericInputLine *contrast;

	TButton *applySettingsButton;


	// Bitmap:
	TNumericInputLine *xSize;
	TNumericInputLine *ySize;

	TButton *showBitmapButton;
	TButton *clearBitmapButton;
	TButton *loadBitmapButton;
	TButton *saveBitmapButton;


	// Scan:
	TNumericInputLine *steps;
	TPercentageText *progressText;

	TButton *startButton;
	TButton *suspendButton;
	TButton *resumeButton;
	TButton *stopButton;
	TButton *closeButton;


	// Status:
	clock_t lastSaveTime;

	clock_t lastPulseTime;
	TCheckBoxes *pulseIndicator;

	TPercentageText *penPositionX;
	TPercentageText *penPositionY;

	TPercentageText *brightnessText;
	TBrightnessIndicator *brightnessIndicator;
};

#endif