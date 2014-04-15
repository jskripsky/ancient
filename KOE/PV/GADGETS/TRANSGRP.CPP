/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		TransGroup Source File 		    		*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Gadgets\TransGrp.Use"

#define Uses_TEvent
#define Uses_TKeys

#include <TV.H>
#include "Gadgets\TransGrp.H"


/*---- Constructors, Destructors ---------------*/

TTransGroup::TTransGroup( TRect& bounds ) :
	TGroup( bounds )
{
	options |= ofFirstClick;
}


/*---- Public Methods --------------------------*/

void TTransGroup::selectFirst()
{
	last->select();
	selectNext( False );
}


void TTransGroup::handleEvent( TEvent& event )
{
	static Boolean broadcasting = False;

	if( event.what == evKeyDown )
		switch( event.keyDown.keyCode )
			{
			case kbTab:
				selectNext( False );
				clearEvent( event );
				return;

			case kbShiftTab:
				selectNext( True );
				clearEvent( event );
				return;

			case kbF6:
				owner->selectNext( False );
				clearEvent( event );
				return;

			case kbShiftF6:
				owner->selectNext( True );
				clearEvent( event );
				return;

			case kbCtrlHome:
			case kbF10:
				selectFirst();
				clearEvent( event );
				return;
			}
	TGroup::handleEvent( event );
	if( event.what == evKeyDown && !broadcasting )
		{
		broadcasting = True;
		TView *term = owner->last;
		TView *temp = owner->last;

		TView *next = temp->next;
		do
			{
			temp = next;
			next = temp->next;
			if( temp != this )
				temp->handleEvent( event );
			}
		while( temp != term );
		broadcasting = False;
		}
}
