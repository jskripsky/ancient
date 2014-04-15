/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Form Definition Source File 		    */
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "FormDef\FormDef.Use"
#include "Gadgets\VerHead.Use"

#define Uses_MsgBox
#define Uses_fpstream

#include <TV.H>
#include "FormDef\FormDef.H"
#include "Gadgets\VerHead.H"
__link( RVersionHeader );
__link( RResourceCollection );
__link( RForm );
__link( RStringList );
__link( RPerson );

#include <StdLib.H>
#include <String.H>
#include <Dir.H>


const char *stdFormDefFileName = "FormDef.Res";
const char *stdFormDefFileExt  = ".Res";

const char *formKey         = "Form";
const char *stringListKey	= "StringList";
const char *infoKey 		= "Info";
const char *personKey		= "Person";


/*---- Constructors, Destructors ---------------*/

TFormDefinition::TFormDefinition() :
	creation( False )
{
//	char fileName[MAXFILE + MAXEXT];
//
//	if( aFileName == 0 )
//		strcpy( fileName, stdFormDefFileName );
//	else
//		strcpy( fileName, aFileName );
//
//	strcat( fileName, stdFormDefFileExt );
//	strupr( fileName );

	fpstream *formDefFile = new fpstream( "FormDef.Res",
										  ios::in | ios::nocreate );

	if( !(*formDefFile) )
		{
		messageBox( "Datei \"FORMDEF.RES\" kann nicht ge”ffnet werden!",
					mfError | mfOKButton );
		exit( EXIT_FAILURE );
		}

	TVersionHeader *verHead;
	(ipstream&)(*formDefFile) >> verHead;
	destroy( (TObject *)verHead );

	resourceFile = new TResourceFile( formDefFile );
	form		= (TForm *)resourceFile->get( formKey );
	infoHead    = (TInfoHead *)resourceFile->get( infoKey );
	person      = (TPerson *)resourceFile->get( personKey );
	stringList  = (TStringList *)resourceFile->get( stringListKey );


	char *settingsString = new char[maxStringLength + 1];

	settingsString[0] = 0;
	stringList->get( settingsString, skOldDevice );
	if( settingsString[0] )
		oldDevice = True;
	else
		oldDevice = False;

	settingsString[0] = 0;
	stringList->get( settingsString, skFormatedRawPrint );
	if( settingsString[0] )
		formatedRawPrint = True;
	else
		formatedRawPrint = False;

	settingsString[0] = 0;
	stringList->get( settingsString, skNumRPCopiesDlg );
	if( settingsString[0] )
		numRawPrintCopiesDlg = True;
	else
		numRawPrintCopiesDlg = False;

	settingsString[0] = 0;
	stringList->get( settingsString, skAutoSave );
	if( settingsString[0] )
		autoSave = True;
	else
		autoSave = False;

	settingsString[0] = 0;
	stringList->get( settingsString, skConfirmNewPerson );
	if( settingsString[0] )
		confirmNewPerson = True;
	else
		confirmNewPerson = False;

	settingsString[0] = 0;
	stringList->get( settingsString, skDisableOptions );
	if( settingsString[0] )
		disableOptions = True;
	else
		disableOptions = False;

	delete[] settingsString;
}


TFormDefinition::TFormDefinition( TForm *(*cForm)(),
								  TStrListMaker *(*cStrList)() ) :
	creation( True )
{
	form = (*cForm)();
	strListMaker = (*cStrList)();

	infoHead = new TInfoHead();
	form->registerInfo( *infoHead );
	person = new TPerson( creationInit );

	fpstream *formDefFile =
		new fpstream( stdFormDefFileName, ios::out | ios::trunc );

	if( !(*formDefFile) )
		{
		messageBox( "Datei \"FormDef.Res\" kann nicht erstellt werden!",
					mfError | mfOKButton);
		exit( EXIT_FAILURE );
		}

	TVersionHeader *verHead;
	verHead = new TVersionHeader( "Form Definition Resource", 0x0100 );
	(opstream&)(*formDefFile) << verHead;
	destroy( (TObject *)verHead );

	resourceFile = new TResourceFile( formDefFile );
	resourceFile->put( (TStreamable *)form, formKey );
	resourceFile->put( (TStreamable *)infoHead, infoKey );
	resourceFile->put( (TStreamable *)person, personKey );
	resourceFile->put( strListMaker, stringListKey );
	resourceFile->flush();
}


TFormDefinition::~TFormDefinition()
{
	destroy( (TObject *)person );
	destroy( (TObject *)form );
	destroy( resourceFile );
}
