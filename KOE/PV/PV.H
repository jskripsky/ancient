/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		PV Include File    						*/
/*												*/
/*----------------------------------------------*/


#include "About.H"
#include "ListWin.H"
#include "Gadgets\Gadgets.H"

#include <Time.H>

class THelpFile;
class THelpWindow;


class TPV : public TApplication
{
public:
	TPV();
	~TPV();

	virtual void handleEvent( TEvent& );
	virtual void getEvent( TEvent &event );

	virtual void idle();
	virtual TPalette& getPalette() const;
	virtual void outOfMemory();

	void createHeapView();
	void createClockView();

private:
	static TStatusLine *initStatusLine( TRect );
	static TMenuBar *initMenuBar( TRect rect );

	void readConfig();
	void writeConfig();
	void loadHelp();
	void destroyHelp();

	THelpFile *hlpFile;
	THelpWindow *hlpWindow;

	TAboutDialog *aboutDlg;
	TListWindow *listWindow;

	THeapView *heap;
	TClockView *clock;

	time_t startTimer;
};
