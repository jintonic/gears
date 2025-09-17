:: Add gears folder to user PATH

:: Disable printing commands on screen
@echo OFF

if not exist gears.exe (
  if not exist ..\gears.exe (
    echo cannot find gears.exe, please compile gears.cc first
    pause & exit /b
  )
)

:: Get curernt user PATH from the registry
:: https://stackoverflow.com/questions/46712814
:: https://stackoverflow.com/questions/14509652
for /f "skip=2 tokens=1-2*" %%G in ('Reg Query HKCU\Environment /V PATH 2^>nul') do set user_path=%%I

:: check if current folder is already in PATH
echo %user_path% | findstr /i /c:%~dp0 > nul
if %errorlevel% neq 0 (
  echo add "%~dp0" to user PATH
  setx path "%user_path%%~dp0;"
) else (
  echo %~dp0 & echo is already in your user PATH:
  echo %user_path:;=&echo.%
)

echo gears.exe can be executed anywhere now
:: keep terminal open to show result if the script is run manually
pause & exit /b
