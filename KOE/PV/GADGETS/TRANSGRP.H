/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		TransGroup Include File		    		*/
/*												*/
/*----------------------------------------------*/

#ifndef TRANSGRP
#define TRANSGRP


class TTransGroup : public TGroup
{
public:
	TTransGroup( TRect& bounds );

	void selectFirst();

	virtual void handleEvent( TEvent& );
};


#endif