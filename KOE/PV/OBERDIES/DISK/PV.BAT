ECHO OFF
CD \PV
MODE COM1:9600,E,7
PV
CLS
ECHO Sicherheitkopien werden hergestellt...
DEL BACKUP\PLIST04.*
REN BACKUP\PLIST03.* PLIST04.*
REN BACKUP\PLIST02.* PLIST03.*
REN BACKUP\PLIST01.* PLIST02.*
COPY PLIST.* BACKUP\PLIST01.* >NUL
ECHO OK.
CD \
