/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		PV Event Source File    			    */
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "PV.Use"
#include "Gadgets\Config.Use"
#include "FormDef\FormDef.Use"

#define Uses_TDeskTop
#define Uses_MsgBox
#define Uses_fpstream

#include <TV.H>
#include <Help.H>
#include "PV.H"
#include "Gadgets\Config.H"
#include "FormDef\FormDef.H"
#include "Defs\Commands.H"


Boolean isSaveable = False;

/*---- Public Methods --------------------------*/

void TPV::getEvent( TEvent &event )
{
//	static Boolean helpInUse = False;

	TApplication::getEvent(event);
	switch (event.what)
		{
//		case evCommand:
//			if( (event.message.command == cmHelp) && (helpInUse == False)
//				&& (hlpFile != 0) )
//				{
//				helpInUse = True;
//				((THelpViewer *)hlpWindow->last)->switchToTopic( getHelpCtx() );
//				execView( hlpWindow );
//
//				clearEvent( event );
//				}
//				helpInUse = False;
//			break;
		case evMouseDown:
			if( event.mouse.buttons != 1 )
				event.what = evNothing;
			break;
		}
}


void TPV::handleEvent( TEvent& event )
{
	TApplication::handleEvent( event );
	if( event.what == evCommand )
		{
		switch( event.message.command )
			{
			case cmAboutDismissed:
				deskTop->insert( (TView *)listWindow );
				break;

			case cmMIPrinter:
				config->dlgPrinterPort();
				break;
			}
		clearEvent( event );
		}
}


void TPV::idle()
{
	TProgram::idle();
	clock->update();

	if( heap )
		heap->update();

	if( formDef && formDef->autoSave && isSaveable )
		{
		if( startTimer == 0 )
			time( &startTimer );
		else
			{
			time_t timeNow;
			time( &timeNow );

			if( timeNow - startTimer > 60 )
				{
				isSaveable = False;
				startTimer = 0;
				message( (TView *)listWindow, evCommand, cmSaveList, 0 );
				}
			}
		}
}


void TPV::outOfMemory()
{
	messageBox( "Nicht genÅgend Speicher verfÅgbar, "
				"um Operation auszufÅhren!",
				mfError | mfOKButton );
}
