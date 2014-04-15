/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Person Info Source File		    		*/
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "Person\Info.Use"
#include "FormDef\FormDef.Use"

#define Uses_TStreamableClass

#include <TV.H>
#include "Person\Info.H"
#include "FormDef\FormDef.H"
#include "Database\DataBase.H"

#include "Database\Buffer.H"

#include <String.H>


int TInfo::instances = 0;
TBuffer **TInfo::buffers = 0;

static ushort itemCounter;

extern Boolean controlField;


/*---- Constructors, Destructors ---------------*/

TInfo::TInfo()
{
	init();
}


TInfo::~TInfo()
{
	for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
		buffers[i]->releaseArea( strings[i] );

///	instances--;

///	if( instances == 0 )
///		{
///		for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
///			delete buffers[i];
///
///		delete[] buffers;
///		}

	delete[] strings;


/*
	for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
		delete[] strings[i]; //!!!!!!!!!!!!!!

	delete[] strings;
*/
}


void TInfo::init()
{
///	if( instances == 0 )
	if( !buffers )
		{
		buffers = new TBuffer *[formDef->infoHead->getCount()];
		for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
			{
			stringItem *strItem = formDef->infoHead->at( i );
			buffers[i] = new TBuffer( strItem->maxLen + 1, 150 );
			}
		}

	strings = new char *[formDef->infoHead->getCount()];

	for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
		{
		strings[i] = (char *)buffers[i]->getArea();

		strcpy( strings[i], "" );
		}

	access = 0;

///	instances++;


/*
	strings = new char *[formDef->infoHead->getCount()];

	for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
		{
		stringItem *strItem = formDef->infoHead->at( i );
		strings[i] = new char[strItem->maxLen + 1];

		strcpy( strings[i], "" );
		}
*/
}

/*---- Public Methods --------------------------*/

TInfo& TInfo::operator = ( const TInfo& info )
{
	for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
		strcpy( strings[i], info.strings[i] );

	dataBase = info.dataBase;
	record = info.record;

	recordDescriptor = info.recordDescriptor;

	access = info.access;

	return *this;
}


void TInfo::getKey( char *rec, ushort maxLen )
{
	getString( rec, ilNormal, maxLen );
}


char *TInfo::getKey()
{
	return strings[0];
}


char *TInfo::at( ccIndex index )
{
	return strings[index];
}


void TInfo::getString( char *rec, ushort level, ushort maxLen )
{
	ushort len = 0;
	strcpy( rec, "" );

	level;

	for( int i = 0; i < formDef->infoHead->getCount(); i++ )
		{
		if( i > 0 )
			{
			strncat( rec, ", ", maxLen - len );
			len += 2;
			}

		if( strlen( strings[i] ) < maxLen - len )
			{
			strcat( rec, strings[i] );
			len += strlen( strings[i] );
			}
		else
			{
			strncat( rec, strings[i], maxLen - len );
			break;
			}
		}

	rec[maxLen - 1] = 0;
}


char *TInfo::firstString( ushort level )
{
	ushort l = 0;
	while( (formDef->infoHead->at( l )->level) > level )
		l++;
	return strings[l];
}


/*---- TStreamable Methods ---------------------*/

const char * const TInfo::name = "TInfo";


TInfo::TInfo( StreamableInit ) :
	TDBEntry( streamableInit )
{
	init();
}


TStreamable *TInfo::build()
{
	return new TInfo( streamableInit );
}


void TInfo::write( opstream& os )
{
	TDBEntry::write( os );

	for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
		{
		stringItem *strItem = formDef->infoHead->at( i );
		os.writeBytes( strings[i], strItem->maxLen + 1 );
		}

	if( controlField )
		os << access;
}


void *TInfo::read( ipstream& is )
{
	TDBEntry::read( is );

	for( ccIndex i = 0; i < formDef->infoHead->getCount(); i++ )
		{
		stringItem *strItem = formDef->infoHead->at( i );
		is.readBytes( strings[i], strItem->maxLen + 1 );
		}

	if( controlField )
		is >> access;

	return this;
}


TStreamableClass RInfo( TInfo::name,
						TInfo::build,
						__DELTA(TInfo)
					  );
