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
**  tvFolder Class                                                          **
**  --------------                                                          **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvFolder                                                      **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFOLDER.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TListBox
#define Uses_TCollection
#define Uses_TNSCollection
#define Uses_TProgram
#define Uses_TDeskTop
#define Uses_TDialog
#define Uses_TButton
#define Uses_TScrollBar
#define Uses_TLabel
#define Uses_TStreamableClass
#include "tvFolder.H"
#include "TFoldDlg.H"
#include "TObjColl.H"
#include "TLBCol.H"


// -----------------------
// Basic tvObject Protocol
// -----------------------

tvFolder::tvFolder( tvFolder *aFolder, const char *aTitle, Boolean sorted ) :
	tvObject( aFolder, aTitle ),
	objects( new TObjCollection( 20, 5 ) )
{
	objects->sorted = sorted;
	objects->insert( 0 );
}


tvFolder::~tvFolder()
{
	destroy( objects );
}


void tvFolder::tvDelete()
{
	while( objects->getCount() > 0 )
		{
		tvObject *obj = (tvObject *)objects->at( 0 );
		objects->remove( obj );
		if( obj )
			obj->tvDelete();
		}

	tvObject::tvDelete();
}


// --------------------------
// Object Management Protocol
// --------------------------

void tvFolder::insertObject( tvObject *obj )
{
	if( obj == 0 )
		return;

	TListBox *lb = ((TFolderDlg *)dlg)->listBox;

	int index;
	if( !objects->sorted )
		objects->atInsert( lb->focused, obj );
	else
		index = objects->insert( obj );

	lb->setRange( objects->getCount() );

	if( objects->sorted )
		lb->focusItem( index );

	lb->drawView();
	editObject();
}


void tvFolder::editObject()
{
	TListBox *lb = ((TFolderDlg *)dlg)->listBox;
	tvObject *obj = (tvObject *)objects->at( lb->focused );
	if( obj != 0 )
		obj->tvOpen();
}


void tvFolder::deleteObject()
{
	TListBox *lb = ((TFolderDlg *)dlg)->listBox;
	tvObject *obj = (tvObject *)objects->at( lb->focused );
	if( isObjectDeletable() )
		{
		objects->remove( obj );
		lb->setRange( objects->getCount() );
		obj->tvDelete();
		lb->drawView();
		}
}


int tvFolder::getObjectActions()
{
	int mask = oaNew | oaEdit | oaMove | oaDelete;
	if( objects->sorted )
		mask &= ~oaMove;

	return mask;
}


Boolean tvFolder::isObjectDeletable()
{
	TListBox *lb = ((TFolderDlg *)dlg)->listBox;
	tvObject *obj = (tvObject *)objects->at( lb->focused );
	if( (obj != 0) && (obj->getAttributes() & oaDeletable) )
		return True;
	else
		return False;
}


TObjCollection *tvFolder::getObjects()
{
	return objects;
}


int tvFolder::selectClass( TNSCollection *classes )
{
	TLBCollection *clsList = new TLBCollection( 9, 1 );

	TDialog *clsDlg = new TDialog( TRect( 28, 3, 52, 19 ), "Neues Objekt" );
	TScrollBar *clsSB = new TScrollBar( TRect( 20, 3, 21, 10 ) );
	TListBox *clsLB = new TListBox( TRect( 3, 3, 20, 10 ), 1, clsSB );

	for( int i = 0; i < classes->getCount(); i++ )
		clsList->insert( classes->at( i ) );

	clsLB->newList( clsList );
	clsDlg->insert( clsLB );
	clsDlg->insert( clsSB );
	clsDlg->insert( new TLabel( TRect( 2, 2, 21, 3 ), "~T~yp", clsLB ) );
	clsDlg->insert( new TButton( TRect( 5, 11, 19, 13 ), "~O~K",
								 cmOK, bfDefault ) );
	clsDlg->insert( new TButton( TRect( 5, 13, 19, 15 ), "~A~bbrechen",
								 cmCancel, bfNormal ) );
	clsLB->select();

	int rc;
	if( TProgram::deskTop->execView( clsDlg ) == cmOK )
		{
		rc = clsLB->focused + 1;
		}
	else
		rc = 0;

	destroy( clsDlg );
	delete clsList;
	return rc;
}


// ---------------
// Dialog Protocol
// ---------------

void tvFolder::fillDlg()
{
	tvObject::fillDlg();

	TFolderDlg *dlg = (TFolderDlg *)tvObject::dlg;
	if( dlg->listBox && (dlg->listBox->list() != objects) )
		((TFolderDlg *)dlg)->listBox->newList( objects );
}


void tvFolder::update( tvObject *obj )
{
	TListBox *lb = ((TFolderDlg *)dlg)->listBox;
	if( objects->sorted )
		{
		objects->remove( obj );
		int index = objects->insert( obj );
		lb->focusItem( index );
		lb->drawView();
		}
}


Boolean tvFolder::startMoveObject()
{
	TListBox *lb = ((TFolderDlg *)dlg)->listBox;
	tvObject *obj = (tvObject *)objects->at( lb->focused );
	if( obj )
		{
		movingObject = obj;
		objects->remove( obj );
		lb->setRange( objects->getCount() );
		lb->drawView();
		return True;
		}
	else
		return False;
}


void tvFolder::endMoveObject()
{
	TListBox *lb = ((TFolderDlg *)dlg)->listBox;
	objects->atInsert( lb->focused, movingObject );
	lb->setRange( objects->getCount() );
	lb->drawView();
}


TObjDlg *tvFolder::createDlg()
{
	return( new TFolderDlg( TRect( 1, 1, 27, 22 ), this ) );
}


// --------------------
// TStreamable Protocol
// --------------------

tvFolder::tvFolder( StreamableInit ) :
	tvObject( streamableInit )
	{}


void *tvFolder::read( ipstream& is )
{
	tvObject::read( is );

	int version;
	is >> version;

	is >> objects;
	for( int i = 0; i < objects->getCount(); i++ )
		((tvObject *)objects->at( i ))->folder = this;

	objects->insert( 0 );
	return this;
}


void tvFolder::write( opstream& os )
{
	tvObject::write( os );

	os << (int)0x0100;

	objects->remove( 0 );
	os << objects;
	objects->insert( 0 );
}
