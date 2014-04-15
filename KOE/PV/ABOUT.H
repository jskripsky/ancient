/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		About Dialog Include File		    	*/
/*												*/
/*----------------------------------------------*/

#ifndef ABOUT
#define ABOUT


class TAboutDialog : private TDialog
{
public:
	TAboutDialog();

	virtual void handleEvent( TEvent& );

private:
	TStaticText *status;
};


#endif