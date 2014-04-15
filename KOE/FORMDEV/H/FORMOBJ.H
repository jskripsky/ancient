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
**  FormObj Class                                                           **
**  -------------                                                           **
**                                                                          **
**  Declared classes:                                                       **
**    - Class FormObj     											        **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: FORMOBJ.H                                                  **
**                                                                          **
*****************************************************************************/

#ifndef FORMOBJ
#define FORMOBJ

class FormDevice;

class FormObj
{
public:
	virtual void write( FormDevice *formDev ) = 0;
	virtual void writeCustomBlock( FormDevice *form )
		{}
};


#endif
