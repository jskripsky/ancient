#include "Form.H"
#include "FormWin.H"
#include "Storage.H"
#include "Field.H"
#include "FieldPrn.H"
#include "zApp.HPP"

#include <String.H>

declSlist( Field );
declSlist( FieldPrint );

//==========================================================
//===  constructors and destructor  ========================
//==========================================================

Form::Form() :
	fields( new FieldSlist() ),
	fieldPrints( new FieldPrintSlist() )
{
}


Form::~Form()
{
	// JS: delete all field objects.
   delete fieldPrints;
	delete fields;
}


const char *Form::getClassName()
{
	return "Form";
}


void Form::attachField( Field *f )
{
	fields->append( f );
   getFormWindow()->attachField( f );
}


Field *Form::getFieldByID( char *ID )
{
	FieldSlistIter *iter = getFieldsIterator();
	Field *f;

	while( ((f = (*iter)()) != 0) && strcmp( f->getID(), ID ) );
	delete iter;

	return f;
}


void Form::attachFieldPrint( FieldPrint *fp )
{
	fieldPrints->append( fp );
}


void Form::newPerson()
{
	FieldSlistIter *iter = getFieldsIterator();
	Field *f;

	while( ((f = (*iter)()) != 0) )
   	f->setToDefault();
	delete iter;
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
