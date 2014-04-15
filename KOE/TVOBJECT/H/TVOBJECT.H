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
**  tvObject Class                                                          **
**  --------------                                                          **
**                                                                          **
**  Declared classes:                                                       **
**    - Class tvObject                                                      **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVOBJECT.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TVOBJECT
#define TVOBJECT

#include "TUnique.H"


#define maxTitleLength	40

#define oaDeletable		0x0001

enum Priority { Low, Normal, High };

class tvFolder;
class tvDocument;
class TObjDlg;
class TDataCollection;
class TNSCollection;
class TObjListBox;

class tvObject : public TUnique
{
public:
	// Basic tvObject Protocol
	// -----------------------

	tvObject( tvFolder *aFolder, const char *aTitle );
	virtual ~tvObject();

	virtual void tvOpen();
	virtual Boolean tvClose();
	virtual void tvDelete();

	// Dialog Protocol
	// ---------------

	virtual Boolean handleNotification( TView * );

	virtual void fillDlg();
	virtual void undoDlg();

	// Folder Protocol
	// ---------------

	int setAttribute( int mask, Boolean state = True );
	int getAttributes();

	virtual char *getTitle();

	virtual Priority getPriority();
	virtual int compareWith( tvObject& );

	tvFolder *folder;

	// Shadow Source Protocol
	// ----------------------

	void insertShadowInto( tvObject& dest );
	void removeShadowFrom( tvObject& dest );

	// Document Protocol
	// -----------------

	virtual tvDocument *getDocument();

protected:
	// Dialog Protocol
	// ---------------

	virtual TObjDlg *createDlg();
	virtual ushort getHelpCtx();

	TObjDlg *dlg;

	// Shadow Destination Protocol
	// ---------------------------

	void registerShadowHandle( int *handle );
	void deRegisterShadowHandle( int *handle );

	virtual void invalidateShadow( tvObject *shadow );

protected:
	char title[maxTitleLength + 1];
	int attribute;

	// Dialog Protocol
	// ---------------

	Boolean open;
	void *undoData;

	// Shadow Source Protocol
	// ----------------------

	Boolean hasShadows;
	TDataCollection *shadowOwners;

	// Shadow Destination Protocol
	// ---------------------------

	Boolean ownsShadows;
	TNSCollection *shadows;
	int *oldShadows;


// TStreamable Protocol
// --------------------

protected:
	tvObject( StreamableInit );

public: // protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );
};


inline char *tvObject::getTitle()
	{ return title; }

inline int tvObject::getAttributes()
	{ return attribute; }

inline Priority tvObject::getPriority()
	{ return Normal; }

inline ushort tvObject::getHelpCtx()
	{ return 0; }


inline ipstream& operator >> ( ipstream& is, tvObject& cl )
	{ return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, tvObject*& cl )
	{ return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, tvObject& cl )
	{ return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, tvObject* cl )
	{ return os << (TStreamable *)cl; }

#endif
