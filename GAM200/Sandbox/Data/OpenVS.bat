
@REM currently not in use

@REM ----------------------------------------------------------------------------------------------------------

@REM QPROCESS "Scripts.exe">NUL
@REM IF %ERRORLEVEL% EQU 0 ECHO "Process running"

@REM devenv /edit ..\Assets\Scripts\Scripts.sln

@REM SET MyProcess=..\Assets\Scripts\Scripts.sln
@REM ECHO "%MyProcess%"
@REM tasklist | findstr /I "%MyProcess%"
@REM IF ERRORLEVEL 1 (GOTO EOF) ELSE (ECHO "not found" )
@REM tasklist /fi "IMAGENAME eq ..\Assets\Scripts\Scripts.sln" /fo csv 2>NUL | find /I "Scripts.sln">NUL
@REM if "%ERRORLEVEL%"=="0" echo Program is running



@REM ..\Assets\Scripts\Scripts.sln echo off || start ..\Assets\Scripts\Scripts.sln
@REM File.OpenProject "..\Assets\Scripts\Scripts.csproj"
@REM File.NewFile temporary /t:"General\HTML Page" /e:"Source Code (text) Editor"
@REM File.AddNewItem temporary /t:"Visual C++\C++ File (.cpp)"

:EOF