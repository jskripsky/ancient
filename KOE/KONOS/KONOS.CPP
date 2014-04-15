#include "Frame.H"

//==========================================================
//===  application entry point =============================
//==========================================================

void zApp::main()
{
        Frame *frame =
                new Frame( 0, new zSizer, zSTDFRAME, "KONOS" );
        frame->show();
        go();
        delete frame;
}
