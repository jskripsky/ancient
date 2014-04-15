#include "Compiler.H"

#include "BMPScan.H"

#define Uses_ofpstream
#define Uses_ifpstream
#include "CtrlPnl.H"
#include "NumInptL.H"


void TScanControlPanel::applyNewSettings()
{
	int data;
	pulse->getData( &data );
	pulseTime = (double)data / 1000;

	int topRange;
	int bottomRange;
	lightRangeBottom->getData( &bottomRange );
	lightRangeTop->getData( &topRange );
	bitmapScanner->SetLightRange(
		(double)bottomRange / 1000,
		(double)topRange / 1000 );

	brightness->getData( &data );
	bitmapScanner->SetBrightness( (double)data / 1000 );
	contrast->getData( &data );
	bitmapScanner->SetContrast( (double)data / 1000 );
}


const char settingsFileName[] = "Scan.Cfg";

void TScanControlPanel::writeSettingsToDisk()
{
	ofpstream os( settingsFileName, ios::out | ios::trunc | ios::binary );
	if( !os )
		return;

	int data;

	lightRangeBottom->getData( &data );
	os << data;
	lightRangeTop->getData( &data );
	os << data;

	pulse->getData( &data );
	os << data;

	brightness->getData( &data );
	os << data;
	contrast->getData( &data );
	os << data;

	xSize->getData( &data );
	os << data;
	ySize->getData( &data );
	os << data;

	steps->getData( &data );
	os << data;

	os.close();
}


void TScanControlPanel::readSettingsFromDisk()
{
	ifpstream is( settingsFileName, ios::in | ios::nocreate );
	if( !is )
		return;

	int data;

	is >> data;
	lightRangeBottom->setData( &data );
	is >> data;
	lightRangeTop->setData( &data );

	is >> data;
	pulse->setData( &data );

	is >> data;
	brightness->setData( &data );
	is >> data;
	contrast->setData( &data );

	is >> data;
	xSize->setData( &data );
	is >> data;
	ySize->setData( &data );

	is >> data;
	steps->setData( &data );

	is.close();

	applyNewSettings();
}
