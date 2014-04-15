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
**  TStdDlg Class                                                           **
**  -------------                                                           **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TStdDlg                                                       **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TSTDDLG.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TSTDDLG
#define TSTDDLG

#include "TDlg.H"


class TButtonBar;

class TStdDlg : public TDlg
{
public:
	TStdDlg( const TRect& bounds, const char *aTitle = 0 );
	virtual ~TStdDlg();

	void setup();

	virtual void setState( ushort aState, Boolean enable );

	virtual void handleNotification( TView * );

protected:
	virtual void handleEvent( TEvent& event );

	virtual void undo();
	virtual void close();

	virtual void setupDialog();
	void addLine( int y );

	TButtonBar *buttonBar;
	virtual TButtonBar *createButtonBar();
	virtual void setupButtons();

	virtual void addCloseButton( Boolean longForm = True );
	virtual void addUndoButton( Boolean longForm = True );
};


inline void TStdDlg::handleNotification( TView * )
	{}


inline void TStdDlg::undo()
	{}


inline void TStdDlg::close()
	{ TDlg::close(); }



#endif
