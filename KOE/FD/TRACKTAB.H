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
**  Declared classes:                                                       **
**    - Class TrackTable                                                    **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: TRACKTAB.H                                                 **
**                                                                          **
*****************************************************************************/

#ifndef TRACKTAB
#define TRACKTAB

#include <TV.H>


#define numTracks 			 20
#define trackLength         142
#define numDisplayTracks	  1
#define numMagneticTracks	  3

#define numCategories		  3


class tvField;
class TNSCollection;
class TObjCollection;

class TrackTable
{
public:
	TrackTable( TObjCollection * );
	~TrackTable();

	virtual Boolean reorder();

protected:
	TObjCollection *fields;

	TNSCollection *tracks[numTracks];
	TNSCollection *fieldCategories[numCategories];

	void sortByCategory();

	virtual Boolean fillInManualPosFields();

	virtual void fillTrack( int trackNum, TNSCollection *flds );
	virtual void fillTrackArea( int trackNum, int length, tvField *successor,
								TNSCollection *flds );

	virtual tvField *findShorterField( int length, TNSCollection *flds );

	void updateFields();


private:
	void fill( int spareRoom );

	TNSCollection *bestCombination;
	int bestSpareRoom;

	TNSCollection *temp;
	TNSCollection *restFields;
};


#endif