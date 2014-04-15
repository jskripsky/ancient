#include "KonasApp.H"
#include "Form.H"

#include "FormDef.H"

//==========================================================
//===  constructors and destructor  ========================
//==========================================================

KonasApp::KonasApp()
{
        form = createFormDefinition();
}


KonasApp::~KonasApp()
{
        delete form;
}
