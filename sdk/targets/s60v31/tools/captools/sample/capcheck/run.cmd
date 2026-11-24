@ECHO off

perl -I \work\CapTools\src ..\..\src\CapCheck.pl -r myRom.log -e myECL.txt -s e32capability.h -R report.html
