/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		LogPrinter Include File    				*/
/*												*/
/*----------------------------------------------*/

#ifndef LOGPRINT
#define LOGPRINT


class ofstream;

struct date;
struct time;

class TInfo;

class LogPrinter
{
public:
	LogPrinter( int aMode, date *aLogDate );
	~LogPrinter();

	void writeEntry( TInfo * );

	void writeDate( struct date * );
	void writeTime( struct time * );
	void write( const char *, int length = 0 );

	void startNewLine();
//	void startNewPage();

protected:
	ofstream *printer;
	date *logDate;
	int mode;

	int line;
};


#endif