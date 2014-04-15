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
**  SystemImport                                                            **
**  ------------                                                            **
**                                                                          **
**  Declared classes:                                                       **
**    - Class SystemImport                                                  **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: SYSIMP.H                                                   **
**                                                                          **
*****************************************************************************/

#ifndef SYSIMP
#define SYSIMP

#include <TV.H>

class Character;
class ifpstream;


class SystemImport
{
public:
	SystemImport( char *aID, Character *aCharacters );
	~SystemImport();

	Boolean import();


protected:
	ifpstream *textFile;

	char *ID;
	Character *characters;

	Boolean findScanCodeBlock();
	Boolean findBlockStart();
	int getNextNumber();

};


#endif