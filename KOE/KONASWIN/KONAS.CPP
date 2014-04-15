#include "KonasFrm.H"

//==========================================================
//===  application entry point =============================
//==========================================================

void zApp::main()
{
        KonasFrame *konasFrame =
                new KonasFrame( "Koelliker KONAS (Demo Version)" );
        konasFrame->show();
        go();
        delete konasFrame;
}
