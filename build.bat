@echo off
setlocal
echo ===================================================
echo   Building Wordle CLI with Automatic Dependencies
echo ===================================================

where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERROR] CMake was not found in your PATH.
    echo Please install CMake from https://cmake.org/download/ or via 'winget install Kitware.CMake'
    pause
    exit /b 1
)

echo.
echo [1/2] Configuring CMake and fetching dependencies (CPR, nlohmann-json)...
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
if %errorlevel% neq 0 (
    echo [ERROR] CMake configuration failed.
    pause
    exit /b 1
)

echo.
echo [2/2] Compiling Wordle CLI...
cmake --build build --config Release
if %errorlevel% neq 0 (
    echo [ERROR] Build failed.
    pause
    exit /b 1
)

echo.
echo ===================================================
echo [SUCCESS] Build completed!
if exist "build\Release\wordle.exe" (
    echo Binary: build\Release\wordle.exe
) else (
    echo Binary: build\wordle.exe
)
echo Run 'install.bat' to add wordle to your system PATH.
echo ===================================================
pause
