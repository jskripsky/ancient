/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Field Source File    			        */
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Field\Field.Use"

#define Uses_MsgBox
#define Uses_TScrollBar //!!!!!!!!!!!

#include <TV.H>
#include "Field\Field.H"
__link( RView );
__link( RLabel );
__link( RStaticText );
__link( RScrollBar );


#include <StdLib.H>
#include <String.H>


/*---- Constructors, Destructors ---------------*/

TField::TField( TMeasurements& m, TPoint (*controlSize)(),
				const char *aLabel, ushort aStringLength, ushort options ) :
	stringLength( aStringLength ),
	necessary( False ),
	infoLevel( 0 ),
	label( 0 ),
	staticText( 0 ),
	scrollBar( 0 )
{
	devOptions.fieldLength = aStringLength;
	devOptions.card = False;
	devOptions.cardLabel = False;
	devOptions.screenOnly = False;

	adjustMeasurements( &m, controlSize(), aLabel, options );
}


/*---- Public Methods --------------------------*/

void TField::enableCard( unsigned char aOffset, char aTrack, char aLength )
{
	devOptions.card = True;
	devOptions.track = aTrack;
	devOptions.offset = aOffset;
	if( aLength == 0 )
		devOptions.length = stringLength;
	else
		devOptions.length = aLength;
}


void TField::enableCardLabel( char aOffset, char aLine, char aLength )
{
	devOptions.cardLabel = True;
	devOptions.labelLine = aLine;
	devOptions.labelOffset = aOffset;
	if( aLength == 0 )
		devOptions.labelLength = stringLength;
	else
		devOptions.labelLength = aLength;
}


void TField::adjustMeasurements( TMeasurements *m, TPoint controlSize,
								 const char *aLabel, ushort options )
{
	if( options & moHor )
		m->label.y = 0;
	if( options & moVert )
		m->label.y = -1;

	if( m->label.y == 0 )
		m->label.x = -strlen( aLabel ) - 1;
	else
		m->label.x = 0;

	if( m->control.b.x > 0 )
		if( m->label.y == 0 )
			m->control.a.x = m->control.b.x + 2;// + abs( m->label.x ) - 2;
		else
			m->control.a.x = m->control.b.x + abs( m->label.x ) + 2;
	else
		m->control.a.x = 0;
	m->control.b.x = m->control.a.x + controlSize.x + stringLength;

	if( m->label.y == 0 )
		{
		m->control.a.x += abs( m->label.x );
		m->control.b.x += abs( m->label.x );
		}
	m->control.b.y = m->control.a.y + 1;

	if( ((m->control.b.x >= 42) || (options & moDown)) &&
		 !(options & moRight) )
		{
		int shiftDist = m->control.b.y - m->control.a.y +
						abs( m->label.y ) + 1;
		if( options & moNoSpace )
			shiftDist--;
		if( (m->label.y != 0) && (aLabel == 0) )
			shiftDist--;

		m->control.a.y += shiftDist; m->control.b.y += shiftDist;

		int sizeX = m->control.b.x - m->control.a.x;
		m->control.a.x = -m->label.x;
		m->control.b.x = m->control.a.x + sizeX;
		}

	if( m->control.b.x - m->control.a.x + abs( m->label.x ) >= 42 )
		m->control.b.x = 41;
}


void TField::createLabel( const TMeasurements& m, const char *aLabel )
{
	TRect bounds;

	bounds.a = m.control.a + m.label;
	bounds.a.x--;

	if( m.label.x >= 0 )
		bounds.b.x = m.control.b.x;
	else
		bounds.b.x = bounds.a.x + strlen( aLabel ) + 1;

	bounds.b.y = bounds.a.y + 1;
	label = new TLabel(	bounds, aLabel, control );
}


void TField::insertInto( TGroup *dialog )
{
	dialog->insert( control );
	if( label )
		dialog->insert( label );
	if( staticText )
		dialog->insert( staticText );

	if( scrollBar )
		dialog->insert( scrollBar );
}


void TField::removeFrom( TGroup *dialog )
{
	dialog->remove( control );
	if( label )
		dialog->remove( label );
	if( staticText )
		dialog->remove( staticText );
}


void TField::select()
{
	control->select();
}


void TField::checkError( const char *errorText )
{
	messageBox( errorText,
				mfError | mfOKButton );
	control->owner->select();
	control->select();
}


void TField::move( TPoint distance )
{
	control->moveTo( control->origin.x + distance.x,
					 control->origin.y + distance.y );
	if( label )
		label->moveTo( label->origin.x + distance.x,
					   label->origin.y + distance.y );
	if( staticText )
		staticText->moveTo( staticText->origin.x + distance.x,
							staticText->origin.y + distance.y );
}


void TField::attachStaticText( const TPoint pos, const char *text )
{
	staticText = new TStaticText( TRect( pos.x, pos.y, pos.x + 1 +
										 strlen( text ), pos.y + 1 ),
								  text );
}


void TField::registerInfo( TInfoHead& info )
{
	if( infoLevel > 0 )
		infoIndex = info.append( infoLevel, stringLength );
}


void TField::setAccessCode( TInfo& )
{}


ushort TField::dataSize( void )
{
	return stringLength + 1;
}


Boolean TField::check()
{
	if( necessary && isEmpty() )
		{
		checkError( "Muss-Feld ist leer!" );
		return False;
		}

	return True;
}


/*---- TStreamable Methods ---------------------*/

void TField::write( opstream& os )
{
	os << stringLength;
	os << necessary;

	os.writeBytes( &devOptions, sizeof( devOptions ) );

	os << infoLevel;
	if( infoLevel > 0 )
		os << infoIndex;

	os << *control;

	os << (ushort)label;
	if( label )
		os << *label;

	os << (ushort)staticText;
	if( staticText )
		os << *staticText;
}


void *TField::read( ipstream& is )
{
	is >> stringLength;
	is >> (int)necessary;

	is.readBytes( &devOptions, sizeof( devOptions ) );

	is >> infoLevel;
	if( infoLevel > 0 )
		is >> infoIndex;

	is >> *control;

	ushort flag;
	is >> flag;
	if( flag )
		{
		label = (TLabel *)TLabel::build();
		is >> *label;
		}
	else
		label = 0;

	is >> flag;
	if( flag )
		{
		staticText = (TStaticText *)TStaticText::build();
		is >> *staticText;
		}
	else
		staticText = 0;

	return this;
}
