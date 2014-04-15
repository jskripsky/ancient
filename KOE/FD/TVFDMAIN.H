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
**  tvFDMainFolder                                                          **
**  --------------                                                          **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvFDMainFolder												**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFDMAIN.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVFDMAINFL
#define TVFDMAINFL

#include "tvMainFl.H"


class tvFDMainFolder : public tvMainFolder
{
public:
	tvFDMainFolder() :
		tvMainFolder( "Form Designer", False )
		{}

	virtual void insertObject( tvObject * );

protected:
	tvFDMainFolder( StreamableInit );

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


#endif
