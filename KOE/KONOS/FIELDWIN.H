#ifndef FIELDWIN
#define FIELDWIN


#include "FldPres.H"
#include "Window.H"


class FieldWindow : public FieldPresentation, public Window
{
public:
	//=== constructors and destructor =====
	FieldWindow( Field *, zWindow *parent );
	virtual ~FieldWindow();

	void incLockCount();
	void decLockCount();

protected:
	long lockCount;


	virtual void update() = 0;
	// Called by owner (Field), whenever its data changes.

	virtual boolean validate() = 0;
	// Check for "visual errors" (e.g. Date "1=1=1995" instead of "1.1.1995").

	virtual void lock();
	virtual void unlock();

	virtual void showErrorMessage( const char *error );


protected:
	//=== form design / metadata =====
	long pageNumber;
	char *label;

protected:
	//=== storage (PersistentObject) =====
	virtual void write( StorageUnit& );
	virtual void read( StorageUnit& );
};


#endif