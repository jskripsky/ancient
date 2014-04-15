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
**  TObjDlg Class                                                           **
**  -------------                                                           **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TObjDlg                                                       **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TOBJDLG.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TOBJDLG
#define TOBJDLG

#include "TStdDlg.H"


class TInputLine;
class tvObject;

class TObjDlg : public TStdDlg
{
public:
	TObjDlg( const TRect& bounds, tvObject *anOwner );

	TInputLine *titleLine;

	virtual void handleNotification( TView * );

protected:
	tvObject *owner;

	virtual void undo();
	virtual void close();

	virtual void setupDialog();
	virtual void addTitleLine( int y );
};


#endif
