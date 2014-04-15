/*****************************************************************************
**                                                                          **
**                                                                          **
**  Form Designer                                                           **
**  =============                                                           **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  tvFormField Class                                                       **
**  -----------------                                                       **
**                                                                          **
**  Defined classes:                                                        **
**    - Class tvFormField                                                   **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TVFRMFLD.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TInputLine
#define Uses_TCollection
#define Uses_TListBox
#include "tvFrmFld.H"
#include "TFFldDlg.H"


tvFormField::tvFormField( tvFolder *aFolder, const char *aTitle ) :
	tvFormObj( aFolder, aTitle ),
	field( 0 )
{
	registerShadowHandle( &field ); 
}


Boolean tvFormField::handleNotification( TView *view )
{
	TFormObjDlg *dlg = (TFormObjDlg *)tvObject::dlg;

	if( view == dlg->fieldSel )
		{
		view->getData( &field );
		return True;
		}

	return False;
}


void tvFormField::fillDlg()
{
	TFormObjDlg *dlg = (TFormObjDlg *)tvObject::dlg;

	dlg->fieldSel->setData( &field );
	handleNotification( dlg->fieldSel );
}


void tvFormField::invalidateShadow( tvObject * )
{
	field = 0;
}


TObjDlg *tvFormField::createDlg()
{
	return( new TFormFieldDlg( TRect( 33, 1, 77, 22 ), this ) );
}


tvFormField::tvFormField( StreamableInit ) :
	tvFormObj( streamableInit )
{
	registerShadowHandle( &field );
}


void tvFormField::write( opstream& os )
{
	os << (int)0x0100;

	os << field;
}


void *tvFormField::read( ipstream& is )
{
	int version;
	is >> version;

	is >> field;

	return this;
}
