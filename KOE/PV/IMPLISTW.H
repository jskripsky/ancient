/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Import List Window Include File		    */
/*												*/
/*----------------------------------------------*/

#ifndef IMPLISTWIN
#define IMPLISTWIN


#include "ListWin.H"

const int	OldFormat	= 1,
			Normal		= 2;


class TImportListWindow : public TListWindow
{
public:
	TImportListWindow( int aOptions );

	virtual void setState( ushort aState, Boolean enable );

private:
	virtual void openForm( Boolean newPerson = False );

	int options;
};


#endif