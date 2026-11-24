@echo off

attrib -r \epoc32\wins\c\system\data\cdbv3.dat
attrib -r \epoc32\winscw\c\system\data\cdbv3.dat

if "%1"=="" goto help
if "%1"=="wins" goto wins
if "%1"=="hw" goto hw

goto help

:wins
Echo Switching commsdb for NT RAS...
copy \epoc32\wins\c\system\data\Cdbv3.dat.%1 \epoc32\wins\c\system\data\Cdbv3.dat
copy \epoc32\winscw\c\system\data\Cdbv3.dat.%1 \epoc32\winscw\c\system\data\Cdbv3.dat
goto end

:hw
Echo Switching commsdb for hardware...
copy \epoc32\data\z\system\data\DefaultCdbv3.dat \epoc32\wins\c\system\data\Cdbv3.dat
copy \epoc32\data\z\system\data\DefaultCdbv3.dat \epoc32\winscw\c\system\data\Cdbv3.dat
goto end

:help
echo.
echo "Usage: setcommsdb < wins | hw >"
echo.
echo   setcommsdb wins - sets emulator commsdb (NT RAS)
echo   setcommsdb hw   - sets hardware commsdb (emulator + phone)
echo.
goto end

:End

