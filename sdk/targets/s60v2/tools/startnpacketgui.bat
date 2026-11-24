echo off
rem This is start script file ONLY for installer program in Windows 2000.
rem Use network_config.bat to launch Network Configuration. 
echo on
%1 -jar npacketgui.jar -useDHCP TRUE -useAutoDNS TRUE -useProxy FALSE %2 %3 %4 %5 %6 %7 %8 %9