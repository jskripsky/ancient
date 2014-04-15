/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Import List Window Source File 		    */
/*												*/
/*----------------------------------------------*/

#include "BC_OPT.H"

#include "ImpListW.Use"
#include "FormDef\FormDef.Use"
#include "Gadgets\Gadgets.Use"

#define Uses_TDeskTop
#define Uses_TProgram
#define Uses_ifpstream

//!!!!!!!!!!!!!!:
#define Uses_TProgram

#include "ImpListW.H"
#include "FormDef\FormDef.H"
#include "Gadgets\Config.H"

#include <DOS.H>
#include <String.H>
#include "Defs\Commands.H"


/*---- Constructors, Destructors ---------------*/

TImportListWindow::TImportListWindow( int aOptions ) :
	TListWindow( "Aufbau der Datenbank..." ),
	TWindowInit( &TImportListWindow::initFrame ),
	options( aOptions )
{
}


/*---- Public Methods --------------------------*/

//#include <StdLib.H> //!!!!!!!!!!!!!!!!!!!

void TImportListWindow::setState( ushort aState, Boolean enable )
{
	static Boolean firstTime = True;

	TDialog::setState( aState, enable );

	char prefix[11];
	prefix[10] = 0;
	char suffix;

	streampos pos;

	if( (aState & sfVisible) && enable && firstTime )
		{
		firstTime = False;

/*		randomize();
		for( int i = 0; i < 400; i++ )
			{
			TInfo *info = new TInfo();
			TPerson *person = new TPerson( *formDef->person );
			info->attachRecord( person );

			memset( ((TPerson *)info->getRecord())->getData(), '1',
					200 );

			char *data = (char *)((TPerson *)info->getRecord())->getData();
//			itoa( i, &data[10], 10 );
			data[10] = (char)((rand() % ('Z' - 'A')) + 'A' );
			data[11] = (char)((rand() % ('Z' - 'A')) + 'A' );
			data[12] = (char)((rand() % ('Z' - 'A')) + 'A' );
			data[13] = (char)((rand() % ('Z' - 'A')) + 'A' );
			data[14] = (char)((rand() % ('Z' - 'A')) + 'A' );

			// lock();

			box->insert( info );
			message( this, evCommand, cmEditPerson, 0 );

			// unlock();

			TProgram::application->idle();
			}
*/

		ifpstream *oldList;
//		ifpstream *oldList = new ifpstream( "OldPList.Dat",
//											ios::in | ios::binary );

		switch( options )
			{
			case OldFormat:
				oldList = new ifpstream( "OldPList.Dat",
										 ios::in | ios::binary );
				break;
			case Normal:
				oldList = new ifpstream( "PList___.Dat",
										 ios::in | ios::binary );
				break;
			}

		do
			{
			Boolean stop = False;

			pos = oldList->tellg();

			switch( options )
				{
				case OldFormat:
					do
						{
						oldList->readBytes( prefix, 10 );
						if( (memcmp( prefix, "Spare", 5 ) == 0) ||
							(memcmp( prefix, "SPARE", 5 ) == 0) ||
							(memcmp( prefix, "spare", 5 ) == 0) )
							oldList->seekg( 2, ios::cur );
						}
					while( (memcmp( prefix, "Spare", 5 ) == 0) ||
						   (memcmp( prefix, "SPARE", 5 ) == 0) ||
						   (memcmp( prefix, "spare", 5 ) == 0) );

					if( oldList->tellg() == pos )
						{
						stop = True;
						break;
						}

					if( prefix[1] != '[' ) // korrekt geloeschter Eintrag
						oldList->seekg( -12, ios::cur );

					break;

				case Normal:
					uchar inUse = oldList->readByte();
					uchar status = oldList->readByte();
					if( oldList->tellg() == pos )
						{
						stop = True;
						break;
						}

					while( !inUse )
						{
						oldList->seekg(
							TPerson::dataSize(),
							ios::cur );

						pos = oldList->tellg();
						inUse = oldList->readByte();
						status = oldList->readByte();
						status;

						if( oldList->tellg() == pos )
							{
							stop = True;
							break;
							}
						}
					break;
				}

			if( stop )
				break;

			TInfo *info = new TInfo();
			TPerson *person = new TPerson( *formDef->person );
			info->attachRecord( person );

			char *data = (char *)((TPerson *)info->getRecord())->getData();

			oldList->readBytes( data,
				((TPerson *)info->getRecord())->dataSize() );

			if( options == OldFormat )
				if( prefix[1] != '[' ) // korrekt geloeschter Eintrag
					{
					data[0] = '9';
					data[1] = '9';
					}

//			lock();

			box->insert( info );
			message( this, evCommand, cmEditPerson, 0 );

//			unlock();
			TProgram::application->idle(); //!!!!!!!!

			if( options == OldFormat )
				oldList->readBytes( &suffix, 1 );
			}
		while( !(oldList->eof()) );

		oldList->close();
		delete oldList;

		messageBoxRect( TRect( 15, 7, 65, 18 ),
					"Der Aufbau der Datenbank wurde abgeschlossen.\n"
					"Drcken Sie Enter (oder k), um die Index- "
					"Dateien zu speichern und das Programm zu "
					"verlassen.\n\n"
					"PV kann danach wie gewohnt benutzt werden.",
					mfInformation | mfOKButton );

		message( TProgram::application, evCommand, cmQuit, 0 );
		}

}



/*---- Private Methods -------------------------*/


void TImportListWindow::openForm( Boolean newPerson )
{
	formDialog->loadPerson( box->focusedPerson(), newPerson );
	message( (TView *)formDialog, evCommand, cmImportOK, 0 );

//	formDialog->loadPerson( box->focusedPerson(), newPerson );
//	hide();
//	TProgram::deskTop->execView( (TView *)formDialog );
//	show();

};
