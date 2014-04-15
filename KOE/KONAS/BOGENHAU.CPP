#include "Form.H"
#include "FieldWin.H"
#include "EntryFld.H"
// include all field types....


// Place Field- creation macros here..........


// FIELD( ID, RECT, LABEL_RECT, LABEL_TEXT )

// ENTRY_FLD( ID, MAXLEN, DEFAULT, RECT, LABEL_RECT, LABEL_TEXT )

Form *createFormDefinition()
{
        Form *form = new Form();

        Field *field = new EntryField();
        field->attachToForm( form );

        // create all fields...........

        return form;
}
