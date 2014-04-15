#include "FieldWin.H"
#include "Field.H"
#include "Storage.H"

#include "zApp.HPP"


//==========================================================
//===  constructors and destructor  ========================
//==========================================================

FieldWindow::FieldWindow( Field *field ) :
	Presentation( field ),
	Window( field ),
	FieldPresentation( field ),
	lockCount( 0 ),
	labelText( 0 ),
        label( 0 ),
	pageNumber( 0 )
{
}


FieldWindow::~FieldWindow()
{
	if( labelText )
		delete[] labelText;

        if( label )
                delete label;
}


void FieldWindow::createLabel()
{
        zWindow *parent = window->parent();
        //..............!!!!
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
        //!!!!!!!!!!!!!!!!!
}


void FieldWindow::unlock()
{
        //!!!!!!!!!!
}


void FieldWindow::showErrorMessage( const char *errorText )
{
        acquireUserFocus();

        zMessage *message = new zMessage( 0, errorText, "Fehler" );
        delete message;
}


void FieldWindow::adjustzWindowRect()
{
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
