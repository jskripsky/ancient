/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0					       			*/
/*		Field Include File     					*/
/*												*/
/*----------------------------------------------*/

#ifndef FIELD
#define FIELD


#define Uses_TOject
#define Uses_TStreamable
#define Uses_TPoint
#define Uses_TRect
#define Uses_TView
#define Uses_TGroup
#define Uses_TStaticText
#define Uses_TLabel
#define Uses_TScrollBar

#include "Person\Info.H"
#include "Device.H"
#include "InfoHead.H"


class TMeasurements : public TObject
{
public:
	TMeasurements()
		{
		  label.x = 0; label.y = 0;
		  control.a.x = 0; control.a.y = 0;
		  control.b.x = 0; control.b.y = 0;
		}

	TPoint label;
	TRect control;

	void reset()
		{
		label.x = 0; label.y = 0;
		control.a.x = 0; control.a.y = 0;
		control.b.x = 0; control.b.y = 0;
		}

};


const ushort moHor			= 1 << 0;
const ushort moVert			= 1 << 1;
const ushort moRight		= 1 << 2;
const ushort moDown 		= 1 << 3;
const ushort moNoSpace		= 1 << 4;


class TField : public TObject, public TStreamable
{
public:
	TField( TMeasurements&, TPoint (*)(), const char *aLabel,
			ushort aStringLength, ushort options = 0 );
	virtual ~TField() {};

	void setInfoLevel( ushort );
	void makeNecessary();
	void disablePrint();
	void enableCard( unsigned char aOffset, char aTrack, char aLength = 0 );
	void enableCardLabel( char aOffset, char aLine, char aLength = 0 );

	virtual void adjustMeasurements( TMeasurements *, TPoint controlSize,
									 const char *aLabel, ushort options );

	virtual void createControl( TMeasurements& ) = 0;
	void createLabel( const TMeasurements&, const char * );

    virtual void setup();

	virtual void insertInto( TGroup * );
	virtual void removeFrom( TGroup * );

	virtual void select();
	virtual void move( TPoint );

	void checkError( const char * );

	void attachStaticText( const TPoint, const char * );
	void registerInfo( TInfoHead& );
	virtual void setInfo( TInfo& ) = 0;

	virtual void setAccessCode( TInfo& );

	ushort dataSize( void );
	virtual void getString( char * ) = 0;
	virtual void print( TOutputDevice& ) = 0;

	virtual Boolean check();
	virtual Boolean isEmpty() = 0;

    virtual Boolean isHidden();

protected:
	TView *control;

	TLabel *label;
	TStaticText *staticText;
	TScrollBar *scrollBar;

	ushort stringLength;
	Boolean necessary;

	deviceOptions devOptions;

	ushort infoLevel;
	ushort infoIndex;

public:
	TField( StreamableInit )
		{ scrollBar = 0; }

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const = 0;
};


inline void TField::setInfoLevel( ushort level )
	{ infoLevel = level; }

inline void TField::makeNecessary()
	{ necessary = True; }

inline void TField::setup()
	{ }

inline void TField::disablePrint()
	{ devOptions.screenOnly = True; }

inline Boolean TField::isHidden()
	{ return False; }


inline ipstream& operator >> ( ipstream& is, TField& cl )
	{ return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TField*& cl )
	{ return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TField& cl )
	{ return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TField* cl )
	{ return os << (TStreamable *)cl; }


#endif