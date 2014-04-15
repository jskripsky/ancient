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
**  Defined classes:                                                        **
**    - Class TButtonBar                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TBTNBAR.CPP                                                **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TNSCollection
#define Uses_TGroup
#include "TBtnBar.H"


#define baXAlignments  (baLeft | baRight | baCentered | baJustified)


TButtonBar::TButtonBar( TGroup *anOwner, const TRect& aBounds,
						int align ) :
	owner( anOwner ),
	bounds( aBounds ),
	alignment( align ),
	buttons( new TNSCollection( 10, 2 ) )
{
	bounds.a.x--;
	if( alignment & baNoYSpace )
		nextButton.y = bounds.a.y - 1;
	else
		nextButton.y = bounds.a.y - 2;

	startNewLine();
}


TButtonBar::~TButtonBar()
{
	buttons->removeAll();
	delete buttons;
}


void TButtonBar::insert( TButton *b )
{
	TRect br;

	switch( alignment & baXAlignments )
		{
		case baLeft:
			b->moveTo( nextButton.x, nextButton.y );
			br = b->getBounds();
			if( br.b.x > bounds.b.x )
				{
				startNewLine();
				insert( b );
				return;
				}

			nextButton.x = br.b.x + 1;
			nextButton.y = br.a.y;
			break;

		case baRight:
			br = b->getExtent();
			nextButton.x -= br.b.x;
			if( nextButton.x + 1 < bounds.a.x )
				{
				startNewLine();
				insert( b );
				return;
				}

			shiftBack( nextButton.y, br.b.x + 1 );

			b->moveTo( bounds.b.x - br.b.x, nextButton.y );
			nextButton.x -= 1;
			break;
		}

	int count = buttons->getCount();
	if( count == 0 )
		owner->insert( b );
	else
		owner->insertBefore( b, (TButton *)buttons->at( count - 1 ) );

	buttons->insert( b );
}


void TButtonBar::disable( Boolean enable )
{
	for( int i = 0; i < buttons->getCount(); i++ )
		((TButton *)buttons->at( i ))->setState( sfDisabled, enable );
}


void TButtonBar::startNewLine()
{
	if( alignment & baNoYSpace )
		nextButton.y += 1;
	else
		nextButton.y += 2;

	switch( alignment & baXAlignments )
		{
		case baLeft:
		case baJustified:
			nextButton.x = bounds.a.x;
			break;

		case baRight:
			nextButton.x = bounds.b.x - 1;
			break;

		case baCentered:
			nextButton.x = (bounds.a.x + bounds.b.x) / 2;
			break;
		}
}


void TButtonBar::shiftBack( int y, int delta )
{
	TRect button;
	for( int i = 0; i < buttons->getCount(); i++ )
		{
		button = ((TButton *)buttons->at( i ))->getBounds();
		if( button.a.y == y )
			{
			button.a.x -= delta;
			((TButton *)buttons->at( i ))->moveTo( button.a.x, button.a.y );
            }
		}
}
