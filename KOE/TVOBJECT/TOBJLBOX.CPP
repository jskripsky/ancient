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
**  TObjListBox Class                                                       **
**  -----------------                                                       **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TObjListBox                                                   **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TOBJLBOX.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TCollection
#define Uses_TEvent
#define Uses_TGroup
#include "TObjLBox.H"
#include "tvObject.H"
#include "TFoldDlg.H"

#include <String.H>


TObjListBox::TObjListBox( const TRect& bounds, TScrollBar *aScrollBar ) :
	TNListBox( bounds, 1, aScrollBar )
{
}


ushort TObjListBox::dataSize()
{
	return sizeof( int );
}


void TObjListBox::getData( void *rec )
{
	tvObject *obj = (tvObject *)list()->at( focused );
	if( obj )
		*(int *)rec = obj->getHandle();
	else
		*(int *)rec = 0;
}


void TObjListBox::setData( void *rec )
{
	tvObject *obj;

	if( *(int *)rec )
		obj = (tvObject *)tvObject::getObject( *(int *)rec );
	else
		obj = 0;

	focusItem( list()->indexOf( obj ) );
}


void TObjListBox::getText( char *dest, short item, short maxLen )
{
	if( list()->at( item ) == 0 )
		strcpy( dest, "." );
	else
		{
		strncpy( dest, ((tvObject *)list()->at( item ))->getTitle(),
				 maxLen );
		dest[maxLen - 1] = EOS;
		}
}


void TObjListBox::handleEvent( TEvent& event )
{
	if( (event.what & evMouse) && event.mouse.doubleClick )
		{
		message( owner, evCommand, cmEdit, 0 );
		clearEvent( event );
		return;
		}
	TNListBox::handleEvent( event );
}
