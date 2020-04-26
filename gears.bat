:: Add gears executable folder to user PATH
:: References:
:: https://ss64.com/nt/for.html
:: https://stackoverflow.com/questions/14509652/what-is-the-difference-between-and-in-a-cmd-file
:: https://stackoverflow.com/questions/46712814/get-current-users-path-variable-without-system-path-using-cmd

@echo OFF

for /f "skip=2 tokens=1-2*" %%G in ('Reg Query HKCU\Environment /V PATH 2^>Nul') do set user_path=%%I

set new_path=%user_path:gears=%
if "%new_path%"=="%user_path%" (
  echo Add %~dp0out\build\x64-Release to user PATH
  setx path "%user_path%;%~dp0out\build\x64-Release"
) else (
  echo It seems %~dp0out\build\x64-Release is already in PATH:
  echo %user_path%
)
pause
