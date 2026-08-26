@echo off
setlocal

set UE_ROOT=C:\UE_5.8
set PROJECT_PATH=G:\Unreal\SmartEnemyAI\SmartEnemyAI.uproject"
set PROJECT_NAME=SmartEnemyAI

echo ============================================
echo  Stopping running editor if any...
echo ============================================
taskkill /F /IM UnrealEditor.exe 2>nul
timeout /t 2 /nobreak >nul

echo ============================================
echo  Building %PROJECT_NAME% Editor Win64 Development
echo ============================================

call "%UE_ROOT%\Engine\Build\BatchFiles\Build.bat" %PROJECT_NAME%Editor Win64 Development -Project="%PROJECT_PATH%" -WaitMutex -NoLiveCoding

if %ERRORLEVEL% neq 0 (
    echo.
    echo [ERROR] Build failed with code %ERRORLEVEL%
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo ============================================
echo  Build succeeded! Launching editor...
echo ============================================

call "%UE_ROOT%\Engine\Binaryaries\Win64\UnrealEditor.exe" "%PROJECT_PATH%"

endlocal
