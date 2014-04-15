/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		List Window Source File 		    	*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "ListWin.Use"
#include "Device.Use"
#include "FormDef\FormDef.Use"
#include "Gadgets\Gadgets.Use"

#define Uses_TDeskTop
#define Uses_TProgram
#define Uses_TButton
#define Uses_MsgBox
#define Uses_TRadioButtons
#define Uses_TCheckBoxes
#define Uses_TInputLine
#define Uses_TLabel

#include <TV.H>
#include "ListWin.H"
#include "Device.H"
#include "FormDef\FormDef.H"
#include "Gadgets\Config.H"
#include "LogPrint.H"
#include "Defs\Commands.H"
#include "Defs\HelpCtx.H"

#include "Date.H"

#include <String.H>
#include <DOS.H>
#include <StdLib.H>


#define	Export		0
#define Protocol	1


extern Boolean isDirty;
extern Boolean isSaveable;

extern Boolean controlField;

/*---- Constructors, Destructors ---------------*/

TListWindow::TListWindow( const char *title ) :
	TWindowInit( &TListWindow::initFrame ),
	TDialog( TRect( 0, 0, 80, 23 ), title )
{
	options &= ~ofBuffered;

	helpCtx = hcListWin;
	flags &= ~(wfClose | wfMove);

	insert( scrollBar = new TScrollBar( TRect( 46, 3, 47, 21 ) ) );

	insert( (TView *)(box = new TAlphaListBox( TRect( 4, 3, 46, 21 ),
											   scrollBar )) );

	char *string = new char[maxStringLength + 1];
	formDef->stringList->get( string, skPersonList );
	insert( new TLabel( TRect( 3, 2, 46, 3 ), string, (TView *)box ) );

	formDef->stringList->get( string, skNewPerson );
	insert( new TButton( TRect( 50, 3, 75,  5 ), string,
						 cmNewPerson, bfNormal | bfLeftJust ) );

	formDef->stringList->get( string, skDeletePerson );
	if( strlen( string ) > 0 )
		insert( new TButton( TRect( 50, 5, 75,  7 ), string,
							 cmDeletePerson, bfNormal | bfLeftJust ) );

	formDef->stringList->get( string, skEditPerson );
	insert( new TButton( TRect( 50, 7, 75,  9 ), string,
						 cmEditPerson, bfNormal | bfLeftJust ) );

	formDef->stringList->get( string, skPrintPerson );
	if( strlen( string ) > 0 )
		insert( new TButton( TRect( 50, 10, 75, 12 ), string,
							 cmPrintPerson, bfNormal | bfLeftJust ) );

	formDef->stringList->get( string, skRawPrintPerson );
	if( strlen( string ) > 0 )
		insert( new TButton( TRect( 50, 12, 75, 14 ), string,
							 cmRawPrintPerson, bfNormal | bfLeftJust ) );

	formDef->stringList->get( string, skEncodeCard );
	if( strlen( string ) > 0 )
		insert( new TButton( TRect( 50, 14, 75, 16 ), string,
							 cmEncodeCard, bfNormal | bfLeftJust ) );

	formDef->stringList->get( string, skPrintLog );
	if( strlen( string ) > 0 )
		insert( new TButton( TRect( 50, 16, 75, 18 ), string,
							 cmPrintLog, bfNormal | bfLeftJust ) );

	formDef->stringList->get( string, skExportData );
	if( strlen( string ) > 0 )
		insert( new TButton( TRect( 50, 18, 75, 20 ), string,
							 cmExportData, bfNormal | bfLeftJust ) );

	delete[] string;

	insert( new TButton( TRect( 51, 20, 74, 22 ), "Programm ~v~erlassen",
						 cmQuit, bfNormal | bfLeftJust ) );

	box->select();
	formDialog = new( TFormDialog );
}


TListWindow::~TListWindow()
{
	isSaveable = False;
	destroy( (TObject *)formDialog );
}


/*---- Public Methods --------------------------*/

void TListWindow::setState( ushort aState, Boolean enable )
{
	TDialog::setState( aState, enable );

	if( (aState & sfVisible) && enable )
		if( box->list()->getCount() == 0 )
			message( this, evCommand, cmNewPerson, 0 );
}


