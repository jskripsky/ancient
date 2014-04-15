/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Numeric Fields Include File    			*/
/*												*/
/*----------------------------------------------*/

#ifndef NUMFLDS
#define NUMFLDS


#include "Field\StdFlds.H"

class TNumericField : public TTextField
{
public:
	TNumericField( TMeasurements&, const char *aLabel, ushort aStringLength,
				   const char *aValidChars = 0, ushort options = 0 );
	~TNumericField();

	virtual Boolean check();

private:
	char *validChars;

public:
	TNumericField( StreamableInit );

	static const char *const name;
	static TStreamable *build();

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


#endif