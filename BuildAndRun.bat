@echo off
setlocal EnableExtensions

REM ==========================================================
REM  SmartEnemyAI - build from command line and launch
REM  Development Editor (Win64). No Visual Studio needed.
REM  Engine: UE 5.8 (Installed Build)
REM ==========================================================

set "ENGINE_ROOT=C:\Program Files\Epic Games\UE_5.8\Engine"
set "PROJECT=%~dp0SmartEnemyAI.uproject"

set "BUILD_BAT=%ENGINE_ROOT%\Build\BatchFiles\Build.bat"
set "EDITOR_EXE=%ENGINE_ROOT%\Binaries\Win64\UnrealEditor.exe"

echo ============================================================
echo  [1/2] Building SmartEnemyAIEditor (Win64 Development)
echo ============================================================
call "%BUILD_BAT%" SmartEnemyAIEditor Win64 Development -Project="%PROJECT%" -WaitMutex -FromMsBuild
if errorlevel 1 (
    echo.
    echo [ERROR] Build failed. Editor will not launch. Check the log above.
    pause
    exit /b 1
)

echo.
echo ============================================================
echo  [2/2] Build succeeded. Launching editor...
echo ============================================================
start "" "%EDITOR_EXE%" "%PROJECT%"

exit /b 0
