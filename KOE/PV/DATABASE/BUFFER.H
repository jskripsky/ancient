/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database Buffer Include File		    */
/*												*/
/*----------------------------------------------*/

#ifndef DBBUFFER
#define DBBUFFER

#define Uses_TObject

#include <TV.H>


class TBuffer : public TObject
{
public:
	TBuffer( size_t aElementSize, int numElements );
	virtual ~TBuffer();

	virtual void *getArea();
	virtual void releaseArea( void * );

protected:
	size_t elementSize;
	int blockSize;

	struct Block
		{
		char *buffer;
		void **pointers;
		Boolean *map;
		} *block;
};


#endif