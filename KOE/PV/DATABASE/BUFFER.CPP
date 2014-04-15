/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Database Buffer Source File 		    */
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#define Uses_TNSCollection

#include "Database\Buffer.H"

#include <StdLib.H>

/*---- Constructors, Destructors ---------------*/

TBuffer::TBuffer( size_t aElementSize, int numElements ) :
	elementSize( aElementSize ),
	blockSize( numElements )
{
	block = new Block;

	block->buffer = new char[blockSize * elementSize];
	block->pointers = new void *[blockSize];
	block->map = new Boolean[blockSize];

	for( int i = 0; i < blockSize; i++ )
		{
		block->pointers[i] = &block->buffer[i * elementSize];
		block->map[i] = False;
		}
}


TBuffer::~TBuffer()
{
	delete[] block->map;
	delete[] block->pointers;
	delete[] block->buffer;

	delete block;
}


/*---- Public Methods --------------------------*/

void *TBuffer::getArea()
{
	int i = 0;
	while( block->map[i] && (i < blockSize) )
		i++;

	if( i == blockSize )
		abort();

	block->map[i] = True;
	return block->pointers[i];
}


void TBuffer::releaseArea( void *area )
{
	int i = 0;
	while( block->pointers[i] != area )
		i++;

	if( i == blockSize )
		abort();

	block->map[i] = False;
}

