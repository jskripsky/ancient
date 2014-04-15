/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		ListFile Include File    				*/
/*												*/
/*----------------------------------------------*/

#ifndef LISTFILE
#define LISTFILE


#define ScreenStringLength 40

class ifstream;

class ListFile
{
public:
	ListFile( const char *fileName, int aStringLength );
	~ListFile();

	void getNextItem( char *screen, char *printer );
	int endOfList()
		{ return endOfFile; }

protected:
	int stringLength;
	ifstream *file;

	int endOfFile;
};


#endif