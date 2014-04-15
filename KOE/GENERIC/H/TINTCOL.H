/*****************************************************************************
**                                                                          **
**                                                                          **
**  Form Designer                                                           **
**  =============                                                           **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  TIntCollection Class                                                    **
**  --------------------                                                    **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TIntCollection                                                **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TINTCOL.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TINTCOL
#define TINTCOL

#define Uses_TCollection
#include <TV.H>


class TIntCollection : public TCollection
{
public:
	TIntCollection( ccIndex aLimit, ccIndex aDelta );

protected:
	TIntCollection( StreamableInit );

public:
	static const char * const near name;
	static TStreamable *build();

protected:
	virtual void writeItem( void *item, opstream& );
	virtual void *readItem( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


inline ipstream& operator >> ( ipstream& is, TIntCollection& cl )
	{ return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TIntCollection*& cl )
	{ return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TIntCollection& cl )
	{ return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TIntCollection* cl )
	{ return os << (TStreamable *)cl; }


#endif