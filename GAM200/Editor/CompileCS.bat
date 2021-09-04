@REM file is called on initialization to use the compiler for c#
@REM Vendor files (csc/msbuild) is stored at current bat file + \Vendor\Microsoft.NET\Framework64\v4.0.30319
@REM E.g: C:\Users\jianw\Desktop\Digipen\GAM200\GAM200\Vendor\Microsoft.NET\Framework64\v4.0.30319
@REM %~dp0 for current file directory  %filename% to concatenate the names
@REM set currentDirectory=%~dp0
@REM set PATH=%currentDirectory%Vendor\Microsoft.NET\Framework64\v4.0.30319
@REM %~dp0 for current file directory
@REM set reference=%currentDirectory%Data\EngineCS.dll
@REM   Type	   Reference to dll	   Target Location		Source
@REM csc /t:library /r:%reference%  /out:Data\CSScript.dll  Assets\Scripts\*cs

@REM above are the original code that uses the csc framework that will be downloaded with the engine
@REM below is the updated version where it assume that user have the framework in whichever drive they
@REM put the engine folder in

set PATH=%CD:~0,3%Windows\Microsoft.NET\Framework64\v4.0.30319
set currentDirectory=%~dp0
set reference=%currentDirectory%Data\EngineCS.dll
@REM   Type	   Reference to dll	   Target Location		Source
csc /t:library /r:%reference%  /out:Data\CSScript.dll  Assets\Scripts\*cs