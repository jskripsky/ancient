/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Special Fields Include File    			*/
/*												*/
/*----------------------------------------------*/

#ifndef SPECFLDS
#define SPECFLDS


#include "Field\StdFlds.H"

class TSpecCardTextField : public TTextField
{
public:
	TSpecCardTextField( TMeasurements& m, const char *aLabel,
						ushort aStringLength, ushort options = 0 ) :
		TTextField( m, aLabel, aStringLength, options )
		{ }

	virtual void print( TOutputDevice& );

public:
	TSpecCardTextField( StreamableInit );

	static const char *const name;
	static TStreamable *build();

private:
	virtual const char *streamableName() const
		{ return name; }
};


class THiddenConstField : public TField
{
public:
	THiddenConstField( TMeasurements&, char *aText, ushort aStringLength );

	virtual void adjustMeasurements( TMeasurements *, TPoint,
									 const char *, ushort ) {}

	virtual void createControl( TMeasurements& ) {}

	virtual void insertInto( TGroup * ) {}
	virtual void removeFrom( TGroup * ) {}

	virtual void select() {}
	virtual void move( TPoint ) {}

	virtual void setInfo( TInfo& ) {}

	virtual void getString( char * );
	virtual void print( TOutputDevice& );

	virtual Boolean check()
		{ return True; }
	virtual Boolean isEmpty()
		{ return False; }

	virtual Boolean isHidden()
		{ return True; }


protected:
	char text[40];

private:
	static TPoint controlSize();

public:
	THiddenConstField( StreamableInit );

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