/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Borland C++ Release Compilation      	*/
/*		Options Include File					*/
/*												*/
/*----------------------------------------------*/

#ifdef RELEASE

#define NDEBUG

#pragma option -ml		// Memory model =  large
#pragma option -b		// Enums word-sized
#pragma option -f-		// Floating point, don't do
#pragma option -2		// 80286 protected-mode compatible instructions
#pragma option -v-		// Source debugging off
#pragma option -u		// Underscores, generate
#pragma option -O2		// Optimize, fastest code
//#pragma option -O1		// Optimize, smallest code

#endif
