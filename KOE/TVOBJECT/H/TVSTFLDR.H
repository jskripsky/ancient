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
**  tvStaticTitleFolder Class                                               **
**  -------------------------                                               **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvStaticTitleFolder                                           **
**    - Class TSTFolderDlg                                                  **
**                                                                          **
**                                                                          **
**  Module Name: TVSTFLDR.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVSTFLDR
#define TVSTFLDR

#include "tvFolder.H"
#include "TFoldDlg.H"


class tvStaticTitleFolder : public tvFolder
{
public:
	tvStaticTitleFolder( tvFolder *aFolder, const char *aTitle,
						 Boolean sorted = False ) :
		tvFolder( aFolder, aTitle, sorted )
		{}

protected:
	virtual TObjDlg *createDlg();


protected:
	tvStaticTitleFolder( StreamableInit );

public:
	static const char * const near name;
	static TStreamable *build();

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


class TSTFolderDlg : public TFolderDlg
{
public:
	TSTFolderDlg( const TRect& bounds, tvObject *anOwner ) :
		TWindowInit( &TSTFolderDlg::initFrame ),
		TFolderDlg( bounds, anOwner )
		{}

protected:
	virtual TListBox *createListBox( TScrollBar * );
	virtual TScrollBar *createScrollBar();

	virtual void addTitleLine( int y );
};


#endif
