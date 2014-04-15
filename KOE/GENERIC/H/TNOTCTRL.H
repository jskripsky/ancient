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
**  Declared classes:                                                       **
**    - Class TNInputLine                                                   **
**    - Class TNRadioButtons                                                **
**                                                                          **
**                                                                          **
**  Module Name: TNOTCTRL.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TNOTCTRL
#define TNOTCTRL

#define Uses_TInputLine
#define Uses_TRadioButtons
#define Uses_TCheckBoxes
#define Uses_TListBox
#include <TV.H>


#define cmNotification	150

class TNInputLine : public TInputLine
{
public:
	TNInputLine( const TRect& bounds, int aMaxLen ) :
		TInputLine( bounds, aMaxLen )
		{}

protected:
	virtual void handleEvent( TEvent& event );
};


class TNRadioButtons : public TRadioButtons
{
public:
	TNRadioButtons( const TRect& bounds, TSItem *aStrings ) :
		TRadioButtons( bounds, aStrings )
		{}

protected:
	virtual void handleEvent( TEvent& event );
	virtual void press( int item );
};


class TNCheckBoxes : public TCheckBoxes
{
public:
	TNCheckBoxes( const TRect& bounds, TSItem *aStrings ) :
		TCheckBoxes( bounds, aStrings )
		{}

protected:
	virtual void press( int item );
};


class TNListBox : public TListBox
{
public:
	TNListBox( const TRect& bounds, ushort aNumCols,
			   TScrollBar *aScrollBar ) :
		TListBox( bounds, aNumCols, aScrollBar ),
		settingData( False )
		{}

	virtual void handleEvent( TEvent& event );

	virtual ushort dataSize();
	virtual void getData( void *rec );
	virtual void setData( void *rec );

protected:
	virtual void focusItemNum( short item );

private:
	Boolean settingData;
};


#endif
