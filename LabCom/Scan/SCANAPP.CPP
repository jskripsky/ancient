#include "Compiler.H"


#define Uses_TDeskTop
#define Uses_TStatusLine
#define Uses_TStatusDef
#define Uses_TStatusItem
#include "ScanApp.H"
#include "CtrlPnl.H"
#include "Clock.H"
#include "HC.H"


TScanApplication::TScanApplication( Boolean aDumpMode ) :
	TProgInit( &TScanApplication::initStatusLine, 0,
			 &TScanApplication::initDeskTop ),
	dumpMode( aDumpMode )
{
	statusLine->hide();

	TRect r = getExtent();
	r.a.x = r.b.x - 10;
	r.a.y = r.b.y - 1;
	insert( clock = new TClockView( r ) );
	clock->update();

	scanControlPanel = new TScanControlPanel();
	scanControlPanel->hide();
	deskTop->insert( scanControlPanel );
	scanControlPanel->select();

	scanControlPanel->showAboutBox();
}


TScanApplication::~TScanApplication()
{
	remove( scanControlPanel );
	delete scanControlPanel;

	remove( clock );
	delete clock;
}


TDeskTop *TScanApplication::initDeskTop( TRect r )
{
    return new TDeskTop( r );
}


TStatusLine *TScanApplication::initStatusLine( TRect r )
{
	r.a.y = r.b.y - 1;
	return new TStatusLine( r,
		*new TStatusDef( hcNoContext, hcNoContext ) +
		*new TStatusItem( "", 0, 0 ) +
		*new TStatusDef( hcInitHardware, hcInitHardware ) +
		*new TStatusItem( "Initializing Hardware...", 0, 0 ) +
		*new TStatusDef( hcSetupControlPanel, hcSetupControlPanel ) +
		*new TStatusItem( "Setting up Control Panel...", 0, 0 ) );
}


void TScanApplication::idle()
{
	TApplication::idle();
	clock->update();
	scanControlPanel->idle();
}
