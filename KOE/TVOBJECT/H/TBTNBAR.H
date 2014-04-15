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
**  TButtonBar Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TButtonBar                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TBTNBAR.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TBTNBAR
#define TBTNBAR

#define Uses_TObject
#define Uses_TButton
#define Uses_TRect
#include <TV.H>


#define baLeft			1
#define baRight			2
#define baCentered		4
#define baJustified		8
#define baNoYSpace		16
#define baNoXSpace		32


class TNSCollection;
class TButton;
class TGroup;
class TPoint;

class TButtonBar : public TObject
{
public:
	TButtonBar( TGroup *anOwner, const TRect& aBounds,
				int align = baRight );
	~TButtonBar();

	virtual void insert( TButton *b );
	virtual void disable( Boolean enable );

protected:
	TGroup *owner;
	TRect bounds;
	int alignment;

	TPoint nextButton;
	TNSCollection *buttons;

private:
	void startNewLine();
	void shiftBack( int y, int delta );
};


#endif
