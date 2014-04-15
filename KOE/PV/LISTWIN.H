/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		List Window Include File		    	*/
/*												*/
/*----------------------------------------------*/

#ifndef LISTWIN
#define LISTWIN


#include "ListBox.H"
#include "FormDlg.H"

class TInfo;


class TListWindow : public TDialog
{
public:
	TListWindow( const char *title );
	virtual ~TListWindow();

	virtual void setState( ushort aState, Boolean enable );
	virtual void handleEvent( TEvent& );

protected:
	TAlphaListBox *box;
	TScrollBar *scrollBar;

	virtual void openForm( Boolean newPerson = False );
	TFormDialog *formDialog;

	void print( ushort mode );

	void exportData( int mode );

private:
	void BogenhausenExport( TInfo * );
	void BogenhausenProtocol( TInfo * );
};


#endif