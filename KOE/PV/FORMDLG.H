/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Form Dialog Include File		    	*/
/*												*/
/*----------------------------------------------*/

#ifndef FORMDLG
#define FORMDLG


#include "Form.H"
#include "Gadgets\TransGrp.H"
#include "Person\Person.H"


class TOutputDevice;
class TPoint;
class TEvent;

const ushort noPage			=	  99;


class TFormDialog : protected TDialog
{
public:
	TFormDialog();
	~TFormDialog();

	void loadPerson( TInfo *, Boolean aNewPerson = False );
	void print( TOutputDevice& );

	TPage *currentPage();
	void changeToPageNo( ushort, Boolean check = True );

	void adjustForm( TPoint );

	virtual void handleEvent( TEvent& );

protected:
	TInfo *originalInfo;

	TInfo *info;
	TPerson *person;

	TTransGroup *controls;

	TForm *form;
	ushort curPageNo;

	void setTitle( char * );

	Boolean newPerson;
};


inline TPage *TFormDialog::currentPage()
	{ return form->at( curPageNo ); }

inline void TFormDialog::adjustForm( TPoint distance )
	{ form->adjust( distance ); }


#endif