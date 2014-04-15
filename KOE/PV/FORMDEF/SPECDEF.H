/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Specific Form Definition Include File 	*/
/*												*/
/*----------------------------------------------*/


#include "FormDef\FormDef.H"


class TSpecDefinition : public TFormDefinition
{
public:
	TSpecDefinition( TForm *(*)(), TStrListMaker *(*)() );

	static TForm *initForm();
	static TStrListMaker *initStringList();
};
