#include "FieldWin.H"
#include "Field.H"
#include "Storage.H"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

FieldWindow::FieldWindow( Field *field, zWindow *parent ) :
	FieldPresentation( field ),
	Window( field, parent ),
	Presentation( field ),
	lockCount( 0 ),
	label( 0 ),
	pageNumber( 0 )
{
}


FieldWindow::~FieldWindow()
{
	if( label )
		delete[] label;
}


void FieldWindow::incLockCount()
{
	if( lockCount == 0 )
		lock();

	lockCount++;
}


void FieldWindow::decLockCount()
{
	if( lockCount > 0 )
		{
		lockCount--;

		if( lockCount == 0 )
			unlock();
		}
}


void FieldWindow::lock()
{
        //!!!!!!!!!!
}


void FieldWindow::unlock()
{
        //!!!!!!!!!!
}


void FieldWindow::showErrorMessage( const char *error )
{
        error;
        //!!!!!!!!!!
}


//==========================================================
//===  storage methods (PersistentObject)  =================
//==========================================================

void FieldWindow::write( StorageUnit& su )
{
	FieldPresentation::write( su );
	su << pageNumber;
}


void FieldWindow::read( StorageUnit& su )
{
	FieldPresentation::write( su );
	su >> pageNumber;
}
