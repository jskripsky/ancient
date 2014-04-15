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
**  TUnique Class                                                           **
**  ------------                                                            **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TUnique                                                       **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TUNIQUE.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TUNIQUE
#define TUNIQUE

#define Uses_TObject
#define Uses_TStreamable
#define Uses_TNSCollection
#include <TV.H>


class TUnique : public TObject, public TStreamable
{
public:
	TUnique();
	virtual ~TUnique();

	int getHandle();
	void deleteHandle();

private:
	int handle;


public:
	static TUnique *getObject( int handle );

private:
	static TNSCollection *uniqueObjects;


protected:
	TUnique( StreamableInit );

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );
};


inline int TUnique::getHandle()
	{ return handle; }


#endif