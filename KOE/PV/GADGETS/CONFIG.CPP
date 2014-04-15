/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Configuration Source File 		        */
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Gadgets\Config.Use"

#define Uses_TStreamableClass
#define Uses_TDialog
#define Uses_TLabel
#define Uses_TRadioButtons
#define Uses_TSItem
#define Uses_TButton
#define Uses_TProgram
#define Uses_TDeskTop

#include <TV.H>
#include "Gadgets\Config.H"

#include <String.H>


/*---- Constructors, Destructors ---------------*/

TConfiguration::TConfiguration()
{
	ports[printer] = 0;
	ports[encoder] = 0;
}


/*---- Public Methods --------------------------*/


void TConfiguration::dlgPrinterPort()
{
	TDialog *dlg = new TDialog( TRect( 24, 4, 55, 20 ), "Schnittstellen" );

#ifdef RELEASE
	TRadioButtons *rb = new TRadioButtons( TRect( 3, 3, 14, 11 ),
			new TSItem( "kein",
			new TSItem( "LPT1",
			new TSItem( "LPT2",
			new TSItem( "LPT3",
			new TSItem( "COM1",
			new TSItem( "COM2",
			new TSItem( "COM3",
			new TSItem( "COM4", 0 ) )))))))
			);
#else
	TRadioButtons *rb = new TRadioButtons( TRect( 3, 3, 14, 12 ),
			new TSItem( "kein",
			new TSItem( "LPT1",
			new TSItem( "LPT2",
			new TSItem( "LPT3",
			new TSItem( "COM1",
			new TSItem( "COM2",
			new TSItem( "COM3",
			new TSItem( "COM4",
			new TSItem( "PRT", 0 ) ))))))))
			);
#endif

	dlg->insert( rb );
	dlg->insert( new TLabel( TRect( 2, 2, 16, 3 ), "Drucker", rb ) );

#ifdef RELEASE
	rb = new TRadioButtons( TRect( 16, 3, 27, 11 ),
			new TSItem( "kein",
			new TSItem( "LPT1",
			new TSItem( "LPT2",
			new TSItem( "LPT3",
			new TSItem( "COM1",
			new TSItem( "COM2",
			new TSItem( "COM3",
			new TSItem( "COM4", 0 ) )))))))
			);
#else
	rb = new TRadioButtons( TRect( 16, 3, 27, 12 ),
			new TSItem( "kein",
			new TSItem( "LPT1",
			new TSItem( "LPT2",
			new TSItem( "LPT3",
			new TSItem( "COM1",
			new TSItem( "COM2",
			new TSItem( "COM3",
			new TSItem( "COM4",
			new TSItem( "PRT", 0 ) ))))))))
			);
#endif

	dlg->insert( rb );
	dlg->insert( new TLabel( TRect( 15, 2, 29, 3 ), "Codierer", rb ) );

	dlg->insert( new TButton( TRect( 2, 13, 14, 15 ), "~O~K", cmOK,
							  bfDefault ) );

	dlg->insert( new TButton( TRect( 15, 13, 28, 15 ), "~A~bbrechen", cmOK,
							  bfNormal ) );


	dlg->setData( ports );

	dlg->selectNext( False );

	if( TProgram::deskTop->execView( dlg ) == cmOK )
		dlg->getData( ports );

	destroy( dlg );
}


void TConfiguration::getPrinterPortName( char *rec )
{
	switch( ports[printer] )
		{
		case 0:
			strcpy( rec, "NUL" );
			break;
		case 1:
			strcpy( rec, "LPT1" );
			break;
		case 2:
			strcpy( rec, "LPT2" );
			break;
		case 3:
			strcpy( rec, "LPT3" );
			break;
		case 4:
			strcpy( rec, "COM1" );
			break;
		case 5:
			strcpy( rec, "COM2" );
			break;
		case 6:
			strcpy( rec, "COM3" );
			break;
		case 7:
			strcpy( rec, "COM4" );
			break;
#ifndef RELEASE
		case 8:
			strcpy( rec, "PRT" );
			break;
#endif
		}
}


void TConfiguration::getEncoderPortName( char *rec )
{
	switch( ports[encoder] )
		{
		case 0:
			strcpy( rec, "NUL" );
			break;
		case 1:
			strcpy( rec, "LPT1" );
			break;
		case 2:
			strcpy( rec, "LPT2" );
			break;
		case 3:
			strcpy( rec, "LPT3" );
			break;
		case 4:
			strcpy( rec, "COM1" );
			break;
		case 5:
			strcpy( rec, "COM2" );
			break;
		case 6:
			strcpy( rec, "COM3" );
			break;
		case 7:
			strcpy( rec, "COM4" );
			break;
#ifndef RELEASE
		case 8:
			strcpy( rec, "PRT" );
			break;
#endif
		}
}


Boolean TConfiguration::passThrough()
{
	if( ports[encoder] == ports[printer] )
		return True;
	else
		return False;
}


/*---- TStreamable Methods ---------------------*/

const char * const TConfiguration::name = "TConfiguration";


TStreamable *TConfiguration::build()
{
	return new TConfiguration( streamableInit );
}


void TConfiguration::write( opstream& os )
{
	os.writeBytes( ports, sizeof( ports ) );
}


void *TConfiguration::read( ipstream& is )
{
	is.readBytes( ports, sizeof( ports ) );
	return this;
}


TStreamableClass RConfiguration( TConfiguration::name,
			 TConfiguration::build,
			 __DELTA(TConfiguration)
			   );
