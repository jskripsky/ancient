/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		ListField Source File    				*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Field\ListFld.Use"

#define Uses_TStreamableClass
#define Uses_TScrollBar
#define Uses_TListBox

#include <TV.H>
#include "Field\ListFld.H"
__link( RFieldListBox );
__link( RListBox );
__link( RScrollBar );

#include "ListFile.H"
#include "Database\Buffer.H"

#include <String.H>


struct Entry
{
	char screenText[ScreenStringLength + 1];
	char *printerText;
};


TListField::TListField( TMeasurements& m, const char *aLabel,
						ushort aStringLength, const char *aListFilename,
						int visibleLines, ushort options ) :
	TField( m, TListField::controlSize, aLabel, aStringLength, options ),
	list( new TFieldListCollection( 20, 5 ) )
{
	strcpy( listFilename, aListFilename );

	m.control.b.y = m.control.a.y + visibleLines;

	TRect sb;
	sb.a.x = m.control.b.x + 1;
	sb.b.x = sb.a.x + 1;

	sb.a.y = m.control.a.y;
	sb.b.y = m.control.b.y;

	scrollBar = new TScrollBar( sb );

	createControl( m );

	if( aLabel )
		createLabel( m, aLabel );
}


TListField::~TListField()
{
	while( list->getCount() )
		{
//		delete (xxx *)list->at( 0 ));
		list->atRemove( 0 );
		}

	delete list;
}


/*---- Public Methods --------------------------*/

void TListField::createControl( TMeasurements& m )
{
	control = new TFieldListBox( m.control, scrollBar );
}


void TListField::getString( char *rec )
{
	char screenString[ScreenStringLength + 1];
	control->getData( screenString );

	for( ccIndex i = 0; i < list->getCount(); i++ )
		if( strcmp( screenString,
					((Entry *)list->at( i ))->screenText ) == 0 )
			break;

	strcpy( rec, ((Entry *)list->at( i ))->printerText );
}


void TListField::print( TOutputDevice& outputDevice )
{
	char *string = new char[stringLength + 1];
	getString( string );

	outputDevice.print( devOptions, string );

	delete[] string;
}


void TListField::setInfo( TInfo& info )
{
	if( infoLevel > 0 )
		getString( (char *)info.at( infoIndex ) );
}


Boolean TListField::isEmpty()
{
	Boolean empty = True;
	char *string = new char[stringLength + 1];
	getString( string );

	for( int i = 0; i < strlen( string ); i++ )
		if( string[i] != ' ' )
			{
			empty = False;
			break;
			}

	delete[] string;
	return empty;
}


/*---- Private Methods -------------------------*/

TPoint TListField::controlSize()
{
	TPoint temp = { 30, 3 };
	return temp;
}


/*---- TStreamable Methods ---------------------*/

const char * const TListField::name = "TListField";


TListField::TListField( StreamableInit ) :
	TField( streamableInit ),
	list( new TFieldListCollection( 20, 5 ) )
{
	control = (TFieldListBox *)TFieldListBox::build();
}


TStreamable *TListField::build()
{
	return (TStreamable *)new TListField( streamableInit );
}


void TListField::write( opstream& os )
{
	TField::write( os );
	os.writeString( listFilename );
}


void *TListField::read( ipstream& is )
{
	TField::read( is );
	scrollBar = ((TListBox *)control)->vScrollBar;

	is.readString( listFilename, 13 );

	TBuffer *printerBuffer;
	TBuffer *entryBuffer;

	ListFile *listFile = new ListFile( listFilename, stringLength );
	while( !listFile->endOfList() && (list->getCount() < 2000) )
		{
		if( (list->getCount() % 100) == 0 )
			{
			entryBuffer = new TBuffer( sizeof( Entry ), 100 );
			printerBuffer = new TBuffer( stringLength + 1, 100 );
			}

//		char *screen = new char[ScreenStringLength + 1];
//		char *printer = new char[stringLength + 1];
		Entry *entry = (Entry *)entryBuffer->getArea();
		entry->printerText = (char *)printerBuffer->getArea();

		listFile->getNextItem( entry->screenText, entry->printerText );

		list->insert( entry );
		}

	((TListBox *)control)->newList( list );

	return this;
}


TStreamableClass RListField( TListField::name,
			 TListField::build,
			 __DELTA(TListField)
			   );


/*----------------------------------------------*/

TFieldListBox::TFieldListBox( const TRect& bounds, TScrollBar *aScrollBar ) :
	TListBox( bounds, 1, aScrollBar )
	{ }


ushort TFieldListBox::dataSize()
{
	return ScreenStringLength + 1;
}


void TFieldListBox::getData( void *rec )
{
	getText( (char *)rec, focused, ScreenStringLength );
}


void TFieldListBox::setData( void *rec )
{
	for( int i = 0; i < list()->getCount(); i++ )
		if( strcmp( (char *)rec, (char *)(list()->at( i )) ) == 0 )
			break;

	if( i == list()->getCount() )
		i = 0;

	focusItem( i );
}


/*---- TStreamable Methods ---------------------*/

const char * const TFieldListBox::name = "TFieldListBox";


TFieldListBox::TFieldListBox( StreamableInit ) :
	TListBox( streamableInit )
	{}

TStreamable *TFieldListBox::build()
{
	return (TStreamable *)new TFieldListBox( streamableInit );
}


void TFieldListBox::write( opstream& os )
{
	TListBox::write( os );
}


void *TFieldListBox::read( ipstream& is )
{
	TListBox::read( is );
	return this;
}


TStreamableClass RFieldListBox( TFieldListBox::name,
			 TFieldListBox::build,
			 __DELTA(TFieldListBox)
			   );


TFieldListCollection::TFieldListCollection(
	ccIndex aLimit, ccIndex aDelta ) :
	TCollection( aLimit, aDelta )
{
}
