/*----------------------------------------------*/
/*                                  			*/
/*		FD_PV 1.0   				    		*/
/*		PV_FD Include File    					*/
/*												*/
/*----------------------------------------------*/


class TPV_FD : public TApplication
{
public:
	TPV_FD();
	~TPV_FD();

private:
	static TStatusLine *initStatusLine( TRect );
};
