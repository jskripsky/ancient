#include "Form.H"
#include "FormWin.H"
#include "FieldWin.H"
#include "Label.H"

#include "FieldPrn.H"
#include "SFldPrn.H"
#include "EntryFld.H"
#include "SelFld.H"
// include all field types....

declSlist( Entry );

#define START_FORM_DEFINITION															\
Form *createFormDefinition()															\
{																								\
	Form *form = new Form();                                             \
	form->openWindow();																	\
																								\
	long page = -1;                                                      \
	struct Rectangle r;                                                  \
	Field *f;                                                            \
	FieldPrint *fp;																		\
																								\
	Entry *entry;																			\
	EntryField *ef;																		\
																								\
	SelectionField *sf;


#define END_FORM_DEFINITION															\
	form->getFormWindow()->setupPanel();											\
																								\
	return form;																			\
}


#define PAGE( TITLE )																	\
	page++;																					\
	form->getFormWindow()->addNewPage( TITLE ); 


#define FIELD( RX, RY, RW, RH )														\
	f->attachToForm( form );															\
	fp = f->createPrint( 0 );															\
	form->attachFieldPrint( fp );														\
	f->getWindow()->pageNumber = page;												\
	r.x = RX; r.y = RY; r.cx = RW; r.cy = RH;										\
	f->getWindow()->setRectangle( r );

#define LABEL( LRX, LRY, LRW,															\
					LABEL_TEXT )															\
	f->getWindow()->labelText = LABEL_TEXT;										\
	f->getWindow()->createLabel();													\
	r.x = LRX; r.y = LRY; r.cx = LRW; r.cy = 8;									\
	f->getWindow()->label->setRectangle( r );

#define OBLIGATORY        																\
	f->obligatory = True;

#define DISABLE_PRINT																	\
	fp->disable();

// Place Field- creation macros here..........

#define ENTRY( ID, MAXLEN, DEFAULT )												\
	f = ef = new EntryField();															\
	f->setID( ID );																		\
	ef->maxTextLength = MAXLEN;														\
	ef->defaultText = DEFAULT;															\
	ef->initializeData();


#define SELECTION( ID, DISPLAY_TYPE, DEFAULT_SELECTION, NO_SELECTION )	\
	f = sf = new SelectionField();												   \
	f->setID( ID );																		\
	sf->displayType = DISPLAY_TYPE;													\
	sf->defaultSelection = DEFAULT_SELECTION;										\
	sf->noSelection = NO_SELECTION;

#define LISTBOX		SelectionField::ListBox
#define RADIOBUTTONS SelecitonField::RadioButtons

#define ITEM( TEXT )																		\
	entry = new Entry;																	\
	entry->string = TEXT;																\
	sf->list->append( entry );															\

#define PRINT_ITEM( TEXT )																\
	entry = new Entry;																	\
	entry->string = TEXT;																\
	((SelectionFieldPrint *)fp)->list->append( entry );


#define ENTRY_HEIGHT 12

