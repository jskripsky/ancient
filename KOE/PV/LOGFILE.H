/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		LogFile Include File    				*/
/*												*/
/*----------------------------------------------*/

#ifndef LOGFILE
#define LOGFILE


class ofstream;

class LogFile
{
public:
	LogFile( const char *fileName );
	~LogFile();

	void writeDate();
	void writeTime();
	void write( const char * );
	void writeByte( char byte );

protected:
	ofstream *file;
};


#endif