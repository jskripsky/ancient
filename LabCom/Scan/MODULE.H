#ifndef MODULE
#define MODULE

#include "Types.H"

class TBoard;


/* This is the abstract base class of all module classes.
   Derived classes take care of actually interpretating and formulating
   the data stream between Board object und Module object.

   Derived classes have to specify whether they're encapsulate an input
   or an output device.

   At construction time, Module objects get adopted by and connected to
   a Board object.
*/

class TModule
{
public:
	TModule( TBoard * );

	enum EType { kInput, kOutput };
	virtual EType GetType() = 0;

protected:
	TBoard *fBoard;
};

#endif