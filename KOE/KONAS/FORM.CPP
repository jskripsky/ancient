#include "Form.H"
#include "Storage.H"
#include "Field.H"
#include "zApp.HPP"

#include <String.H>

declSlist(Field);

//==========================================================
//===  constructors and destructor  ========================
//==========================================================

Form::Form() :
        fields( new FieldSlist() )
{
        fields->append( (Field *)1 );
}


Form::~Form()
{
	// JS: delete all field objects.

        delete fields;
}


const char *Form::getClassName()
{
	return "Form";
}


void Form::attachField( Field *f )
{
//	fields->append( f );
}


Field *Form::getFieldByID( char *ID )
{
        FieldSlistIter *iter = getFieldsIterator();
        Field *f;
                 
        while( (f = (*iter)()) && strcmp( f->getID(), ID ) );
        delete iter;

        return f;
}


FieldSlistIter *Form::getFieldsIterator()
{
        return new FieldSlistIter( fields );
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
