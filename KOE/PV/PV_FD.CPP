/*----------------------------------------------*/
/*                                  			*/
/*		PV_FD 1.0   				    		*/
/*		PV_FD Source File    					*/
/*												*/
/*----------------------------------------------*/

#include "PV_FD.Use"
#include "FormDef\SpecDef.Use"
#include "Gadgets\Config.Use"

#define Uses_TStatusLine
#define Uses_TStatusDef
#define Uses_TStatusItem
#define Uses_TKeys
#define Uses_TDeskTop
#define Uses_TView
#define Uses_MsgBox

#include <TV.H>
#include "PV_FD.H"
#include "FormDef\SpecDef.H"
#include "Gadgets\Config.H"

#include <StdLib.H>


TFormDefinition *formDef;
TConfiguration *config;

Boolean applEnding;

void main()
{
	TPV_FD PV_FD;

	PV_FD.run();
}


TPV_FD::TPV_FD() :
	TProgInit( &TPV_FD::initStatusLine,
			   &TPV_FD::initMenuBar,
			   &TPV_FD::initDeskTop )
{
	formDef = new TSpecDefinition( TSpecDefinition::initForm,
								   TSpecDefinition::initStringList );
}


TPV_FD::~TPV_FD()
{
	destroy( (TObject *)formDef );
}


TStatusLine *TPV_FD::initStatusLine( TRect rect )
{
	rect.a.y = rect.b.y - 1;
	return new TStatusLine( rect,
		*new TStatusDef( 0, 0xFFFF ) +
		*new TStatusItem( "~Alt-X~ Programm verlassen", kbAltX, cmQuit )
		);
}
