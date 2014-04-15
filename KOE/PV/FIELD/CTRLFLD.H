/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		ControlField Include File    			*/
/*												*/
/*----------------------------------------------*/

#ifndef CTRLFLD
#define CTRLFLD

#include "Field\StdFlds.H"


class TControlField : public TRadioField
{
public:
	TControlField( TMeasurements&, const char *aLabel, ushort aStringLength,
				   TSItem *aStrings, TSItem *aDeviceStrings,
				   ushort options = 0 );

	virtual void setAccessCode( TInfo& );


public:
	TControlField( StreamableInit );

	static const char *const name;
	static TStreamable *build();

private:
	virtual const char *streamableName() const
		{ return name; }
};


#endif