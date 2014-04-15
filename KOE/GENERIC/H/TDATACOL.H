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
**  TDataCollection Class                                                   **
**  ---------------------                                                   **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TDataCollection                                               **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TDATACOL.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TDATACOL
#define TDATACOL

#define Uses_TCollection
#include <TV.H>


class TDataCollection : public TCollection
{
public:
	TDataCollection( ushort aDataSize, ccIndex aLimit, ccIndex aDelta );

protected:
	ushort dataSize;

	virtual void freeItem( void *item );


protected:
	TDataCollection( StreamableInit );

public:
	static const char * const near name;
	static TStreamable *build();

protected:
	virtual void *read( ipstream& is );
	virtual void write( opstream& os );

	virtual void writeItem( void *item, opstream& );
	virtual void *readItem( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


inline ipstream& operator >> ( ipstream& is, TDataCollection& cl )
	{ return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TDataCollection*& cl )
	{ return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TDataCollection& cl )
	{ return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TDataCollection* cl )
	{ return os << (TStreamable *)cl; }


#endif