/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		ControlField Source File    			*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Field\CtrlFld.Use"

#define Uses_TStreamableClass

#include <TV.H>
#include "Field\CtrlFld.H"


Boolean controlField = False;

TControlField::TControlField( TMeasurements& m, const char *aLabel,
							  ushort aStringLength, TSItem *aStrings,
							  TSItem *aDeviceStrings,
							  ushort options ) :
	TRadioField( m, aLabel, aStringLength, aStrings, aDeviceStrings,
				 options )
{
	controlField = True;
}


/*---- Public Methods --------------------------*/

void TControlField::setAccessCode( TInfo& info )
{
	ushort value;
	control->getData( &value );
	info.setAccessCode( value );
}


/*---- TStreamable Methods ---------------------*/

const char * const TControlField::name = "TControlField";


TControlField::TControlField( StreamableInit ) :
	TRadioField( streamableInit )
{
	controlField = True;
}


TStreamable *TControlField::build()
{
	return (TStreamable *)new TControlField( streamableInit );
}


TStreamableClass RControlField( TControlField::name,
			 TControlField::build,
			 __DELTA(TControlField)
			   );

