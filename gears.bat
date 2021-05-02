:: Add gears executable folder to user PATH

:: https://ss64.com/nt/for.html
@echo OFF

:: https://stackoverflow.com/questions/46712814
:: https://stackoverflow.com/questions/14509652
for /f "skip=2 tokens=1-2*" %%G in ('Reg Query HKCU\Environment /V PATH 2^>Nul') do set user_path=%%I

:: https://stackoverflow.com/questions/2772456
:: https://stackoverflow.com/questions/4419868
if "%user_path:gears=%"=="%user_path%" (
  echo Add %~dp0 to user PATH
  setx path %user_path%%~dp0
) else (
  echo It seems %~dp0 is already in PATH:
  echo %user_path%
)
