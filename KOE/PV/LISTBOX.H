/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		List Box Include File		    		*/
/*												*/
/*----------------------------------------------*/

#ifndef LISTBOX
#define LISTBOX


#include "DataBase\DataBase.H"
#include "Person\Info.H"

class TPerson;


class TAlphaListBox : public TSortedListBox
{
public:
	TAlphaListBox( const TRect& bounds, TScrollBar *aScrollBar );

	~TAlphaListBox();

	void writeListFile();

	TDataBase *list();
	virtual void getText( char *, short item, short maxLen );

	TInfo *focusedPerson();
	void insert( TInfo * );
	void free();

	void select();
	void update();
};


inline TDataBase *TAlphaListBox::list()
	{ return (TDataBase *)TSortedListBox::list(); }

inline void TAlphaListBox::select()
	{ TSortedListBox::select(); }


#endif