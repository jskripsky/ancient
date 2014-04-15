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
**  Declared classes:                                                       **
**    - Class TObjListBox                                                   **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TOBJLBOX.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TOBJLBOX
#define TOBJLBOX

#include "TNotCtrl.H"


class TObjListBox : public TNListBox
{
public:
	TObjListBox( const TRect& bounds, TScrollBar *aScrollBar );

	virtual ushort dataSize();

	virtual void getData( void *rec );
	virtual void setData( void *rec );

protected:
	virtual void getText( char *dest, short item, short maxLen );
	virtual void handleEvent( TEvent& event );
};


#endif
