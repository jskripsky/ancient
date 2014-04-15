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
**  tvFieldsFolder Class                                                    **
**  --------------------                                                    **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvFieldsFolder                                                **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFLDFLD.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TStreamableClass
#include "tvFldFld.H"
#include "tvField.H"
#include "HelpCtx.H"
#include "TObjColl.H"
#include "TrackTab.H"
#include "FrmPrn.H"


tvFieldsFolder::tvFieldsFolder( tvFolder *aFolder ) :
	tvStaticTitleFolder( aFolder, "Felder", False ),
	trackTable( new TrackTable( objects ) )
{
	setAttribute( oaDeletable, False );
}


tvFieldsFolder::~tvFieldsFolder()
{
	delete trackTable;
}


void tvFieldsFolder::insertObject( tvObject * )
{
	tvStaticTitleFolder::insertObject( new tvField( this ) );
}


void tvFieldsFolder::deleteObject()
{
	tvStaticTitleFolder::deleteObject();
	trackTable->reorder();
}



TObjDlg *tvFieldsFolder::createDlg()
{
	return( new TSTFolderDlg( TRect( 3, 2, 29, 21 ), this ) );
}


ushort tvFieldsFolder::getHelpCtx()
	{ return  hcFieldsFolder; }


void tvFieldsFolder::write( FormDevice *formDevice )
{
	switch( tvField::printMode )
		{
		case Blockung:
			formDevice->openBlock( "blockung" );
			break;
		case Felder:
			formDevice->openBlock( "felder" );
			formDevice->writeNumber( 1 );
			formDevice->writeNumber( 1 );
			formDevice->writeNumber( 1 );
			formDevice->newLine();
			break;
		}

	formDevice->registerCustomBlockClosing( &tvFieldsFolder::blockClosing );

	for( int i = 0; i < objects->getCount(); i++ )
		{
		tvField *field = (tvField *)objects->at( i );
		if( field )
			field->write( formDevice );
		}

	formDevice->closeBlock();
}


void tvFieldsFolder::blockClosing( FormDevice *formDevice )
{
	formDevice->disableZeroConversion();
	formDevice->writeByte( 0 );
	formDevice->writeByte( 0 );
	formDevice->enableZeroConversion();

	formDevice->standardBlockClosing();
}


int tvFieldsFolder::getFieldsLengthSum()
{
	int sum = 0;
	for( int i = 0; i < objects->getCount(); i++ )
		{
		tvField *field = (tvField *)objects->at( i );
		if( field )
			sum += field->getLength();
		}
	return sum;
}


const char *const near tvFieldsFolder::name = "tvFieldsFolder";

TStreamableClass RtvFieldsFolder( tvFieldsFolder::name,
								  tvFieldsFolder::build,
								  __DELTA( tvFieldsFolder )
								  );


tvFieldsFolder::tvFieldsFolder( StreamableInit ) :
	tvStaticTitleFolder( streamableInit )
	{}


TStreamable *tvFieldsFolder::build()
{
	return new tvFieldsFolder( streamableInit );
}


void *tvFieldsFolder::read( ipstream& is )
{
	tvStaticTitleFolder::read( is );

	int version;
	is >> version;

	trackTable = new TrackTable( objects );
	return this;
}


void tvFieldsFolder::write( opstream& os )
{
	tvStaticTitleFolder::write( os );
	os << (int)0x0100;
}