void TListWindow::handleEvent( TEvent& event )
{
	Boolean temp;
	TDialog::handleEvent( event );
	if( event.what == evCommand )
		{
		switch( event.message.command )
			{
			case cmNewPerson:
				if( formDef->confirmNewPerson )
					if( messageBox( "Soll wirklich eine neue Person eingefgt werden?",
									mfConfirmation | mfOKButton | mfCancelButton ) ==
						cmCancel )
						break;

				isSaveable = False;

				TInfo *info = new TInfo();
				if( lowMemory() )
					{
					destroy( (TObject *)info );
					TProgram::application->outOfMemory();
					break;
					}

				TPerson *person = new TPerson( *formDef->person );
				info->attachRecord( person );

				box->insert( info );

				openForm( True );
				box->update();
				box->select();

				isSaveable = True;
				break;

			case cmEditPerson:
				isSaveable = False;

				openForm();
				box->update();
				box->select();

				isSaveable = True;
				break;

			case cmDeletePerson:
				isSaveable = False;

				if( box->list()->getCount() > 1 )
					if( messageBox( "Soll diese Person wirklich gel”scht werden?",
									mfConfirmation | mfOKButton | mfCancelButton ) ==
						cmOK )
						{
						box->free();
						box->update();
						box->select();
						if( box->list()->getCount() == 0 )
							message( this, evCommand, cmNewPerson, 0 );
						}

				box->select();

				isSaveable = True;
				break;

			case cmPrintPerson:
				temp = isSaveable;
				isSaveable = False;

				print( form );
				box->select();

				isSaveable = temp;
				break;

			case cmRawPrintPerson:
				temp = isSaveable;
				isSaveable = False;

				print( text );
				box->select();

				isSaveable = temp;
				break;

			case cmEncodeCard:
				temp = isSaveable;
				isSaveable = False;

				print( card );
				box->select();

				isSaveable = temp;
				break;

			case cmSaveList:
				box->writeListFile();
				break;

			case cmPrintLog:
				temp = isSaveable;
				isSaveable = False;

				exportData( Protocol );

				isSaveable = temp;
				break;

			case cmExportData:
				temp = isSaveable;
				isSaveable = False;

				exportData( Export );

				isSaveable = temp;
				break;


			default:
				return;
			}
		clearEvent( event );
		}
}


/*---- Private Methods -------------------------*/

void TListWindow::print( ushort mode )
{
	TDialog *statusDlg = new TDialog( TRect( 20, 9, 58, 14),
									  "Drucken / Kodieren..." );
	TStaticText *st;

	switch( mode )
		{
		case form:
			st = new TStaticText( TRect( 7, 2, 32, 3 ),
								  "Formular wird gedruckt..." );
			break;

		case text:
			st = new TStaticText( TRect( 7, 2, 32, 3 ),
								  "Daten werden gedruckt..." );
			break;

		case card:
			st = new TStaticText( TRect( 9, 2, 31, 3 ),
								  "Karte wird codiert..." );
			break;
		}

	statusDlg->insert( st );
	TProgram::deskTop->insert( statusDlg );

	formDialog->loadPerson( box->focusedPerson() );

	TOutputDevice *printer;
	printer = new TOutputDevice( mode );

	formDialog->print( *printer );
	delete printer;

	TProgram::deskTop->remove( statusDlg );
	destroy( statusDlg );
}


