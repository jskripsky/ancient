/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		About Dialog Source File 		    	*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "About.Use"
#include "PV.Use"

#define Uses_TProgram
#define Uses_TDeskTop
#define Uses_TEvent
#define Uses_TButton
#define Uses_MsgBox

#include <TV.H>
#include "About.H"
#include "IntRev.H"
#include "PV.H"
#include "Defs\Commands.H"
#include "Defs\HelpCtx.H"


/*---- Constructors, Destructors ---------------*/

TAboutDialog::TAboutDialog() :
	TWindowInit( &TAboutDialog::initFrame ),
	TDialog( TRect( 20, 2, 59, 20 ), "PV" )
{
	status = 0;
	helpCtx = hcFormDefInit;
	insert( new TStaticText( TRect( 6,  3, 34,  4 ),
							 "Koelliker Broautomation AG" ) );

	insert( new TStaticText( TRect( 10,  5, 29,  6 ), "Personen-Verwaltung" ) );
	insert( new TStaticText( TRect( 10,  6, 29,  7 ), "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ" ) );
	insert( new TStaticText( TRect( 13,  7, 25,  8 ), "Version 2.97" ) );
	insert( new TStaticText( TRect(  9,  9, 30, 10 ), "Copyright (c) 1994 by" ) );
	insert( new TStaticText( TRect( 12, 11, 26, 12 ), "Juraj Skripsky" ) );
}


/*---- Public Methods --------------------------*/

void TAboutDialog::handleEvent( TEvent& event )
{
	if( event.what == evCommand )
		switch( event.message.command )
			{
			case cmFormDefInit:
				if( status != 0 )
					{
					remove( status );
					destroy( status );
					}
				status = new TStaticText( TRect(  7, 14, 31, 15 ),
										  "Formular wird geladen..." );
				insert( status );
				clearEvent( event );
				return;

			case cmListLoad:
				if( status != 0 )
					{
					remove( status );
					destroy( status );
					}
				status = new TStaticText( TRect(  8, 14, 31, 15 ),
										  "Daten werden geladen..." );
				insert( status );
				clearEvent( event );
				return;

			case cmInitDone:
				if( status != 0 )
					{
					remove( status );
					destroy( status );
					}
				insert( new TButton( TRect( 14, 14, 24, 16 ), "OK", cmOK,
									 bfDefault ) );
				helpCtx = hcEnter;
				drawView();
				clearEvent( event );
				return;

			case cmOK:
			case cmClose:
				message( TProgram::deskTop->owner, evCommand, cmAboutDismissed, 0 );
				owner->remove( this );
				clearEvent( event );
				return;

			case cmIntRevision:
				messageBoxRect( TRect( 24, 7, 55, 17 ),
							mfInformation | mfOKButton,
							"%s\nBorland C++ %X.%X\n%s, %s\n%s",
							internalRevision,
							__BCPLUSPLUS__ / 0xFF,
							__BCPLUSPLUS__ % 0xFF,
							__DATE__, __TIME__,
#ifndef RELEASE
							"--- DEBUG VERSION!!!! ---"
#else
							"-------------------------"
#endif
						  );

				clearEvent( event );
				return;

			case cmHeapView:
				((TPV *)TProgram::application)->createHeapView();
				clearEvent( event );
				return;
			}
	TDialog::handleEvent( event );
}
