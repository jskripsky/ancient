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
**  tvMainFolder Class                                                      **
**  ------------------                                                      **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvMainFolder                                                  **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVMAINFL.CPP                                               **
**                                                                          **
*****************************************************************************/

#ifndef TVMAINFL
#define TVMAINFL

#include "tvSTFldr.H"


class tvMainFolder : public tvStaticTitleFolder
{
public:
	tvMainFolder( const char *aTitle, Boolean sorted = False );

	Boolean tvClose();

	// Document Protocol
	// -----------------

	virtual tvDocument *getDocument();

protected:
	virtual TObjDlg *createDlg();
    virtual ushort getHelpCtx();


protected:
	tvMainFolder( StreamableInit );

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

extern tvMainFolder *mainFolder;


inline ipstream& operator >> ( ipstream& is, tvMainFolder& cl )
	{ return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, tvMainFolder*& cl )
	{ return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, tvMainFolder& cl )
	{ return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, tvMainFolder* cl )
	{ return os << (TStreamable *)cl; }


#endif
