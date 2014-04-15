PROJ = DICE
PROJFILE = DICE.MAK
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
LFLAGS_D  = /CO /INC /FAR /PACKC
LFLAGS_R  =  /E /F /PACKC
MAPFILE_D  = NUL
MAPFILE_R  = NUL
CC  = cl
CFLAGS_G  = /W0 /BATCH
CFLAGS_D  = /qc /Gi$(PROJ).mdt /Zr /Zi /Od
CFLAGS_R  = /Ot /Ol /Og /Op /Oe /Oi /Oa /Gs
ASM  = masm
AFLAGS_G  = /Mx /T
AFLAGS_D  = /Zi

OBJS  = DICE.obj
SBRS  = DICE.sbr

all: $(PROJ).exe

.SUFFIXES: .c .sbr .obj

DICE.obj : DICE.C D:\C600\INCLUDE\stdlib.h D:\C600\INCLUDE\dos.h

DICE.sbr : DICE.C D:\C600\INCLUDE\stdlib.h D:\C600\INCLUDE\dos.h


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
	$(ILINK) -a -e "$(LINKER) @$(PROJ).lrf" $@
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
	CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
