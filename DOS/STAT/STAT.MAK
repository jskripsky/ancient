PROJ = stat
PROJFILE = stat.mak
DEBUG = 0

PWBRMAKE  = pwbrmake
NMAKEBSC1  = set
NMAKEBSC2  = nmake
CC  = cl
CFLAGS_G  = /W2 /G2 /BATCH
CFLAGS_D  = /Od /Zi /Gi$(PROJ).mdt
CFLAGS_R  = /Ot /Ol /Og /Op /Oe /Oi /Oa /Gs
ASM  = masm
AFLAGS_G  = /Mx /T
AFLAGS_D  = /Zi
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
BIND  = bind
RC  = rc
IMPLIB	= implib
LFLAGS_G  =  /NOI  /BATCH
LFLAGS_D  =  /CO /NOF /NOP
LFLAGS_R  =  /E /F /PACKC
MAPFILE_D  = NUL
MAPFILE_R  = NUL

OBJS  = Main.obj StdLib.obj WinLib.obj Periode.obj Einstell.obj CheckLst.obj\
	Begruend.obj Abteil.obj ExpConv.obj Durchsch.obj Allgem.obj\
	Printer.obj Personen.obj Uebers.obj Ueberz.obj ZKonti.obj PMBegrue.obj
SBRS  = Main.sbr StdLib.sbr WinLib.sbr Periode.sbr Einstell.sbr CheckLst.sbr\
	Begruend.sbr Abteil.sbr ExpConv.sbr Durchsch.sbr Allgem.sbr\
	Printer.sbr Personen.sbr Uebers.sbr Ueberz.sbr ZKonti.sbr PMBegrue.sbr

all: $(PROJ).exe

.SUFFIXES: .c .sbr .obj

Main.obj : Main.C

Main.sbr : Main.C

StdLib.obj : StdLib.C

StdLib.sbr : StdLib.C

WinLib.obj : WinLib.C

WinLib.sbr : WinLib.C

Periode.obj : Periode.C

Periode.sbr : Periode.C

Einstell.obj : Einstell.C

Einstell.sbr : Einstell.C

CheckLst.obj : CheckLst.C

CheckLst.sbr : CheckLst.C

Begruend.obj : Begruend.C

Begruend.sbr : Begruend.C

Abteil.obj : Abteil.C

Abteil.sbr : Abteil.C

ExpConv.obj : ExpConv.C

ExpConv.sbr : ExpConv.C

Durchsch.obj : Durchsch.C

Durchsch.sbr : Durchsch.C

Allgem.obj : Allgem.C

Allgem.sbr : Allgem.C

Printer.obj : Printer.C

Printer.sbr : Printer.C

Personen.obj : Personen.C

Personen.sbr : Personen.C

Uebers.obj : Uebers.C

Uebers.sbr : Uebers.C

Ueberz.obj : Ueberz.C

Ueberz.sbr : Ueberz.C

ZKonti.obj : ZKonti.c

ZKonti.sbr : ZKonti.c

PMBegrue.obj : PMBegrue.C

PMBegrue.sbr : PMBegrue.C


$(PROJ).bsc : $(SBRS)
	$(PWBRMAKE) @<<
$(BRFLAGS) $(SBRS)
<<

$(PROJ).exe : $(OBJS)
!IF $(DEBUG)
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_D)
$(LLIBS_G: = +^
) +
$(LLIBS_D: = +^
) +
$(LIBS: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_D);
<<
!ELSE
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_R)
$(LLIBS_G: = +^
) +
$(LLIBS_R: = +^
) +
$(LIBS: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_R);
<<
!ENDIF
!IF $(DEBUG)
	$(LINKER) @$(PROJ).lrf
!ELSE
	$(LINKER) @$(PROJ).lrf
!ENDIF


.c.sbr :
!IF $(DEBUG)
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_D) /FR$@ $<
!ELSE
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_R) /FR$@ $<
!ENDIF

.c.obj :
!IF $(DEBUG)
	$(CC) /c $(CFLAGS_G) $(CFLAGS_D) /Fo$@ $<
!ELSE
	$(CC) /c $(CFLAGS_G) $(CFLAGS_R) /Fo$@ $<
!ENDIF


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CVP $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
