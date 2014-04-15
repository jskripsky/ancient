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
**  Defined classes:                                                        **
**    - Class SystemImport                                                  **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: SYSIMP.CPP                                                 **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TFileDialog
#define Uses_TProgram
#define Uses_TDeskTop
#define Uses_ifpstream
#include "SysImp.H"
#include "tvSystem.H"

#include <String.H>
#include <CType.H>


SystemImport::SystemImport( char *aID, Character *aCharacters ) :
	ID( aID ),
	characters( aCharacters ),
	textFile( 0 )
{
}


SystemImport::~SystemImport()
{
	if( textFile )
		{
		textFile->close();
		delete textFile;
		}
}


Boolean SystemImport::import()
{
	TFileDialog *fileDlg = new TFileDialog( "*.ALL", "System Import",
	"Name", fdOKButton, 0 );

	TProgram::deskTop->execView( fileDlg );

	char fileName[256];
	fileDlg->getFileName( fileName );

	textFile = new ifpstream( fileName, ios::nocreate );

	if( !findScanCodeBlock() )
		return False;


	for( int i1 = 0; i1 < 128; i1++ )
		{
		for( int i2 = 0; i2 < 4; i2++ )
			characters[i1].bytes[i2] = (uchar)getNextNumber();

		if( getNextNumber() != 0 )
			characters[i1].shift = True;
		else
			characters[i1].shift = False;
		}

	return True;
}


Boolean SystemImport::findScanCodeBlock()
{
	char *foundID = new char[strlen( ID ) + 1];
	foundID[strlen( ID )] = 0;

	do
		{
		char scanCode[10];
		scanCode[9] = 0;
		do
			{
			if( !findBlockStart() )
				{
				delete[] foundID;
				return False;
				}

			textFile->readBytes( scanCode, 9 );
			}
		while( strcmp( scanCode, "scancode_" ) );

		textFile->readBytes( foundID, strlen( ID ) );
		}
	while( strcmp( foundID, ID ) );

	delete[] foundID;
	return True;
}


Boolean SystemImport::findBlockStart()
{
	char blockPrefix;

	do
		{
		streampos pos = textFile->tellg();
		*textFile >> blockPrefix;
		if( textFile->tellg() == pos )
			return False;
		}
	while( !textFile->eof() && (blockPrefix != '#' ) );

	if( textFile->eof() )
		return False;

	return True;
}


int SystemImport::getNextNumber()
{
	char temp;

	do
		{
		*textFile >> temp;
		if( temp == '*' )
			{
			temp = 0;
			char preTemp;

			do
				{
				preTemp = temp;
				*textFile >> temp;
				}
			while( !((preTemp == '*') && (temp == '/')) );
			*textFile >> temp;
			}
		}
	while( !isalpha( temp ) && !isdigit( temp ) );

	char numString[10];
	int i = 0;

	do
		{
		numString[i] = temp;
		i++;
		*textFile >> temp;
		}
	while( isalpha( temp ) || isdigit( temp ) );

	numString[i] = 0;


	int number = 0;
	int posMultiplier = 1;

	for( int pos = strlen( numString ) - 1; pos >= 0; pos-- )
		{
		char c = numString[pos];
		if( isdigit( c ) )
			c -= '0';
		else
			if( isupper( c ) )
				c -= 'A' - 10;
			else
				c -= 'a' - 10;

		number += posMultiplier * c;
		posMultiplier *= 16;
		}

	return number;
}
