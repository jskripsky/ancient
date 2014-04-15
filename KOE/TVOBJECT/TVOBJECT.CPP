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
**  tvObject Class                                                          **
**  --------------                                                          **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvObject                                                      **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVOBJECT.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TProgram
#define Uses_TDeskTop
#define Uses_TInputLine
#define Uses_TView
#include "tvObject.H"
#include "tvFolder.H"
#include "tvDoc.H"
#include "TObjDlg.H"
#include "TDataCol.H"

#include <String.H>


struct ShadowOwner
{
	int ownerHandle;
	int documentHandle;
};


// -----------------------
// Basic tvObject Protocol
// -----------------------

tvObject::tvObject( tvFolder *aFolder, const char *aTitle ) :
	folder( aFolder ),
	attribute( oaDeletable ),
	hasShadows( False ),
	ownsShadows( False ),
	open( False )
{
	if( aTitle )
		{
		strncpy( title, aTitle, maxTitleLength );
		title[maxTitleLength] = 0;
		}
	else
		title[0] = 0;
}


tvObject::~tvObject()
{
	if( hasShadows )
		destroy( shadowOwners );

	if( ownsShadows )
		delete shadows;
}


void tvObject::tvOpen()
{
	if( !open )
		{
		if( ownsShadows )
			{
			oldShadows = new int[shadows->getCount()];
			for( int i = 0; i < shadows->getCount(); i++ )
				oldShadows[i] = *(int *)shadows->at( i );
			}

		if( folder )
			folder->dlg->setState( sfDisabled, True );

		dlg = createDlg();
		dlg->helpCtx = getHelpCtx();
		dlg->setup();

		fillDlg();
		undoData = new char[dlg->dataSize()];
		dlg->getData( undoData );

		dlg->setTitle( title );
		TProgram::deskTop->insert( dlg );
		dlg->show();
		open = True;
		}
	else
		dlg->select();
}


Boolean tvObject::tvClose()
{
	if( open )
		{
		if( ownsShadows )
			{
			for( int i = 0; i < shadows->getCount(); i++ )
				if( *(int *)shadows->at( i ) != oldShadows[i] )
					{
					tvObject *shadowObj;
					if( oldShadows[i] != 0 )
						{
						shadowObj =
							(tvObject *)tvObject::getObject( oldShadows[i] );
						shadowObj->removeShadowFrom( *this );
						}

					if( *(int *)shadows->at( i ) != 0 )
						{
						shadowObj = (tvObject *)tvObject::getObject(
							*(int *)shadows->at( i ) );

						shadowObj->insertShadowInto( *this );
						}
					}

			delete[] oldShadows;
			}

		delete[] undoData;

		dlg->hide();
		TProgram::deskTop->remove( dlg );
		destroy( dlg );

		open = False;
		if( folder )
			{
			folder->update( this );
			folder->dlg->setState( sfDisabled, False );
			}

		return True;
		}
	else
		return False;
}


void tvObject::tvDelete()
{
	while( hasShadows )
		{
		ShadowOwner *so =
			(ShadowOwner *)shadowOwners->at( shadowOwners->getCount() - 1 );

		tvDocument *doc = 0;

		Boolean write = False;

		if( so->documentHandle )
			{
			doc = (tvDocument *)tvObject::getObject( so->documentHandle );
			if( !doc->isDocumentLoaded() )
				{
				doc->readFile();
				write = True;
				}
			}

		tvObject *owner = (tvObject *)tvObject::getObject( so->ownerHandle );
		removeShadowFrom( *owner );

		owner->invalidateShadow( this );

		if( doc && write )
			doc->writeFile();
		}

	if( ownsShadows )
		for( int i = 0; i < shadows->getCount(); i++ )
			{
			int handle = *(int *)shadows->at( i );
			if( handle )
				{
				tvObject *shadowObj =
					(tvObject *)tvObject::getObject( handle );
				shadowObj->removeShadowFrom( *this );
				}
			}

	deleteHandle();

	destroy( this );
}


// ---------------
// Dialog Protocol
// ---------------

Boolean tvObject::handleNotification( TView *view )
{
	if( view == dlg )
		{
		dlg->handleNotification( dlg );
		return True;
		}

	if( view == dlg->titleLine )
		{
		dlg->titleLine->getData( title );
		dlg->setTitle( title );
		return True;
		}

	return False;
}


