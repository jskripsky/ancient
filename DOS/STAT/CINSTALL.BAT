@ECHO OFF
IF "%1"=="" GOTO SYNTAX

MKDIR %1\STAT
ECHO Dateien werden kopiert...
COPY *.* %1\STAT
CD %1\STAT
%1

ECHO ***********************************************
ECHO *  Das Statistik-Programm wurde installiert.  *
ECHO *  "Stat" startet das Programm.               *
ECHO ***********************************************

GOTO END

:SYNTAX
ECHO **************************
ECHO *  Syntax: "Install C:"  *
ECHO **************************
ECHO ("C:" durch das Laufwerk ersetzen, auf welchem sich TMS befindet.)


:END

