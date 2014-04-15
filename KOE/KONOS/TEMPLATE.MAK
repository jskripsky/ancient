!ifndef ZAPPDIR
ZAPPDIR = F:\ZAPPOS2
!endif

!ifndef COMPILER
COMPILER = icc
!endif

!ifndef BCDIR
BCDIR = C:\BCOS2
!endif

!ifndef IBMTOOLKTDIR
IBMTOOLKTDIR = F:\TOOLKIT
!endif

!ifndef COMPILER
#COMPILER=icc
#COMPILER = bor10
COMPILER = boros2
!endif

!ifndef TRANSLATE
TRANSLATE=0
!endif

!ifndef PERSIST
PERSIST=0
!endif

!ifndef ZAPPDEBUG
ZAPPDEBUG=0
!endif

!ifndef DEBUG
DEBUG=0
!endif

!ifndef OPTIMIZE
OPTIMIZE = 0
!endif

!ifndef PRECOMP
PRECOMP = 1
!endif

!ifdef RES
RESRES = $(NAME).res
!endif

!ifndef OFILES
OFILES=$(NAME).obj
!endif

!ifndef LFILES
LFILES = $(OFILES)
!endif

!ifndef DDE
DDE=0
!endif

!ifndef COMMDLG
COMMDLG=0
!endif

!ifndef ZUSETEMP
ZUSETEMP = 1
!endif

!ifndef ZAPPDLL
ZAPPDLL=1
!endif

!ifndef MAKEDLL
MAKEDLL=0
!endif

!if $(MAKEDLL)
ZAPPDLL=1
!endif

!ifndef RCTOPT
RCTOPT=
!endif

## Everything above this line may be set in the makefile by the user ##

!if $(MAKEDLL)
!if "$(COMPILER)"=="icc"
ZDLLOPTS=/Ge- -DZ_CLIDLL=1
!else
ZDLLOPTS=-DZ_CLIDLL=1
!endif
!endif

!if $(MAKEDLL)
LIBMESSAGE0=DLL
!else
LIBMESSAGE0=app
!endif

!if $(PERSIST)
!if $(ZAPPDEBUG)

LIBMESSAGE1 = persistent, debugging
DB=x
DBGFLAGS=-DZ_DB=1
!else

LIBMESSAGE1 = persistent
DB=p
!endif
!else
!if $(ZAPPDEBUG)

LIBMESSAGE1 = debugging
DB=d
PFLAGS=-DZ_NP=1
DBGFLAGS=-DZ_DB=1
!else

LIBMESSAGE1 = non-persistent, non-debugging
DB=
PFLAGS=-DZ_NP=1
!endif
!endif


!if $(ZAPPDLL)
LIBMESSAGE2 = zApp 2.2 .dll
!else
LIBMESSAGE2 = zApp 2.2 .lib
!endif

!if "$(COMPILER)"=="icc"
LIBMESSAGE3 = IBM Compiler
!else
!if "$(COMPILER)"=="boros2"
LIBMESSAGE3 = Borland 1.5
!else
LIBMESSAGE3 = Borland 1.0
!endif
!endif


!if $(ZAPPDLL)
!if "$(COMPILER)"=="icc"
DLLNAME=zpo01i2$(DB)
!else

!if "$(COMPILER)"=="boros2"
DLLNAME=zpo01b1$(DB)
!else
DLLNAME=zpo01b0$(DB)
!endif
!endif
!endif

!if "$(COMPILER)"=="boros2" || "$(COMPILER)"=="bor10"
CC = bcc

!ifndef RC
RC = brcc
!endif

!if $(PRECOMP)
POPT = -H=$(ZAPPDIR)\zapp.sym
!else
POPT = 
!endif

!if $(MAKEDLL)
LFLAGS = /w-stk /Tod /aa
!else
LFLAGS = /Toe /aa
!endif

!if $(DEBUG)
RCTOPT=$(RCTOPT) -d
DFLAGS=-v -vi
LFLAGS = $(LFLAGS) /s/v
!else
DFLAGS=
!endif

!if "$(COMPILER)"=="bor10"
RTTIOPT=
!else
RTTIOPT=-RT- -x-
!endif

!if $(OPTIMIZE)
CPPFLAGS=-w-par -wamb -O2 $(COPT) $(DFLAGS) $(CDEF) $(POPT) $(RTTIOPT)
!else
CPPFLAGS=-w-par -wamb $(COPT) $(DFLAGS) $(CDEF) $(POPT) $(RTTIOPT)
!endif

!if $(MAKEDLL)
CPPFLAGS=$(CPPFLAGS) $(ZDLLOPTS)
!endif

!if $(ZAPPDLL)
ALIB0 = $(ZAPPDIR)\lib\$(DLLNAME).lib+c2i
!else
ALIB0 = $(ZAPPDIR)\lib\zobor$(DB).lib+c2
!endif

