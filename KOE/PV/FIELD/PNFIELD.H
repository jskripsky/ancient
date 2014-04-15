/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		PNumberField Include File    			*/
/*												*/
/*----------------------------------------------*/

#ifndef PNFIELD
#define PNFIELD

#include "Field\StdFlds.H"


class TPNumberField : public TTextField
{
public:
	TPNumberField( TMeasurements&, const char *aLabel, ushort aStringLength,
				   const char *aNumberRangeFilename, ushort options = 0 );

	virtual void setup();
	virtual Boolean check();

protected:
	char numberRangeFilename[13];

    void getNumberRange( long *start, long *end );


public:
	TPNumberField( StreamableInit );

	static const char *const name;
	static TStreamable *build();

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


class TSchwyzPNumberField : public TTextField
{
public:
	TSchwyzPNumberField( TMeasurements&, const char *aLabel,
						 ushort aStringLength,
						 const char *aNumberRangeFilename,
						 ushort options = 0 );

	virtual void setup();
	virtual Boolean check();

protected:
	char numberRangeFilename[13];

    void getNumberRange( long *start, long *end );


public:
	TSchwyzPNumberField( StreamableInit );

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