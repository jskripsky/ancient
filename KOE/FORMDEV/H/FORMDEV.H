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
**  FormDevice Class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Declared classes:                                                       **
**    - Class FormDevice  											        **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: FORMDEV.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef FORMDEV
#define FORMDEV

#include "StrDev.H"

class FormObj;
class TNSCollection;

class FormDevice : public virtual StreamDevice
{
public:
	FormDevice();
	virtual ~FormDevice();

	void openBlock( const char *title );
	void closeBlock();

    void standardBlockClosing();

	void newLine();

	virtual void writeByte( unsigned char );
	virtual void writeNumber( int );

	virtual void enableZeroConversion();
	virtual void disableZeroConversion();

	virtual void writeComment( const char * );

	void registerCustomBlockClosing(
		void (*blockClosing)(FormDevice *formDev) );

	void addCustomBlock( FormObj * );
	void writeCustomBlocks();

protected:

	Boolean convertZero;

	char *lastTitle;
	TNSCollection *customBlocks;

	void (*customBlockClosing)(FormDevice *);
};


inline void FormDevice::enableZeroConversion()
	{ convertZero = True; }

inline void FormDevice::disableZeroConversion()
	{ convertZero = False; }


#endif
