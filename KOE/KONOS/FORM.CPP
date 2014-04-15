#include "Form.H"
#include "Storage.H"

//==========================================================
//===  constructors and destructor  ========================
//==========================================================

Form::Form()
{
}


Form::~Form()
{
	//delete all fields
}


const char *Form::getClassName()
{
	return "Form";
}


void Form::insert( Field *f )
{
	fields.insert( f );
}


//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================

void Form::write( StorageUnit& su )
{
	su;
//	su << *(Container<PersistentObject *> *)fields;
//	fields.writeToStorage( su );
}


void Form::read( StorageUnit& su )
{
	su;
//	su >> *(Container<PersistentObject *> *)fields;
//	fields.readFromStorage( su );
}
