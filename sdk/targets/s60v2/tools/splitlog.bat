@echo off
if "%1" == "-h" GOTO Help
if "%1" == "-a" GOTO PerlHelp
if "%1" == "" GOTO Default
perl -S extractlog.pl %1 %2
GOTO End
:Default
echo -h for help
echo Attempting to extract log.txt
perl -S extractlog.pl log.txt
GOTO End
:Help
echo.
echo Flogger log extraction/splitting tool
echo Common Usage: splitlog [logfile [-v]]
echo If logfile not supplied, log.txt is used for logfile.
echo "splitlog -a" for advanced help or see the How_to_Use_flogger User Guide for more information
echo.
GOTO End
:PerlHelp
echo This help comes from the perl script...
perl -S extractlog.pl
echo.
:End
