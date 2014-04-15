#include "Form.H"
#include "FieldPrn.H"
#include "zApp.HPP"

#include <String.H>
#include <FStream.H>

declSlist( FieldPrint );


void Form::print()
{
	ofstream *printer =
		new ofstream( "Person.Prn", ios::out | ios::trunc );

	printer->write( "@BS", 3 );
	
	FieldPrintSlistIter iter( fieldPrints );

	FieldPrint *fp;

	while( (fp = iter()) != 0 )
		{
		char *string = fp->copyPrintString();
		if( string )
			{
			printer->write( string, strlen( string ) );
			delete[] string;
			}
		}
	delete printer;
}
