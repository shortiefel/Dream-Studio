

@REM MSBuild version
set PATH=%CD:~0,3%Windows\Microsoft.NET\Framework64\v4.0.30319
set outDir=%~dp0Data\CSScript\
msbuild.exe Assets\Scripts\Scripts.csproj /t:build /p:Configuration=Release /flp:logfile=Data\msbuild.log /flp:verbosity=normal
@REM msbuild.exe Assets\Scripts\Scripts.csproj /t:build /p:OutputPath=Data\CSScript\ /p:Configuration=Release /flp:logfile=Data\msbuild.log /flp:verbosity=normal