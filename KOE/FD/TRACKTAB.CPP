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
**  TrackTable class                                                        **
**  ----------------                                                        **
**                                                                          **
**  Defined classes:                                                        **
**    - Class TrackTable                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TRACKTAB.CPP                                               **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_TNSCollection
#include "TrackTab.H"
#include "tvField.H"
#include "TObjColl.H"


#define makeField( p )	((tvField *)p)


TrackTable::TrackTable( TObjCollection *aFields ) :
	fields( aFields )
{
	for( int i = 0; i < numTracks; i++ )
		tracks[i] = new TNSCollection( 10, 5 );

	for( i = 0; i < numCategories; i++ )
		fieldCategories[i] = new TNSCollection( 10, 5 );

	reorder();
}


TrackTable::~TrackTable()
{
	for( int i = 0; i < numTracks; i++ )
		delete tracks[i];

	for( i = 0; i < numCategories; i++ )
		delete fieldCategories[i];
}


Boolean TrackTable::reorder()
{
	for( int i = 0; i < numTracks; i++ )
		tracks[i]->removeAll();

	if( !fillInManualPosFields() )
		return False;

	for( i = 0; i < numCategories; i++ )
		fieldCategories[i]->removeAll();

	sortByCategory();

	if( fieldCategories[Display]->getCount() > 0 )
		fillTrack( 0, fieldCategories[Display] );

	if( fieldCategories[Display]->getCount() > 0 )
		return False;


	if( fieldCategories[Magnetic]->getCount() > 0 )
		for( i = 0; i < numMagneticTracks; i++ )
			fillTrack( i, fieldCategories[Magnetic] );

	if( fieldCategories[Magnetic]->getCount() > 0 )
		return False;


	if( fieldCategories[None]->getCount() > 0 )
		for( i = 0; i < numTracks; i++ )
			fillTrack( i, fieldCategories[None] );

	if( fieldCategories[None]->getCount() > 0 )
		return False;


	updateFields();
	return True;
}


void TrackTable::sortByCategory()
{
	for( int i = 0; i < numCategories; i++ )
		fieldCategories[i]->removeAll();

	for( i = 0; i < fields->getCount(); i++ )
		{
		tvField *field = makeField( fields->at( i ) );
		if( field )
			{
			if( field->isAutoPos() && !field->isDumpable() )
				fieldCategories[field->getRestriction()]->insert( field );
			}
		}
}


Boolean TrackTable::fillInManualPosFields()
{
	for( int i = 0; i < fields->getCount(); i++ )
		{
		tvField *field = makeField( fields->at( i ) );
		if( field )
			{
			if( !field->isAutoPos() && !field->isDumpable() )
				{
				if( (field->pos.x < 0 ) ||
					(field->pos.y < 0 ) ||
					(field->pos.y >= numTracks) ||
					(field->pos.x + field->getRealLength() > trackLength) )
					return False;

				TNSCollection *track = tracks[field->pos.y];
				for( int index = 0; index < track->getCount(); index++ )
					{
					tvField *tempField = makeField( track->at( index ) );
					if( field->pos.x <= tempField->pos.x )
						break;
					}
				if( index < track->getCount() )
					{
					if( (field->pos.x + field->getRealLength()) >
						makeField( track->at( index ) )->pos.x )
						return False;

					track->atInsert( index, field );
					}
				else
					track->insert( field );
				}
			}
		}

	return True;
}


void TrackTable::fillTrack( int trackNum, TNSCollection *flds )
{
	TNSCollection *track = tracks[trackNum];

	if( track->getCount() == 0 )
		{
		fillTrackArea( trackNum, trackLength, 0, flds );
		return;
		}

	tvField *before;
	tvField *after = makeField( track->at( 0 ) );

	fillTrackArea( trackNum, after->pos.x, 0, flds );

	for( int i = 1; i < track->getCount(); i++ )
		{
		before = after;
		after = makeField( track->at( i ) );

		fillTrackArea( trackNum,
					   after->pos.x - before->pos.x -
					   before->getRealLength(),
					   after, flds );
		}

	before = after;
	fillTrackArea( trackNum,
				   trackLength - before->pos.x - before->getRealLength(),
				   0, flds );
}


void TrackTable::fillTrackArea( int trackNum, int length, tvField *successor,
								TNSCollection *flds )
{
	restFields = flds;
	bestCombination = new TNSCollection( 10, 5 );
	temp = new TNSCollection( 10, 5 );
	bestSpareRoom = length;

	fill( length );

	TNSCollection *track = tracks[trackNum];
	if( !successor )
		{
		for( int c = 0; c < bestCombination->getCount(); c++ )
			{
			track->insert( bestCombination->at( c ) );
			flds->remove( bestCombination->at( c ) );
			}
		}
	else
		{
		for( int c = bestCombination->getCount() - 1; c >= 0; c-- )
			{
			track->atInsert( track->indexOf( successor ),
							 bestCombination->at( c ) );
			flds->remove( bestCombination->at( c ) );
			}
		}

	delete bestCombination;
	delete temp;
}


void TrackTable::fill( int spareRoom )
{
	if( bestSpareRoom == 0 )
		return;

	tvField *field = findShorterField( spareRoom + 1, restFields );
	if( !field  )
		{
		if( spareRoom < bestSpareRoom )
			{
			bestCombination->removeAll();
			for( int c = 0; c < temp->getCount(); c++ )
				bestCombination->insert( temp->at( c ) );
			bestSpareRoom = spareRoom;
			}
		return;
		}

	int size;

	do
	{
		size = field->getRealLength();

		restFields->remove( field );
		temp->insert( field );

		fill( spareRoom - size );

		temp->remove( field );
		restFields->insert( field );

		field = findShorterField( size, restFields );
	}
	while( field );
}


tvField *TrackTable::findShorterField( int length, TNSCollection *flds )
{
	tvField *field = 0;
	for( int i = 0; i < flds->getCount(); i++ )
		{
		tvField *tempField = makeField( flds->at( i ) );
		if( tempField->getRealLength() < length )
			{
			if( !field )
				field = tempField;
			else
				if( tempField->getRealLength() > field->getRealLength() )
					field = tempField;
			}
		}

	return field;
}


void TrackTable::updateFields()
{
	for( int i = 0; i < fields->getCount(); i++ )
		{
		tvField *field = makeField( fields->at( i ) );
		if( field && field->isDumpable() )
			{
			field->pos.x = 0;
			field->pos.y = numTracks;
			}
		}

	for( i = 0; i < numTracks; i++ )
		{
		TNSCollection *track = tracks[i];
		int actPos = 0;
		for( int f = 0; f < track->getCount(); f++ )
			{
			tvField *field = makeField( track->at( f ) );
			field->pos.y = i;

			if( !field->isAutoPos() )
				actPos = field->pos.x;
			else
				field->pos.x = actPos;
			actPos += field->getRealLength();
			}
		}
}
