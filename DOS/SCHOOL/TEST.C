#include <stdlib.h>

void main( void )
{

    int _far *timer = (int _far *)0x0040006C;

    unsigned long counter;
    double x;
    double y;
    unsigned long hits = 0;
    double pi;

    srand( *timer );

    for( counter = 1; counter <= 10000; counter++ )
	{
	x = (double)(rand() % 351) / 350;
	y = (double)(rand() % 351) / 350;
	if( (x * x) + (y * y) <= 1 )
	    hits++;
	}


    pi = (double)hits * 4 / (double)counter;

    printf( "Pi-N„herung: %f", (float)pi );


}
