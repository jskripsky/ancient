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
**  TCard Class                                                             **
**  -----------                                                             **
**                                                                          **
**  Declared classes:                                                       **
**    - Class TCard                                                         **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TCARD.H                                                    **
**                                                                          **
*****************************************************************************/

#ifndef TCARD
#define TCARD

#define Uses_TCollection
#include <TV.H>


enum Format { Alpha, Numeric, TTMMJJJJ, MMJJ };

struct CardField
{
	CardField( int aTag, int aLength, const char *aDescription,
			   Format aFormat = Alpha );

	CardField();

	char description[41];
	int tag;
	int length;
	Format format;
};


class TCard : public TCollection
{
public:
	TCard();

protected:

	virtual void freeItem( void *item );


protected:
	TCard( StreamableInit );

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


inline ipstream& operator >> ( ipstream& is, TCard& cl )
	{ return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TCard*& cl )
	{ return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TCard& cl )
	{ return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TCard* cl )
	{ return os << (TStreamable *)cl; }


inline CardField::CardField()
	{}


#endif