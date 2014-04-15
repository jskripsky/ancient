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
**  Notification-Control Classes                                            **
**  ----------------------------                                            **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TNInputLine                                                   **
**    - Class TNRadioButtons                                                **
**                                                                          **
**                                                                          **
**  Module Name: TNOTCTRL.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TEvent
#define Uses_TGroup
#define Uses_TKeys
#include "TNotCtrl.H"


void TNInputLine::handleEvent( TEvent& event )
{
	if( event.what == evKeyDown )
		{
		TInputLine::handleEvent( event );
		if( event.what == evNothing )
			{
			TEvent noteEvent;
			noteEvent.what = evCommand;
			noteEvent.message.command = cmNotification;
			noteEvent.message.infoPtr = this;
			owner->putEvent( noteEvent );
			}
		}
	else
		TInputLine::handleEvent( event );
}


void TNRadioButtons::handleEvent( TEvent& event )
{
	if( event.what == evKeyDown )
		{
		TRadioButtons::handleEvent( event );
		if( event.what == evNothing )
			{
			TEvent noteEvent;
			noteEvent.what = evCommand;
			noteEvent.message.command = cmNotification;
			noteEvent.message.infoPtr = this;
			owner->putEvent( noteEvent );
			}
		}
	else
		TRadioButtons::handleEvent( event );
}


void TNRadioButtons::press( int item )
{
	TRadioButtons::press( item );
	TEvent noteEvent;
	noteEvent.what = evCommand;
	noteEvent.message.command = cmNotification;
	noteEvent.message.infoPtr = this;
	owner->putEvent( noteEvent );
}


void TNCheckBoxes::press( int item )
{
	TCheckBoxes::press( item );
	TEvent noteEvent;
	noteEvent.what = evCommand;
	noteEvent.message.command = cmNotification;
	noteEvent.message.infoPtr = this;
	owner->putEvent( noteEvent );
}

void TNListBox::handleEvent( TEvent& event )
{
	if( event.what == evKeyDown )
		{
		switch( event.keyDown.keyCode )
			{
			case kbLeft:
				event.keyDown.keyCode = kbUp;
				break;

			case kbRight:
				event.keyDown.keyCode = kbDown;
				break;
			}
		}

	TListBox::handleEvent( event );
}


ushort TNListBox::dataSize()
{
	return sizeof( short );
}


void TNListBox::getData( void *rec )
{
	*(short *)rec = focused;
}


void TNListBox::setData( void *rec )
{
	settingData = True;
	focusItem( *(short *)rec );
	settingData = False;
}


void TNListBox::focusItemNum( short item )
{
	TListBox::focusItemNum( item );

	if( !settingData )
		{
		TEvent noteEvent;
		noteEvent.what = evCommand;
		noteEvent.message.command = cmNotification;
		noteEvent.message.infoPtr = this;
		// owner->putEvent( noteEvent );
		owner->handleEvent( noteEvent );
		}
}

