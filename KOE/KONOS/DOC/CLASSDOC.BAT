@echo off
echo Drcken Sie eine beliebige Taste, um die
echo Datei "ClassDoc.Prn" an einen HP LaserJet IIP-
echo kompatiblen Drucker (LPT1) zu senden.
pause >nul
copy ClassDoc.Prn /b LPT1 /b