void tvObject::fillDlg()
{
	if( dlg->titleLine )
		{
		dlg->titleLine->setData( title );
		handleNotification( dlg->titleLine );
		}
}


void tvObject::undoDlg()
{
	dlg->setData( undoData );
	handleNotification( dlg );
	dlg->drawView();
}


TObjDlg *tvObject::createDlg()
{
	return( new TObjDlg( TRect( 29, 1, 77, 22 ), this ) );
}



// ---------------
// Folder Protocol
// ---------------

int tvObject::setAttribute( int mask, Boolean state )
{
	if( state == True )
		attribute |= mask;
	else
		attribute &= ~mask;

	return attribute;
}


int tvObject::compareWith( tvObject& obj )
{
	return strcmp( title, obj.title );
}


// ----------------------
// Shadow Source Protocol
// ----------------------

void tvObject::insertShadowInto( tvObject& dest )
{
	if( !hasShadows )
		{
		hasShadows = True;
		shadowOwners = new TDataCollection( sizeof( ShadowOwner ), 1, 2 );
		}

	ShadowOwner *so = new ShadowOwner;
	so->ownerHandle = dest.getHandle();

	tvObject *doc = dest.getDocument();
	if( doc )
		so->documentHandle = doc->getHandle();
	else
		so->documentHandle = 0;

	shadowOwners->insert( so );
}


void tvObject::removeShadowFrom( tvObject& dest )
{
	ushort idx = 0;
	while( ((ShadowOwner *)shadowOwners->at( idx ))->ownerHandle !=
		   dest.getHandle() )
		idx++;

	shadowOwners->atFree( idx );

	if( shadowOwners->getCount() == 0 )
		{
		delete shadowOwners;
		hasShadows = False;
		}
}


// ---------------------------
// Shadow Destination Protocol
// ---------------------------

void tvObject::registerShadowHandle( int *handle )
{
	if( !ownsShadows )
		{
		ownsShadows = True;
		shadows = new TNSCollection( 1, 2 );
		}

	shadows->insert( handle );
}


void tvObject::deRegisterShadowHandle( int *handle )
{
	ushort idx = 0;
	while( (int *)shadows->at( idx ) != handle )
		idx++;

	shadows->atRemove( idx );

	if( shadows->getCount() == 0 )
		{
		delete shadows;
		ownsShadows = False;
		}
}


void tvObject::invalidateShadow( tvObject * )
{
}


// -----------------
// Document Protocol
// -----------------

tvDocument *tvObject::getDocument()
{
	return folder->getDocument();
}


// --------------------
// TStreamable Protocol
// --------------------

tvObject::tvObject( StreamableInit ) :
	TUnique( streamableInit ),
	ownsShadows( False ),
	open( False )
	{}


void tvObject::write( opstream& os )
{
	TUnique::write( os );

	os << (int)0x0114;

	os.writeString( title );
	os << attribute;

	os << (int)hasShadows;
	if( hasShadows )
		os << shadowOwners;
}


void *tvObject::read( ipstream& is )
{
	TUnique::read( is );

	int version;
	is >> version;

	is.readString( title, maxTitleLength + 1 );
	is >> attribute;

	is >> (int)hasShadows;
	if( hasShadows )
		is >> shadowOwners;

	return this;
}



/*

TIntCollection *shadowOwners;

void tvObject::write( opstream& os )
{
	os << (int)0x010A;

	TUnique::write( os );
	os.writeString( title );
	os << attribute;

	os << (int)hasShadows;
	if( hasShadows )
		os << shadowOwners;
}


void *tvObject::read( ipstream& is )
{
	int version;
	is >> version;

	TUnique::read( is );
	is.readString( title, maxTitleLength + 1 );
	is >> attribute;

	is >> (int)hasShadows;
	if( hasShadows )
		{
		is >> shadowOwners;
		if( version < 0x010A )
			{
			for( int i = 1; i < shadowOwners->getCount(); i += 2 )
				shadowOwners->atInsert( i, 0 );

			shadowOwners->insert( 0 );
			}
		}

	return this;
}
*/