:: scan Geant4 data directories in current folder
:: and set environment variables accordingly.
:: Place this batch file into \folder\of\Geant4\data before running it.
:: References:
:: https://ss64.com/nt/for.html
:: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/InstallationGuide/html/postinstall.html#required-environment-settings-on-windows
:: https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/setx
:: https://stackoverflow.com/questions/4419868/what-is-the-current-directory-in-a-batch-file
:: https://stackoverflow.com/questions/1501151/windows-bat-to-move-all-directories-matching-mask-from-dir-a-to-dir-b
:: https://stackoverflow.com/questions/252286/how-do-i-perform-string-operations-on-variables-in-a-for-loop/6310580#6310580
:: https://stackoverflow.com/questions/14347038/why-are-my-set-commands-resulting-in-nothing-getting-stored/14347131#14347131
@echo OFF

setx G4UI_USE_WIN32 1

setlocal enabledelayedexpansion
for /D %%i in ("*") do (
  set dir=%%i
  set dir=!dir:G4ABLA=!
  if not %%i==!dir! (
    echo setx G4ABLADATA "%~dp0%%i"
    setx G4ABLADATA "%~dp0%%i"
  )
  set dir=%%i
  set dir=!dir:G4ENSDFSTATE=!
  if not %%i==!dir! (
    echo setx G4ENSDFSTATEDATA "%~dp0%%i"
    setx G4ENSDFSTATEDATA "%~dp0%%i"
  )
  set dir=%%i
  set dir=!dir:G4INCL=!
  if not %%i==!dir! (
    echo setx G4INCLDATA "%~dp0%%i"
    setx G4INCLDATA "%~dp0%%i"
  )
  set dir=%%i
  set dir=!dir:G4EMLOW=!
  if not %%i==!dir! (
    echo setx G4LEDATA "%~dp0%%i"
    setx G4LEDATA "%~dp0%%i"
  )
  set dir=%%i
  set dir=!dir:PhotonEvaporation=!
  if not %%i==!dir! (
    echo setx G4LEVELGAMMADATA "%~dp0%%i"
    setx G4LEVELGAMMADATA "%~dp0%%i"
  )
  set dir=%%i
  set dir=!dir:G4NDL=!
  if not %%i==!dir! (
    echo setx G4NEUTRONHPDATA "%~dp0%%i"
    setx G4NEUTRONHPDATA "%~dp0%%i"
  )
  set dir=%%i
  set dir=!dir:G4PARTICLEXS=!
  if not %%i==!dir! (
    echo setx G4PARTICLEXSDATA "%~dp0%%i"
    setx G4PARTICLEXSDATA "%~dp0%%i"
  )
  set dir=%%i
  set dir=!dir:G4PII=!
  if not %%i==!dir! (
    echo setx G4PIIDATA "%~dp0%%i"
    setx G4PIIDATA "%~dp0%%i"
  )
  set dir=%%i
  set dir=!dir:RadioactiveDecay=!
  if not %%i==!dir! (
    echo setx G4RADIOACTIVEDATA "%~dp0%%i"
    setx G4RADIOACTIVEDATA "%~dp0%%i"
  )
  set dir=%%i
  set dir=!dir:RealSurface=!
  if not %%i==!dir! (
    echo setx G4REALSURFACEDATA "%~dp0%%i"
    setx G4REALSURFACEDATA "%~dp0%%i"
  )
  set dir=%%i
  set dir=!dir:G4SAIDDATA=!
  if not %%i==!dir! (
    echo setx G4SAIDXSDATA "%~dp0%%i"
    setx G4SAIDXSDATA "%~dp0%%i"
  )
)
pause
