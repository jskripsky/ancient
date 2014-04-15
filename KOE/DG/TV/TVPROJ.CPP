/*****************************************************************************
**                                                                          **
**                                                                          **
**  DOS Dialog Generator                                                    **
**  ====================                                                    **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  tvProject Class                                                         **
**  ---------------                                                         **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvProject                                                     **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVPROJ.CPP                                                 **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#define Uses_ofpstream
#define Uses_ifpstream
#define Uses_TDialog
#define Uses_TListBox
#define Uses_TScrollBar
#define Uses_TLabel
#define Uses_TButton
#define Uses_TProgram
#define Uses_TDeskTop
#include "tvProj.H"
#include "TProjDlg.H"
#include "TObjColl.H"
#include "HelpCtx.H"
#include "tvDialog.H"
#include "FormDlg.H"
#include "TLBCol.H"

#include "tvKeyFld.H"
#include "tvDGMain.H"
#include "tvSysFld.H"

#include <String.H>
#include <StdLib.H>
#include <StdIO.H>


tvProject::tvProject( tvFolder *aFolder ) :
	tvDocument( aFolder, "Applikation", True )
{
	if( !objectsInMemory )
		readFile();

	tvObject *keyFld = new tvKeyFolder( this );
	objects->insert( keyFld );
	keyFolder = keyFld->getHandle();

	writeFile();
}


void tvProject::insertObject( tvObject * )
{
	tvFolder::insertObject( new tvDialog( this ) );
}


TObjDlg *tvProject::createDlg()
{
	return( new TProjectDlg( TRect( 1, 1, 27, 21 ), this ) );
}


ushort tvProject::getHelpCtx()
	{ return  hcProject; }


tvFolder *tvProject::getKeyFolder()
{
	return (tvFolder *)tvObject::getObject( keyFolder );
}


void tvProject::write()
{
	TLBCollection *portList = new TLBCollection( 4, 1 );

	TDialog *portDlg = new TDialog( TRect( 31, 4, 49, 18 ), "Download" );
	TScrollBar *portSB = new TScrollBar( TRect( 14, 3, 15, 8 ) );
	TListBox *portLB = new TListBox( TRect( 3, 3, 14, 8 ), 1, portSB );

	portList->insert( "COM1" );
	portList->insert( "COM2" );
	portList->insert( "COM3" );
	portList->insert( "COM4" );
	portList->insert( "FORM.ALL" );

	portLB->newList( portList );
	portDlg->insert( portLB );
	portDlg->insert( portSB );
	portDlg->insert( new TLabel( TRect( 2, 2, 8, 3 ), "~P~ort", portLB ) );
	portDlg->insert( new TButton( TRect( 2, 9, 16, 11 ), "~O~K",
								 cmOK, bfDefault ) );
	portDlg->insert( new TButton( TRect( 2, 11, 16, 13 ), "~A~bbrechen",
								 cmCancel, bfNormal ) );
	portLB->select();

	if( TProgram::deskTop->execView( portDlg ) == cmOK )
		{
		FormDialog *formDialog;
		if( portLB->focused == 4  )
			formDialog = new FormDialog( "FORM.ALL" );
		else
			formDialog = new FormDialog( portLB->focused + 4 );

		write( formDialog );
		delete formDialog;
		}

	destroy( portDlg );
	delete portList;
}


void tvProject::write( FormDevice *formDevice )
{
	formDevice->openBlock( "insertion_string" );
	formDevice->closeBlock();

	formDevice->openBlock( "extraction_string" );
	formDevice->closeBlock();

	formDevice->openBlock( "error_string" );
	formDevice->closeBlock();

	formDevice->openBlock( "reset_string" );
	formDevice->closeBlock();

	writeObjects( formDevice );

	tvDGMainFolder *DGMainFolder = (tvDGMainFolder*)mainFolder;
	tvSystemsFolder *systemsFolder =
		(tvSystemsFolder *)DGMainFolder->getSystemsFolder();

	systemsFolder->write( formDevice );
}


void tvProject::writeObjects( FormDevice *formDevice )
{
	for( int i = 0; i < objects->getCount(); i++ )
		{
		tvDialog *formObj = (tvDialog *)objects->at( i );
		if( (void *)formObj == (void *)getKeyFolder() )
			continue;

		if( formObj )
			formObj->write( formDevice );
		}
}


const char *const near tvProject::name = "tvDGProject";

TStreamableClass RtvProject( tvProject::name,
							 tvProject::build,
							 __DELTA( tvProject )
							 );


tvProject::tvProject( StreamableInit ) :
	tvDocument( streamableInit )
	{}


TStreamable *tvProject::build()
{
	return new tvProject( streamableInit );
}


void tvProject::write( opstream& os )
{
	tvDocument::write( os );

	os << (int)0x0100;

	os << keyFolder;
}


void *tvProject::read( ipstream& is )
{
	tvDocument::read( is );

	int version;
	is >> version;

	is >> keyFolder;

	return this;
}
