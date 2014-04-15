#include "StrCntr.H"
#include "Storage.H"

#include <String.H>
#include <StdLib.H>


const char *StringContainer::getClassName()
{
	return "StringContainer";
}


//==========================================================
//===  item storage methods (Container)  ===================
//==========================================================

void StringContainer::writeItem( void *item, StorageUnit& su )
{
	char *s = (char *)item;
	su.writeString( s );
}


void *StringContainer::readItem( StorageUnit& su )
{
	char *s = su.readString();
	return s;
}