!ifndef ADDLIB
ALIB1 =
!else
ALIB1 = $(ADDLIB)+
!endif

!ifndef LIBFILES
ALIB2 =
!else
ALIB2 = $(LIBFILES)+
!endif

INC=-I$(ZAPPDIR) -I$(BCDIR)\INCLUDE

!if $(ZAPPDLL)
!if $(MAKEDLL)
LFILES = c02d.obj $(LFILES)
!else
LFILES = c02.obj $(LFILES) $(ZAPPDIR)\lib\$(DLLNAME).obj
!endif
!else
LFILES = c02.obj $(LFILES)
!endif

!if !$(MAKEDLL)
boros2: boros2exe
!else
boros2: bos2dll
!endif

!endif

!if "$(COMPILER)"=="icc"
CC= icc

!ifndef RC
RC = rc
!endif

.SUFFIXES: .obj .exe .c .asm .cpp

!if $(PRECOMP)
POPT = -Si+ -Fi+
!else
POPT = 
!endif

!if $(MAKEDLL)
LFLAGS=/NOE /NOI /NOL
!else
LFLAGS=/NOE /PM:PM /NOL
!endif

!if $(DEBUG)
RCTOPT=$(RCTOPT) -b -d
DFLAGS=-Ti+
# -Gh+ for profiler hooks
# /Tm for memory debugging
LFLAGS = $(LFLAGS) /CO /MAP:F
!else
RCTOPT=$(RCTOPT) -b
DFLAGS=
!endif

!if $(OPTIMIZE)
CPPFLAGS=-O+ -Tdp -Q+ -Gs+ -W2 -Tl2 -Gx+ $(COPT) $(DFLAGS) $(CDEF) $(POPT)
!else
CPPFLAGS=-c -Tdp -Q+ -O- -Gs+ -W2 -Tl2 -Gx+ $(COPT) $(DFLAGS) $(CDEF) $(POPT)
!endif

!if $(MAKEDLL)
CPPFLAGS=$(CPPFLAGS) $(ZDLLOPTS)
!endif

!if $(ZAPPDLL)
ALIB0 = $(ZAPPDIR)\lib\$(DLLNAME).lib
!else
ALIB0 = $(ZAPPDIR)\lib\zoibm$(DB).lib
!endif

!ifndef ADDLIB
ALIB1 =
!else
ALIB1 = $(ADDLIB)+
!endif

!ifndef LIBFILES
ALIB2 =
!else
ALIB2 = $(LIBFILES)+
!endif

INC=-I$(ZAPPDIR)

!if $(ZAPPDLL)
!if !$(MAKEDLL)
LFILES = $(LFILES) $(ZAPPDIR)\lib\$(DLLNAME).obj
!endif
!endif

!if !$(MAKEDLL)
ibm-os2: ibmos2.exe
!else
ibm-os2: ibmos2.dll
!endif

!endif

.cpp.obj:
	$(CC) -DOS2 $(CPPFLAGS) $(PFLAGS) $(DBGFLAGS) $(INC) -c $*.CPP

!ifndef LFLAGS
LFLAGS = 
!endif

message:
	@echo.
	@echo.
	@echo Building $(LIBMESSAGE0) with $(LIBMESSAGE1) $(LIBMESSAGE2) using $(LIBMESSAGE3)
	@echo.
	@echo.

!if "$(COMPILER)"=="boros2" || "$(COMPILER)"=="bor10"

$(NAME).def:
	echo LIBRARY $(NAME) INITINSTANCE TERMINSTANCE > $(NAME).def
	echo DESCRIPTION 'DLL create with zApp' >> $(NAME).def
	echo DATA        MULTIPLE READWRITE LOADONCALL NONSHARED >> $(NAME).def
	echo CODE        LOADONCALL >> $(NAME).def

!if $(ZUSETEMP)
boros2exe: message $(OFILES) $(RESRES)
	tlink $(LNKOPT)$(LFLAGS) -L$(BCDIR)\LIB @&&~
	 $(LFILES)
	 $(NAME)
	 $(NAME)
	 $(ALIB1)$(ALIB2)$(ALIB0)+
	 os2
~
!ifdef RESRES
	rc $(NAME).res
!endif

bos2dll: message $(OFILES) $(NAME).def $(RESRES)
	tlink $(LNKOPT)$(LFLAGS) -L$(BCDIR)\LIB @&&~
	 $(LFILES)
	 $(NAME)
	 $(NAME)
	 $(ALIB1)$(ALIB2)$(ALIB0)+
	 os2
	 $(NAME).def
~
!ifdef RESRES
	rc $(NAME).res $(NAME).dll
!endif
	$(BCDIR)\bin\implib $(NAME).lib $(NAME).dll

!else
boros2exe: message $(OFILES) boros2.lnk $(RESRES)
	tlink $(LNKOPT)$(LFLAGS) -L$(BCDIR)\LIB @boros2.lnk
