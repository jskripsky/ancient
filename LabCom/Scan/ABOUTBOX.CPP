#include "Compiler.H"


#define Uses_TProgram
#define Uses_TDeskTop
#define Uses_TStaticText
#define Uses_TButton

#include "AboutBox.H"

#include "SpeedWnd.H"


TAboutBox::TAboutBox() :
	TWindowInit( &TAboutBox::initFrame ),
	TDialog( TRect( 16, 2, 64, 22 ), "SCAN" )
{
	state &= ~sfVisible;
/*
	insert( new TStaticText( TRect( 2,  5, 33, 10 ),
		"������ͱ��������ͱ������������\n"
		"       ���  ��� ���           \n"
		"       ���  ��� ��� ����      \n"
		"       ���  ��� ���  ���      \n"
		"������ͱ��������ͱ������������" ) );

*/
	insert( new TStaticText( TRect( 5, 3, 43, 8 ),
		"�ͱ�������ͱ������ͱ�������ͱ����ͱ���\n"
		" ���      ���     ���   ��� ����� ��� \n"
		"  ������  ���     ��������� ��������� \n"
		"      ��� ���     ���   ��� ��� ����� \n"
		"ͱ��������ͱ�����ͱ����ͱ��ͱ���ͱ����\n" ) );

	insert( new TStaticText( TRect( 18, 9, 30, 12 ),
		"    SCAN\n"
		"   ������\n"
		"Version 1.0a" ) );

	insert( new TStaticText( TRect( 14, 13, 35, 14 ),
		"Copyright (c) 1995 by" ) );

	insert( new TStaticText( TRect( 17, 14, 32, 15 ),
		"Juraj Skripsky" ) );

	insert( new TButton( TRect( 19, 17, 29, 19 ), "OK", cmOK, bfDefault ) );
}


void TAboutBox::setState( ushort aState, Boolean enable )
{
	if( aState & sfVisible )
		{
		if( enable )
			{
			selectNext( False );

			TSpeedWindow sp( getBounds(), True, 0 );
			TDialog::setState( aState, enable );
			return;
			}
		else
			{
			TProgram::deskTop->lock();
			TDialog::setState( aState, enable );
			TSpeedWindow sp( getBounds(), False, 0 );
			return;
			}
		}

	TDialog::setState( aState, enable );
}