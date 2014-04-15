/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Form Definition Include File 		    */
/*												*/
/*----------------------------------------------*/

#ifndef FORMDEF
#define FORMDEF


#include "Form.H"
#include "Person\Person.H"
#include "InfoHead.H"
#include "FormDef\StrList.H"


const ushort strSize   = 4000;
const ushort indexSize = 200;

const ushort maxStringLength = 80;

class TFormDefinition : private TObject
{
public:
	TFormDefinition();
	TFormDefinition( TForm *(*)(), TStrListMaker *(*)() );

	~TFormDefinition();

	TResourceFile *resourceFile;

	TForm *form;
	TStringList *stringList;

	TInfoHead *infoHead;
	TPerson *person;


	Boolean oldDevice;
	Boolean formatedRawPrint;
	Boolean numRawPrintCopiesDlg;

    Boolean autoSave;

	Boolean confirmNewPerson;
	Boolean disableOptions;

private:
	Boolean creation;
	TStrListMaker *strListMaker;
};


extern TFormDefinition *formDef;


#endif