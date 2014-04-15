#include "zApp.HPP"

class TestFrame : public zDialogFrame
{
public:
	TestFrame( char *title );
};


TestFrame::TestFrame( char *title ) :
	zDialogFrame( 0, new zSizer( 100, 100, 800, 400 ), zSTDFRAME, title )
{
}


//==========================================================
//===  application entry point =============================
//==========================================================

void zApp::main()
{
        TestFrame *testFrame =
                new TestFrame( "KONAS" );
        testFrame->show();
        go();
        delete testFrame;
}
