#include "Compiler.H"

#include "Module.H"

#include "Board.H"


TModule::TModule( TBoard *b ) :
	fBoard( b )
{
	fBoard->AdoptModule( this );
}
