PROJ = CONVERT
PROJFILE = CONVERT.MAK
DEBUG = 0

PWBRMAKE  = pwbrmake
NMAKEBSC1  = set
NMAKEBSC2  = nmake
CC  = cl
CFLAGS_G  =  /BATCH
CFLAGS_D  = /qc /Od /Zi
CFLAGS_R  = /Ot /Ol /Og /Op /Oe /Oi /Oa /Gs /Fa
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
LFLAGS_D  =  /CO /INC /F /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
MAPFILE_D  = NUL
MAPFILE_R  = NUL

OBJS  = CONVERT.obj JSDOSLIB.obj
SBRS  = CONVERT.sbr JSDOSLIB.sbr

all: $(PROJ).exe

.SUFFIXES: .c .sbr .obj

CONVERT.obj : CONVERT.C

CONVERT.sbr : CONVERT.C

JSDOSLIB.obj : JSDOSLIB.C

JSDOSLIB.sbr : JSDOSLIB.C


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
