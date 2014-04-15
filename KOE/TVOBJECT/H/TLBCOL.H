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
**  TLBCollection Class                                                     **
**  -------------------                                                     **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TLBCollection                                                 **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TLBCOL.H                                                   **
**                                                                          **
*****************************************************************************/

#ifndef TLBCOL
#define TLBCOL

#define Uses_TCollection
#include <TV.H>


class TLBCollection : public TCollection
{
public:
	TLBCollection( ccIndex aLimit, ccIndex aDelta) :
		TCollection( aLimit, aDelta )
		{ shouldDelete = False; }

	void *readItem( ipstream& )
		{ return 0; }

	void writeItem( void * ,opstream& )
		{}
};

#endif