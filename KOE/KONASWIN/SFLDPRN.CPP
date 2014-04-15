#include "SFldPrn.H"
#include "SelFld.H"

#include "zApp.HPP"
#include <String.H>

declSlist( Entry );


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

SelectionFieldPrint::SelectionFieldPrint( Field *field ) :
	FieldPrint( field ),
   list( new EntrySlist() )
{
}


SelectionFieldPrint::~SelectionFieldPrint()
{
}

const char *SelectionFieldPrint::getClassName()
{
	return "SelectionFieldPrint";
}


char *SelectionFieldPrint::copyPrintString()
{
	if( enabled )
		{
		SelectionField *sf = (SelectionField *)dataObject;
		long sel = sf->getSelection();

		EntrySlistIter iter( list );
		Entry *e;
		for( int c = 0; c <= sel; c++ )
			e = iter();

		char *str = new char[strlen( e->string )];
		strcpy( str, e->string );
		return str;
		}
	else
		return 0;
}
