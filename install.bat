@echo off
setlocal
echo ===================================================
echo          Wordle CLI Windows Installer
echo ===================================================

set "BIN_SRC="
if exist "build\Release\wordle.exe" set "BIN_SRC=build\Release\wordle.exe"
if exist "build\wordle.exe" set "BIN_SRC=build\wordle.exe"

if "%BIN_SRC%"=="" (
    echo [INFO] Binary not found. Building now...
    call build.bat
    if exist "build\Release\wordle.exe" set "BIN_SRC=build\Release\wordle.exe"
    if exist "build\wordle.exe" set "BIN_SRC=build\wordle.exe"
)

if "%BIN_SRC%"=="" (
    echo [ERROR] wordle.exe could not be found or built.
    pause
    exit /b 1
)

set "TARGET_DIR=%LOCALAPPDATA%\Wordle"
echo.
echo Installing to %TARGET_DIR%...
mkdir "%TARGET_DIR%" 2>nul
copy /Y "%BIN_SRC%" "%TARGET_DIR%\wordle.exe" >nul
if %errorlevel% neq 0 (
    echo [ERROR] Failed to copy wordle.exe to %TARGET_DIR%.
    pause
    exit /b 1
)

echo.
echo Adding %TARGET_DIR% to User PATH...
powershell -NoProfile -Command "$dir = '%TARGET_DIR%'; $path = [Environment]::GetEnvironmentVariable('Path', 'User'); if ($path -split ';' -notcontains $dir) { [Environment]::SetEnvironmentVariable('Path', ($path.TrimEnd(';') + ';' + $dir), 'User'); Write-Host 'PATH updated successfully.' } else { Write-Host 'Directory already in PATH.' }"

echo.
echo ===================================================
echo [SUCCESS] Wordle CLI installed successfully!
echo Open a NEW Command Prompt / PowerShell and type:
echo.
echo   wordle
echo.
echo ===================================================
pause
