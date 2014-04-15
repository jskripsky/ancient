#include "Compiler.H"

#include "InOutMod.H"

#include "Board.H"


int TInputModule::GetData()
{
	return fBoard->GetData( *this );
}


TOutputModule::TOutputModule( TBoard *b ) :
	TModule( b ),
	fData( 0 )
{ }


void TOutputModule::SetData( int b )
{
	fBoard->SetData( *this, b );
	fData = b;
}


int TOutputModule::GetData()
{
	return fData;
}
