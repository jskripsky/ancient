/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Form Dialog Source File 		        */
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "FormDlg.Use"
#include "FormDef\FormDef.Use"

#define Uses_TFrame
#define Uses_TButton
#define Uses_TStaticText
#define Uses_TEvent
#define Uses_TPoint

#include <TV.H>
#include "FormDlg.H"
#include "FormDef\FormDef.H"
#include "Defs\Commands.H"
#include "Defs\HelpCtx.H"

#include <String.H>


const ushort maxPages		=     20;

const TPoint pageOrigin     = { 4, 3 };


/*---- Constructors, Destructors ---------------*/

TFormDialog::TFormDialog() :
	TWindowInit( &TFormDialog::initFrame ),
	TDialog( TRect( 0, 0, 80, 23 ), "                    " ),
	controls( new TTransGroup( TRect( 51, 3, 75, 21 ) ) ),
	curPageNo( noPage )
{
	helpCtx = hcFormDlg;
	flags &= ~(wfClose | wfMove);

	info = new TInfo();
	person = new TPerson( *formDef->person );
	info->attachRecord( person );

	form = formDef->form;
	adjustForm( pageOrigin );

	insert( new TStaticText( TRect( 48, 3, 49, 20 ),
							 "³³³³³³³³³³³³³³³³³" ) );

	controls->insert( new TView( controls->getExtent() ) );
	controls->insert( new TButton( TRect( 0, 0, 19, 2 ), "~N~„chste Seite",
								   cmNextPage, bfLeftJust ) );
	controls->insert( new TButton( TRect( 0, 2, 19, 4 ), "~V~orherige Seite",
								   cmPrevPage, bfLeftJust ) );

	int step = (form->pageCount() <= 5) ? 2 : 1;
	for( int i = 0; i < form->pageCount(); i++ )
		controls->insert( new TButton( TRect(  0,  5 + i * step,
											  24,  7 + i * step ),
									   form->at( i )->title(),
									   cmFirstPage + i, bfLeftJust ) );

	char *string = new char[maxStringLength + 1];
	formDef->stringList->get( string, skFormDlgOK );
	if( strlen( string ) == 0 )
		strcpy( string, "~O~K" );

	controls->insert( new TButton( TRect( 0, 16, 8, 18 ), string,
								   cmOK, 0 ) );

	formDef->stringList->get( string, skFormDlgCancel );
	if( strlen( string ) == 0 )
		strcpy( string, "~A~bbrechen" );

	controls->insert( new TButton( TRect( 9, 16, 24, 18 ), string,
								   cmCancel, 0 ) );

	delete[] string;

	controls->selectNext( False );
	controls->helpCtx = hcFormDlgControl;
	insert( controls );
}


TFormDialog::~TFormDialog()
{
	if( curPageNo != noPage )
		currentPage()->removeFrom( this );
//	destroy( (TObject *)(person->person()) );
//	destroy( (TObject *)person );
}


/*---- Public Methods --------------------------*/

void TFormDialog::loadPerson( TInfo *aInfo, Boolean aNewPerson )
{
	originalInfo = aInfo;

	*info = *originalInfo;
	*person = *((TPerson *)originalInfo->getRecord());

	changeToPageNo( 0 );

	newPerson = aNewPerson;
}


void TFormDialog::changeToPageNo( ushort pageNo, Boolean check )
{
	if( check )
		if( curPageNo != noPage )
			if( !currentPage()->checkFields() )
				return;

	lock();
	if( curPageNo != noPage )
		{
		currentPage()->getData( person->getData() );
		currentPage()->setInfo( *info );
		currentPage()->setAccessCode( *info );
		currentPage()->removeFrom( this );
		}
	if( pageNo == noPage )
		curPageNo = noPage;
	else
		{
		curPageNo = pageNo;
		currentPage()->insertInto( this );
		currentPage()->setData( person->getData() );
		setTitle( currentPage()->title() );
		}
	controls->selectFirst();
	unlock();
}


void TFormDialog::handleEvent( TEvent& event )
{
	if( event.what == evCommand )
		{
		switch( event.message.command )
			{
			case cmNextPage:
				if( curPageNo < (form->pageCount() - 1) )
					changeToPageNo( curPageNo + 1 );
				else
					changeToPageNo( 0 );
				clearEvent( event );
				return;

			case cmPrevPage:
				if( curPageNo > 0 )
					changeToPageNo( curPageNo - 1 );
				else
					changeToPageNo( (form->pageCount() - 1) );
				clearEvent( event );
				return;

			case cmOK:
			case cmImportOK:

//				if( originalInfo->getAccessCode() != 0 )
//					{
//					changeToPageNo( noPage, False );
//					break;
//					}

				switch( event.message.command )
					{
					case cmOK:
						changeToPageNo( noPage );
						break;

					case cmImportOK:
						changeToPageNo( noPage, False );
						break;
					}

				if( curPageNo != noPage )
					{
					clearEvent( event );
					return;
					}

				*originalInfo = *info;
				*((TPerson *)originalInfo->getRecord()) = *person;

				originalInfo->setUpdateFlag();
				originalInfo->getRecord()->setUpdateFlag();
				break;

			case cmCancel:
				if( !newPerson )
					changeToPageNo( noPage, False );
				else
					{
					clearEvent( event );
					return;
					}
				break;

			default:
				if( (event.message.command >= cmFirstPage) &&
					(event.message.command < cmFirstPage + maxPages) )
					{
					changeToPageNo( event.message.command - cmFirstPage );
					clearEvent( event );
					return;
					}
				break;
			}
		}
	TDialog::handleEvent( event );
}


void TFormDialog::print( TOutputDevice& outputDevice )
{
	for( int pcounter = 0; pcounter < form->pageCount(); pcounter++ )
		{
		changeToPageNo( pcounter );
		currentPage()->print( outputDevice );
		}

	changeToPageNo( noPage );
}


/*---- Protected Methods -----------------------*/

void TFormDialog::setTitle( char *aTitle )
{
	strcpy( (char *)title, aTitle );
	frame->drawView();
}
