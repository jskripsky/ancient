#ifndef TYPES
#define TYPES


#ifdef TURBO_VISION

#include <TTYPES.H>
typedef Boolean boolean;

#else

#ifndef __TTYPES_H
enum boolean { False, True };
#else
typedef Boolean boolean;
#endif

#endif


#endif