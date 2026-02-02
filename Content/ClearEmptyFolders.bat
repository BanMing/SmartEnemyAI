@echo off
title Delete Empty Folders
color 0A

echo ========================================
echo      EMPTY FOLDER CLEANER
echo ========================================
echo.

echo Current directory: %cd%
echo.

:: Find and delete empty folders
echo Scanning for empty folders...
echo ----------------------------------------
set "count=0"

for /f "delims=" %%d in ('dir /ad /b /s 2^>nul ^| sort /r') do (
    rd "%%d" 2>nul 1>nul && (
        echo Deleted: %%d
        set /a count+=1
    )
)

if %count% EQU 0 (
    echo No empty folders found.
) else (
    echo ----------------------------------------
    echo Total deleted: %count% folder(s)
)

echo.
echo ========================================
echo Operation completed.
echo Press any key to exit...
pause >nul