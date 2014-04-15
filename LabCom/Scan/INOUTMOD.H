#ifndef INOUTMOD
#define INOUTMOD

#include "Module.H"


/*
*/

class TInputModule : public TModule
{
public:
	TInputModule( TBoard *b ) :
		TModule( b ) {};

	virtual EType GetType()
		{ return kInput; }

protected:
	int GetData();
};


class TOutputModule : public TModule
{
public:
	TOutputModule( TBoard * );

	virtual EType GetType()
		{ return kOutput; }

protected:
	void SetData( int );
	int GetData();

	int fData;
};


#endif