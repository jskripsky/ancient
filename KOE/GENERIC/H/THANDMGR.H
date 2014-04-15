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
**  THandleMgr Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Declared classes:                                                       **
**    - Class THandleMgr                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: THANDMGR.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef THANDMGR
#define THANDMGR

#define Uses_TStreamable
#include <TV.H>


class TIntCollection;

class THandleMgr : public TStreamable
{
public:
	THandleMgr();
	~THandleMgr();

	int createHandle();
	void deleteHandle( int );
	Boolean isHandleFree( int );

protected:
	int lastHandle;

	TIntCollection *freeHandles;

protected:
	THandleMgr( StreamableInit );

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


inline ipstream& operator >> ( ipstream& is, THandleMgr& cl )
	{ return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, THandleMgr*& cl )
	{ return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, THandleMgr& cl )
	{ return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, THandleMgr* cl )
	{ return os << (TStreamable *)cl; }


extern THandleMgr *handleMgr;


#endif