!ifdef RESRES
	rc $(NAME).res
!endif

bos2dll: message $(OFILES) $(NAME).def bos2dll.lnk $(RESRES)
	tlink $(LNKOPT)$(LFLAGS) -L$(BCDIR)\LIB @bos2dll.lnk
!ifdef RESRES
	rc $(NAME).res $(NAME).dll
!endif
	$(BCDIR)\bin\implib $(NAME).lib $(NAME).dll
	del bos2dll.lnk

!endif
!endif





!if "$(COMPILER)"=="icc"

$(NAME).def: message $(OFILES)
	echo LIBRARY $(NAME) INITINSTANCE TERMINSTANCE > $(NAME).def
	echo DESCRIPTION 'DLL create with zApp' >> $(NAME).def
	echo DATA        MULTIPLE READWRITE LOADONCALL NONSHARED >> $(NAME).def
	echo CODE        LOADONCALL >> $(NAME).def
	echo EXPORTS >> $(NAME).def
	cppfilt -b -x -p -o -n -q -c $(OFILES) >> $(NAME).def

!if $(ZUSETEMP)
ibmos2.exe: message $(OFILES) $(RESRES)
	link386 $(LNKOPT)$(LFLAGS) @<<
	 $(LFILES)
	 $(NAME)
	 $(NAME)
	 $(ALIB1)$(ALIB2)+
	 $(ALIB0);
<<
!ifdef RESRES
	rc $(NAME).res
!endif

ibmos2.dll: message $(NAME).def $(RESRES)
	link386 $(LNKOPT)$(LFLAGS) @<<
	 $(LFILES)
	 $(NAME).dll
	 $(NAME)
	 $(ALIB1)$(ALIB2)+
	 $(ALIB0)
	 $(NAME).def;
<<
!ifdef RESRES
	rc $(NAME).res $(NAME).dll
!endif
	$(IBMTOOLKTDIR)\os2bin\implib $(NAME).lib $(NAME).def

!else
ibmos2.exe: message $(OFILES) ibmos2.lnk $(RESRES) 
	link386 $(LNKOPT)$(LFLAGS) @ibmos2.lnk
!ifdef RESRES
	rc $(NAME).res
!endif

ibmos2.dll: message $(NAME).def ibmdll.lnk $(RESRES)
	link386 $(LNKOPT)$(LFLAGS) @ibmdll.lnk
!ifdef RESRES
	rc $(NAME).res $(NAME).dll
!endif
	$(IBMTOOLKTDIR)\os2bin\implib $(NAME).lib $(NAME).def
	del ibmdll.lnk

!endif
!endif

$(NAME).res: $(NAME).rc
!if $(TRANSLATE)
    -md os2rc
    $(ZAPPDIR)\rct\rct $(RCTOPT) -oos2rc\$(NAME).rc $(NAME).rc
    cd os2rc
    $(RC) -r -I -I.. $(NAME).rc
    cd ..
    copy os2rc\*.res .
!else
	$(RC) -r -I $(ZAPPDIR) $(NAME).rc
!endif

run: 
    $(NAME)

!if $(ZUSETEMP)
clean:
	-del *.obj *.res *.exe *.map
!else
clean:
	-del *.obj *.lnk *.res *.exe *.map
!endif

boros2.lnk: $(ZAPPDIR)\samples\template.mak makefile
	echo $(LFILES) > boros2.lnk
	echo $(NAME) >>boros2.lnk
	echo $(NAME) >> boros2.lnk
    echo $(ALIB1)$(ALIB2)$(ALIB0)+>>boros2.lnk
	echo os2 >>boros2.lnk

bos2dll.lnk: $(ZAPPDIR)\samples\template.mak makefile
	echo $(LFILES) > bos2dll.lnk
	echo $(NAME).dll >> bos2dll.lnk
	echo $(NAME) >> bos2dll.lnk
	echo $(ALIB1)$(ALIB2)$(ALIB0)+ >> bos2dll.lnk
	echo os2 >> bos2dll.lnk
	echo $(NAME).def >> bos2dll.lnk

ibmos2.lnk: $(ZAPPDIR)\samples\template.mak makefile
	echo $(LFILES) > ibmos2.lnk
	echo $(NAME) >>ibmos2.lnk
	echo $(NAME) >> ibmos2.lnk
	echo $(ALIB1)$(ALIB2)+ >> ibmos2.lnk
	echo $(ALIB0); >>ibmos2.lnk

ibmdll.lnk: $(ZAPPDIR)\samples\template.mak makefile
	echo $(LFILES) > ibmdll.lnk
	echo $(NAME).dll >> ibmdll.lnk
	echo $(NAME) >> ibmdll.lnk
	echo $(ALIB1)$(ALIB2)+ >> ibmdll.lnk
	echo $(ALIB0) >> ibmdll.lnk
	echo $(NAME).def; >> ibmdll.lnk
