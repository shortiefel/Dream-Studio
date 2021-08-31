@REM file is called on initialization to use the compiler for c#
@REM Vendor files (csc/msbuild) is stored at current bat file + \Vendor\Microsoft.NET\Framework64\v4.0.30319
@REM E.g: C:\Users\jianw\Desktop\Digipen\GAM200\GAM200\Vendor\Microsoft.NET\Framework64\v4.0.30319
@REM %~dp0 for current file directory  %filename% to concatenate the names
set currentDirectory=%~dp0
set PATH=%currentDirectory%Vendor\Microsoft.NET\Framework64\v4.0.30319
@REM %~dp0 for current file directory
set reference=%currentDirectory%Data\EngineCS.dll
@REM   Type	   Reference to dll	   Target Location		Source
csc /t:library /r:%reference%  /out:Data\CSScript.dll  Assets\Scripts\*cs