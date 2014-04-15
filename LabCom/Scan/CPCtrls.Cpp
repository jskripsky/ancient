#include "Compiler.H"

#define Uses_TButton
#define Uses_TInputLine
#define Uses_TStaticText
#define Uses_TLabel
#define Uses_TCheckBoxes
#define Uses_TSItem
#define Uses_TEvent
#define Uses_TProgram
#define Uses_TKeys
#define Uses_TPalette
#include "CtrlPnl.H"
#include "CPID.H"
#include "BrgtInd.H"
#include "PrcntTxt.H"
#include "NumInptL.H"


void TScanControlPanel::setupControls()
{
	// Settings:
	// =========
	insert( new TStaticText( TRect( 4, 2, 20, 3 ), "Settings" ) );

	insert( new TStaticText( TRect( 31, 2, 55, 3 ),
						"         % - 	        %" ) );
	insert( lightRangeBottom =
		new TNumericInputLine( TRect( 31, 2, 39, 3 ), 6, 1 ) );
	insert( lightRangeTop = new TNumericInputLine(
		TRect( 44, 2, 52, 3 ), 6, 1 ) );
	insert( new TLabel( TRect( 17, 2, 29, 3 ), "Light ~R~ange",
					lightRangeBottom ) );

	insert( pulse =
		new TNumericInputLine( TRect( 18, 5, 25, 6 ), 5, 0 ) );
	insert( new TLabel( TRect( 17, 4, 28, 5 ), "P~u~lse Time", pulse ) );
	insert( new TStaticText( TRect( 26, 5, 31, 6 ), "ms" ) );

	insert( brightness =
		new TNumericInputLine( TRect( 42, 4, 50, 5 ), 6, 1 ) );
	insert( new TStaticText( TRect( 51, 4, 53, 5 ), "%" ) );
	insert( new TLabel( TRect( 30, 4, 41, 5 ), "Brightness",
					brightness ) );
	insert( contrast =
		new TNumericInputLine( TRect( 42, 5, 50, 6 ), 6, 1 ) );
	insert( new TStaticText( TRect( 51, 5, 53, 6 ), "%" ) );
	insert( new TLabel( TRect( 30, 5, 41, 6 ), "Contrast", contrast ) );

	insert( applySettingsButton = new TButton( TRect( 60, 5, 71, 7 ),
		"~A~pply", cmApplySettings, bfNormal ) );

	insert( new TStaticText( TRect( 3, 7, 71, 8 ),
						"ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"
						"ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" ) );

	// Bitmap:
	// =======
	insert( new TStaticText( TRect( 4, 8, 20, 9 ), "Bitmap" ) );

	insert( new TStaticText( TRect( 18, 8, 36, 9 ), "Size X          %" ) );
	insert( xSize = new TNumericInputLine( TRect( 25, 8, 33, 9 ), 6, 1 ) );
	insert( new TStaticText( TRect( 23, 9, 36, 10 ), "Y          %" ) );
	insert( ySize = new TNumericInputLine( TRect( 25, 9, 33, 10 ), 6, 1 ) );

	insert( showBitmapButton =
		new TButton( TRect( 38, 8, 48, 10 ), "~S~how", cmShowBitmap,
				   bfNormal ) );

	insert( clearBitmapButton =
		new TButton( TRect( 49, 8, 60, 10 ), "~C~lear", cmClearBitmap,
				   bfNormal ) );

	insert( saveBitmapButton =
		new TButton( TRect( 61, 8, 71, 10 ), "Sa~v~e", cmSaveBitmap,
				   bfNormal ) );

	insert( loadBitmapButton =
		new TButton( TRect( 61, 9, 71, 11 ), "~L~oad", cmLoadBitmap,
				   bfNormal ) );

	insert( new TStaticText( TRect( 3, 11, 71, 12 ),
						"ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"
						"ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" ) );

	// Scan:
	// =====
	insert( new TStaticText( TRect( 4, 12, 20, 13 ), "Scan" ) );


	insert( steps = new TNumericInputLine( TRect( 35, 12, 40, 13 ), 3, 0 ) );
	insert( new TLabel( TRect( 17, 12, 33, 13 ), "Steps per Pulse",
					steps ) );

	insert( new TButton( TRect( 49, 12, 59, 14 ), "~H~elp", cmHelp,
					 bfNormal ) );

	insert( new TButton( TRect( 60, 12, 71, 14 ), "A~b~out", cmAbout,
					 bfNormal ) );

	insert( startButton =
		new TButton( TRect( 49, 14, 60, 16 ), "S~t~art", cmOK,
				   bfDefault ) );

	insert( suspendButton =
		new TButton( TRect( 47, 14, 60, 16 ), "Suspend", cmSuspend,
				   bfNormal ) );

	insert( resumeButton =
		new TButton( TRect( 48, 14, 60, 16 ), "Resume", cmResume,
				   bfNormal ) );

	insert( stopButton =
		new TButton( TRect( 61, 14, 71, 16 ), "Sto~p~", cmCancel,
				   bfNormal ) );

	insert( closeButton =
		new TButton( TRect( 61, 14, 71, 16 ), "E~x~it", cmQuit,
				   bfNormal ) );

	insert( new TStaticText( TRect( 3, 16, 71, 17 ),
						"ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"
						"ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" ) );

	// Status:
	// =======
	insert( new TStaticText( TRect( 4, 17, 20, 18 ), "Status" ) );

	insert( new TStaticText( TRect( 18, 17, 21, 18 ), "Pen" ) );

	insert( new TStaticText( TRect( 18, 18, 20, 19 ), "X" ) );
	insert( penPositionX =
		new TPercentageText( TRect( 20, 18, 27, 19 ), 1 ) );

	insert( new TStaticText( TRect( 18, 19, 20, 20 ), "Y" ) );
	insert( penPositionY =
		new TPercentageText( TRect( 20, 19, 27, 20 ), 1 ) );

	insert( new TStaticText( TRect( 30, 17, 41, 18 ), "Brightness" ) );
	insert( brightnessText =
		new TPercentageText( TRect( 44, 17, 51, 18 ), 1 ) );
	insert( brightnessIndicator =
		new TBrightnessIndicator( TRect( 30, 18, 50, 20 ), 1000 ) );

	insert( pulseIndicator =
		new TCheckBoxes( TRect( 4, 19, 15, 20 ),
					  new TSItem( "Pulse", 0 ) ) );


	insert( new TStaticText( TRect( 53, 16, 54, 20 ), "Â³³³" ) );
	insert( new TStaticText( TRect( 55, 17, 72, 20 ),
						"ÍÍÍÍÍ SCAN ÍÍÍÍÍ\n"
						"  Version 1.0a\n"
						"(c) 1995 Skribby" ) );
}
