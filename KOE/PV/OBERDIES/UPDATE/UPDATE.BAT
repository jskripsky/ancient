@ECHO OFF
CLS
ECHO ****************************************************
ECHO **  Updateprozess wurde gestartet.                **
ECHO **  Bitte warten....                              **
ECHO ****************************************************
COPY \UPDATE\PV.EXE       \PV >NUL
COPY \UPDATE\FORMDEF.RES  \PV >NUL
CD \PV
\UPDATE\DATA -E -Y
CD \UPDATE

DEL \UPDATE\PV.EXE       >NUL
DEL \UPDATE\FORMDEF.RES  >NUL
DEL \UPDATE\DATA.EXE     >NUL

CD \

CLS
ECHO ****************************************************
ECHO **  Update abgeschlossen.                         **
ECHO **  Die Diskette kann nun entfernt werden.        **
ECHO ****************************************************
ECHO **                                                **
ECHO **  PV Version 2.0a                               **
ECHO **  Formular Oberdiesbach                         **
ECHO **                                                **
ECHO ****************************************************
ECHO **                                                **
ECHO **  Bitte die Diskette zurueck an Koelliker       **
ECHO **  senden.                                       **
ECHO **                                                **
ECHO **  Danke.                                        **
ECHO **                                                **
ECHO ****************************************************
