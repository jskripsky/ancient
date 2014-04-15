#ifndef MCGA
#define MCGA

#include "Types.H"

typedef unsigned int	    word;
typedef unsigned long int   dword;

typedef signed long int     sdword;
typedef unsigned char	    bool;


void _far _cdecl McgaSetVideoMode( bool savescreen );
void _far _cdecl McgaRestoreVideoMode( bool savescreen );
void _far _cdecl McgaClearScreen( byte color );

void _far _cdecl McgaGetPalette( void _far *palette );
void _far _cdecl McgaSetPalette( const void _far *palette );

void _far _cdecl McgaDrawBox( byte color, word x1, word y1, word x2, word y2 );
void _far _cdecl McgaDrawXLine( byte color, word y, word x1, word x2 );
void _far _cdecl McgaDrawYLine( byte color, word x, word y1, word y2 );

#endif