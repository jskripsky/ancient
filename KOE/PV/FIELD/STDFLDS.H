/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Standard Fields Include File    		*/
/*												*/
/*----------------------------------------------*/

#ifndef STDFLDS
#define STDFLDS


#include "Field\Field.H"

class TTextField : public TField
{
public:
	TTextField( TMeasurements&, const char *aLabel, ushort aStringLength,
				ushort options = 0 );

	virtual void createControl( TMeasurements& );

	virtual void getString( char * );
	virtual void print( TOutputDevice& );
	virtual void setInfo( TInfo& );

	virtual Boolean isEmpty();

private:
	static TPoint controlSize();

public:
	TTextField( StreamableInit );

	static const char *const name;
	static TStreamable *build();

private:
	virtual const char *streamableName() const
		{ return name; }
};


class TNameField : public TTextField
{
public:
	TNameField( TMeasurements& m, const char *aLabel, ushort aStringLength,
				ushort options = 0 ) :
		TTextField( m, aLabel, aStringLength, options )
		{ setInfoLevel( ilNormal ); }

	virtual Boolean check();

	void deleteEndSpaces();

public:
	TNameField( StreamableInit ) :
		TTextField( streamableInit )
		{ }

	static const char *const name;
	static TStreamable *build();

private:
	virtual const char *streamableName() const
		{ return name; }
};


/*class TForeNameField : public TNameField
{
public:
	TForeNameField( TMeasurements& m, const char *aLabel,
					ushort aStringLength, ushort options = 0 ) :
		TNameField( m, aLabel, aStringLength, options )
		{ }

	virtual void setInfo( TInfo& );

public:
	TForeNameField( StreamableInit );

	static const char *const name;
	static TStreamable *build();

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};
*/

class TRadioField : public TField
{
public:
	TRadioField( TMeasurements&, const char *aLabel, ushort aStringLength,
				 TSItem *aStrings, TSItem *aDeviceStrings,
				 ushort options = 0 );

	virtual void createControl( TMeasurements& );

	virtual void getString( char * );
	virtual void print( TOutputDevice& );
	virtual void setInfo( TInfo& );

	virtual Boolean isEmpty();

private:
	static TPoint controlSize();

	void adjustRBMeasurements( TMeasurements&, TSItem *i );
	TStringCollection *deviceStrings;
	TSItem *strings;

public:
	TRadioField( StreamableInit );

	static const char *const name;
	static TStreamable *build();

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


class TCheckField : public TField
{
//
//
};


#endif