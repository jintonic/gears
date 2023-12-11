:: Add gears executable folder to user PATH

:: Disable printing commands on screen
@echo OFF

if not exist gears.exe (
  echo cannot find gears.exe, please compile gears.cc first
  pause & exit /b
)

:: Get curernt user PATH from the registry
:: https://stackoverflow.com/questions/46712814
:: https://stackoverflow.com/questions/14509652
for /f "skip=2 tokens=1-2*" %%G in ('Reg Query HKCU\Environment /V PATH 2^>nul') do set user_path=%%I

echo add "%~dp0" to user PATH
:: setx won't create duplicated entries,
:: the following command can be run multiple times
setx path "%user_path%%~dp0"
