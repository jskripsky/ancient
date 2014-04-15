/*****************************************************************************
**                                                                          **
**                                                                          **
**  DOS Form Designer                                                       **
**  =================                                                       **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  tvFormFolder Class                                                      **
**  ------------------                                                      **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvFormFolder                                                  **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFORM.CPP                                                 **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_TRadioButtons
#define Uses_TInputLine
#define Uses_TNSCollection
#include "tvForm.H"
#include "TFormDlg.H"
#include "HelpCtx.H"
#include "FrmPrn.H"
#include "FrmSpace.H"
#include "TObjColl.H"

#include "tvFrmTF.H"
#include "tvFrmSTx.H"

#include <String.H>
#include <StdLib.H>


tvFormFolder::tvFormFolder( tvFolder *aFolder ) :
	tvFolder( aFolder, "Formular 1", True ),
	type( Formular ),
	number( 1 )
{
}


void tvFormFolder::insertObject( tvObject * )
{
	TNSCollection *classes = new TNSCollection( 2, 1 );
	classes->insert( "Text" );
	classes->insert( "Fester Text" );

	tvObject *obj;
	switch( selectClass( classes ) )
		{
		case 1:
			obj = new tvFormTextField( this, "Text" );
			break;

		case 2:
			obj = new tvFormStaticText( this, "Fester Text" );
			break;

		default:
			obj = 0;
			break;
		}

	if( obj )
		tvFolder::insertObject( obj );

	delete classes;
}


Boolean tvFormFolder::handleNotification( TView *view )
{
	if( tvObject::handleNotification( view ) )
		return True;

	TFormFldDlg *dlg = (TFormFldDlg *)tvObject::dlg;

	if( (view == dlg->typeSwitch) || (view == dlg->formNumber) )
		{
		dlg->typeSwitch->getData( &type );
		dlg->formNumber->getData( &number );

		dlg->titleLine->getData( title );

		switch( type )
			{
			case Formular:
				memcpy( title, "Formular ", 9 );
				break;
			case Etikette:
				memcpy( title, "Etikette ", 9 );
				break;
			}
		itoa( number, &title[9], 10 );
		dlg->titleLine->setData( title );

		return handleNotification( dlg->titleLine );
		}
	return False;
}


void tvFormFolder::fillDlg()
{
	tvFolder::fillDlg();

	TFormFldDlg *dlg = (TFormFldDlg *)tvObject::dlg;
	dlg->typeSwitch->setData( &type );
	dlg->formNumber->setData( &number );
}


TObjDlg *tvFormFolder::createDlg()
{
	return( new TFormFldDlg( TRect( 3, 2, 29, 21 ), this ) );
}


ushort tvFormFolder::getHelpCtx()
	{ return  hcFormFolder; }


void tvFormFolder::write( FormDevice *formDevice )
{
	char blockTitle[11];
	switch( type )
		{
		case Formular:
			memcpy( blockTitle, "formular", 9 );
			break;
		case Etikette:
			memcpy( blockTitle, "etikett", 9 );
			break;
		}
	itoa( number, &blockTitle[strlen( blockTitle )], 10 );

	formDevice->openBlock( blockTitle );
	formDevice->registerCustomBlockClosing( &tvFormFolder::blockClosing );

	for( int i = 0; i < objects->getCount(); i++ )
		{
		tvFormObj *formObj = (tvFormObj *)objects->at( i );
		if( formObj )
			formObj->write( formDevice );
		}

	((FormPrinter *)formDevice)->getPaperSpace()->formFeed();

	formDevice->closeBlock();
}

void tvFormFolder::blockClosing( FormDevice *formDevice )
{
	formDevice->disableZeroConversion();
	formDevice->writeByte( 0 );
	formDevice->enableZeroConversion();

	formDevice->standardBlockClosing();
}


const char *const near tvFormFolder::name = "tvFormFolder";

TStreamableClass RtvFormFolder( tvFormFolder::name,
								tvFormFolder::build,
								__DELTA( tvFormFolder )
							  );


tvFormFolder::tvFormFolder( StreamableInit ) :
	tvFolder( streamableInit )
	{}


TStreamable *tvFormFolder::build()
{
	return new tvFormFolder( streamableInit );
}


void tvFormFolder::write( opstream& os )
{
	tvFolder::write( os );

	os << (int)0x0100;

	os << (int)type;
	os << number;
}


void *tvFormFolder::read( ipstream& is )
{
	tvFolder::read( is );

	int version;
	is >> version;

	is >> (int)type;
	is >> number;
	return this;
}
