ECHO OFF
CLS
ECHO Updateprozess wurde gestartet. Bitte warten...
COPY B:\*.* \UPDATE
CD \UPDATE
UPDATE.BAT
CD \
