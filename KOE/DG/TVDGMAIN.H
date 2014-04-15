/*****************************************************************************
**                                                                          **
**                                                                          **
**  DOS Dialog Generator                                                    **
**  ====================                                                    **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  tvDGMainFolder                                                          **
**  --------------                                                          **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvDGMainFolder												**
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVDGMAIN.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVDGMAINFL
#define TVDGMAINFL

#include "tvMainFl.H"

class TCard;
class TLBCollection;


class tvDGMainFolder : public tvMainFolder
{
public:
	tvDGMainFolder();

	virtual void insertObject( tvObject * );

	tvFolder *getSystemsFolder();

	TCard *getCard();
	TLBCollection *getCharacters();

protected:
	int systemsFolder;

	TCard *card;
	TLBCollection *characters;

	void loadCard();
	void loadCharacters();


protected:
	tvDGMainFolder( StreamableInit );

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


inline TCard *tvDGMainFolder::getCard()
	{ return card; }

inline TLBCollection *tvDGMainFolder::getCharacters()
	{ return characters; }


#endif
