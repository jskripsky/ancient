PROJ = STAT
PROJFILE = STAT.MAK
DEBUG = 0

PWBRMAKE  = pwbrmake
NMAKEBSC1  = set
NMAKEBSC2  = nmake
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
BIND  = bind
RC  = rc
IMPLIB	= implib
LFLAGS_G  =  /NOI  /BATCH
LFLAGS_D  =  /CO /F /PACKC
LFLAGS_R  =  /E /F /PACKC
MAPFILE_D  = NUL
MAPFILE_R  = NUL
CC  = cl
CFLAGS_G  = /W0 /G2 /Gr /BATCH
CFLAGS_D  = /qc /Od /Zi /Gi$(PROJ).mdt
CFLAGS_R  = /Ot /Ol /Og /Op /Oe /Oi /Gs
ASM  = masm
AFLAGS_G  = /Mx /T
AFLAGS_D  = /Zi

OBJS  = STAT.obj JS-STDLI.obj JS-BOXLI.obj MAINMENU.obj KONFIG.obj\
	STATISTI.obj
SBRS  = STAT.sbr JS-STDLI.sbr JS-BOXLI.sbr MAINMENU.sbr KONFIG.sbr\
	STATISTI.sbr

all: $(PROJ).exe

.SUFFIXES: .c .obj .sbr

STAT.obj : STAT.C constant.h E:\C600\INCLUDE\malloc.h

STAT.sbr : STAT.C constant.h E:\C600\INCLUDE\malloc.h

JS-STDLI.obj : JS-STDLI.C constant.h E:\C600\INCLUDE\malloc.h

JS-STDLI.sbr : JS-STDLI.C constant.h E:\C600\INCLUDE\malloc.h

JS-BOXLI.obj : JS-BOXLI.C constant.h E:\C600\INCLUDE\malloc.h

JS-BOXLI.sbr : JS-BOXLI.C constant.h E:\C600\INCLUDE\malloc.h

MAINMENU.obj : MAINMENU.C constant.h E:\C600\INCLUDE\malloc.h

MAINMENU.sbr : MAINMENU.C constant.h E:\C600\INCLUDE\malloc.h

KONFIG.obj : KONFIG.C constant.h E:\C600\INCLUDE\malloc.h

KONFIG.sbr : KONFIG.C constant.h E:\C600\INCLUDE\malloc.h

STATISTI.obj : STATISTI.C constant.h E:\C600\INCLUDE\malloc.h

STATISTI.sbr : STATISTI.C constant.h E:\C600\INCLUDE\malloc.h


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


.c.obj :
!IF $(DEBUG)
	$(CC) /c $(CFLAGS_G) $(CFLAGS_D) /Fo$@ $<
!ELSE
	$(CC) /c $(CFLAGS_G) $(CFLAGS_R) /Fo$@ $<
!ENDIF

.c.sbr :
!IF $(DEBUG)
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_D) /FR$@ $<
!ELSE
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_R) /FR$@ $<
!ENDIF


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
