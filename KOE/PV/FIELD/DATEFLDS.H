/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Date Fields Include File    			*/
/*												*/
/*----------------------------------------------*/

#ifndef DATEFLDS
#define DATEFLDS


#include "Field\StdFlds.H"

class TDateField : public TTextField
{
public:
	TDateField( TMeasurements&, const char *aLabel, ushort aStringLength,
				const char *format = 0, ushort options = 0 );

	virtual Boolean check();

protected:
	short readNumber( const char *string, ushort& pos, ushort maxLen );
	void setupFormat( const char *format );
	virtual Boolean validDate( short day, short month, short& year );
	void formatDate( short day, short month, short year );

	ushort yearLen;
	char separator;


public:
	TDateField( StreamableInit );

	static const char *const name;
	static TStreamable *build();

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


class TSystemDateField : public TDateField
{
public:
	TSystemDateField( TMeasurements& m, const char *aLabel,
					  ushort aStringLength, const char *format = 0,
					  ushort options = 0 ) :
		TDateField( m, aLabel, aStringLength, format, options )
		{ }


	virtual void setup();

public:
	TSystemDateField( StreamableInit );

	static const char *const name;
	static TStreamable *build();

private:
	virtual const char *streamableName() const
		{ return name; }
};


class TSystemTimeField : public TTextField
{
public:
	TSystemTimeField( TMeasurements&, const char *aLabel,
					  ushort options = 0 );

	virtual void setup();

public:
	TSystemTimeField( StreamableInit );

	static const char *const name;
	static TStreamable *build();

private:
	virtual const char *streamableName() const
		{ return name; }
};


class TBirthDateField : public TDateField
{
public:
	TBirthDateField( TMeasurements& m, const char *aLabel,
					 ushort aStringLength, const char *format = 0,
					 ushort options = 0 ) :
		TDateField( m, aLabel, aStringLength, format, options )
		{ }

protected:
	virtual Boolean validDate( short day, short month, short& year );


public:
	TBirthDateField( StreamableInit );

	static const char *const name;
	static TStreamable *build();

private:
	virtual const char *streamableName() const
		{ return name; }
};


#endif