void TListWindow::exportData( int mode )
{
	char title[30];
	switch( mode )
		{
		case Export:
			strcpy( title, "Datenexport..." );
			break;
		case Protocol:
			strcpy( title, "Reportliste..." );
			break;
		}

	TDialog *dlg = new TDialog( TRect( 25, 2, 54, 22 ), title );

	dlg->insert( new TButton( TRect( 9, 15, 19, 17 ), "~O~K",
							  cmOK, bfDefault ) );

	dlg->insert( new TButton( TRect( 6, 17, 22, 19 ), "~A~bbrechen",
							  cmCancel, 0 ) );

	TInputLine *il = new TInputLine( TRect( 9, 2, 22, 3 ), 11 );
	dlg->insert( il );
	dlg->insert( new TLabel( TRect( 2, 2, 8, 3 ), "Datum", il ) );


	struct date dateToday;
	char dateStr[11];

	strcpy( dateStr, "  .  .    " );

	getdate( &dateToday );

	int offset;
	if( dateToday.da_day < 10 )
		offset = 1;
	else
		offset = 0;

	itoa( dateToday.da_day, &dateStr[offset], 10 );
	dateStr[2] = '.';

	if( dateToday.da_mon < 10 )
		offset = 1;
	else
		offset = 0;

	itoa( dateToday.da_mon, &dateStr[3 + offset], 10 );
	dateStr[5] = '.';

	itoa( dateToday.da_year, &dateStr[6], 10 );

	il->setData( dateStr );


	Boolean moreLists = True;

	TRadioButtons *rb;
	TCheckBoxes *cb;

	if( mode == Protocol )
		{
		rb = new TRadioButtons( TRect( 3, 5, 26, 12 ),
					  new TSItem( "in Behandlung",
					  new TSItem( "entlassen",
					  new TSItem( "station„r",
					  new TSItem( "D13 Eigenunfall entl.",
					  new TSItem( "D13 Eigenunfall stat.",
					  new TSItem( "D13 entlassen",
					  new TSItem( "D13 station„r", 0 ))))))) );

		dlg->insert( rb );
		dlg->insert( new TLabel( TRect( 2, 4, 20, 5 ), "Auswahl", rb ) );

		cb = new TCheckBoxes( TRect( 3, 13, 26, 14 ),
				new TSItem( "weitere Listen...", 0 ) );

		dlg->insert( cb );

		cb->setData( &moreLists );
		}
	else
		moreLists = False;

	int rc;

	do
		{
		il->select();
		rc = TProgram::deskTop->execView( dlg );
		if( rc == cmCancel )
			break;

		if( mode == Protocol )
			cb->getData( &moreLists );

		struct date userDate;
		char dateString[11];
		il->getData( dateString );

		for( int c = 0; c < strlen( dateString ); c++ )
			if( dateString[c] == '.' )
				dateString[c] = 0;

		int ofs = 0;
		userDate.da_day = atoi( &dateString[ofs] );
		ofs += strlen( &dateString[ofs] ) + 1;
		userDate.da_mon = atoi( &dateString[ofs] );
		ofs += strlen( &dateString[ofs] ) + 1;
		userDate.da_year = atoi( &dateString[6] );

		Date date;
		if( !date.set( userDate.da_year, (Month)userDate.da_mon,
					  userDate.da_day ) )
			{
			messageBox( "Datum ist ungltig!", mfError | mfOKButton );
			continue;
			}


		LogPrinter *logPrinter;

		int ctrlMode;

		if( mode == Protocol )
			{
			rb->getData( &ctrlMode );

			logPrinter = new LogPrinter( ctrlMode, &userDate );
			}

		for( short item = 0; item < box->list()->getCount(); item++ )
			{
			box->focusItem( item );
			TInfo *info = box->focusedPerson();

			TPerson *person = (TPerson *)info->getRecord();

			char *data = (char *)person->getData();
			strcpy( dateString, &data[0x45] );

			struct date personDate;

			dateString[2] = 0;
			dateString[5] = 0;
			dateString[8] = 0;

			personDate.da_day = atoi( &dateString[0] );
			personDate.da_mon = atoi( &dateString[3] );
			personDate.da_year = atoi( &dateString[6] ) + 1900;

			if( (personDate.da_day == userDate.da_day) &&
				(personDate.da_mon == userDate.da_mon) &&
				(personDate.da_year == userDate.da_year) )
				{
				formDialog->loadPerson( box->focusedPerson(), False );
				switch( mode )
					{
					case Protocol:

						if( info->getAccessCode() == ctrlMode )
							logPrinter->writeEntry( info );

						break;

					case Export:
						switch( info->getAccessCode() )
							{
							case 1:
							case 3:
							case 5:
								char *data;
								data = (char *)((TPerson *)info->getRecord())->getData();
								if( data[0xCB] == 2 )
									break;

							case 2:
							case 4:
							case 6:
								BogenhausenExport( info );
								break;
							}

						if( info->getAccessCode() != 0 )
							{
							if( info->getAccessCode() == 0 )
							BogenhausenExport( info );
							}
						break;
					}
				}

			}

		if( mode == Protocol )
			delete logPrinter;
		}
	while( moreLists );

	destroy( dlg );
}


void TListWindow::openForm( Boolean newPerson )
{
	formDialog->loadPerson( box->focusedPerson(), newPerson );
	hide();
	TProgram::deskTop->execView( (TView *)formDialog );
	show();
};
