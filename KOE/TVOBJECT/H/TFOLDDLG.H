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
**  TFolderDlg Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TFolderDlg                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TFOLDDLG.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TFOLDDLG
#define TFOLDDLG

#include "TObjDlg.H"


#define cmInsert    110
#define cmEdit		111
#define cmMove 		112
#define cmDelete	113


class TListBox;
class TScrollBar;

class TFolderDlg : public TObjDlg
{
public:
	TFolderDlg( const TRect& bounds, tvObject *anOwner );

	TListBox *listBox;

	virtual void setState( ushort aState, Boolean enable );

protected:
	virtual void handleEvent( TEvent& event );

	TButtonBar *actionBar;
	virtual TButtonBar *createActionBar();
	virtual void setupActionBar();
	virtual void addNewButton();
	virtual void addEditButton();
	virtual void addMoveButton();
	virtual void addDeleteButton();

	virtual void setupDialog();

	virtual TListBox *createListBox( TScrollBar * );
	virtual TScrollBar *createScrollBar();

	virtual void setupButtons();
};


#endif
