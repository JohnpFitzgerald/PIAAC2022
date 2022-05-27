@echo off
rem ===================================================
rem install.bat
rem initial test for piaac cms
rem 
rem ===================================================
mkdir C:\CSO\
mkdir C:\CSO\Piaac\
mkdir C:\CSO\piaac\pilot2022

rem
rem ============================
rem Version Control
xcopy /y "*.txt" C:\CSO\piaac\pilot2022\
rem ============================
rem
xcopy /s /e /y "*.*" C:\CSO\piaac\pilot2022\


rem
rem --------------------------------------
rem placeholder for desktop icon
rem --------------------------------------
xcopy /y "PIAAC 2022 Interviewer.lnk" "%public%\desktop\"

