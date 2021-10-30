
@REM set PATH=%CD:~0,3%Windows\Microsoft.NET\Framework64\v4.0.30319
@REM set currentDirectory=%~dp0
@REM set reference=%currentDirectory%Data\EngineCS.dll
@REM   Type	   Reference to dll	   Target Location		Source
@REM csc /t:library /r:%reference%  /out:Data\CSScript.dll  Assets\Scripts\*cs


@REM Above is the updated version where it assume that user have the framework in whichever drive they
@REM put the engine folder in
@REM ----------------------------------------------------------------------------------------------------------

@REM MSBuild version
set PATH=%CD:~0,3%Windows\Microsoft.NET\Framework64\v4.0.30319
@REM outDir: C:\Users\jianw\Desktop\Digipen\GAM200\GAM200\Editor\  +  Data\
set outDir=%~dp0Data\CSScript\
msbuild.exe Assets\Scripts\Scripts.csproj /t:rebuild /p:OutputPath=%outDir% /p:Configuration=Release /flp:logfile=Data\msbuild.log /flp:verbosity=normal
