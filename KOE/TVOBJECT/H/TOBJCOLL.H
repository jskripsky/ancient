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
**  TObjCollection Classes                                                  **
**  ------------------------                                                **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TObjCollection                                                **
**    - Class TObjSortedCollection                                          **
**                                                                          **
**                                                                          **
**  Module Name: TOBJCOLL.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TOBJCOLL
#define TOBJCOLL

#define Uses_TSortedCollection
#include <TV.H>


class TObjCollection : public TSortedCollection
{
public:
	TObjCollection( ccIndex aLimit, ccIndex aDelta );

	Boolean sorted;

	virtual ccIndex insert( void *item );
	virtual ccIndex indexOf( void *item );

protected:
	virtual int compare( void *key1, void *key2 );

	virtual void freeItem( void *item );


protected:
	TObjCollection( StreamableInit );

public:
	static const char * const near name;
	static TStreamable *build();

protected:
	virtual void write( opstream& os );
	virtual void *read( ipstream& is );

	virtual void writeItem( void *item, opstream& );
	virtual void *readItem( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


inline ipstream& operator >> ( ipstream& is, TObjCollection& cl )
	{ return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TObjCollection*& cl )
	{ return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TObjCollection& cl )
	{ return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TObjCollection* cl )
	{ return os << (TStreamable *)cl; }


#endif
