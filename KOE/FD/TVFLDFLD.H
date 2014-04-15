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
**  tvFieldsFolder Class                                                    **
**  --------------------                                                    **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvFieldsFolder                                                **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFLDFLD.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVFLDFLD
#define TVFLDFLD

#include "tvStFldr.H"
#include "FormObj.H"


class TrackTable;

class tvFieldsFolder : public tvStaticTitleFolder, public FormObj
{
public:
	tvFieldsFolder( tvFolder *aFolder );
	virtual ~tvFieldsFolder();

	virtual void insertObject( tvObject * );
	virtual void deleteObject();

	virtual Priority getPriority();

    TrackTable *getTrackTable();

protected:
	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();

	TrackTable *trackTable;


public:
	virtual void write( FormDevice * );
	static void blockClosing( FormDevice * );
	int getFieldsLengthSum();


protected:
	tvFieldsFolder( StreamableInit );

public:
	static const char * const near name;
	static TStreamable *build();

protected:
	virtual void *read( ipstream& );
	virtual void write( opstream& os );

private:
	virtual const char *streamableName() const
		{ return name; }
};


inline Priority tvFieldsFolder::getPriority()
	{ return High; }

inline TrackTable *tvFieldsFolder::getTrackTable()
	{ return trackTable; }


#endif
