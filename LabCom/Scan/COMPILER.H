/*****************************************************************************
**                                                                          **
**                                                                          **
**  DOS Scan                                                                **
**  ========                                                                **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1995 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  Borland C++ Compiler Options for Release                                **
**  ----------------------------------------                                **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: COMPILER.H                                                 **
**                                                                          **
*****************************************************************************/

#ifdef RELEASE

#define NDEBUG

#pragma option -ml		// Memory model =  large
#pragma option -b		// Enums word-sized
#pragma option -f		// Floating point, emulate
#pragma option -1-		// 8088/8086 instructions
#pragma option -v-		// Source debugging off
#pragma option -vi-		// Turns off inline expansion
#pragma option -u		// Underscores, generate
#pragma option -O1		// Optimize, smallest code

/*
#pragma option -O2		// Optimize, fastest code
*/

#endif
