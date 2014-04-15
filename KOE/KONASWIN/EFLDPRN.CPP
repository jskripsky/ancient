#include "EFldPrn.H"
#include "EntryFld.H"

#include <String.H>

//==========================================================
//===  constructors and destructor  ========================
//==========================================================

EntryFieldPrint::EntryFieldPrint( Field *field ) :
	FieldPrint( field )
{
}


EntryFieldPrint::~EntryFieldPrint()
{
}

const char *EntryFieldPrint::getClassName()
{
	return "EntryFieldPrint";
}


char *EntryFieldPrint::copyPrintString()
{
	if( enabled )
		{
		EntryField *ef = (EntryField *)dataObject;

		char *string =
			new char[(int)ef->getMaxTextLength() + 1];

		strcpy( string, ef->getText() );
		for( int o = strlen( string ); o < ef->getMaxTextLength(); o++ )
			string[o] = ' ';

		string[o] = 0;

		return string;
		}
	else
		return 0;
}
