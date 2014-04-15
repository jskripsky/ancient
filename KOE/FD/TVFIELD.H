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
**  tvField Class                                                           **
**  -------------                                                           **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvField                                                       **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFIELD.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef TVFIELD
#define TVFIELD

#include "Pos.H"
#include "tvObject.H"
#include "FormObj.H"


enum Restriction { None, Magnetic, Display };
enum PrintMode { Blockung, Felder };


class tvField : public tvObject, public FormObj
{
public:
	tvField( tvFolder *aFolder );

	virtual Boolean handleNotification( TView * );

	virtual void fillDlg();

protected:
	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();


public:
	int getRealLength();

	Boolean isDumpable();
	Boolean isAutoPos();
	Restriction getRestriction();

	Pos pos;

protected:
	int length;
	int offset;

	Boolean dumpable;

	Boolean autoPos;
	Restriction restriction;


public:
	int getLength();
	int getIndex();

	virtual void write( FormDevice * );


	static PrintMode printMode;


protected:
	tvField( StreamableInit );

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


inline int tvField::getRealLength()
	{ return length - offset; }

inline Boolean tvField::isDumpable()
	{ return dumpable; }

inline Boolean tvField::isAutoPos()
	{ return autoPos; }

inline Restriction tvField::getRestriction()
	{ return restriction; }

inline int tvField::getLength()
	{ return length; }


#endif