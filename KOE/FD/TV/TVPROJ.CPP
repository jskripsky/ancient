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
#include "tvProj.H"
#include "TProjDlg.H"
#include "TObjColl.H"
#include "tvFldFld.H"
#include "tvForm.H"
#include "tvField.H"
#include "HelpCtx.H"
#include "FrmPrn.H"
#include "FrmSpace.H"

#include <String.H>
#include <StdLib.H>
#include <StdIO.H>


tvProject::tvProject( tvFolder *aFolder ) :
	tvDocument( aFolder, "Applikation", True )
{
	if( !objectsInMemory )
		readFile();

	tvObject *fldFld = new tvFieldsFolder( this );
	fieldsFolder = fldFld->getHandle();
	objects->insert( fldFld );

	writeFile();
}


void tvProject::insertObject( tvObject * )
{
	tvFolder::insertObject( new tvFormFolder( this ) );
}


tvFolder *tvProject::getFieldsFolder()
{
	return (tvFolder *)tvObject::getObject( fieldsFolder );
}


TObjDlg *tvProject::createDlg()
{
	return( new TProjectDlg( TRect( 1, 1, 27, 20 ), this ) );
}


ushort tvProject::getHelpCtx()
	{ return  hcProject; }


void tvProject::writeDocument( opstream& os )
{
	tvDocument::writeDocument( os );
	os << fieldsFolder;
}


void tvProject::readDocument( ipstream& is )
{
	tvDocument::readDocument( is );
	is >> fieldsFolder;
}


void tvProject::write()
{
	FormPrinter *printer = new FormPrinter( "Test.Prn" );
	FormSpace *formSpace = new FormSpace( printer );

	write( printer );
	printer->writeCustomBlocks();
	delete formSpace;
	delete printer;
}


void tvProject::write( FormDevice *formDevice )
{
	tvFieldsFolder *fieldsFolder = (tvFieldsFolder *)getFieldsFolder();

	formDevice->openBlock( "start_blockung" );
	formDevice->writeNumber( 40 );
	formDevice->writeNumber( 42 );
	formDevice->writeNumber( 53 );
	formDevice->closeBlock();

	formDevice->openBlock( "ende_blockung" );
	formDevice->closeBlock();

	formDevice->openBlock( "laenge_blockung" );
	formDevice->writeNumber( fieldsFolder->getFieldsLengthSum() + 3 );
	formDevice->closeBlock();

	tvField::printMode = Blockung;
	fieldsFolder->write( formDevice );

	tvField::printMode = Felder;
	fieldsFolder->write( formDevice );

	for( int i = 0; i < objects->getCount(); i++ )
		{
		tvFormFolder *formFolder = (tvFormFolder *)objects->at( i );
		if( (void *)formFolder == (void *)fieldsFolder )
			continue;

		if( formFolder )
			formFolder->write( formDevice );
		}

}


const char *const near tvProject::name = "tvProject";

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
}


void *tvProject::read( ipstream& is )
{
	tvDocument::read( is );

	int version;
	is >> version;

	return this;
}
