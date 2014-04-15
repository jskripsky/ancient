#ifndef PHOTCELL
#define PHOTCELL


/*
   This Object doesn't adopt the TVoltageInputModule object.
*/

class TVoltageInputModule;

class TPhotoCell
{
public:
	TPhotoCell( TVoltageInputModule * );

	double GetIntensity();
protected:
	TVoltageInputModule *fModule;
};

#endif